#ifndef UTILS_H
#define UTILS_H

#include <ncurses.h>
#include <stdbool.h>

typedef uint32_t COLOR_T;

typedef struct sPoint {
    int x;
    int y;
} Point;

typedef enum ColorScheme {
	COLORSCHEME_BLACK  = 1,
	COLORSCHEME_WHITE  = 2,
    COLORSCHEME_YELLOW = 3,
    COLORSCHEME_GREEN = 4
} ColorScheme;


void ncurses_initialize_color_schemes();
void set_window_colors_scheme(WINDOW* h_win, ColorScheme color_scheme) ;


bool y_within_bounds(WINDOW* h_win, int y);
bool x_within_bounds(WINDOW* h_win, int x);
void set_default_colors();

#endif /* UTILS_H */
