#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <sstream>
#include <string>
#include "Texture.h"
#include "Constants.h"
#include "Variables.h"
#include "Timer.h"
#include "function.h"

using namespace std;

int main(int argc, char *args[])
{
	if (!init())
	{
		std::cout << "Failed to initialize SDL! SDL_Error: " << SDL_GetError() << std::endl;
		return -1;
	}
	else
	{
		if (!loadMedia())
		{
			std::cout << "Failed to load media!" << std::endl;
			return -1;
		}
		else
		{

			bool quit = false;

			if (loadMenuMedia)
			{
				while (!quit)
				{

					while (mainLoop)
					{

						if (isChoosing)
						{
							showModeChoice();
						}

						while (isRunning)
						{
							SDL_RenderClear(gRenderer);
							handleEvent();
							setButtonPosition();
							// timer.start();

							while (!gameOver && !quit && !isWinning)
							{
								handleEvent();
								isWinning = checkWinning();

								renderGame();

								int width, height;
								SDL_GetWindowSize(gWindow, &width, &height);

								mineManager(width);
								flagManager(width);

								if (easy || medium)
								{
									TimeManager(width);
								}
								if (hard)
								{
									updateTimer();
									renderTime(width);
								}

								SDL_RenderPresent(gRenderer);
							}

						}
					}
				}
			}
		}
	}

	close();
	return 0;
}
