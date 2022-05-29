#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "types.h"
#include "tetris_grid.h"
#include "tetris_block.h"

typedef struct sGameState {

    bool game_over;
    int score;
    /* ... */
    TetrisGrid* h_tetris_grid;
    TetrisBlock* h_tetris_block;
    TetrisBlock* h_next_tetris_block;

} GameState;

void GameState_init(GameState** self, TetrisGrid* h_grid,
    TetrisBlock* h_block, TetrisBlock* h_n_tetris_block);
void GameState_destroy(GameState** self);

#endif /* GAMESTATE_H */