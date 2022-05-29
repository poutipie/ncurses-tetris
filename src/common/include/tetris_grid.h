#ifndef TETRIS_GRID_H
#define TETRIS_GRID_H

#include "utils.h"

typedef struct sTetrisGrid {

    size_t total_rows;
    size_t total_columns;

    bool** filled_squares;
    ColorScheme** filled_square_colors;

} TetrisGrid;


void TetrisGrid_init(TetrisGrid** self, size_t rows, size_t cols);
void TetrisGrid_destroy(TetrisGrid* self);

bool TetrisGrid_square_filled(TetrisGrid* self, Point position);
void TetrisGrid_fill_square(TetrisGrid* self, Point position, ColorScheme color);

bool TetrisGrid_row_filled(TetrisGrid* self, unsigned int row_index);
int TetrisGrid_find_filled_row(TetrisGrid* self);

void TetrisGrid_clear_row(TetrisGrid* self, WINDOW* h_win, unsigned int row_index);

#endif  /* TETRIS_GRID_H */
#