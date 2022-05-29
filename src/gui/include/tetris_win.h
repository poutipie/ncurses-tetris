#ifndef TETRIS_WIN_H
#define TETRIS_WIN_H

#include "utils.h"

#include "game_state.h"

typedef struct sTetrisWin {

    WINDOW* m_win;

} TetrisWin;

void TetrisWin_init(TetrisWin** self);
void _TetrisWin_create_win(TetrisWin* self);
void TetrisWin_destroy(TetrisWin* self);

void TetrisWin_draw(TetrisWin* self, GameState* h_game_state);

void _TetrisWin_draw_tetris_square(TetrisWin* self, Point position, ColorScheme color);
void _TetrisWin_clear_tetris_square(TetrisWin* self, Point position);

#endif /* TETRIS_WIN_H */