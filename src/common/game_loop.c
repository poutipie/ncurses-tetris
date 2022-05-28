#include "game_loop.h"

#include <stdlib.h>

void GameLoop_init(GameLoop** self) {

    *self = (GameLoop*)malloc(sizeof(GameLoop));

    GameLoop_create_tetris_win(*self);
    set_window_colors_scheme((*self)->tetris_win, COLORSCHEME_WHITE);
    GameState_init(&(*self)->game_state, (*self)->tetris_win);
    TetrisBlock_init(&(*self)->active_block, TETRISBLOCKTYPE_S, 1, 1);

}

void GameLoop_destroy(GameLoop* self) {
    TetrisBlock_destroy(self->active_block);
    GameState_destroy(self->game_state);
    GameLoop_destroy_tetris_win(self);
}

void GameLoop_create_tetris_win(GameLoop* self) {

    int height = 14;
	int width = 10;
    /* Calculating for a center placement of the window*/
	int starty = (LINES - height) / 2;
	int startx = (COLS - width) / 2;

	self->tetris_win = newwin(height, width, starty, startx);
	box(self->tetris_win, 0 , 0);		/* 0, 0 gives default box outline*/
	wrefresh(self->tetris_win);		/* Show that box 		*/
}

void GameLoop_destroy_tetris_win(GameLoop* self) {
    wborder(self->tetris_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wrefresh(self->tetris_win);
	delwin(self->tetris_win);
}

void GameLoop_game_loop(GameLoop* self) {

    int ch = wgetch(stdscr);

    switch(ch) {
        case KEY_LEFT:
            TetrisBlock_move(self->active_block, self->tetris_win, self->game_state, -1, 0);
            break;
        case KEY_RIGHT:
            TetrisBlock_move(self->active_block, self->tetris_win, self->game_state, 1, 0);
            break;
        case KEY_UP:
            TetrisBlock_rotate(self->active_block, self->tetris_win, self->game_state);
        default:
            TetrisBlock_move(self->active_block, self->tetris_win, self->game_state, 0, 0);
            break;
    }
		
    if (!TetrisBlock_fall(self->active_block, self->tetris_win, self->game_state)) {
        TetrisBlock_destroy(self->active_block);
        TetrisBlock_init(&self->active_block, TETRISBLOCKTYPE_SQUARE, 1, 1);
    }
    
    int filled_row = GameState_find_filled_row(self->game_state);
    while (filled_row != -1) {
        move(0,0);
        printw("ROW WAS FILLED!");
        GameState_clear_row(self->game_state, self->tetris_win, filled_row);
        filled_row = GameState_find_filled_row(self->game_state);
    }

    wrefresh(self->tetris_win);
}
