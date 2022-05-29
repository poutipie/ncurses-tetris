#include "game_loop.h"

#include <stdlib.h>
#include "ncurses_api.h"

void GameLoop_init(GameLoop** self) {

    *self = (GameLoop*)malloc(sizeof(GameLoop));

    (*self)->exiting = false;
    (*self)->active_block = NULL;
    (*self)->next_block = NULL;

    TetrisGrid_init(&(*self)->tetris_grid, TETRIS_ROWS, TETRIS_COLUMNS);
    GameState_init(&(*self)->game_state, (*self)->tetris_grid, 
        (*self)->active_block, (*self)->next_block);
    GameLoop_take_next_block(*self);

}

void GameLoop_destroy(GameLoop** self) {

    if ((*self)->active_block != NULL) {
        TetrisBlock_destroy(&(*self)->active_block);
    }
    if ((*self)->next_block != NULL) {
        TetrisBlock_destroy(&(*self)->next_block);
    }

    TetrisGrid_destroy(&(*self)->tetris_grid);
    GameState_destroy(&(*self)->game_state);
    free(*self);
    *self = NULL;
}

void GameLoop_reset(GameLoop* self) {

    if (self->active_block != NULL) {
        TetrisBlock_destroy(&self->active_block);
    }
    if (self->tetris_grid != NULL) {
        TetrisGrid_destroy(&self->tetris_grid);
    }
    GameState_destroy(&self->game_state);

    TetrisGrid_init(&self->tetris_grid, TETRIS_ROWS, TETRIS_COLUMNS);
    GameState_init(&self->game_state, self->tetris_grid, 
        self->active_block, self->next_block);
    GameLoop_take_next_block(self);
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
        GameLoop_take_next_block(self);
    }
    
    int filled_row = TetrisGrid_find_filled_row(self->tetris_grid);
    while (filled_row != -1) {
        TetrisGrid_clear_row(self->tetris_grid, filled_row);
        filled_row = TetrisGrid_find_filled_row(self->tetris_grid);
        self->game_state->score += 50;
    }
}

void GameLoop_create_next_block(GameLoop* self) {

    if (self->next_block != NULL) {
        TetrisBlock_destroy(&self->next_block);
    }

    TetrisBlockType new_block_type = rand() % TETRISBLOCKS_COUNT;
    TetrisBlock_init(&self->next_block, new_block_type, TETRIS_COLUMNS/2, 0);

}

void GameLoop_take_next_block(GameLoop* self) {

    if (self->next_block == NULL) {
        GameLoop_create_next_block(self);
    }
    if (self->active_block != NULL) {
        TetrisBlock_destroy(&self->active_block);
    }

    self->active_block = self->next_block;
    self->next_block = NULL;

    if (TetrisBlock_is_on_filled_point(self->active_block, self->tetris_grid)) {
        self->game_state->game_over = true;
    }

    GameLoop_create_next_block(self);

    self->game_state->h_tetris_block = self->active_block;
    self->game_state->h_next_tetris_block = self->next_block;
}
