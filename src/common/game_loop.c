#include "game_loop.h"

#include <stdlib.h>

void GameLoop_init(GameLoop** self, WINDOW* h_tetris_win) {

    *self = (GameLoop*)malloc(sizeof(GameLoop));

    (*self)->h_tetris_win = h_tetris_win;

    TetrisGrid_init(&(*self)->tetris_grid, TETRIS_ROWS, TETRIS_COLUMNS);
    TetrisBlock_init(&(*self)->active_block, TETRISBLOCKTYPE_S, 1, 1);
    GameState_init(&(*self)->game_state, (*self)->tetris_grid, (*self)->active_block);

}

void GameLoop_destroy(GameLoop* self) {
    TetrisBlock_destroy(self->active_block);
    TetrisGrid_destroy(self->tetris_grid);
    GameState_destroy(self->game_state);
}

void GameLoop_game_loop(GameLoop* self) {

    int ch = wgetch(stdscr);

    switch(ch) {
        case KEY_LEFT:
            TetrisBlock_move(self->active_block, self->h_tetris_win, self->tetris_grid, -1, 0);
            break;
        case KEY_RIGHT:
            TetrisBlock_move(self->active_block, self->h_tetris_win, self->tetris_grid, 1, 0);
            break;
        case KEY_UP:
            TetrisBlock_rotate(self->active_block, self->h_tetris_win, self->tetris_grid);
        default:
            TetrisBlock_move(self->active_block, self->h_tetris_win, self->tetris_grid, 0, 0);
            break;
    }
		
    if (!TetrisBlock_fall(self->active_block, self->h_tetris_win, self->tetris_grid)) {
        TetrisBlock_destroy(self->active_block);
        TetrisBlock_init(&self->active_block, TETRISBLOCKTYPE_SQUARE, 1, 1);
    }
    
    int filled_row = TetrisGrid_find_filled_row(self->tetris_grid);
    while (filled_row != -1) {
        move(0,0);
        printw("ROW WAS FILLED!");
        TetrisGrid_clear_row(self->tetris_grid, self->h_tetris_win, filled_row);
        filled_row = TetrisGrid_find_filled_row(self->tetris_grid);
    }
}
