#include "title_win.h"

#include <stdlib.h>

void TitleWin_init(TitleWin** self) {
    *self = (TitleWin*)malloc(sizeof(TitleWin));
    _TitleWin_create_win(*self);
}

void _TitleWin_create_win(TitleWin* self) {

    self->m_height = 3;
    self->m_width = (TETRIS_COLUMNS + 2) * 3;

	int starty = ((LINES - (TETRIS_ROWS + 2)) / 2) - self->m_height -1;
	int startx = (COLS - self->m_width) / 2;

	self->m_win = newwin(self->m_height, self->m_width, starty, startx);
	box(self->m_win, 0 , 0);		/* 0, 0 gives default box outline*/
	wrefresh(self->m_win);		/* Show that box 		*/
	set_window_colors_scheme(self->m_win, COLORSCHEME_BLACK);

}

void TitleWin_destroy(TitleWin* self) {

    destroy_gui_win(self->m_win);
    free(self);
}

void TitleWin_draw(TitleWin* self, GameState* h_game_state) {

    char title[] = "NCurses Tetris";

    box(self->m_win, 0 , 0);
    wmove(self->m_win, 1, 1);
    wprintw(self->m_win, "%s", title);
    wrefresh(self->m_win);
}