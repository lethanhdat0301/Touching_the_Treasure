
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <sstream>
#include <string>
#include "Texture.h"
#include "Constants.h"
#include "Variables.h"

using namespace std;

LButton gButtons[ROW_SIZE][COL_SIZE];

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Initializes playground
void createTableWithMine ();

//Check win flag
bool checkWinning ();

//Render number of flag/mine left
void mineManager();


int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		cout << "Failed to initialize!\n";
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			cout << "Failed to load media!\n";
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit )
			{
			    createTableWithMine();

			    //While game is not over yet
			    while ( !gameOver && !quit && !isWinning)
                {
                    //Handle events on queue
                    while( SDL_PollEvent( &e ) != 0 )
                    {
                        //User requests quit
                        if( e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
                        {
                            quit = true;
                        }

                        //Handle button events
                        for (int i = 0; i < ROW_SIZE; i++)
                        {
                            for (int j = 0; j < COL_SIZE; j++)
                            {
                                gButtons[i][j].handleEvent( &e );
                            }
                        }
                        isWinning = checkWinning();
                    }

                    //Clear screen
                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                    SDL_RenderClear( gRenderer );

                    //Render background
                    gBackgroundTexture.render(0, 0);

                    //Render buttons
                    for( int i = 0; i < ROW_SIZE; i++ )
                    {
                        for ( int j = 0; j < COL_SIZE; j++ )
                        {
                            gButtons[i][j].render(i, j);
                        }
                    }
                    //Render mine/flag left
                    mineManager();


                    //Update screen
                    SDL_RenderPresent( gRenderer );
                }
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
	{
	    cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{

			cout << "Warning: Linear texture filtering not enabled!";
		}

		//Create window
		gWindow = SDL_CreateWindow( "Minesweeper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
			    cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
				success = false;
			}
			else
			{
				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
				    cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
					success = false;
				}

			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;


    if ( !gBackgroundTexture.loadFromFile( "assets/Background.png" ) )
    {
        cout << "Failed to load background texture!\n";
        success = false;
    }

	//Load sprites
	if( !gButtonSpriteSheetTexture.loadFromFile( "assets/Tiles.png" ) )
	{
		cout << "Failed to load sprites texture!\n";
		success = false;
	}
	else
    {
        //Set sprites
		for( int i = 0; i < SPRITE_TOTAL; i++ )
		{
			gSpriteClips[ i ].x = i * 32;
			gSpriteClips[ i ].y = 0;
			gSpriteClips[ i ].w = TILE_SIZE;
			gSpriteClips[ i ].h = TILE_SIZE;
		}
		//Set buttons position
		for (int i = 0; i < ROW_SIZE; i++)
        {
            for (int j = 0; j < COL_SIZE; j++)
            {
                gButtons[i][j].setPosition(j * TILE_SIZE + DISTANCE_BETWEEN, i * TILE_SIZE + DISTANCE_BETWEEN);
            }
        }
    }


	return success;
}

void createTableWithMine ()
{
    srand(time(NULL));
    int mine = 0;
    for (int i = 0; i < ROW_SIZE; i++)
    {
        for (int j = 0; j < COL_SIZE; j++)
        {
            sBoard[i][j] = 10;
            board[i][j] = 0;
        }
    }
    while (mine < MINE_COUNT)
    {
        int i = rand() % ROW_SIZE;
        int j = rand() % COL_SIZE;
        if ( board[i][j] == 9 )
        {
            continue;
        }
        else
        {
            board[i][j] = 9;
            mine++;
            if (board[i-1][j] != 9 && i > 0)
                board[i-1][j]++;
            if (board[i][j-1] != 9 && j > 0)
                board[i][j-1]++;
            if (board[i+1][j] != 9 && i < ROW_SIZE - 1)
                board[i+1][j]++;
            if (board[i][j+1] != 9 && j < COL_SIZE - 1)
                board[i][j+1]++;
            if (board[i-1][j-1] != 9 && i > 0 && j > 0)
                board[i-1][j-1]++;
            if (board[i-1][j+1] != 9 && i > 0 && j < COL_SIZE - 1)
                board[i-1][j+1]++;
            if (board[i+1][j-1] != 9 && j > 0 && i < ROW_SIZE - 1)
                board[i+1][j-1]++;
            if (board[i+1][j+1] != 9 && i < ROW_SIZE - 1 && j < COL_SIZE - 1)
                board[i+1][j+1]++;
        }
    }
}

bool checkWinning ()
{
    bool win = false;
    if (countTileLeft == MINE_COUNT)
    {
        win = true;
    }
    return win;
}

void mineManager()
{
    //Render text
    if ( !gameOver && !isWinning )
    {
        //Set text color
        SDL_Color textColor = { 140, 140, 140, 255 };

        //Erase the buffer
        mineLeft.str ( "" );
        mineLeft << "Mine left: " << countMineLeft;

        //Render text
        gMineLeftTexture.render( ( SCREEN_WIDTH - gMineLeftTexture.getWidth() ) / 2, 0 );
    }
}

void flagManager()
{
    //Check if win
    if ( isWinning && !gameOver )
    {
        //Update screen
        SDL_RenderPresent( gRenderer );

        //Delay loading screen
        SDL_Delay(500);
    }

    //Check if lose
    if ( gameOver )
    {
        //Render game over text
        gTextTexture.render( ( SCREEN_WIDTH - gTextTexture.getWidth() ) / 2, 0 );


        for( int i = 0; i < ROW_SIZE; i++ )
        {
            for ( int j = 0; j < COL_SIZE; j++ )
            {
                sBoard[i][j] = board[i][j];
                gButtons[i][j].render(i, j);
            }
        }
    }
}



void close()
{
	//Free loaded images
	gButtonSpriteSheetTexture.free();
	gMineLeftTexture.free();
	gBackgroundTexture.free();
	gTextTexture.free();



	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

