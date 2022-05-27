#ifndef TETRIS_BLOCK_H
#define TETRIS_BLOCK_H

#include <ncurses.h>
#include "utils.h"

typedef enum TetrisBlockType {
	TETRISBLOCKTYPE_SQUARE = 0,
	TETRISBLOCKTYPE_S = 1
} TetrisBlockType;

typedef struct TetrisBlock {
	TetrisBlockType m_type;
	ColorScheme m_color_scheme;
	bool falling;
	int size;
	int* x_coords;
	int* y_coords;
} TETRIS_BLOCK;

void TetrisBlock_init(TETRIS_BLOCK** self, TetrisBlockType block_type, int x, int y);
void TetrisBlock_init_Square(TETRIS_BLOCK* self, int x, int y);

void TetrisBlock_destroy(TETRIS_BLOCK* self);

void TetrisBlock_move(TETRIS_BLOCK* self, WINDOW* h_win, int x, int y);
void TetrisBlock_draw(TETRIS_BLOCK* self, WINDOW* h_win);
void TetrisBlock_clear(TETRIS_BLOCK* self, WINDOW* h_win);

#endif /* TETRIS_BLOCK_H */