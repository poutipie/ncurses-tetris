#include "game_state.h"

#include<stdlib.h>

void GameState_init(GameState** self, WINDOW* h_win) {

    *self = (GameState*)malloc(sizeof(GameState));

    (*self)->m_filled_squares_size = getmaxy(h_win) * getmaxx(h_win);
    (*self)->m_filled_squares = (TetrisSquare*)malloc(
        (*self)->m_filled_squares_size * sizeof(TetrisSquare)
    );
    (*self)->m_filled_squares_end = 0;
}

void GameState_destroy(GameState* self) {

    free(self->m_filled_squares);
    free(self);
}

bool GameState_square_filled(GameState* self, Point position) {

    bool is_filled = false;
    for (int i = 0; i < self->m_filled_squares_end; ++i) {
        is_filled |= (
            position.x == self->m_filled_squares[i].position.x && 
            position.y == self->m_filled_squares[i].position.y
        );
        if (is_filled) {
            move(1, 0);
            printw("FILLED!!");
            break;
        }
    }
    return is_filled;
}

void GameState_fill_square(GameState* self, Point point, ColorScheme color) {

    TetrisSquare new_square = {
        .position = point,
        .color = color
    };

    self->m_filled_squares[self->m_filled_squares_end] = new_square;
    ++self->m_filled_squares_end;
}
