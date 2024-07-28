#ifndef VARIABLES_H_INCLUDED
#define VARIABLES_H_INCLUDED

#include <sstream>
#include "Texture.h"
#include "Constants.h"
#include "Button.h"

extern SDL_Window* gWindow;

extern SDL_Renderer* gRenderer;

extern SDL_Rect gSpriteClips[ SPRITE_TOTAL ];
extern LTexture gButtonSpriteSheetTexture;

extern LTexture gBackgroundTexture;

extern LTexture gTextTexture;
extern LTexture gMineLeftTexture;

extern int countMineLeft;
extern int countTileLeft;
extern bool gameOver;
extern bool isWinning;


//In memory text stream
extern stringstream mineLeft;

//Board with mine
extern int board[ROW_SIZE][COL_SIZE];

//Board for showing
extern int sBoard[ROW_SIZE][COL_SIZE];
#endif // VARIABLES_H_INCLUDED
