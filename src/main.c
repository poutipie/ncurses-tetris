
#include <ncurses.h>
#include <unistd.h>

#include "tetris_block.h"
#include "game_state.h"
#include "game_loop.h"
#include "utils.h"

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

int main(int argc, char *argv[])
{	
	GameLoop* game_loop;
	WINDOW* h_tetris_win;
	WINDOW* h_score_win;

	initscr();			/* Start curses mode 		*/
	
	if (has_colors() == FALSE) {
		endwin();
		printf("Your terminal does not support color\n");
		return 1;
	}
	
	start_color();
	ncurses_initialize_color_schemes();
	set_window_colors_scheme(stdscr, COLORSCHEME_BLACK);
	
	cbreak();			/* Line buffering disabled */
	keypad(stdscr, TRUE);
	wtimeout(stdscr, 500); /* Make sure getch does not block execution */
	curs_set(0); /* Hide cursor highlighting */


	h_tetris_win = create_tetris_win();
	h_score_win = create_score_win();
	GameLoop_init(&game_loop, h_tetris_win);

	// Animation loop
	while(true) {
		GameLoop_game_loop(game_loop);
		wrefresh(h_tetris_win);
		wrefresh(h_score_win);
	}
	destroy_gui_win(h_tetris_win);
	destroy_gui_win(h_score_win);
	endwin();			/* End curses mode		  */
	return 0;
}
