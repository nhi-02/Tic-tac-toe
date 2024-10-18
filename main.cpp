#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "caro.cpp"
using namespace std;
const int WIDTH = 805, HEIGHT = 805;

int main(int argc, char *argv[])
{
    SDL_Surface *imageSurface = NULL;
    SDL_Surface *imageX = NULL;
    SDL_Surface *imageO = NULL;
    SDL_Surface *imageToDraw = NULL;
    SDL_Surface *windowSurface = NULL;
    char turn = 'x';

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
    }
    SDL_Window *window = SDL_CreateWindow("Hello SDL World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    windowSurface = SDL_GetWindowSurface(window);

    if (NULL == window)
    {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;

        return EXIT_FAILURE;
    }
    BoardGame bg(windowSurface);
    Cell c;
    SDL_Event event;
    imageSurface = IMG_Load("board.png");
    imageX = IMG_Load("x1.png");
    imageO = IMG_Load("o1.png");

    SDL_Rect area = {0, 0, 800, 800};
    SDL_Rect area2 = {0, 0, 50, 50};
    // Update the surface
    // SDL_UpdateWindowSurface(window);
    if (imageSurface == NULL)
    {
        std::cout << "SDL could not load image! SDL Error: " << SDL_GetError() << std::endl;
    }

    while (true)
    {
        if (SDL_PollEvent(&event))
        {
            if (SDL_QUIT == event.type)
            {
                break;
            }
            if (SDL_MOUSEBUTTONDOWN == event.type)
            {
                if (SDL_BUTTON_LEFT == event.button.button)
                {
                    int row, col;
                    col = event.button.x / 50;
                    row = event.button.y / 50;
                    // area2.x = col * 50;
                    // area2.y = row * 50;
                    bg.click(row, col);
                }
            }
        }
        // Update the surface
        SDL_UpdateWindowSurface(window);
    }

    SDL_FreeSurface(imageSurface);
    SDL_FreeSurface(windowSurface);

    imageSurface = NULL;
    windowSurface = NULL;

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
