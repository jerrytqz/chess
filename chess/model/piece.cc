#include "piece.h"
#include "./board.h"

Piece::Piece(Coordinate::Coordinate position, Colour colour, PieceType pieceType, Board* board) 
    : position{position}, colour{colour}, board{board}, pieceType{pieceType} {}

std::unique_ptr<Piece> Piece::clone() {
    return std::unique_ptr<Piece>(cloneImpl());
}

Piece* Piece::cloneToBoard(Board* b) {
    Piece* c = cloneImpl();
    c->board = b;
    return c;
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

bool Piece::makeMove(Coordinate::Coordinate dest, bool simulate) {
    if (!simulate) {
        std::vector<Coordinate::Coordinate> validMoves = getValidMoves();
        if (std::find(validMoves.begin(), validMoves.end(), dest) == validMoves.end()) {
            return false;
        }
    }

    adjustAfterMove(dest);
    position = dest;

    return true;
}

void Piece::adjustAfterMove(Coordinate::Coordinate) {
    return;
}

int Piece::getMovementData() const {
    return 0;
}

std::vector<Coordinate::Coordinate> Piece::getValidLegalMoves() const {
    std::vector<Coordinate::Coordinate> validLegalMoves;
    for (Coordinate::Coordinate nextPos : getValidMoves()) {
        if (board->takeTurn(position, nextPos, colour, true)) {
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
    Coordinate::Coordinate ogPos = position;
    position = from;
    bool canTarget = Piece::canTargetSquare(square);
    position = ogPos;
    return canTarget;
}
