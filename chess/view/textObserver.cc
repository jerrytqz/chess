#include "textObserver.h"
#include <iostream>

void TextObserver::notify() { //this method interfaces with std::cout
    Game::GameState gameState = game->getGameState();

    //print board
    for (int i = 0; i < gameState.boardDimension; i++) {
        std::cout << 8 - i << " ";
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
                    std::cout << std::endl;
                }
        }
    }

    std::cout << std::endl;
    std::cout << "  ";
    for (int i = 0; i < gameState.boardDimension; i++) {
        std::cout << static_cast<char>('a' + i);
    }
    std::cout << std::endl;

    if (gameState.boardState == Board::BoardState::WhiteChecked) {
        std::cout << "White is in check.";
    }
    else if (gameState.boardState == Board::BoardState::BlackChecked) {
        std::cout << "Black is in check.";
    }
    else if (gameState.boardState == Board::BoardState::WhiteCheckmated) {
        std::cout << "Checkmate! Black wins!";
    }
    else if (gameState.boardState == Board::BoardState::BlackCheckmated) {
        std::cout << "Checkmate! White wins!";
    }
    else if (gameState.boardState == Board::BoardState::Stalemate) {
        std::cout << "Stalemate!";
    }
}
