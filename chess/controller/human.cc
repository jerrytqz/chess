#include <iostream>
#include <string>
#include "human.h"
#include "../model/board.h"
#include "../shared/colour.h"
#include "../shared/coordinate.h"

HumanPlayer::HumanPlayer(Board* board, Colour colour) : board(board), colour(colour) {}

bool HumanPlayer::takeTurn() {
    if (colour == Colour::White) {
        std::cout << "White's turn: ";
    }
    else {
        std::cout << "Black's turn: ";
    }

    while (true) {
        std::string action;
        std::cin >> action;
        if (action == "move") {
            std::string from, to;
            std::cin >> from >> to;

            if (!Coordinate::checkValidChess(from) || !Coordinate::checkValidChess(to)) {
                std::cout << "Invalid move, try again: ";
                continue;
            }

            if (!board->takeTurn(Coordinate::chessToCartesian(from), Coordinate::chessToCartesian(to), colour)) {
                std::cout << "Invalid move, try again: ";
                continue;
            }
            
            return true;
        }
        else if (action == "resign") {
            return false;
        }
        else {
            std::cout << "Invalid action, try again: ";
        }
    }
}
