
#ifndef TITLE_WIN_H
#define TITLE_WIN_H

#include "ncurses_api.h"
#include "game_state.h"

typedef struct sTitleWin {
    WINDOW* m_win;

    size_t m_width;
    size_t m_height;
} TitleWin;

void TitleWin_init(TitleWin** self);
void TitleWin_destroy(TitleWin** self);
void _TitleWin_create_win(TitleWin* self);

void TitleWin_draw(TitleWin* self);

#endif /* TITLE_WIN_H */