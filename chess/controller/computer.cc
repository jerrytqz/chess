#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "computer.h"
#include "../model/board.h"
#include "../shared/colour.h"
#include "../shared/coordinate.h"

ComputerPlayer::ComputerPlayer(Board* board, Colour colour, int level)
    : Player{board, colour}, level(level), gen(rd()) {}

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
                myPieces.push_back(pieces[i][j]);
            }
        }
    }

    std::uniform_int_distribution<> pieceDist(0, myPieces.size() - 1);
    int randPiece = pieceDist(gen);

    std::vector<Coordinate::Coordinate> validMoves = myPieces[randPiece]->getValidMoves();

    std::uniform_int_distribution<> moveDist(0, validMoves.size() - 1);
    int randMove = moveDist(gen);

    board->takeTurn(myPieces[randPiece]->getPosition(), validMoves[randMove], colour);
}