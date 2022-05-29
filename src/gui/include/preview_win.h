
#ifndef PREVIEW_WIN_H
#define PREVIEW_WIN_H

#include "ncurses_api.h"
#include "game_state.h"

typedef struct sPreviewWin {
    WINDOW* m_win;

    size_t m_width;
    size_t m_height;
} PreviewWin;

void PreviewWin_init(PreviewWin** self);
void PreviewWin_destroy(PreviewWin** self);
void _PreviewWin_create_win(PreviewWin* self);
void PreviewWin_draw(PreviewWin* self, GameState* h_game_state);

#endif /* PREVIEW_WIN_H */