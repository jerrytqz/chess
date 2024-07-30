#include "king.h"
#include "../board.h"
#include <utility>

King::King(Coordinate::Coordinate position, Colour colour, Board* board):
    PieceClonable{position, colour, Piece::PieceType::King, board}, hasMoved{false} {}

std::vector<Coordinate::Coordinate> King::getValidMoves() const {
    std::vector<Coordinate::Coordinate> validMoves;

    // Possible relative moves for a king
    std::vector<std::pair<int, int>> directions = {{
        {1, 0},
        {1, 1},
        {0, 1},
        {-1, 1},
        {-1, 0},
        {-1, -1},
        {0, -1},
        {1, -1}
    }};

    for (const auto& dir : directions) {
        Coordinate::Coordinate nextPos{position.row + dir.first, position.col + dir.second};

        // Check if the move is within bounds and doesn't leave the king in check
        if (Coordinate::checkBounds(nextPos, board->getBoardDimension())) {
            std::unique_ptr<Piece> targetPiece = board->getPiece(nextPos);
            bool canMove = !targetPiece || targetPiece->getColour() != this->getColour();

            if (canMove) {
                validMoves.push_back(nextPos);
            }
        }
    }

    bool checked = colour == Colour::Black
        ? (board->getBoardState() == Board::BoardState::BlackChecked)
        : (board->getBoardState() == Board::BoardState::WhiteChecked);

    if (
        !hasMoved && !checked &&
        position.col == 5 &&
        (position.row == 0 || position.row == 7)
    ) {
        std::unique_ptr<Piece> col1 = board->getPiece(position.row, 0);
        if (
            col1 != nullptr &&
            col1 ->getPieceType() == Piece::PieceType::Rook &&
            col1 ->getColour() == colour &&
            col1 ->getMovementData() == 0
        ) {
            bool canReach = true;
            for (int i = 1; i < position.col; ++i) {
                if (board->getPiece(position.row, i) != nullptr) {
                    canReach = false;
                    break;
                }
            }

            if (canReach) {
                validMoves.push_back(Coordinate::Coordinate{position.row, 2});
            }
        }

        std::unique_ptr<Piece> col7 = board->getPiece(position.row, 7);

        if (
            col7 != nullptr &&
            col7->getPieceType() == Piece::PieceType::Rook &&
            col7 ->getColour() == colour &&
            col7->getMovementData() == 0
        ) {
            bool canReach = true;
            for (int i = 1; i < position.col; ++i) {
                if (board->getPiece(position.row, i) != nullptr) {
                    canReach = false;
                    break;
                }
            }

            if (canReach) {
                validMoves.push_back(Coordinate::Coordinate{position.row, 6});
            }
        }
    }

    return validMoves;
}

void King::adjustAfterMove(Coordinate::Coordinate dest) {
    bool checked = colour == Colour::Black
        ? (board->getBoardState() == Board::BoardState::BlackChecked)
        : (board->getBoardState() == Board::BoardState::WhiteChecked);
    if (
        !hasMoved && !checked &&
        position.col == 5 &&
        (position.row == 0 || position.row == 7)
    ) {
        std::unique_ptr<Piece> col1 = board->getPiece(position.row, 0);
        std::unique_ptr<Piece> col7 = board->getPiece(position.row, 7);
        if (
            dest == Coordinate::Coordinate{position.row, 2} &&
            col1 != nullptr &&
            col1 ->getPieceType() == Piece::PieceType::Rook &&
            col1 ->getColour() == colour &&
            col1 ->getMovementData() == 0
        ) {
            board->takeTurn(col1->getPosition(), Coordinate::Coordinate{position.row, 3}, colour, false);
        }
        else if (
            dest == Coordinate::Coordinate{position.row, 6} &&
            col7 != nullptr &&
            col7 ->getPieceType() == Piece::PieceType::Rook &&
            col7 ->getColour() == colour &&
            col7 ->getMovementData() == 0
        ) {
            board->takeTurn(col7->getPosition(), Coordinate::Coordinate{position.row, 5}, colour, false);
        }
    }
    
    hasMoved = true;
}
