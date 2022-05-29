#include "ncurses_api.h"

void ncurses_initialize_color_schemes() {
	init_pair(COLORSCHEME_BLACK, COLOR_WHITE, COLOR_BLACK);
	init_pair(COLORSCHEME_WHITE, COLOR_BLACK, COLOR_WHITE);
	init_pair(COLORSCHEME_YELLOW, COLOR_WHITE, COLOR_YELLOW);
	init_pair(COLORSCHEME_RED, COLOR_WHITE, COLOR_RED);
	init_pair(COLORSCHEME_GREEN, COLOR_WHITE, COLOR_GREEN);
	init_pair(COLORSCHEME_BLUE, COLOR_WHITE, COLOR_BLUE);
	init_pair(COLORSCHEME_CYAN, COLOR_WHITE, COLOR_CYAN);
	init_pair(COLORSCHEME_MAGENTA, COLOR_WHITE, COLOR_MAGENTA);
}

void set_window_colors_scheme(WINDOW* h_win, ColorScheme color_scheme) {
	int color = (int)color_scheme;
	wbkgd(h_win, COLOR_PAIR(color));
}

void destroy_gui_win(WINDOW* h_tetris_win) {
    wborder(h_tetris_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wrefresh(h_tetris_win);
	delwin(h_tetris_win);
}
