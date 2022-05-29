
#include <ncurses.h>
#include <unistd.h>

#include "types.h"
#include "tetris_block.h"
#include "game_state.h"
#include "game_loop.h"
#include "tetris_win.h"
#include "score_win.h"
#include "title_win.h"
#include "info_win.h"
#include "preview_win.h"

int main(int argc, char *argv[])
{	
	GameLoop* game_loop;

	TetrisWin* tetris_win;
	ScoreWin* score_win;
	TitleWin* title_win;
	InfoWin* info_win;
	PreviewWin* preview_win;

	initscr();			/* Start curses mode 		*/
	
	if (has_colors() == FALSE) {
		endwin();
		printf("Your terminal does not support color\n");
		return 1;
	}

	if (LINES < 33 || COLS < 45) {
		endwin();
		printf("Your terminal should have at least 33 lines and 45 columns\n");
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
	InfoWin_init(&info_win);
	PreviewWin_init(&preview_win);
	GameLoop_init(&game_loop);

	// Animation loop
	while(!game_loop->exiting) {
		GameLoop_game_loop(game_loop);
		TetrisWin_draw(tetris_win, game_loop->game_state);
		ScoreWin_draw(score_win, game_loop->game_state);
		PreviewWin_draw(preview_win, game_loop->game_state);
		TitleWin_draw(title_win);
		InfoWin_draw(info_win);
	}
	TetrisWin_destroy(&tetris_win);
	ScoreWin_destroy(&score_win);
	TitleWin_destroy(&title_win);
	InfoWin_destroy(&info_win);
	PreviewWin_destroy(&preview_win);
	GameLoop_destroy(&game_loop);
	endwin();			/* End curses mode		  */
	return 0;
}
