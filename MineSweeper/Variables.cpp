#include "Variables.h"

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Mouse button texture
SDL_Rect gSpriteClips[ SPRITE_TOTAL ];
LTexture gButtonSpriteSheetTexture;

LTexture gBackgroundTexture;

LTexture gTextTexture;
LTexture gMineLeftTexture;

int countMineLeft = MINE_COUNT;
int countTileLeft = ROW_SIZE * COL_SIZE;
bool gameOver = false;
bool isWinning = false;

//In memory text stream
stringstream mineLeft;

//Board with mine
int board[ROW_SIZE][COL_SIZE];

//Board for showing
int sBoard[ROW_SIZE][COL_SIZE];
