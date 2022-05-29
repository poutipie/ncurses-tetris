
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
        move(1, 0);
        printw("FILLED!!");
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

void TetrisGrid_clear_row(TetrisGrid* self, WINDOW* h_win, unsigned int row_index) {
    if (row_index < 0 || row_index >= self->total_rows) {
        return;
    }

    for (int i = row_index; i >= 0; --i) {
        for (int j = 0; j < self->total_columns; ++j) {
            
            /* Clear Data */
            self->filled_squares[i][j] = false;
            self->filled_square_colors[i][j] = COLORSCHEME_BLACK;

            /* Clear Graphic */
            Point clear_position = {
                .x = j,
                .y = i
            };
            clear_tetris_square(h_win, clear_position);

            /* Shift Data (if not uppermost row) */         
            if (i == 0) {
                break;
            }
            self->filled_squares[i][j] = self->filled_squares[i-1][j];
            self->filled_square_colors[i][j] = 
                self->filled_square_colors[i-1][j];
            
            /* Draw new graphic if we shifted an actual block */
            if (self->filled_squares[i][j]) {
                draw_tetris_square(h_win, clear_position, 
                self->filled_square_colors[i][j]);
            }
        }
    }

}