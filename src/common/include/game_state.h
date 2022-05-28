#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "utils.h"

typedef struct sGameState {

    int score;
    /* ... */
    Point* m_filled_points;
    unsigned int m_filled_points_end;
    size_t m_filled_points_size;

} GameState;

void GameState_init(GameState** self, WINDOW* h_win);
void GameState_destroy(GameState* self);

bool GameState_point_is_filled(GameState* self, Point point);
void GameState_fill_points(GameState* self, Point* points, size_t points_size);

#endif /* GAMESTATE_H */