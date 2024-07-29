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

    bool turnTaken;

    switch (level)
    {
    case 4:
        turnTaken = levelFour();
        break;
    case 3:
        turnTaken = levelThree();
        break;
    case 2:
        turnTaken = levelTwo();
        break;
    default:
        turnTaken = levelOne();
        break;
    }

    return turnTaken;
}

bool ComputerPlayer::levelOne() {
    std::unique_ptr<Piece> **pieces = board->cloneBoard();
    std::vector<std::unique_ptr<Piece>> myPieces {};

    for (int i = 0; i < board->getBoardDimension(); ++i) {
        for (int j = 0; j < board->getBoardDimension(); ++j) {
            if (pieces[i][j]->getColour() == colour) {
                myPieces.push_back(pieces[i][j]);
            }
        }
    }

    while (myPieces.size() > 0)
    {
        int randPiece = rand() % myPieces.size();

        std::vector<Coordinate::Coordinate> validMoves = myPieces[randPiece]->getValidMoves();

        if (validMoves.size() == 0) {
            myPieces.erase(myPieces.begin() + randPiece);
            continue;
        }

        int randMove = rand() % validMoves.size();

        bool turnTaken = board->takeTurn(myPieces[randPiece]->getPosition(), validMoves[randMove], colour);

        if (turnTaken)
            return true;
    }

    return false;
}

bool ComputerPlayer::levelOne() {
    std::unique_ptr<Piece> **pieces = board->cloneBoard();
    std::vector<std::unique_ptr<Piece>> myPieces {};

    for (int i = 0; i < board->getBoardDimension(); ++i) {
        for (int j = 0; j < board->getBoardDimension(); ++j) {
            if (pieces[i][j]->getColour() == colour) {
                myPieces.push_back(pieces[i][j]);
            }
        }
    }

    while (myPieces.size() > 0)
    {
        int randPiece = rand() % myPieces.size();

        std::vector<Coordinate::Coordinate> validMoves = myPieces[randPiece]->getValidMoves();

        if (validMoves.size() == 0) {
            myPieces.erase(myPieces.begin() + randPiece);
            continue;
        }

        int randMove = rand() % validMoves.size();

        bool turnTaken = board->takeTurn(myPieces[randPiece]->getPosition(), validMoves[randMove], colour);

        if (turnTaken)
            return true;
    }

    return false;
}