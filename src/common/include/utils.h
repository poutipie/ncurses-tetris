#ifndef UTILS_H
#define UTILS_H

#include <ncurses.h>
#include <stdbool.h>

#define TETRIS_ROWS       16
#define TETRIS_COLUMNS    12

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

WINDOW* create_score_win();
void destroy_gui_win(WINDOW* h_tetris_win);

void ncurses_initialize_color_schemes();
void set_window_colors_scheme(WINDOW* h_win, ColorScheme color_scheme) ;

#endif /* UTILS_H */
