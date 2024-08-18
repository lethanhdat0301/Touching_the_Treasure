#include "function.h"

vector<vector<LButton>> Buttons(3, vector<LButton>(2));

LTimer timer;

Uint32 startTime;
Uint32 remainingTime = 60000;
bool timerRunning = false;

bool init()
{
	// Initialization flag
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
		success = false;
	}
	else
	{
		// Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{

			cout << "Warning: Linear texture filtering not enabled!";
		}

		// Create window
		gWindow = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
			success = false;
		}
		else
		{
			// Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
				success = false;
			}
			else
			{
				// Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
					success = false;
				}

				// Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
					success = false;
				}

				// Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	// Loading success flag
	bool success = true;

	// Open the font
	gGameOver = TTF_OpenFont("Font/DTM-Sans.ttf", 40);
	if (gGameOver == NULL)
	{
		cout << "Failed to load DTM-Sans font! SDL_ttf Error: " << TTF_GetError() << endl;
		success = false;
	}
	else
	{
		// Render text
		SDL_Color textColor = {140, 140, 140};
		if (!gTextTexture.loadFromRenderedText("GAME OVER!", textColor))
		{
			cout << "Failed to render text texture!\n";
			success = false;
		}
	}

	// Load scene

	if (!gWinningTexture.loadFromFile("assets/Winner.png"))
	{
		cout << "Failed to load winning texture!\n";
		success = false;
	}
	if (!gBackgroundTexture.loadFromFile("assets/Background.png"))
	{
		cout << "Failed to load background texture!\n";
		success = false;
	}

	// Load sprites
	if (!gButtonSpriteSheetTexture.loadFromFile("assets/s.jpg"))
	{
		cout << "Failed to load sprites texture!\n";
		success = false;
	}

	if (!gHomeButton.loadFromFile("assets/home.png"))
	{
		cout << "Failed to load home button!\n";
		success = false;
	}

	if (!gMenuTheme.loadFromFile("assets/menuTheme.png"))
	{
		cout << "Failed to load menu theme!\n";
		success = false;
	}
	else
	{
		// Set sprites
		for (int i = 0; i < SPRITE_TOTAL; i++)
		{
			gSpriteClips[i].x = i * 32;
			gSpriteClips[i].y = 0;
			gSpriteClips[i].w = TILE_SIZE;
			gSpriteClips[i].h = TILE_SIZE;
		}
		// Set buttons position
		/*for (int i = 0; i < ROW_SIZE; i++)
		{
			for (int j = 0; j < COL_SIZE; j++)
			{
				gButtons[i][j].setPosition(j * TILE_SIZE + DISTANCE_BETWEEN, i * TILE_SIZE + DISTANCE_BETWEEN);
			}
		}*/
	}

	// Load sound effects
	winner = Mix_LoadMUS("Sounds/winner.mp3");
	if (winner == NULL)
	{
		cout << "Failed to load winner sound effect! SDL_mixer Error: " << Mix_GetError() << endl;
		success = false;
	}

	loser = Mix_LoadMUS("Sounds/loser.wav");
	if (loser == NULL)
	{
		cout << "Failed to load loser sound effect! SDL_mixer Error: " << Mix_GetError() << endl;
		success = false;
	}

	click = Mix_LoadWAV("Sounds/click.wav");
	if (click == NULL)
	{
		cout << "Failed to load click sound effect! SDL_mixer Error: " << Mix_GetError() << endl;
		success = false;
	}

	return success;
}

bool loadMenuMedia()
{
	bool success = true;
	// load background of menu
	if (!gMenuTheme.loadFromFile("//assets//menuTheme.png"))
	{
		printf("Fail!");
		success = false;
	}

	return success;
}

void createTableWithMine()
{
	srand(time(0));
	int mine = 0;
	int heartCount = 1;
	// Initialization
	for (int i = 0; i < BOARD_SIZE_X; i++)
	{
		for (int j = 0; j < BOARD_SIZE_Y; j++)
		{
			sBoard[i][j] = 10;
			board[i][j] = 0;
		}
	}

	while (heartCount > 0)
	{
		int i = rand() % BOARD_SIZE_X;
		int j = rand() % BOARD_SIZE_Y;
		if (board[i][j] == 0)
		{
			board[i][j] = 12; // Đặt trái tim ở vị trí này
			heartCount--;
		}
	}

	// Random mines in board
	while (mine < MINE_COUNT)
	{
		int i = rand() % BOARD_SIZE_X;
		int j = rand() % BOARD_SIZE_Y;
		if (board[i][j] == 9 || board[i][j] == 12)
			continue;
		board[i][j] = 9;
		mine++;
	}

	// Calculate the number of mines around each cell
	for (int i = 0; i < BOARD_SIZE_X; i++)
	{
		for (int j = 0; j < BOARD_SIZE_Y; j++)
		{
			if (board[i][j] == 9 || board[i][j] == 12)
				continue;
			for (int x = -1; x <= 1; x++)
			{
				for (int y = -1; y <= 1; y++)
				{
					int xpos = i + x;
					int ypos = j + y;
					if (xpos < 0 || xpos > BOARD_SIZE_X - 1 || ypos < 0 || ypos > BOARD_SIZE_Y - 1)
						continue;
					if (board[xpos][ypos] == 9)
						board[i][j]++;
				}
			}
		}
	}
}

void setButtonPosition()
{
	for (int i = 0; i < BOARD_SIZE_X; ++i)
	{
		for (int j = 0; j < BOARD_SIZE_Y; ++j)
		{
			Buttons[i][j].setPosition(j * TILE_SIZE + distance_y, i * TILE_SIZE + distance_x);
		}
	}
}

void handleEvent()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		// User requests quit
		if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
		{
			mainLoop = false;
			isRunning = false;
		}

		// Home button
		if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
		{
			int x, y;
			SDL_GetMouseState(&x, &y);

			bool homeInside = (x >= 0 && x <= 0 + gHomeButton.getWidth() &&
							   y >= 0 && y <= 0 + gHomeButton.getHeight());

			if (homeInside)
			{
				isRunning = false;
				isChoosing = true;
				easy = false;
				medium = false;
				hard = false;
				exitGame = false;

				// SDL_RenderClear(gRenderer);
				SDL_SetWindowSize(gWindow, SCREEN_WIDTH, SCREEN_HEIGHT);
				showModeChoice();
				// SDL_RenderPresent(gRenderer);
				break;
			}
		}

		// Handle button events
		for (int i = 0; i < BOARD_SIZE_X; i++)
		{
			for (int j = 0; j < BOARD_SIZE_Y; j++)
			{
				Buttons[i][j].handleEvent(&e);
			}
		}
	}
}

void renderGame()
{
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	SDL_Rect destRect = {0, 0, 1000, SCREEN_HEIGHT};
	SDL_RenderCopy(gRenderer, gBackgroundTexture.getTexture(), NULL, &destRect);

	gHomeButton.render(0, 0);

	for (int i = 0; i < BOARD_SIZE_X; i++)
	{
		for (int j = 0; j < BOARD_SIZE_Y; j++)
		{
			Buttons[i][j].render(i, j);
		}
	}
}

bool checkWinning()
{
	bool win = false;
	if (countTileLeft == MINE_COUNT)
	{
		timer.pause();
		win = true;
	}
	return win;
}

void mineManager(int dx)
{
	// Render text
	if (!gameOver && !isWinning)
	{
		// Set text color
		SDL_Color textColor = {140, 140, 140, 255};

		// Erase the buffer for "Mine left:"
		mineLeft.str("");
		mineLeft << "Mine left:";
		if (!gMineLeftTexture.loadFromRenderedText(mineLeft.str().c_str(), textColor))
		{
			cout << "Unable to render mine left texture!\n";
		}

		// Erase the buffer for countMineLeft
		mineLeft.str("");
		mineLeft << countMineLeft;
		if (!gCountMineLeftTexture.loadFromRenderedText(mineLeft.str().c_str(), textColor))
		{
			cout << "Unable to render count mine left texture!\n";
		}

		// Render "Mine left:" text
		// gMineLeftTexture.render((SCREEN_WIDTH - gMineLeftTexture.getWidth()) / 2, 0);

		// Render countMineLeft text below "Mine left:"
		// gCountMineLeftTexture.render((SCREEN_WIDTH - gCountMineLeftTexture.getWidth()) / 2, gMineLeftTexture.getHeight() - 10);

		// Render "Mine left:" text
		int s = dx - (gMineLeftTexture.getWidth() + 100 + gCountMineLeftTexture.getWidth());
		gMineLeftTexture.render(s / 2, 0);

		// Render countMineLeft text below "Mine left:"
		gCountMineLeftTexture.render(s / 2 + gMineLeftTexture.getWidth() / 2 - gCountMineLeftTexture.getWidth() / 2, gMineLeftTexture.getHeight() - 10);
	}
}

void flagManager(int dx)
{
	// Check if win
	if (isWinning && !gameOver)
	{
		// Update screen
		SDL_RenderPresent(gRenderer);

		// Delay loading screen
		SDL_Delay(500);

		// Play victory music
		Mix_PlayMusic(winner, 0);

		// Render winning scene
		gWinningTexture.render(0, 0);
	}

	// Check if lose
	if (gameOver)
	{

		int s = (dx - gTextTexture.getWidth()) / 2;
		// Render game over text
		gTextTexture.render(s, 10);

		// Play losing music
		Mix_PlayMusic(loser, 0);

		for (int i = 0; i < BOARD_SIZE_X; i++)
		{
			for (int j = 0; j < BOARD_SIZE_Y; j++)
			{
				sBoard[i][j] = board[i][j];
				Buttons[i][j].render(i, j);
			}
		}
	}
}

std::string getTime()
{
	stringstream Time{};
	if (isWinning == true)
	{
		int n = timer.getTicks() / 1000;
		int h, m, s;
		h = n / 3600;
		m = (n - h * 3600) / 60;
		s = (n - h * 3600 - m * 60);
		Time.str("");
		Time << h << ":" << m << ":" << s;
		return Time.str();
	}
}

void timeRender(int n, int xPos, int dx)
{
	if (!gameOver && !isWinning)
	{
		SDL_Color textColor = {140, 140, 140, 255};

		// Erase the buffer for "Time:"
		timeText.str("");
		timeText << "Time :";
		if (!gTimeText.loadFromRenderedText(timeText.str().c_str(), textColor))
		{
			cout << "Unable to render time text texture!\n";
		}

		// Erase the buffer for time Text
		timeText.str("");
		timeText << n;
		if (!gTime.loadFromRenderedText(timeText.str().c_str(), textColor))
		{
			cout << "Unable to render time texture!\n";
		}

		int s = dx - (gMineLeftTexture.getWidth() + 100 + gCountMineLeftTexture.getWidth());

		// Render "Time:" text
		gTimeText.render(s / 2 + 50 + gMineLeftTexture.getWidth(), 0);

		// Render time text at the specified position
		gTime.render(xPos, gTimeText.getHeight() - 10);
	}
}

void TimeManager(int screen_width)
{
	int n = timer.getTicks() / 1000;
	int s = screen_width - (gMineLeftTexture.getWidth() + 100 + gCountMineLeftTexture.getWidth());
	int xPos = s / 2 + 50 + gMineLeftTexture.getWidth() + gTimeText.getWidth() / 2 - gTime.getWidth() / 2;

	if (n < 10)
	{
		timeRender(n, xPos, screen_width);
	}
	else
	{
		int digits[10]; // Array to store digits
		int i = 0;

		// Extract digits from n and store them in reverse order
		while (n > 0)
		{
			digits[i++] = n % 10;
			n /= 10;
		}

		// Render digits in correct order
		for (int j = i - 1; j >= 0; j--)
		{
			timeRender(digits[j], xPos - 10, screen_width);
			xPos += 20; // Move x position for the next digit
		}
	}
}

void renderMenu()
{
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	SDL_Rect destRect;
	destRect.x = 0;
	destRect.y = 0;
	destRect.w = SCREEN_WIDTH;	// Set width to screen width
	destRect.h = SCREEN_HEIGHT; // Set height to screen height

	// Render the texture to cover the entire screen
	SDL_RenderCopy(gRenderer, gMenuTheme.getTexture(), NULL, &destRect);

	SDL_Color textColor = {0, 0, 0, 255};
	// Render "Easy" button
	gEasyChoice.loadFromRenderedText("Easy", textColor);
	gEasyChoice.render(75, 640);

	// Render "Medium" button
	gMediumChoice.loadFromRenderedText("Medium", textColor);
	gMediumChoice.render(200, 640);

	// Render "Hard" button
	gHardChoice.loadFromRenderedText("Hard", textColor);
	gHardChoice.render(375, 640);

	// Render "Exit" button
	gExitButton.loadFromRenderedText("Exit", textColor);
	gExitButton.render(550, 640);
}

void showModeChoice()
{
	bool easyInside = false;
	bool mediumInside = false;
	bool hardInside = false;
	bool exitInside = false;
	renderMenu();

	SDL_Event event;

	while (isChoosing)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				mainLoop = false;
				isChoosing = false;
			}
			if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);

				// Kiểm tra xem chuột có đang ở trong phạm vi các lựa chọn không
				easyInside = (x > 75 && x < 75 + gEasyChoice.getWidth() && y > 640 && y < 640 + gEasyChoice.getHeight());
				mediumInside = (x > 200 && x < 200 + gMediumChoice.getWidth() && y > 640 && y < 640 + gMediumChoice.getHeight());
				hardInside = (x > 375 && x < 375 + gHardChoice.getWidth() && y > 640 && y < 640 + gHardChoice.getHeight());
				exitInside = (x > 550 && x < 550 + gExitButton.getWidth() && y > 640 && y < 640 + gExitButton.getHeight());

				if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
				{
					if (easyInside)
					{
						timer.start();
						isRunning = true;
						timerRunning = false;
						isChoosing = false;
						easy = true;
						medium = false;
						hard = false;
						exitGame = false;
						SDL_SetWindowSize(gWindow, 450, 450);
						setGameMode(9, 9, 10, 90, 81, BOARD_SIZE_X, BOARD_SIZE_Y, MINE_COUNT, countMineLeft, countTileLeft, distance_x, distance_y);
						createTableWithMine();
					}
					else if (mediumInside)
					{
						timer.start();
						timerRunning = false;
						isRunning = true;
						isChoosing = false;
						easy = false;
						medium = true;
						hard = false;
						exitGame = false;
						SDL_SetWindowSize(gWindow, 600, 600);
						setGameMode(12, 12, 30, 100, 108, BOARD_SIZE_X, BOARD_SIZE_Y, MINE_COUNT, countMineLeft, countTileLeft, distance_x, distance_y);
						createTableWithMine();
					}
					else if (hardInside)
					{
						startTime = SDL_GetTicks();
						timerRunning = true;
						isRunning = true;
						isChoosing = false;
						easy = false;
						medium = false;
						hard = true;
						exitGame = false;
						SDL_SetWindowSize(gWindow, 700, 700);

						setGameMode(16, 16, 50, 100, 94, BOARD_SIZE_X, BOARD_SIZE_Y, MINE_COUNT, countMineLeft, countTileLeft, distance_x, distance_y);
						createTableWithMine();
					}
					else if (exitInside)
					{
						isRunning = false;
						isChoosing = false;
						easy = false;
						medium = false;
						hard = false;
						exitGame = true;
						mainLoop = false;

						SDL_QUIT;
						exit(0);
					}
				}
			}
		}
		// Cập nhật màn hình
		SDL_RenderPresent(gRenderer);
	}
}

void setGameMode(int x, int y, int n, int dx, int dy, int &BOARD_SIZE_X, int &BOARD_SIZE_Y, int &NumberOfMines, int &mineCountLeft, int &CountTileLeft, int &distance_x, int &distance_y)
{
	BOARD_SIZE_X = x;
	BOARD_SIZE_Y = y;
	NumberOfMines = n;
	mineCountLeft = n;
	CountTileLeft = x * y;
	distance_x = dx;
	distance_y = dy;

	// Tính toán khoảng cách từ cạnh trái và trên của màn hình tới bảng chơi game

	Buttons.resize(BOARD_SIZE_X);
	for (int i = 0; i < BOARD_SIZE_X; i++)
	{
		Buttons[i].resize(BOARD_SIZE_Y);
	}
	sBoard.resize(BOARD_SIZE_X);
	for (int i = 0; i < BOARD_SIZE_X; i++)
	{
		sBoard[i].resize(BOARD_SIZE_Y);
	}
	board.resize(BOARD_SIZE_X);
	for (int i = 0; i < BOARD_SIZE_X; i++)
	{
		board[i].resize(BOARD_SIZE_Y);
	}
}

void startTimer()
{
	startTime = SDL_GetTicks(); // Lưu thời gian hiện tại (tính bằng milliseconds)
	timerRunning = true;
}

void updateTimer()
{
	if (timerRunning)
	{
		Uint32 currentTime = SDL_GetTicks();
		Uint32 elapsedTime = currentTime - startTime;
		remainingTime = 60000 - elapsedTime; // Giả sử bạn muốn đếm ngược 60 giây

		if (remainingTime <= 0)
		{
			remainingTime = 0;
			timerRunning = false;
		}
	}
}

void renderTime(int dx)
{
	if (!gameOver && !isWinning)
	{
		SDL_Color textColor = {140, 140, 140, 255};

		// Erase the buffer for "Time:"
		timeText.str("");
		timeText << "Time :";
		if (!gTextTime.loadFromRenderedText(timeText.str().c_str(), textColor))
		{
			cout << "Unable to render time text texture!\n";
		}
		int s = dx - (gMineLeftTexture.getWidth() + 100 + gCountMineLeftTexture.getWidth());
		gTextTime.render(s / 2 + 50 + gMineLeftTexture.getWidth(), 0);

		int seconds = remainingTime / 1000;
		int milliseconds = remainingTime % 1000;
		std::string timeText = std::to_string(seconds) + "." + std::to_string(milliseconds / 100);

		SDL_Surface *textSurface = TTF_RenderText_Solid(gGameOver, timeText.c_str(), textColor);
		SDL_Texture *textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);

		int textWidth = textSurface->w;
		int textHeight = textSurface->h;
		SDL_Rect renderQuad = {s / 2 + 50 + gMineLeftTexture.getWidth() + gTextTime.getWidth() / 2 - textWidth / 2, gTextTime.getHeight() - 10, textWidth, textHeight};

		SDL_RenderCopy(gRenderer, textTexture, NULL, &renderQuad);

		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(textTexture);
	}
}



void close()
{
	// Free loaded images
	gButtonSpriteSheetTexture.free();
	gMineLeftTexture.free();
	gBackgroundTexture.free();
	gWinningTexture.free();
	gTextTexture.free();
	gMenuTheme.free();
	gCountMineLeftTexture.free();
	gTime.free();
	gTimeText.free();
	gMenu.free();
	gMenu1.free();
	gEasyChoice.free();
	gMediumChoice.free();
	gHardChoice.free();
	gExitButton.free();
	gHomeButton.free();
	gTextTime.free();

	// Free global font
	TTF_CloseFont(gGameOver);
	gGameOver = NULL;

	// Free the sound effects
	Mix_FreeMusic(winner);
	Mix_FreeMusic(loser);
	Mix_FreeChunk(click);
	winner = NULL;
	loser = NULL;
	click = NULL;

	// Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	// Quit SDL subsystems
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
