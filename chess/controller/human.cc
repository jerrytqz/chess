#include <iostream>
#include <string>
#include "human.h"
#include "../model/board.h"
#include "../shared/colour.h"
#include "../shared/coordinate.h"

HumanPlayer::HumanPlayer(Board* board, Colour colour) : board(board), colour(colour) {}

void HumanPlayer::takeTurn() {
    std::string action;
    std::cin >> action;

    bool validMoveMade = false;

    while (!validMoveMade) {
        if (action == "move") {
            std::string from, to;
            std::cin >> from >> to;

            if (!Coordinate::checkValidChess(from) || !Coordinate::checkValidChess(to)) {
                std::cout << "Invalid move, try again" << std::endl;
                continue;
            }

            board->takeTurn(Coordinate::chessToCartesian(from), Coordinate::chessToCartesian(to), colour);

            validMoveMade = true;
        }
        else if (action == "resign") {
            // TODO: Implement later
        }
        else {
            std::cout << "Invalid action, try again" << std::endl;
            continue;
        }
    }
}
