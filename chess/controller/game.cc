#include "game.h"

Game::Game(Board* board, Player* whitePlayer, Player* blackPlayer): board{board}, whitePlayer{whitePlayer}, blackPlayer{blackPlayer} {

}

Game::~Game() {
    delete board;
    delete whitePlayer; //REMEMBER TO DELETE PLAYERS DURING UPDATEPLAYER TOO
    delete blackPlayer;
}