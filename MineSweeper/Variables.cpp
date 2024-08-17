#include "Variables.h"

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The window renderer
SDL_Renderer *gRenderer = NULL;

/*bool showMenu;*/
extern bool isChoosing = true;
extern bool isRunning = false;
extern bool mainLoop = true;

// The sound effects that will be used
Mix_Music *winner = NULL;
Mix_Music *loser = NULL;
Mix_Chunk *click = NULL;

// Globally used font
TTF_Font *gGameOver = NULL;

// Mouse button texture
SDL_Rect gSpriteClips[SPRITE_TOTAL];
LTexture gButtonSpriteSheetTexture;

// Screen texture
LTexture gMenuTheme;
LTexture gWinningTexture;
LTexture gBackgroundTexture;

// Rendered texture
LTexture gTextTexture;
LTexture gMineLeftTexture;
LTexture gCountMineLeftTexture;
LTexture gTime;
LTexture gTimeText;
LTexture gMenu;
LTexture gMenu1;
LTexture gEasyChoice;
LTexture gMediumChoice;
LTexture gHardChoice;
LTexture gExitButton;
LTexture gHomeButton;
LTexture gTextTime;

// Gameplay variables
int countMineLeft = MINE_COUNT;
int countTileLeft = BOARD_SIZE_X * BOARD_SIZE_Y;
bool gameOver = false;
bool isWinning = false;
bool easy = false;
bool medium = false;
bool hard = false;
bool exitGame = false;
bool showMenu = true;
bool hardMode = false;

// In memory text stream
stringstream mineLeft;
stringstream timeText;

// Distance between the board and the screen
extern int distance_x = 0;
extern int distance_y = 0;

// Board size
extern int BOARD_SIZE_X = 0;
extern int BOARD_SIZE_Y = 0;
extern int MINE_COUNT = 0;

extern std::vector<std::vector<int>> sBoard(3, std::vector<int>(2, 0));
extern std::vector<std::vector<int>> board(3, std::vector<int>(2, 0));
