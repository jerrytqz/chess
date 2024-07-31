#include "pawn.h"
#include "../board.h"
#include <cmath>

Pawn::Pawn(Coordinate::Coordinate position, Colour colour, Board* board) 
    : PieceClonable{position, colour, Piece::PieceType::Pawn, board}, hasMoved{false}, justMovedTwice{false} {}

std::vector<Coordinate::Coordinate> Pawn::getValidMoves() const {
    std::vector<Coordinate::Coordinate> validMoves;

    int twoOffset = colour == Colour::White ? 2 : -2;
    int oneOffset = colour == Colour::White ? 1 : -1;

    Coordinate::Coordinate c1{position.row + oneOffset, position.col}; // One move forward
    Coordinate::Coordinate c2{position.row + twoOffset, position.col}; // Two moves forward
    Coordinate::Coordinate c3{position.row + oneOffset, position.col + oneOffset}; // Diagonal right
    Coordinate::Coordinate c4{position.row + oneOffset, position.col - oneOffset}; // Diagonal left

    if (!hasMoved && Coordinate::checkBounds(c2, board->getBoardDimension()) && Coordinate::checkBounds(c1, board->getBoardDimension())
        && !board->getPiece(c2) && !board->getPiece(c1)) {
        validMoves.push_back(c2);
    }

    if (Coordinate::checkBounds(c1, board->getBoardDimension()) && !board->getPiece(c1)) {
        validMoves.push_back(c1);
    }

    if (Coordinate::checkBounds(c3, board->getBoardDimension()) && board->getPiece(c3) 
        && board->getPiece(c3)->getColour() != colour) {
        validMoves.push_back(c3);
    }

    if (Coordinate::checkBounds(c4, board->getBoardDimension()) && board->getPiece(c4) 
        && board->getPiece(c4)->getColour() != colour) {
        validMoves.push_back(c4);
    }

    // En passant
    Coordinate::Coordinate leftAdjacent{position.row, position.col - 1};
    Coordinate::Coordinate rightAdjacent{position.row, position.col + 1};

    if (Coordinate::checkBounds(leftAdjacent, board->getBoardDimension())) {
        std::unique_ptr<Piece> leftPiece = board->getPiece(leftAdjacent);
        if (leftPiece && leftPiece->getColour() != colour && leftPiece->getPieceType() == Piece::PieceType::Pawn) {
            if (leftPiece->getMovementData() == 1) {
                validMoves.push_back(Coordinate::Coordinate{position.row + oneOffset, position.col - 1});
            }
        }
    }
    if (Coordinate::checkBounds(rightAdjacent, board->getBoardDimension())) {
        std::unique_ptr<Piece> rightPiece = board->getPiece(rightAdjacent);
        if (rightPiece && rightPiece->getColour() != colour && rightPiece->getPieceType() == Piece::PieceType::Pawn) {
            if (rightPiece->getMovementData() == 1) {
                validMoves.push_back(Coordinate::Coordinate{position.row + oneOffset, position.col + 1});
            }
        }
    }

    return validMoves;
}

bool Pawn::canTargetSquare(Coordinate::Coordinate square) const {
    int oneOffset = colour == Colour::White ? 1 : -1;

    Coordinate::Coordinate r{position.row + oneOffset, position.col + oneOffset}; // Diagonal right
    Coordinate::Coordinate l{position.row + oneOffset, position.col - oneOffset}; // Diagonal left

    if (square == r || square == l)
        return true;

    return false;
}

void Pawn::adjustAfterMove(Coordinate::Coordinate dest, bool) {
    hasMoved = true;
    justMovedTwice = std::abs(dest.row - position.row) == 2;
}

int Pawn::getMovementData() const {
    if (justMovedTwice)
        return 1;
    return 0;
}
