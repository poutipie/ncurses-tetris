
#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include "utils.h"
#include "game_state.h"
#include "tetris_block.h"
#include "tetris_grid.h"

typedef struct sGameLoop {

    WINDOW* h_tetris_win;
    GameState* game_state;
    TetrisGrid* tetris_grid;
    TetrisBlock* active_block;

} GameLoop;

void GameLoop_init(GameLoop** self, WINDOW* h_tetris_win);
void GameLoop_destroy(GameLoop* self);

void GameLoop_game_loop(GameLoop* self);

#endif /* GAME_LOOP_H */
