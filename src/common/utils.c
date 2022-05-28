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

size_t tetris_row_count(WINDOW* h_win) {
	return getmaxy(h_win) - 2;
}

size_t tetris_column_count(WINDOW* h_win) {
	return getmaxx(h_win) - 2;
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

bool y_within_bounds(WINDOW* h_win, int y) {
	size_t num_rows = tetris_row_count(h_win);
	return  ! (y < 0 || y > num_rows - 1);
}

bool x_within_bounds(WINDOW* h_win, int x) {
	size_t num_columns = tetris_column_count(h_win);
	return ! ( x < 0 || x > num_columns - 1);
}
