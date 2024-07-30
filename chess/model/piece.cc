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

int Piece::getValue() const {
    if (pieceType == Piece::PieceType::Queen) return 9;
    if (pieceType == Piece::PieceType::Rook) return 5;
    if (pieceType == Piece::PieceType::Bishop) return 3;
    if (pieceType == Piece::PieceType::Knight) return 3;
    if (pieceType == Piece::PieceType::Pawn) return 1;
    return 0;
}

std::vector<Coordinate::Coordinate> Piece::getValidLegalMoves() const {
    std::vector<Coordinate::Coordinate> validLegalMoves;
    for (Coordinate::Coordinate nextPos : getValidMoves()) {
        if (board->verifyNoCheckAfterMove(position, nextPos)) {
            validLegalMoves.push_back(nextPos);
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

bool Piece::canTargetSquareFrom(Coordinate::Coordinate from, Coordinate::Coordinate square) {
    Coordinate::Coordinate og_pos = position;
    position = from;
    bool canTarget = Piece::canTargetSquare(square);
    position = og_pos;
    return canTarget;
}
