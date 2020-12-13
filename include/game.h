#ifndef GAME_H_
#define GAME_H_

// N x N Board
const int N = 3;

// board states
enum BoardStates {
    Empty, P1_Spot, P2_Spot
};

// current player
enum CurrentStates {
    P1_Plays, P2_Plays, GameOver
};

// game state
enum GameStates {
    P1_Won, P2_Won, Tie, Playing
};

// game state structure
struct GameData {
    BoardStates board[N * N];
    CurrentStates current;
    GameStates state;
};

// update game state
void updateGame(int click_x, int click_y, GameData& game_in);

#endif // GAME_H_
