#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "utils.h"

typedef struct sGameState {

    int score;
    /* ... */
    TetrisSquare* m_filled_squares;
    unsigned int m_filled_squares_end;
    size_t m_filled_squares_size;

} GameState;

void GameState_init(GameState** self, WINDOW* h_win);
void GameState_destroy(GameState* self);

bool GameState_square_filled(GameState* self, Point position);
void GameState_fill_square(GameState* self, Point position, ColorScheme color);

#endif /* GAMESTATE_H */