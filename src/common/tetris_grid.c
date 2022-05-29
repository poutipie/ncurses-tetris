
#include "tetris_grid.h"
#include <stdlib.h>

void TetrisGrid_init(TetrisGrid** self, size_t rows, size_t cols) {
    
    *self = (TetrisGrid*)malloc(sizeof(TetrisGrid));

    (*self)->total_rows = rows;
    (*self)->total_columns = cols;


    /* Allocate grids with necessary information about filled squares */
    (*self)->filled_square_colors = (ColorScheme**)malloc(
        (*self)->total_rows * sizeof(ColorScheme*)
    );
    (*self)->filled_squares = (bool**)malloc(
        (*self)->total_rows * sizeof(bool*)
    );
    for (int i = 0; i < (*self)->total_rows; ++i) {
        (*self)->filled_square_colors[i] = (ColorScheme*)malloc(
            (*self)->total_columns * sizeof(ColorScheme)
        );
        (*self)->filled_squares[i] = (bool*)malloc(
            (*self)->total_columns * sizeof(bool)
        );
    }

    /* Start out by initializing all colors as black and with empty grid */
    for (int i = 0; i < (*self)->total_rows; ++i) {
        for(int j = 0; j < (*self)->total_columns; ++ j) {
            (*self)->filled_square_colors[i][j] = COLORSCHEME_BLACK;
            (*self)->filled_squares[i][j] = false;
        }
    }
}

bool TetrisGrid_y_within_bounds(TetrisGrid* self, int y) {
	return  ! (y < 0 || y > self->total_rows - 1);
}

bool TetrisGrid_x_within_bounds(TetrisGrid* self, int x) {
	return ! ( x < 0 || x > self->total_columns - 1);
}

void TetrisGrid_destroy(TetrisGrid* self) {

    for (int i = 0; i < self->total_rows; ++i) {
        free(self->filled_square_colors[i]);
        free(self->filled_squares[i]);
    }
    free(self->filled_square_colors);
    free(self->filled_squares);
}

bool TetrisGrid_square_filled(TetrisGrid* self, Point position) {

    if (position.y >= self->total_rows || position.y < 0) {
        return false;
    }
    if (position.x >= self->total_columns || position.x < 0) {
        return false;
    }

    if (self->filled_squares[position.y][position.x]) {
        return true;
    }
    return false;
}

void TetrisGrid_fill_square(TetrisGrid* self, Point point, ColorScheme color) {

    self->filled_squares[point.y][point.x] = true;
    self->filled_square_colors[point.y][point.x] = color;
}

bool TetrisGrid_row_filled(TetrisGrid* self, unsigned int row_index) {

    if (row_index < 0 || row_index >= self->total_rows) {
        return false;
    }

    bool row_is_filled = true;
    for (int i = 0; i < self->total_columns; ++i) {
        row_is_filled &= self->filled_squares[row_index][i];
        if (!row_is_filled) {
            break;
        }
    }
    return row_is_filled;
}

int TetrisGrid_find_filled_row(TetrisGrid* self) {
    for (int i = 0; i < self->total_rows; ++i) {
        if (TetrisGrid_row_filled(self, i)) {
            return i;
        }
    }
    return -1;
}

void TetrisGrid_clear_row(TetrisGrid* self, unsigned int row_index) {
    if (row_index < 0 || row_index >= self->total_rows) {
        return;
    }

    for (int i = row_index; i >= 0; --i) {
        for (int j = 0; j < self->total_columns; ++j) {
            
            /* Clear Data */
            self->filled_squares[i][j] = false;
            self->filled_square_colors[i][j] = COLORSCHEME_BLACK;

            /* Shift Data (if not uppermost row) */         
            if (i == 0) {
                break;
            }
            self->filled_squares[i][j] = self->filled_squares[i-1][j];
            self->filled_square_colors[i][j] = 
                self->filled_square_colors[i-1][j];
        }
    }

}