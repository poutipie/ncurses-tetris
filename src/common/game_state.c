#include "game_state.h"

#include<stdlib.h>

void GameState_init(GameState** self, WINDOW* h_win) {

    *self = (GameState*)malloc(sizeof(GameState));

    (*self)->m_filled_points_size = getmaxy(h_win) * getmaxx(h_win);
    (*self)->m_filled_points = (Point*)malloc(
        (*self)->m_filled_points_size * sizeof(Point)
    );
    (*self)->m_filled_points_end = 0;
}

void GameState_destroy(GameState* self) {

    free(self->m_filled_points);
    free(self);
}

bool GameState_point_filled(GameState* self, Point point) {

    bool is_filled = false;
    for (int i = 0; i < self->m_filled_points_end; ++i) {
        move(0,0);
        printw("TESTING IF (%d, %d) == (%d, %d)", point.x, point.y, self->m_filled_points[i].x , self->m_filled_points[i].y);
        is_filled |= (
            point.x == self->m_filled_points[i].x && 
            point.y == self->m_filled_points[i].y
        );
        if (is_filled) {
            move(1, 0);
            printw("FILLED!!");
            break;
        }
    }
    return is_filled;
}

void GameState_fill_point(GameState* self, Point point) {
    self->m_filled_points[self->m_filled_points_end] = point;
    ++self->m_filled_points_end;
}
