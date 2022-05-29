
#ifndef SCORE_WIN_H
#define SCORE_WIN_H

#include "utils.h"
#include "game_state.h"

typedef struct sScoreWin {
    WINDOW* m_win;
} ScoreWin;

void ScoreWin_init(ScoreWin** self);
void _ScoreWin_create_win(ScoreWin* self);
void ScoreWin_destroy(ScoreWin* self);

void ScoreWin_draw(ScoreWin* self, GameState* h_game_state);

#endif /* SCORE_WIN_H */