#include "textObserver.h"
#include <iostream>

void TextObserver::notify() { //this method interfaces with std::cout
    Game::GameState gameState = game->getGameState();

    //print board
    for (int i = 0; i < gameState.boardDimension; i++) {
        for (int j = 0; j < gameState.boardDimension; j++) {
            int row = gameState.boardDimension - 1 - i;
            if (gameState.board[row][j] != nullptr) { //piece exists
                std::cout << gameState.board[row][j]->toChar();
            }
            else { //no piece
                bool isEvenRank = (row % 2 == 0);
                bool isEvenFile = (j % 2 == 0);

                if ((isEvenRank && isEvenFile) || (!isEvenRank && !isEvenFile)) {
                    std::cout << '_';
                } else {
                    std::cout << ' ';
                }
                }

                if (j == gameState.boardDimension - 1) { //last column in row
                    std::cout << '\n';
                }
        }
    }

    if (gameState.boardState == Board::BoardState::WhiteChecked) {
        std::cout << "White is in check.\n";
    }
    else if (gameState.boardState == Board::BoardState::BlackChecked) {
        std::cout << "Black is in check.\n";
    }
    else if (gameState.boardState == Board::BoardState::WhiteCheckmated) {
        std::cout << "Checkmate! Black wins!\n";
    }
    else if (gameState.boardState == Board::BoardState::BlackCheckmated) {
        std::cout << "Checkmate! White wins!\n";
    }
    else if (gameState.boardState == Board::BoardState::Stalemate) {
        std::cout << "Stalemate!\n";
    }
}
