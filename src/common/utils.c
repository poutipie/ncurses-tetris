#include "utils.h"

void ncurses_initialize_color_schemes() {
	init_pair(COLORSCHEME_BLACK, COLOR_WHITE, COLOR_BLACK);
	init_pair(COLORSCHEME_WHITE, COLOR_BLACK, COLOR_WHITE);
	init_pair(COLORSCHEME_YELLOW, COLOR_WHITE, COLOR_YELLOW);
	init_pair(COLORSCHEME_GREEN, COLOR_WHITE, COLOR_GREEN);
}

bool y_within_bounds(WINDOW* h_win, int y) {
	int max_y = getmaxy(h_win) - 2;
	return  ! (y < 1 || y > max_y);
}

bool x_within_bounds(WINDOW* h_win, int x) {
	int max_x = getmaxx(h_win) - 2;
	return ! ( x < 1 || x > max_x);
}

void set_window_colors_scheme(WINDOW* h_win, ColorScheme color_scheme) {
	int color = (int)color_scheme;
	wbkgd(h_win, COLOR_PAIR(color));
}
