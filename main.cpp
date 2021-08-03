#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include "maze.h"
// const
const int posX =450, posY = 30, width = 1000, height = 1000;

// code time 2 hours 20 min

int main(int argc, char* argv[]) {
    // the dimensions of the grid
    std::cout << "write the dimensions of the grid divisable by 10 and less than 100: ";
    int size;
    std::cin >> size;

    std::cout << "" << std::endl;

    // height of the square (interval)
    int interv = height / size;

    // the starting and ending points
    std::pair<int,int> start;
    std::pair<int,int> end;

    std::cout << "write the starting and ending points" << std::endl;

    std::cout << "Start: ";
    std::cin >> start.first >> start.second;
    std::cout << "" << std::endl;

    std::cout << "End: ";
    std::cin >> end.first >> end.second;

    /// initializes SDL
    SDL_Window* win = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO);

    win = SDL_CreateWindow("Hello World", posX, posY, width, height, 0);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    // background color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    // Clear the entire screen to our selected color.
    SDL_RenderClear(renderer);

    // sets color of line
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

    // creates the default squares
    for (int x = 0; x <= height; x+= interv){
        for (int y = 0; y <= height; y += interv){
            // adds the lines
            SDL_RenderDrawLine(renderer, x, y, x, height);
            SDL_RenderDrawLine(renderer, x, y, height, y);
        }
    }
    // draws an extra line for the bottom
    SDL_RenderDrawLine(renderer, 0, height-1, height-1,height-1);
    SDL_RenderDrawLine(renderer, height-1, 0, height-1,height-1);

    // draws the start and end
    SDL_Rect rect = {(start.first - 1)*interv, (start.second - 1)*interv, interv, interv};
    SDL_Rect rect2 = {(end.first - 1)*interv, (end.second - 1)*interv, interv, interv};

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 255, 34, 241, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect2);

    // updates the screen
    SDL_RenderPresent(renderer);

    // initializes maze class
    Maze maze = Maze(size,renderer, interv, start, end);


    return 0;
}
