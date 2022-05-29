
#include "tetris_win.h"
#include <stdlib.h>

void TetrisWin_init(TetrisWin** self) {

    *self = (TetrisWin*)malloc(sizeof(TetrisWin));
    _TetrisWin_create_win(*self);
}

void TetrisWin_destroy(TetrisWin* self) {

    destroy_gui_win(self->m_win);
    free(self);
}

void TetrisWin_draw(TetrisWin* self, GameState* h_game_state) {

    TetrisGrid* h_grid = h_game_state->h_tetris_grid;
    TetrisBlock* h_blk = h_game_state->h_tetris_block;

    /* Draw the grid */
    for(int i = 0; i < h_grid->total_rows; ++i) {
        for (int j = 0; j < h_grid->total_columns; ++j) {

            Point draw_point = {
                .x = j,
                .y = i
            };

            if (h_grid->filled_squares[i][j]) {
                draw_tetris_square(self->m_win, draw_point, 
                    h_grid->filled_square_colors[i][j]
                );
            }
            else {
                clear_tetris_square(self->m_win, draw_point);
            }
        }
    }

    /* Draw the block */
    for(int i = 0; i < h_blk->m_blk_size; ++i) {

        Point draw_point = {
            .x = h_blk->m_blk_coords[i].x + h_blk->m_world_pos_x,
            .y = h_blk->m_blk_coords[i].y + h_blk->m_world_pos_y
        };

        draw_tetris_square(self->m_win, draw_point, h_blk->m_color_scheme);

    }

    wrefresh(self->m_win);
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