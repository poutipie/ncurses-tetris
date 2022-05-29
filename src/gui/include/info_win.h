
#ifndef INFO_WIN_H
#define INFO_WIN_H

#include "ncurses_api.h"
#include "game_state.h"

typedef struct sInfoWin {
    WINDOW* m_win;

    size_t m_width;
    size_t m_height;
} InfoWin;

void InfoWin_init(InfoWin** self);
void _InfoWin_create_win(InfoWin* self);
void InfoWin_destroy(InfoWin* self);

void InfoWin_draw(InfoWin* self, GameState* h_game_state);

#endif /* INFO_WIN_H */