#pragma once

#include <SDL_mixer.h>
#include <sstream>
#include <vector>
#include "Texture.h"
#include "Constants.h"
#include "Button.h"

// The window we'll be rendering to
extern SDL_Window *gWindow;

// The window renderer
extern SDL_Renderer *gRenderer;
extern bool mainLoop;
extern bool isRunning;
extern bool isChoosing;

// The sound effects that will be used
extern Mix_Music *winner;
extern Mix_Music *loser;
extern Mix_Chunk *click;

// Globally used font
extern TTF_Font *gGameOver;

// Mouse button texture
extern SDL_Rect gSpriteClips[SPRITE_TOTAL];
extern LTexture gButtonSpriteSheetTexture;

// Screen texture
extern LTexture gMenuTheme;
extern LTexture gWinningTexture;
extern LTexture gBackgroundTexture;

// Rendered texture
extern LTexture gTextTexture;
extern LTexture gMineLeftTexture;
extern LTexture gCountMineLeftTexture;
extern LTexture gTime;
extern LTexture gTimeText;
extern LTexture gMenu;
extern LTexture gMenu1;
extern LTexture gEasyChoice;
extern LTexture gMediumChoice;
extern LTexture gHardChoice;
extern LTexture gExitButton;
extern LTexture gHomeButton;
extern LTexture gTextTime;

// Gameplay variables
extern int countMineLeft;
extern int countTileLeft;
extern bool gameOver;
extern bool isWinning;
extern bool start;
extern bool easy;
extern bool medium;
extern bool hard;
extern bool exitGame;
extern bool showMenu;
extern bool hardMode;

// In memory text stream
extern stringstream mineLeft;
extern stringstream timeText;

// Distance between the board and the screen
extern int distance_x;
extern int distance_y;

// Board size
extern int BOARD_SIZE_X;
extern int BOARD_SIZE_Y;
extern int MINE_COUNT;

extern std::vector<std::vector<int>> sBoard;
extern std::vector<std::vector<int>> board;
