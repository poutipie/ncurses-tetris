#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "utils.h"

typedef struct sGameState {

    int score;
    /* ... */

    bool** m_filled_squares;
    ColorScheme** m_filled_square_colors;
    unsigned int total_rows;
    unsigned int total_columns;

} GameState;

void GameState_init(GameState** self, WINDOW* h_win);
void GameState_destroy(GameState* self);

bool GameState_square_filled(GameState* self, Point position);
void GameState_fill_square(GameState* self, Point position, ColorScheme color);

#endif /* GAMESTATE_H */