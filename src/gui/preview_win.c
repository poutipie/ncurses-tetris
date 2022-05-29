#include "preview_win.h"

void PreviewWin_init(PreviewWin** self) {
    *self = (PreviewWin*)malloc(sizeof(PreviewWin));
    _PreviewWin_create_win(*self);
}
void _PreviewWin_create_win(PreviewWin* self) {

    self->m_height = 6;
    self->m_width = 10;

	int starty = ((LINES - (TETRIS_ROWS + 2)) / 2) + self->m_height + 1;
	int startx = ((COLS - (TETRIS_COLUMNS + 2)) / 2) + TETRIS_COLUMNS + 2 + 4;

	self->m_win = newwin(self->m_height, self->m_width, starty, startx);
	box(self->m_win, 0 , 0);		/* 0, 0 gives default box outline*/
	wrefresh(self->m_win);		/* Show that box 		*/
	set_window_colors_scheme(self->m_win, COLORSCHEME_WHITE);
}
void PreviewWin_destroy(PreviewWin** self) {
    destroy_gui_win((*self)->m_win);
    free(*self);
    *self = NULL;
}

void PreviewWin_draw(PreviewWin* self, GameState* h_game_state) {

    TetrisBlock* preview_block = h_game_state->h_next_tetris_block;

    for (int i = 1; i < self->m_width - 1; ++i) {
        for (int j = 1; j < self->m_height - 1; ++j) {
            wmove(self->m_win, j, i);
            wprintw(self->m_win, " ");
        }
    }

    size_t offset_x = (self->m_width / 2) - 1;
    size_t offset_y = (self->m_height / 2) - 1;

    wattron(self->m_win, COLOR_PAIR(preview_block->m_color_scheme));
    for (int i = 0; i < preview_block->m_blk_size; ++i) {

        int draw_row = preview_block->m_blk_coords[i].y + offset_y;
        int draw_column = preview_block->m_blk_coords[i].x + offset_x;

        if (draw_row <= self->m_width || draw_column <= self->m_height) {
            wmove(self->m_win, draw_row, draw_column);
            wprintw(self->m_win, "*");
        }
    }
    wattroff(self->m_win, COLOR_PAIR(preview_block->m_color_scheme));

    wrefresh(self->m_win);
}
