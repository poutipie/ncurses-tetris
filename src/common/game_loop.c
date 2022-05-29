#include "game_loop.h"

#include <stdlib.h>

void GameLoop_init(GameLoop** self) {

    *self = (GameLoop*)malloc(sizeof(GameLoop));

    (*self)->exiting = false;

    TetrisGrid_init(&(*self)->tetris_grid, TETRIS_ROWS, TETRIS_COLUMNS);
    GameLoop_start_new_block(*self);
    GameState_init(&(*self)->game_state, (*self)->tetris_grid, (*self)->active_block);

}

void GameLoop_destroy(GameLoop* self) {

    TetrisBlock_destroy(self->active_block);
    TetrisGrid_destroy(self->tetris_grid);
    GameState_destroy(self->game_state);
    free(self);
}

void GameLoop_reset(GameLoop* self) {

    TetrisBlock_destroy(self->active_block);
    TetrisGrid_destroy(self->tetris_grid);
    GameState_destroy(self->game_state);

    TetrisGrid_init(&self->tetris_grid, TETRIS_ROWS, TETRIS_COLUMNS);
    GameLoop_start_new_block(self);
    GameState_init(&self->game_state, self->tetris_grid, self->active_block);
}

void GameLoop_game_loop(GameLoop* self) {

    int ch = wgetch(stdscr);

    /* Handle menu keys */
    switch(ch) {
        case 'r':
            GameLoop_reset(self);
            return;
        case 'q':
            self->exiting = true;
            return;
        default:
            break;
    }

    if (self->game_state->game_over || self->exiting) {
        return;
    }

    /* Handle action keys */
    switch(ch) {
        case KEY_LEFT:
            TetrisBlock_move(self->active_block, self->tetris_grid, -1, 0);
            break;
        case KEY_RIGHT:
            TetrisBlock_move(self->active_block, self->tetris_grid, 1, 0);
            break;
        case KEY_UP:
            TetrisBlock_rotate(self->active_block, self->tetris_grid);
            break;
        default:
            break;
    }
		
    if (!TetrisBlock_fall(self->active_block, self->tetris_grid)) {
        TetrisBlock_destroy(self->active_block);
        GameLoop_start_new_block(self);
    }
    
    int filled_row = TetrisGrid_find_filled_row(self->tetris_grid);
    while (filled_row != -1) {
        TetrisGrid_clear_row(self->tetris_grid, filled_row);
        filled_row = TetrisGrid_find_filled_row(self->tetris_grid);
        self->game_state->score += 50;
    }
}

void GameLoop_start_new_block(GameLoop* self) {

    TetrisBlockType new_block_type = rand() % 2;
    TetrisBlock_init(&self->active_block, new_block_type, TETRIS_COLUMNS/2, 0);

    if (TetrisBlock_is_on_filled_point(self->active_block, self->tetris_grid)) {
        self->game_state->game_over = true;
    }

}
