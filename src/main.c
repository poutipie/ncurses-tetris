
#include <ncurses.h>
#include <unistd.h>

#include "tetris_block.h"

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

int main(int argc, char *argv[])
{	
	WINDOW *my_win;
	TETRIS_BLOCK* my_rect;

	int startx, starty, width, height;

	initscr();			/* Start curses mode 		*/
	cbreak();			/* Line buffering disabled, Pass on
					 * everty thing to me 		*/
	keypad(stdscr, TRUE);		/* I need that nifty F1 	*/
	wtimeout(stdscr, 500); /* Make sure getch does not block execution */

	TetrisBlock_init(&my_rect, TETRISBLOCKTYPE_SQUARE, 4, 4);

	height = 50;
	width = 40;
	starty = (LINES - height) / 2;	
	/* Calculating for a center placement */
	startx = (COLS - width) / 2;	/* of the window		*/
	refresh();
	my_win = create_newwin(height, width, starty, startx);


	int ch;
	// Animation loop
	while(true) {

		ch = wgetch(stdscr);
		switch(ch) {
			case KEY_LEFT:
				TetrisBlock_move(my_rect, my_win, -1, 0);
				break;
			case KEY_RIGHT:
				TetrisBlock_move(my_rect, my_win, 1, 0);
				break;
			default:
				TetrisBlock_move(my_rect, my_win, 0, 0);
				break;
		}
		TetrisBlock_move(my_rect, my_win, 0, 1);
		wrefresh(my_win);
	}
	endwin();			/* End curses mode		  */
	TetrisBlock_destroy(my_rect);
	return 0;
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

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
