#include "preview_win.h"

void PreviewWin_init(PreviewWin** self) {
    *self = (PreviewWin*)malloc(sizeof(PreviewWin));
    _PreviewWin_create_win(*self);
}
void _PreviewWin_create_win(PreviewWin* self) {

    self->m_height = 5;
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
    wrefresh(self->m_win);
}
