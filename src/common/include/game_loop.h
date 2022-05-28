
#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include "utils.h"
#include "game_state.h"
#include "tetris_block.h"

typedef struct sGameLoop {

    WINDOW* tetris_win;
    GameState* game_state;
    TetrisBlock* active_block;

} GameLoop;

void GameLoop_init(GameLoop** self);
void GameLoop_destroy(GameLoop* self);
void GameLoop_create_tetris_win(GameLoop* self);
void GameLoop_destroy_tetris_win(GameLoop* self);

void GameLoop_game_loop(GameLoop* self);

#endif /* GAME_LOOP_H */
