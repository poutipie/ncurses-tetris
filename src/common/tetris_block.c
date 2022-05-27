#include "tetris_block.h"
#include "stdlib.h"

void TetrisBlock_init(TETRIS_BLOCK** self, TetrisBlockType block_type, int x, int y) {

    *self = (TETRIS_BLOCK*)malloc(sizeof(TETRIS_BLOCK));

    (*self)->m_type = block_type;
    (*self)->falling = false;

    switch (block_type)
    {
        case TETRISBLOCKTYPE_SQUARE:
            TetrisBlock_init_Square(*self, x, y);
            break;
        case TETRISBLOCKTYPE_S:
            TetrisBlock_init_S(*self, x, y);
            break;
        default:
            break;
    }
}

void TetrisBlock_init_Square(TETRIS_BLOCK* self, int x, int y) {

    self->m_color_scheme = COLORSCHEME_YELLOW;
    self->size = 4;
    self->x_coords = (int*)malloc(self->size * sizeof(int));
    self->y_coords = (int*)malloc(self->size * sizeof(int));
    
    /* Top left corner */
    self->x_coords[0] = x;
    self->y_coords[0] = y;
    
    /* Top right corner */
    self->x_coords[1] = x+1;
    self->y_coords[1] = y;

    /* Bottom left corner */
    self->x_coords[2] = x;
    self->y_coords[2] = y + 1;

    /* Bottom right corner */
    self->x_coords[3] = x + 1;
    self->y_coords[3] = y + 1;
    

}

void TetrisBlock_init_S(TETRIS_BLOCK* self, int x, int y) {
    self->m_color_scheme = COLORSCHEME_GREEN;
    self->size = 4;
    self->x_coords = (int*)malloc(self->size * sizeof(int));
    self->y_coords = (int*)malloc(self->size * sizeof(int));

    /* Top left corner */
    self->x_coords[0] = x + 1;
    self->y_coords[0] = y;

    /* Top right corner */
    self->x_coords[1] = x + 2;
    self->y_coords[1] = y;

    /* Bottom left corner */
    self->x_coords[2] = x;
    self->y_coords[2] = y + 1;

    /* Bottom right corner */
    self->x_coords[3] = x + 1;
    self->y_coords[3] = y + 1;
}

void TetrisBlock_destroy(TETRIS_BLOCK* self) {
    free(self->x_coords);
    free(self->y_coords);
    free(self);
}

void TetrisBlock_move(TETRIS_BLOCK* self, WINDOW* h_win, int x, int y) {

    bool movement_allowed = true;
    for (int i = 0; i < self->size; ++i) {
        movement_allowed &= x_within_bounds(h_win, self->x_coords[i] + x);
        movement_allowed &= y_within_bounds(h_win, self->y_coords[i] + y);
    }
    if (movement_allowed == false) {
        return;
    }

    TetrisBlock_clear(self, h_win);
    for (int i = 0; i < self->size; ++i) {
        self->x_coords[i] += x;
        self->y_coords[i] += y;
    }
    TetrisBlock_draw(self, h_win);
}

void TetrisBlock_draw(TETRIS_BLOCK* self, WINDOW* h_win) {

    wattron(h_win, COLOR_PAIR(self->m_color_scheme));
    for(int i = 0; i < self->size; ++i) {
        wmove(h_win, self->y_coords[i], self->x_coords[i]);
        wprintw(h_win, "*");
    }
    wattroff(h_win, COLOR_PAIR(self->m_color_scheme));
}
void TetrisBlock_clear(TETRIS_BLOCK* self, WINDOW* h_win) {
    for(int i = 0; i < self->size; ++i) {
        wmove(h_win, self->y_coords[i], self->x_coords[i]);
        wprintw(h_win, " ");
    }
}
