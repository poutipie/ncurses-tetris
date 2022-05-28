#include "game_state.h"

#include<stdlib.h>

void GameState_init(GameState** self, WINDOW* h_win) {

    *self = (GameState*)malloc(sizeof(GameState));

    (*self)->total_rows = tetris_row_count(h_win);
    (*self)->total_columns = tetris_column_count(h_win);


    /* Allocate grids with necessary information about filled squares */
    (*self)->m_filled_square_colors = (ColorScheme**)malloc(
        (*self)->total_rows * sizeof(ColorScheme*)
    );
    (*self)->m_filled_squares = (bool**)malloc(
        (*self)->total_rows * sizeof(bool*)
    );
    for (int i = 0; i < (*self)->total_rows; ++i) {
        (*self)->m_filled_square_colors[i] = (ColorScheme*)malloc(
            (*self)->total_columns * sizeof(ColorScheme)
        );
        (*self)->m_filled_squares[i] = (bool*)malloc(
            (*self)->total_columns * sizeof(bool)
        );
    }

    /* Start out by initializing all colors as black and with empty grid */
    for (int i = 0; i < (*self)->total_rows; ++i) {
        for(int j = 0; j < (*self)->total_columns; ++ j) {
            (*self)->m_filled_square_colors[i][j] = COLORSCHEME_BLACK;
            (*self)->m_filled_squares[i][j] = false;
        }
    }

}

void GameState_destroy(GameState* self) {

    for (int i = 0; i < self->total_rows; ++i) {
        free(self->m_filled_square_colors[i]);
        free(self->m_filled_squares[i]);
    }
    free(self->m_filled_square_colors);
    free(self->m_filled_squares);
    free(self);
}

bool GameState_square_filled(GameState* self, Point position) {

    if (position.y >= self->total_rows || position.y < 0) {
        return false;
    }
    if (position.x >= self->total_columns || position.x < 0) {
        return false;
    }

    if (self->m_filled_squares[position.y][position.x]) {
        move(1, 0);
        printw("FILLED!!");
        return true;
    }
    return false;
}

void GameState_fill_square(GameState* self, Point point, ColorScheme color) {

    self->m_filled_squares[point.y][point.x] = true;
    self->m_filled_square_colors[point.y][point.x] = color;
}
