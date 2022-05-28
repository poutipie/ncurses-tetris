#include "tetris_block.h"
#include "stdlib.h"

void TetrisBlock_init(TETRIS_BLOCK** self, TetrisBlockType block_type, int x, int y) {

    *self = (TETRIS_BLOCK*)malloc(sizeof(TETRIS_BLOCK));

    (*self)->m_type = block_type;
    (*self)->falling = false;
    (*self)->m_rotation_cnt = 0;

    /* World Position */
    (*self)->m_world_pos_x = x;
    (*self)->m_world_pos_y = y;

    switch (block_type)
    {
        case TETRISBLOCKTYPE_SQUARE:
            TetrisBlock_init_Square(*self);
            break;
        case TETRISBLOCKTYPE_S:
            TetrisBlock_init_S(*self);
            break;
        default:
            break;
    }
}

void TetrisBlock_init_Square(TETRIS_BLOCK* self) {

    self->m_color_scheme = COLORSCHEME_YELLOW;
    self->m_rotation_type = TETRISBLOCKROTATIONTYPE_NO_ROTATION;

    self->m_blk_size = 4;
    self->m_blk_coords = (Point*)malloc(self->m_blk_size * sizeof(Point));

    /* Top left corner */
    self->m_blk_coords[0].x = 0;
    self->m_blk_coords[0].y = 0;
    
    /* Top right corner */
    self->m_blk_coords[1].x = 1;
    self->m_blk_coords[1].y = 0;

    /* Bottom left corner */
    self->m_blk_coords[2].x = 0;
    self->m_blk_coords[2].y = 1;

    /* Bottom right corner */
    self->m_blk_coords[3].x = 1;
    self->m_blk_coords[3].y = 1;
    

}

void TetrisBlock_init_S(TETRIS_BLOCK* self) {

    self->m_color_scheme = COLORSCHEME_GREEN;
    self->m_rotation_type = TETRISBLOCKROTATIONTYPE_TWOWAYS;
    self->m_blk_size = 4;
    self->m_blk_coords = (Point*)malloc(self->m_blk_size * sizeof(Point));

    /* Top left corner */
    self->m_blk_coords[0].x = 0;
    self->m_blk_coords[0].y = 0;

    /* Top right corner */
    self->m_blk_coords[1].x = 1;
    self->m_blk_coords[1].y = 0;

    /* Bottom left corner */
    self->m_blk_coords[2].x = -1;
    self->m_blk_coords[2].y = 1;

    /* Bottom right corner */
    self->m_blk_coords[3].x = 0;
    self->m_blk_coords[3].y = 1;
}

void TetrisBlock_destroy(TETRIS_BLOCK* self) {
    free(self->m_blk_coords);
    free(self);
}

void TetrisBlock_move(TETRIS_BLOCK* self, WINDOW* h_win, int x, int y) {

    bool movement_allowed = true;
    for (int i = 0; i < self->m_blk_size; ++i) {
        movement_allowed &= x_within_bounds(
            h_win, self->m_blk_coords[i].x + x + self->m_world_pos_x
        );
        movement_allowed &= y_within_bounds(
            h_win, self->m_blk_coords[i].y + y + self->m_world_pos_y
        );
    }
    if (movement_allowed == false) {
        return;
    }

    TetrisBlock_clear(self, h_win);
    self->m_world_pos_x += x;
    self->m_world_pos_y += y;
    TetrisBlock_draw(self, h_win);
}

void TetrisBlock_rotate(TETRIS_BLOCK* self, WINDOW* h_win) {
    
    /* Square block never rotates */
    if (self->m_rotation_type == TETRISBLOCKROTATIONTYPE_NO_ROTATION) {
        return;
    }

    /* L,J, and T  Rotate full circles */
    bool rotate_clockwise = false;

    /* S, Z and line rotate only +90 and -90 degrees. */
    if (self->m_rotation_type == TETRISBLOCKROTATIONTYPE_TWOWAYS &&
        self->m_rotation_cnt % 2 == 1
    ) {
        rotate_clockwise = true;
    }

    TetrisBlock_clear(self, h_win);
    _TetrisBlock_rotate_operation(self, rotate_clockwise);
    /* Revert back to original rotation if block does not stay in bounds. */
    if (TetrisBlock_out_of_bounds(self, h_win)) {
        _TetrisBlock_rotate_operation(self, !rotate_clockwise);
    }
    TetrisBlock_draw(self, h_win);

    ++self->m_rotation_cnt;
}

void _TetrisBlock_rotate_operation(TETRIS_BLOCK* self, bool clockwise) {
    
    for(int i = 0; i < self->m_blk_size; ++i) {
        int temp_x = self->m_blk_coords[i].x;
        self->m_blk_coords[i].x = self->m_blk_coords[i].y;
        self->m_blk_coords[i].y = temp_x;

        if (clockwise) {
            self->m_blk_coords[i].x *= -1;
        } 
        else {
            self->m_blk_coords[i].y *= -1;
        }
    }

    return;
}

bool TetrisBlock_is_on_the_floor(TETRIS_BLOCK* self, WINDOW* h_win) {

    int max_y = getmaxy(h_win) - 2;
    
    for(int i = 0; i < self->m_blk_size; ++i) {
        if (self->m_blk_coords[i].y + self->m_world_pos_y == max_y) {
            return true;
        }
    }

    return false;
}

bool TetrisBlock_out_of_bounds(TETRIS_BLOCK* self, WINDOW* h_win) {

    bool within_bounds = true;
    for (int i = 0; i < self->m_blk_size; ++i) {
        within_bounds &= x_within_bounds(
            h_win, self->m_blk_coords[i].x + self->m_world_pos_x
        );
        within_bounds &= y_within_bounds(
            h_win, self->m_blk_coords[i].y + self->m_world_pos_y
        );
    }
    return !within_bounds;

}

void TetrisBlock_draw(TETRIS_BLOCK* self, WINDOW* h_win) {

    wattron(h_win, COLOR_PAIR(self->m_color_scheme));
    for(int i = 0; i < self->m_blk_size; ++i) {
        wmove(
            h_win,
            self->m_world_pos_y + self->m_blk_coords[i].y,
            self->m_world_pos_x + self->m_blk_coords[i].x);
        wprintw(h_win, "*");
    }
    wattroff(h_win, COLOR_PAIR(self->m_color_scheme));
}
void TetrisBlock_clear(TETRIS_BLOCK* self, WINDOW* h_win) {
    for(int i = 0; i < self->m_blk_size; ++i) {
        wmove(
            h_win,
            self->m_world_pos_y + self->m_blk_coords[i].y,
            self->m_world_pos_x + self->m_blk_coords[i].x
        );
        wprintw(h_win, " ");
    }
}
