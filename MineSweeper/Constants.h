#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

// Tile's constants
const int TILE_SIZE = 32;
const int SPRITE_TOTAL = 12;

// Number of mines
const int MINE_COUNT = 10;

//Table's size
const int ROW_SIZE = 9;
const int COL_SIZE = 9;

//Screen dimension constants
const int SCREEN_WIDTH = 460;
const int SCREEN_HEIGHT = 460;
const int DISTANCE_BETWEEN = (SCREEN_WIDTH - ROW_SIZE * TILE_SIZE) / 2;

#endif // CONSTANTS_H_INCLUDED
