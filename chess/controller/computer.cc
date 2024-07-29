#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "computer.h"
#include "../model/board.h"
#include "../shared/colour.h"
#include "../shared/coordinate.h"

ComputerPlayer::ComputerPlayer(Board* board, Colour colour, int level)
    : Player{board, colour}, level(level) {}

bool ComputerPlayer::takeTurn() {
    if (colour == Colour::White) {
        std::cout << "White's turn: ";
    }
    else {
        std::cout << "Black's turn: ";
    }

    switch (level)
    {
    case 4:
        levelFour();
        break;
    case 3:
        levelThree();
        break;
    case 2:
        levelTwo();
        break;
    default:
        levelOne();
        break;
    }

    return true;
}

void ComputerPlayer::levelOne() {
    std::unique_ptr<Piece> **pieces = board->cloneBoard();
    std::vector<std::unique_ptr<Piece>> myPieces {};

    for (int i = 0; i < board->getBoardDimension(); ++i) {
        for (int j = 0; j < board->getBoardDimension(); ++j) {
            if (pieces[i][j]->getColour() == colour) {
                myPieces.push_back(std::move(pieces[i][j]));
            }
        }
    }

    int randPiece = rand() % myPieces.size();

    std::vector<Coordinate::Coordinate> validMoves = myPieces[randPiece]->getValidLegalMoves();

    int randMove = rand() % validMoves.size();

    board->takeTurn(myPieces[randPiece]->getPosition(), validMoves[randMove], colour);
}

void ComputerPlayer::levelTwo() {

}

void ComputerPlayer::levelThree() {

}

void ComputerPlayer::levelFour() {
    
}
