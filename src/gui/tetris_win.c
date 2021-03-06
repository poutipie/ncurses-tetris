
#include "tetris_win.h"

void TetrisWin_init(TetrisWin** self) {

    *self = (TetrisWin*)malloc(sizeof(TetrisWin));
    _TetrisWin_create_win(*self);
}

void _TetrisWin_create_win(TetrisWin* self) {

    int height = TETRIS_ROWS + 2;
	int width = TETRIS_COLUMNS + 2;
    /* Calculating for a center placement of the window*/
	int starty = (LINES - height) / 2;
	int startx = (COLS - width) / 2;

	self->m_win = newwin(height, width, starty, startx);
	box(self->m_win, 0 , 0);		/* 0, 0 gives default box outline*/
	wrefresh(self->m_win);		  /* Show that box 		*/
	set_window_colors_scheme(self->m_win, COLORSCHEME_WHITE);
}

void TetrisWin_destroy(TetrisWin** self) {

    destroy_gui_win((*self)->m_win);
    free(*self);
    *self = NULL;
}

void TetrisWin_draw(TetrisWin* self, GameState* h_game_state) {

    TetrisGrid* h_grid = h_game_state->h_tetris_grid;
    TetrisBlock* h_blk = h_game_state->h_tetris_block;

    box(self->m_win, 0 , 0);		/* Draw outline */

    /* Draw the grid */
    for(int i = 0; i < h_grid->total_rows; ++i) {
        for (int j = 0; j < h_grid->total_columns; ++j) {

            Point draw_point = {
                .x = j,
                .y = i
            };

            if (h_grid->filled_squares[i][j]) {
                _TetrisWin_draw_tetris_square(self, draw_point, 
                    h_grid->filled_square_colors[i][j]
                );
            }
            else {
                _TetrisWin_clear_tetris_square(self, draw_point);
            }
        }
    }

    if (h_game_state->game_over) {
        TetrisWin_draw_game_over(self);
        wrefresh(self->m_win);
        return;
    }

    /* Draw the block */
    for(int i = 0; i < h_blk->m_blk_size; ++i) {

        Point draw_point = {
            .x = h_blk->m_blk_coords[i].x + h_blk->m_world_pos_x,
            .y = h_blk->m_blk_coords[i].y + h_blk->m_world_pos_y
        };

        _TetrisWin_draw_tetris_square(self, draw_point, h_blk->m_color_scheme);

    }

    wrefresh(self->m_win);
}

void TetrisWin_draw_game_over(TetrisWin* self) {

    size_t text_len = 9;

    wmove(self->m_win, (TETRIS_ROWS + 2) / 2, (TETRIS_COLUMNS + 2- text_len) / 2);
    wprintw(self->m_win, "GAME OVER");
}

void _TetrisWin_draw_tetris_square(TetrisWin* self, Point position, ColorScheme color) {
    wattron(self->m_win, COLOR_PAIR(color));
    wmove(self->m_win, position.y + 1, position.x + 1);
    wprintw(self->m_win, "*");
    wattroff(self->m_win, COLOR_PAIR(color));
}
void _TetrisWin_clear_tetris_square(TetrisWin* self, Point position) {
    wmove(self->m_win, position.y + 1, position.x + 1);
    wprintw(self->m_win, " ");
}
