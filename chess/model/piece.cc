#include "piece.h"

Piece::Piece(Coordinate position, Colour colour, PieceType pieceType, Board* board) 
    : position{position}, colour{colour}, board{board}, pieceType{pieceType} {}

std::unique_ptr<Piece> Piece::clone() {
    return std::unique_ptr<Piece>(cloneImpl());
}
