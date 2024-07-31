#include <iostream>
#include <string>
#include <cctype>

#include "human.h"
#include "../model/board.h"
#include "../shared/colour.h"
#include "../shared/coordinate.h"
#include <limits>

HumanPlayer::HumanPlayer(Board* board, Colour colour) : Player{board, colour} {}

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

            if (
                board->getPiece(to)->getPieceType() == Piece::PieceType::Pawn &&
                ((colour == Colour::White && Coordinate::chessToCartesian(to).row == 7) || (colour == Colour::Black && Coordinate::chessToCartesian(to).row == 0))
            ) {
                while (true) {
                    std::string type;
                    Piece::PieceType newPieceType;

                    std::cout << "Promote to (r, n, b, q): ";
                    std::cin >> type;

                    if (type.size() != 1) {
                        std::cout << "Invalid promotion, try again." << std::endl;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        continue;
                    }
                    char c = std::tolower(type[0]);

                    if (c == 'r') {
                        newPieceType = Piece::PieceType::Rook;
                    }
                    else if (c == 'n') {
                        newPieceType = Piece::PieceType::Knight;
                    }
                    else if (c == 'b') {
                        newPieceType = Piece::PieceType::Bishop;
                    }
                    else if (c == 'q') {
                        newPieceType = Piece::PieceType::Queen;
                    }
                    else {
                        std::cout << "Invalid promotion, try again." << std::endl;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        continue;
                    }

                    if (board->promote(Coordinate::chessToCartesian(to), newPieceType, colour))
                        break;
                    else
                        std::cout << "Invalid promotion, try again." << std::endl;
                }
            }
            
            return true;
        }
        else if (action == "resign" || std::cin.eof()) {
            return false;
        }
        else {
            std::cout << "Invalid action, try again: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
