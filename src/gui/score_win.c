#include "score_win.h"

#include <stdlib.h>

void ScoreWin_init(ScoreWin** self) {
    *self = (ScoreWin*)malloc(sizeof(ScoreWin));
    _ScoreWin_create_win(*self);
}

void _ScoreWin_create_win(ScoreWin* self) {

    WINDOW* local_win;

	int height = 5;
	int width = 5;

	int starty = ((LINES - (TETRIS_ROWS + 2)) / 2);
	int startx = ((COLS - (TETRIS_COLUMNS + 2)) / 2) + TETRIS_COLUMNS + 2 + 4;

	self->m_win = newwin(height, width, starty, startx);
	box(self->m_win, 0 , 0);		/* 0, 0 gives default box outline*/
	wrefresh(self->m_win);		/* Show that box 		*/
	set_window_colors_scheme(self->m_win, COLORSCHEME_WHITE);

}

void ScoreWin_destroy(ScoreWin* self) {

    destroy_gui_win(self->m_win);
    free(self);
}

void ScoreWin_draw(ScoreWin* self) {
    wrefresh(self->m_win);
}