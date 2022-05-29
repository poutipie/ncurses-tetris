
#ifndef SCORE_WIN_H
#define SCORE_WIN_H

#include "utils.h"

typedef struct sScoreWin {
    WINDOW* m_win;
} ScoreWin;

void ScoreWin_init(ScoreWin** self);
void _ScoreWin_create_win(ScoreWin* self);
void ScoreWin_destroy(ScoreWin* self);

void ScoreWin_draw(ScoreWin* self);

#endif /* SCORE_WIN_H */