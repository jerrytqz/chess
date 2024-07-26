#include "piece.h"

Piece::Piece(Coordinate position, Colour colour, PieceType pieceType, Board* board) 
    : position{position}, colour{colour}, pieceType{pieceType}, board{board} {}
