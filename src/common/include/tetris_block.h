#ifndef TETRIS_BLOCK_H
#define TETRIS_BLOCK_H

#include <ncurses.h>
#include "utils.h"

typedef enum TetrisBlockType {
	TETRISBLOCKTYPE_SQUARE = 0,
	TETRISBLOCKTYPE_S = 1
} TetrisBlockType;

/* 
	1. L, J, and T rotate full circles
	2. S, Z, and I rotate only +90 and -90 degrees
	3. Square block never rotates
*/
typedef enum TetrisBlockRotationType {
	TETRISBLOCKROTATIONTYPE_COMPLETE,
	TETRISBLOCKROTATIONTYPE_TWOWAYS,
	TETRISBLOCKROTATIONTYPE_NO_ROTATION
} TetrisBlockRotationType;

typedef struct TetrisBlock {
	TetrisBlockType m_type;
	ColorScheme m_color_scheme;
	bool falling;
	int m_blk_size;
	int* m_blk_x_coords;
	int* m_blk_y_coords;
	int m_world_pos_x;
	int m_world_pos_y;

	/* Classic tetris rotations are a bit tricky for each block. */
	TetrisBlockRotationType m_rotation_type;
	int m_rotation_cnt;

} TETRIS_BLOCK;

void TetrisBlock_init(TETRIS_BLOCK** self, TetrisBlockType block_type, int x, int y);
void TetrisBlock_init_Square(TETRIS_BLOCK* self);
void TetrisBlock_init_S(TETRIS_BLOCK* self);
void TetrisBlock_destroy(TETRIS_BLOCK* self);

void TetrisBlock_move(TETRIS_BLOCK* self, WINDOW* h_win, int x, int y);
void TetrisBlock_rotate(TETRIS_BLOCK* self, WINDOW* h_win);
void _TetrisBlock_rotate_operation(TETRIS_BLOCK* self, bool clockwise);

bool TetrisBlock_out_of_bounds(TETRIS_BLOCK* self, WINDOW* h_win);
void TetrisBlock_draw(TETRIS_BLOCK* self, WINDOW* h_win);
void TetrisBlock_clear(TETRIS_BLOCK* self, WINDOW* h_win);

#endif /* TETRIS_BLOCK_H */