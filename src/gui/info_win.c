#include "info_win.h"
#include <stdlib.h>

void InfoWin_init(InfoWin** self) {
    *self = (InfoWin*)malloc(sizeof(InfoWin));
    _InfoWin_create_win(*self);
}
void _InfoWin_create_win(InfoWin* self) {

    self->m_height = 10;
    self->m_width = (TETRIS_COLUMNS + 2) * 3;

	int starty = (LINES - TETRIS_ROWS - 2) / 2 + TETRIS_ROWS + 2;
	int startx = (COLS - self->m_width) / 2;

	self->m_win = newwin(self->m_height, self->m_width, starty, startx);
	box(self->m_win, 0 , 0);		/* 0, 0 gives default box outline*/
	wrefresh(self->m_win);		/* Show that box 		*/
	set_window_colors_scheme(self->m_win, COLORSCHEME_BLACK);
}
void InfoWin_destroy(InfoWin* self) {
    destroy_gui_win(self->m_win);
    free(self);
}

void InfoWin_draw(InfoWin* self, GameState* h_game_state) {

    wmove(self->m_win, 1, 1);
    wprintw(self->m_win,"HOW TO PLAY:");
    wmove(self->m_win, 3, 1);
    wprintw(self->m_win, "Use arrow keys to move");
    wmove(self->m_win, 4, 1);
    wprintw(self->m_win, "Press 'R' key to reset");
    wmove(self->m_win, 5, 1);
    wprintw(self->m_win, "Press 'Q' key to exit game");
    wrefresh(self->m_win);
}
