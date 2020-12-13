#include <iostream>
#include "SDL2/SDL.h"
#include "graphics.h"
#include "constants.h"
#include "game.h"

using namespace std;

int main() {
    // initialize all components
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Tic-Tac-Toe", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // setup game data
    GameData* game = new GameData();
    for (int i = 0; i < (N*N); i++) { game -> board[i] = Empty; } // set board empty
    game -> current = P1_Plays;
    game -> state = Playing;

    // mouse data
    int mouse_x;
    int mouse_y;

    // set up graphical bounds
    setBounds(); 
    
    // game loop
    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                // x button
                case SDL_QUIT:
                    running = false;

                // keyboard
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            running = false;
                        default: {}
                    }

                // mouse
                case SDL_MOUSEBUTTONDOWN:
                    switch (event.button.button) {
                        // left click
                        case SDL_BUTTON_LEFT:
                            SDL_GetMouseState(&mouse_x, &mouse_y); // pass by reference
                            updateGame(mouse_x, mouse_y, *game);

                        default: {}
                    }

                default: {}
            }
        }

        // clear the window to black
        SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
        SDL_RenderClear(renderer);

        //---------------------------------------------------------------------------------------------------
        drawGrid(window, renderer);
        renderGame(window, renderer, *game);
        //---------------------------------------------------------------------------------------------------

        // present the back buffer
        SDL_RenderPresent(renderer); 
    }
    
    // clean it up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
