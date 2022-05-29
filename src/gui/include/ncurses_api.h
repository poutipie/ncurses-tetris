#ifndef NCURSES_API_H
#define NCURSES_API_H

#include "types.h"
#include <ncurses.h>


void destroy_gui_win(WINDOW* h_tetris_win);
void ncurses_initialize_color_schemes();
void set_window_colors_scheme(WINDOW* h_win, ColorScheme color_scheme) ;

#endif /* NCURSES_API */
