#include "utils.h"

void ncurses_initialize_color_schemes() {
	init_pair(COLORSCHEME_BLACK, COLOR_WHITE, COLOR_BLACK);
	init_pair(COLORSCHEME_WHITE, COLOR_BLACK, COLOR_WHITE);
	init_pair(COLORSCHEME_YELLOW, COLOR_WHITE, COLOR_YELLOW);
	init_pair(COLORSCHEME_GREEN, COLOR_WHITE, COLOR_GREEN);
}

void set_window_colors_scheme(WINDOW* h_win, ColorScheme color_scheme) {
	int color = (int)color_scheme;
	wbkgd(h_win, COLOR_PAIR(color));
}

void draw_tetris_square(WINDOW* h_win, Point position, ColorScheme color) {
	wattron(h_win, COLOR_PAIR(color));
    wmove(h_win, position.y + 1, position.x + 1);
    wprintw(h_win, "*");
    wattroff(h_win, COLOR_PAIR(color));
}
void clear_tetris_square(WINDOW* h_win, Point position) {
	wmove(h_win, position.y + 1, position.x + 1);
    wprintw(h_win, " ");
}

WINDOW* create_score_win() {

	WINDOW* local_win;

	int height = 5;
	int width = 5;

	int starty = ((LINES - (TETRIS_ROWS + 2)) / 2);
	int startx = ((COLS - (TETRIS_COLUMNS + 2)) / 2) + TETRIS_COLUMNS + 2 + 4;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default box outline*/
	wrefresh(local_win);		/* Show that box 		*/
	set_window_colors_scheme(local_win, COLORSCHEME_WHITE);

	return local_win;
}

void destroy_gui_win(WINDOW* h_tetris_win) {
    wborder(h_tetris_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wrefresh(h_tetris_win);
	delwin(h_tetris_win);
}
