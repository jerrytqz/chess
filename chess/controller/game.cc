#include "game.h"

Game::Game(Board* board, Player* whitePlayer, Player* blackPlayer): board{board}, whitePlayer{whitePlayer}, blackPlayer{blackPlayer} {
    //no need for implementation
}

Game::~Game() {
    delete board;
    delete whitePlayer; //REMEMBER TO DELETE PLAYERS DURING UPDATEPLAYER TOO
    delete blackPlayer;
}

// void Game::setUp() {

// }

// void Game::play() {

// }

void Game::updatePlayer(Colour colour, Player* player) {
    if (colour == Colour::Black) {
        blackPlayer = player;
    }
    else { //replace white player
        whitePlayer = player;
    }
}

void Game::detachObserver(Observer* obs) {
    //find where observer is in list and delete it
    for (auto it = observers.begin(); it != observers.end(); it++) {
        if (*it == obs) {
            observers.erase(it);
            return;
        }
    }
}

void Game::attachObserver(Observer* obs) {
    observers.push_back(obs); //not our fault if observer is included more than once
}

Game::GameState Game::getGameState() {
    // return GameState {
    //     whiteScore,
    //     blackScore,
    //     currentTurn,
    //     board->getBoardDimension(),

    //     board->getBoardState(),
    // };
}

// void Game::notifyObservers() {

// }
