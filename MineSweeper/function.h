#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED

#include "Timer.h"
#include <SDL.h>
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <sstream>
#include <string>
#include "Texture.h"
#include "Constants.h"
#include "Variables.h"

// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

bool loadMenuMedia();

void createTableWithMine();

void setButtonPosition();

void handleEvent();

void renderGame();

// Check win flag
bool checkWinning();

// Render number of flag/mine left
void mineManager(int dx);

// Perform win/lose flag
void flagManager(int dx);

void timeRender(int n);

void TimeManager(int screen_width);

void renderMenu();

void showModeChoice();

void setGameMode(int x, int y, int n, int dx, int dy, int &BOARD_SIZE_X, int &BOARD_SIZE_Y, int &NumberOfMines, int &mineCountLeft, int &CountTileLeft, int &distance_x, int &distance_y);

void startTimer();

void updateTimer();

void renderTime(int dx);


// Frees media and shuts down SDL
void close();

#endif // FUNCTION_H_INCLUDED
