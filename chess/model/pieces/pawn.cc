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

void Pawn::adjustAfterMove(Coordinate::Coordinate dest) {
    hasMoved = true;
    justMovedTwice = std::abs(dest.row - position.row) == 2;
}
