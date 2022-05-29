#ifndef UTILS_H
#define UTILS_H

#include <ncurses.h>
#include <stdbool.h>

#define TETRIS_ROWS       16
#define TETRIS_COLUMNS    12

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

WINDOW* create_tetris_win();
WINDOW* create_score_win();
void destroy_gui_win(WINDOW* h_tetris_win);

void ncurses_initialize_color_schemes();
void set_window_colors_scheme(WINDOW* h_win, ColorScheme color_scheme) ;

size_t tetris_row_count(WINDOW* h_win);
size_t tetris_column_count(WINDOW* h_win);

void draw_tetris_square(WINDOW* h_win, Point position, ColorScheme color);
void clear_tetris_square(WINDOW* h_win, Point position);

bool y_within_bounds(WINDOW* h_win, int y);
bool x_within_bounds(WINDOW* h_win, int x);
void set_default_colors();

#endif /* UTILS_H */
