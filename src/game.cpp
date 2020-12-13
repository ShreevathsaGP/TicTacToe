#include <iostream>
#include "game.h"
#include "constants.h"

using namespace std;
void printBoard(const GameData& game_in) {
    // print game board
    cout << "[ ";
    for (int i = 0; i < (N*N); i++) {
        cout << game_in.board[i] << " ";
    }
    cout << "]" << endl;
}

// game state passed in by reference
void updateGame(int click_x, int click_y, GameData& game_in) {
    if (game_in.state != Playing) {
        /* cout << game_in.state << endl; */
        for (int i = 0; i < (N*N); i++) {
            game_in.board[i] = Empty;
        }

        game_in.current = P1_Plays;
        game_in.state = Playing;
        return;
    }

    int row;
    int column;
    BoardStates box_clicked;

    // which row was clicked?
    if (0 < click_y && click_y < WINDOW_HEIGHT/3) {
        // row [0]
        row = 0;
    } else if (WINDOW_HEIGHT/3 < click_y && click_y< (WINDOW_HEIGHT/3) * 2) {
        // row [1]
        row = 1;
    } else if ((WINDOW_HEIGHT/3) * 2 < click_y && click_y < WINDOW_HEIGHT) {
        // row [2]
        row = 2; 
    } else {
        return;
    }

    // which column was clicked?
    if (0 < click_x && click_x < WINDOW_WIDTH/3) {
        // column[0]
        column = 0;
    } else if (WINDOW_WIDTH/3 < click_x && click_x< (WINDOW_WIDTH/3) * 2) {
        // column[1]
        column = 1;
    } else if ((WINDOW_WIDTH/3) * 2 < click_x && click_x < WINDOW_WIDTH) {
        // column[2]
        column = 2;
    } else {
        return;
    }

    box_clicked = game_in.board[(N * row) + column];

    if (box_clicked != Empty) { return; }

    // switch over the player
    switch (game_in.current) {
        case P1_Plays:
            /* cout << "player 1 played" << endl; */
            game_in.board[(N * row) + column] = P1_Spot;
            game_in.current = P2_Plays;
            break;
        
        case P2_Plays:
            /* cout << "player 2 played" << endl; */
            game_in.board[(N * row) + column] = P2_Spot;
            game_in.current = P1_Plays;
            break;

        default: { return; }
    }
    /* printBoard(game_in); */

    // check for win, tie, or still playing?

    // row -> 0
    if ((game_in.board[0] == game_in.board[1] && game_in.board[1] == game_in.board[2]) && game_in.board[0] != Empty) {
        if (game_in.board[0] == P1_Spot) {
            game_in.state = P1_Won;
        } else {
            game_in.state = P2_Won;
        }
        return;
    }

    // row -> 1
    if ((game_in.board[3] == game_in.board[4] && game_in.board[4] == game_in.board[5]) && game_in.board[3] != Empty) {
        if (game_in.board[3] == P1_Spot) {
            game_in.state = P1_Won;
        } else {
            game_in.state = P2_Won;
        }
        return;
    }
    
    // row -> 2
    if ((game_in.board[6] == game_in.board[7] && game_in.board[7] == game_in.board[8]) && game_in.board[6] != Empty) {
        if (game_in.board[6] == P1_Spot) {
            game_in.state = P1_Won;
        } else {
            game_in.state = P2_Won;
        }
        return;
    }

    // column -> 0
    if ((game_in.board[0] == game_in.board[3] && game_in.board[3] == game_in.board[6]) && game_in.board[0] != Empty) {
        if (game_in.board[0] == P1_Spot) {
            game_in.state = P1_Won;
        } else {
            game_in.state = P2_Won;
        }
        return;
    }

    // column -> 1
    if ((game_in.board[1] == game_in.board[4] && game_in.board[4] == game_in.board[7]) && game_in.board[1] != Empty) {
        if (game_in.board[1] == P1_Spot) {
            game_in.state = P1_Won;
        } else {
            game_in.state = P2_Won;
        }
        return;
    }

    // column -> 2
    if ((game_in.board[2] == game_in.board[5] && game_in.board[5] == game_in.board[8]) && game_in.board[2] != Empty) {
        if (game_in.board[2] == P1_Spot) {
            game_in.state = P1_Won;
        } else {
            game_in.state = P2_Won;
        }
        return;
    }

    // diagonal -> 0
    if ((game_in.board[0] == game_in.board[4] && game_in.board[4] == game_in.board[8]) && game_in.board[0] != Empty) {
        if (game_in.board[0] == P1_Spot) {
            game_in.state = P1_Won;
        } else {
            game_in.state = P2_Won;
        }
        return;
    }

    // diagonal -> 1
    if ((game_in.board[2] == game_in.board[4] && game_in.board[4] == game_in.board[6]) && game_in.board[2] != Empty) {
        if (game_in.board[2] == P1_Spot) {
            game_in.state = P1_Won;
        } else {
            game_in.state = P2_Won;
        }
        return;
    }
    
    // tie?
    bool not_empty = true;
    for (int i = 0; i < (N*N); i++) {
        if (game_in.board[i] == Empty) {
            not_empty = false;
            break;
        }
    }

    if (not_empty) {
        game_in.state = Tie;
        game_in.current = GameOver;
        /* cout << "tied" << endl; */
    }
}
