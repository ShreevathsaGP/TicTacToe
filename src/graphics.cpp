#include <iostream>
#include "SDL2/SDL.h"
#include "constants.h"
#include "game.h"
#include "graphics.h"
#include <cmath>

#define PI 3.14159

using namespace std;

Bounds bounds = Bounds();

void setBounds() {
    bounds.x_left[0] = buffer_space;
    bounds.x_left[1] = (WINDOW_WIDTH/3) + buffer_space;
    bounds.x_left[2] = ((WINDOW_WIDTH/3) * 2) + buffer_space;

    bounds.x_right[0] = (WINDOW_WIDTH/3) - buffer_space;
    bounds.x_right[1] = ((WINDOW_WIDTH/3) * 2) - buffer_space;
    bounds.x_right[2] = WINDOW_WIDTH - buffer_space;

    bounds.y_bottom[0] = (WINDOW_HEIGHT/3) - buffer_space;
    bounds.y_bottom[1] = ((WINDOW_HEIGHT/3) * 2) - buffer_space;
    bounds.y_bottom[2] = WINDOW_HEIGHT - buffer_space;

    bounds.y_top[0] = buffer_space;
    bounds.y_top[1] = (WINDOW_HEIGHT/3) + buffer_space;
    bounds.y_top[2] = ((WINDOW_HEIGHT/3) * 2) + buffer_space;

    bounds.y_centers[0] = (WINDOW_HEIGHT/3)/2;
    bounds.y_centers[1] = bounds.y_centers[0] * 3;
    bounds.y_centers[2] = WINDOW_HEIGHT - bounds.y_centers[0];
}

int row;
int column;
int center_x;
int center_y;
int radius;

// draw the grid
void drawGrid(SDL_Window* window, SDL_Renderer* renderer) {
    // set color white
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // draw vertical line #1
    for (int y = 0; y < WINDOW_HEIGHT; y++) {
        SDL_RenderDrawPoint(renderer, WINDOW_WIDTH / 3, y);
    }

    // draw verical line #2
    for (int y = 0; y < WINDOW_HEIGHT; y++) {
        SDL_RenderDrawPoint(renderer, (WINDOW_WIDTH / 3) * 2, y);
    }

    // draw horizontal line #1
    for (int x = 0; x < WINDOW_WIDTH; x++) {
        SDL_RenderDrawPoint(renderer, x, WINDOW_HEIGHT / 3);
    }

    // draw horizontal line #2
    for (int x = 0; x < WINDOW_WIDTH; x++) {
        SDL_RenderDrawPoint(renderer, x, (WINDOW_HEIGHT / 3) * 2);
    }
}

// render the game
void renderGame(SDL_Window* window, SDL_Renderer* renderer, const GameData& game_in) {
    // Theta(N) Time
    for (int i = 0; i < (N*N); i++) {
        // get box
        column = i % N;
        row = (i - column) / N;

        if (game_in.board[i] == Empty) { 
            continue; 
        }

        if (game_in.board[i] == P2_Spot) {

            switch (game_in.state) {
                case P1_Won:
                    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
                    break;
                case P2_Won:
                    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
                    break;
                default: 
                    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
            }
            
            // draw x
            SDL_RenderDrawLine(renderer, static_cast<int>(bounds.x_left[column]), static_cast<int>(bounds.y_bottom[row]),
                    static_cast<int>(bounds.x_right[column]), static_cast<int>(bounds.y_top[row]));
            SDL_RenderDrawLine(renderer, static_cast<int>(bounds.x_left[column]), static_cast<int>(bounds.y_top[row]),
                    static_cast<int>(bounds.x_right[column]), static_cast<int>(bounds.y_bottom[row]));
             
            continue;
        }
        
        switch (game_in.state) {
            case P1_Won:
                SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
                break;
            case P2_Won:
                SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
                break;
            default: 
                SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        }
        
        // base case -> draw circle
        center_x = (bounds.x_left[column] + bounds.x_right[column]) / 2;
        center_y = bounds.y_centers[row];
        radius = bounds.x_right[column] - center_x;
        
        for (int degrees = 0; degrees <= 360; degrees+= 1) {
            SDL_RenderDrawPoint(renderer, (center_x + (radius * sin((degrees * (PI/180))))), 
                    (center_y + (radius * cos((degrees * (PI/180))))));
        }
    }
}
