#include "game_state.h"

#include<stdlib.h>

void GameState_init(GameState** self, TetrisGrid* h_grid, TetrisBlock* h_block) {

    *self = (GameState*)malloc(sizeof(GameState));
    
    (*self)->h_tetris_grid = h_grid;
    (*self)->h_tetris_block = h_block;

    (*self)->score = 0;
    (*self)->game_over = false;

}

void GameState_destroy(GameState* self) {

    free(self);
}
