
#include <ncurses.h>
#include <unistd.h>

#include "tetris_block.h"
#include "game_state.h"
#include "game_loop.h"
#include "tetris_win.h"
#include "score_win.h"
#include "title_win.h"
#include "utils.h"

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

int main(int argc, char *argv[])
{	
	GameLoop* game_loop;

	TetrisWin* tetris_win;
	ScoreWin* score_win;
	TitleWin* title_win;

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


	TetrisWin_init(&tetris_win);
	ScoreWin_init(&score_win);
	TitleWin_init(&title_win);
	GameLoop_init(&game_loop);

	// Animation loop
	while(true) {
		GameLoop_game_loop(game_loop);
		TetrisWin_draw(tetris_win, game_loop->game_state);
		ScoreWin_draw(score_win, game_loop->game_state);
		TitleWin_draw(title_win, game_loop->game_state);
	}
	TetrisWin_destroy(tetris_win);
	ScoreWin_destroy(score_win);
	TitleWin_destroy(title_win);
	GameLoop_destroy(game_loop);
	endwin();			/* End curses mode		  */
	return 0;
}
