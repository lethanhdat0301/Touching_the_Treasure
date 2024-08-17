#include <ctime>
#include "Button.h"

void reveal(int i, int j)
{
    if (sBoard[i][j] == 10 || sBoard[i][j] == 11)
    {
        if (sBoard[i][j] == 11)
        {
            countMineLeft++;
        }
        sBoard[i][j] = board[i][j];
        countTileLeft--;

        // Kiểm tra nếu ô chứa trái tim (giá trị 12)
        if (sBoard[i][j] == 12)
        {
            // Reveal 8 ô xung quanh ô có trái tim
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    int newX = i + x;
                    int newY = j + y;

                    // Kiểm tra biên để tránh lỗi truy cập ngoài mảng
                    if (newX >= 0 && newX < BOARD_SIZE_X && newY >= 0 && newY < BOARD_SIZE_Y)
                    {
                        if (sBoard[newX][newY] == 10 || sBoard[newX][newY] == 11)
                        {
                            if (board[newX][newY] == 9)
                            {
                                countMineLeft--;
                            }
                            reveal(newX, newY); // Gọi hàm reveal để mở ô này
                        }
                    }
                }
            }
        }
        else if (sBoard[i][j] == 0) // Nếu ô là 0, tiếp tục reveal các ô liền kề
        {
            if (i < BOARD_SIZE_X - 1)
                reveal(i + 1, j);
            if (i > 0)
                reveal(i - 1, j);
            if (j < BOARD_SIZE_Y - 1)
                reveal(i, j + 1);
            if (j > 0)
                reveal(i, j - 1);
            if (i > 0 && j > 0)
                reveal(i - 1, j - 1);
            if (i < BOARD_SIZE_X - 1 && j < BOARD_SIZE_Y - 1)
                reveal(i + 1, j + 1);
            if (i > 0 && j < BOARD_SIZE_Y - 1)
                reveal(i - 1, j + 1);
            if (i < BOARD_SIZE_X - 1 && j > 0)
                reveal(i + 1, j - 1);
        }
    }
}

LButton::LButton()
{
    mPosition.x = 0;
    mPosition.y = 0;
}

void LButton::setPosition(int x, int y)
{
    mPosition.x = x;
    mPosition.y = y;
}

void LButton::handleEvent(SDL_Event *e)
{
    // If mouse event happened
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        // Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        int i = (y - distance_x) / TILE_SIZE;
        int j = (x - distance_y) / TILE_SIZE;

        // Check if mouse is in button
        bool inside = true;

        // Mouse is left of the button
        if (x < mPosition.x)
        {
            inside = false;
        }
        // Mouse is right of the button
        else if (x > mPosition.x + TILE_SIZE)
        {
            inside = false;
        }
        // Mouse above the button
        else if (y < mPosition.y)
        {
            inside = false;
        }
        // Mouse below the button
        else if (y > mPosition.y + TILE_SIZE)
        {
            inside = false;
        }

        // Mouse is inside button
        if (inside)
        {
            if (e->type == SDL_MOUSEBUTTONDOWN)
            {
                // Play the sound effect
                Mix_PlayChannel(-1, click, 0);
                // Set mouse clicked
                switch (e->button.button)
                {
                case SDL_BUTTON_LEFT:
                {
                    if (sBoard[i][j] != 9)
                    {
                        reveal(i, j);
                        if (board[i][j] == 9)
                        {
                            gameOver = true;
                        }
                    }
                    break;
                }
                case SDL_BUTTON_RIGHT:
                {
                    if (sBoard[i][j] == 10)
                    {
                        if (countMineLeft == 0)
                            break;
                        sBoard[i][j] = 11;
                        countMineLeft--;
                    }
                    else if (sBoard[i][j] == 11)
                    {
                        sBoard[i][j] = 10;
                        countMineLeft++;
                    }
                    break;
                }
                }
            }
        }
    }
}

void LButton::render(int i, int j)
{
    // Show current button sprite
    gButtonSpriteSheetTexture.render(mPosition.x, mPosition.y, &gSpriteClips[sBoard[i][j]]);
}
