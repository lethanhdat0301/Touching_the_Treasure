#include <ctime>
#include "Button.h"

void reveal(int i, int j)
{
    if (sBoard[i][j] == 10 || sBoard[i][j] == 11)
    {
        if (sBoard[i][j] == 11)
        {
            return;
        }
        sBoard[i][j] = board[i][j];
        if (sBoard[i][j] != 9)
            countTileLeft--;
        if (sBoard[i][j] == 0)
        {
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    int xpos = i + x;
                    int ypos = j + y;
                    if (xpos < 0 || xpos > BOARD_SIZE_X - 1 || ypos < 0 || ypos > BOARD_SIZE_Y - 1)
                        continue;
                    reveal(xpos, ypos);
                }
            }
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

                // Set mouse clicked
                switch (e->button.button)
                {
                case SDL_BUTTON_LEFT:
                {
                    reveal(i, j);
                    if (board[i][j] == 9)
                    {
                        gameOver = true;
                    }
                    break;
                }
                case SDL_BUTTON_RIGHT:
                {
                    if (sBoard[i][j] >= 10)
                    {
                        if (sBoard[i][j] == 10)
                        {
                            if (countMineLeft == 0)
                                break;
                            sBoard[i][j] = 11;
                            countMineLeft--;
                        }
                        else
                        {
                            sBoard[i][j] = 10;
                            countMineLeft++;
                        }
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
