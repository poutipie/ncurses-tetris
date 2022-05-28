#ifndef TETRIS_BLOCK_H
#define TETRIS_BLOCK_H

#include <ncurses.h>
#include "game_state.h"
#include "utils.h"

typedef enum eTetrisBlockType {
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

typedef struct sTetrisBlock {
	bool m_frozen;
	TetrisBlockType m_type;
	ColorScheme m_color_scheme;
	int m_blk_size;
	Point* m_blk_coords;
	int m_world_pos_x;
	int m_world_pos_y;

	/* Classic tetris rotations are a bit tricky for each block. */
	TetrisBlockRotationType m_rotation_type;
	int m_rotation_cnt;

} TetrisBlock;

void TetrisBlock_init(TetrisBlock** self, TetrisBlockType block_type, int x, int y);
void TetrisBlock_init_Square(TetrisBlock* self);
void TetrisBlock_init_S(TetrisBlock* self);
void TetrisBlock_destroy(TetrisBlock* self);

void TetrisBlock_move(TetrisBlock* self, WINDOW* h_win, GameState* h_state, int x, int y);
bool TetrisBlock_fall(TetrisBlock* self, WINDOW* h_win, GameState* h_state);
void TetrisBlock_rotate(TetrisBlock* self, WINDOW* h_win, GameState* h_state);
void _TetrisBlock_rotate_operation(TetrisBlock* self, bool clockwise);
void TetrisBlock_freeze(TetrisBlock* self, GameState* h_state);

bool TetrisBlock_cannot_fall(TetrisBlock* self, WINDOW* h_win, GameState* h_state);
bool TetrisBlock_out_of_bounds(TetrisBlock* self, WINDOW* h_win);
bool TetrisBlock_is_on_filled_point(TetrisBlock* self, GameState* h_state);

void TetrisBlock_draw(TetrisBlock* self, WINDOW* h_win);
void TetrisBlock_clear(TetrisBlock* self, WINDOW* h_win);

#endif /* TETRIS_BLOCK_H */