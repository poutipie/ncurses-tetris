
#include <ncurses.h>
#include <unistd.h>

#include "tetris_block.h"
#include "game_state.h"
#include "utils.h"

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

int main(int argc, char *argv[])
{	
	WINDOW* tetris_win;
	GameState* game_state;
	TetrisBlock* curr_block;
	int startx, starty, width, height;

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
	curs_set(0); /* Hide ncurses cursos */

	TetrisBlock_init(&curr_block, TETRISBLOCKTYPE_S, 4, 4);

	height = 25;
	width = 20;
	starty = (LINES - height) / 2;	
	/* Calculating for a center placement */
	startx = (COLS - width) / 2;	/* of the window		*/
	refresh();

	tetris_win = create_newwin(height, width, starty, startx);
	GameState_init(&game_state, tetris_win);
	set_window_colors_scheme(tetris_win, COLORSCHEME_WHITE);


	int ch;
	// Animation loop
	while(true) {
		set_window_colors_scheme(tetris_win, COLORSCHEME_WHITE);

		ch = wgetch(stdscr);
		switch(ch) {
			case KEY_LEFT:
				TetrisBlock_move(curr_block, tetris_win, game_state, -1, 0);
				break;
			case KEY_RIGHT:
				TetrisBlock_move(curr_block, tetris_win, game_state, 1, 0);
				break;
			case KEY_UP:
				TetrisBlock_rotate(curr_block, tetris_win, game_state);
			default:
				TetrisBlock_move(curr_block, tetris_win, game_state, 0, 0);
				break;
		}
		
		if (!TetrisBlock_fall(curr_block, tetris_win, game_state)) {
			TetrisBlock_destroy(curr_block);
			TetrisBlock_init(&curr_block, TETRISBLOCKTYPE_SQUARE, 4, 4);
		}
		
		wrefresh(tetris_win);
	}
	endwin();			/* End curses mode		  */
	TetrisBlock_destroy(curr_block);
	return 0;
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{	
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}

void destroy_win(WINDOW *local_win)
{
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wrefresh(local_win);
	delwin(local_win);
}
