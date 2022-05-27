#ifndef UTILS_H
#define UTILS_H

#include <ncurses.h>

bool y_within_bounds(WINDOW* h_win, int y) {
	int max_y = getmaxy(h_win) - 2;
	return  ! (y < 1 || y > max_y);
}

bool x_within_bounds(WINDOW* h_win, int x) {
	int max_x = getmaxx(h_win) - 2;
	return ! ( x < 1 || x > max_x);
}

#endif /* UTILS_H */
