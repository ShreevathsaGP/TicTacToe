#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "constants.h"
#include "game.h"

const int buffer_space = 7;
const int height = (WINDOW_HEIGHT / 3) - (buffer_space * 2);

// draw tic-tac-toe grid (3 x 3)
void drawGrid(SDL_Window* window, SDL_Renderer* renderer);

// game render function
void renderGame(SDL_Window* window, SDL_Renderer* renderer, const GameData& game_in);

struct Bounds {
    int x_left[N];
    int x_right[N];
    int y_top[N];
    int y_bottom[N];

    int y_centers[N];
};

void setBounds();
#endif // GRAPHICS_H_
