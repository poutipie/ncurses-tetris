#include "score_win.h"

void ScoreWin_init(ScoreWin** self) {
    *self = (ScoreWin*)malloc(sizeof(ScoreWin));
    _ScoreWin_create_win(*self);
}

void _ScoreWin_create_win(ScoreWin* self) {

	int height = 5;
	int width = 10;

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

void ScoreWin_draw(ScoreWin* self, GameState* h_game_state) {

    box(self->m_win, 0 , 0);
    wmove(self->m_win, 1, 1);
    wprintw(self->m_win, "Score:");
    wmove(self->m_win, 2, 1);
    wprintw(self->m_win, "     ");
    wmove(self->m_win, 2, 1);
    wprintw(self->m_win, "%d", h_game_state->score);
    wrefresh(self->m_win);
}