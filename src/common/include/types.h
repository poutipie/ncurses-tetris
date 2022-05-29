#ifndef TYPES_H
#define TYPES_H

#define TETRIS_ROWS       16
#define TETRIS_COLUMNS    12

#include<stdlib.h>
#include<stdbool.h>

typedef struct sPoint {
    int x;
    int y;
} Point;

typedef enum ColorScheme {
	COLORSCHEME_BLACK  = 1,
	COLORSCHEME_WHITE  = 2,
    COLORSCHEME_YELLOW = 3,
    COLORSCHEME_GREEN = 4
} ColorScheme;


#endif /* TYPES_H */
