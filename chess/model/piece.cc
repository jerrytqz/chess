#include "piece.h"
#include "./board.h"

Piece::Piece(Coordinate::Coordinate position, Colour colour, PieceType pieceType, Board* board) 
    : position{position}, colour{colour}, board{board}, pieceType{pieceType} {}

std::unique_ptr<Piece> Piece::clone() {
    return std::unique_ptr<Piece>(cloneImpl());
}

Piece::PieceType Piece::getPieceType() const {
    return pieceType;
}

Coordinate::Coordinate Piece::getPosition() const {
    return position;
}

Colour Piece::getColour() const {
    return colour;
}

std::vector<Coordinate::Coordinate> Piece::getValidLegalMoves() const {
    std::vector<Coordinate::Coordinate> validLegalMoves;
    std::vector<Coordinate::Coordinate> validMoves = getValidMoves();
    for (Coordinate::Coordinate nextPos : validMoves) {
        if (board->verifyNoCheckAfterMove(position, nextPos)) {
            validMoves.push_back(nextPos);
        }
    }
    return validLegalMoves;
}

bool Piece::canTargetSquare(Coordinate::Coordinate square) const {
    std::vector<Coordinate::Coordinate> validMoves = getValidMoves();
    if (std::find(validMoves.begin(), validMoves.end(), square) == validMoves.end()) { //square is not in valid moves
        return false;
    }
    else {
        return true;
    }
}
