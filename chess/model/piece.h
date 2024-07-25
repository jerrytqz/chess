#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include "board.h"
#include "coordinate.h"

class Piece {
public:
    enum class Colour {
        White,
        Black
    };

    enum class PieceType {
        King,
        Queen,
        Bishop,
        Rook,
        Knight,
        Pawn
    };

    Piece(Coordinate position, Colour colour, PieceType pieceType, Board* board) 
        : position{position}, colour{colour}, pieceType{pieceType}, board{board} {}
    virtual ~Piece() = default;

    virtual PieceType getPieceType() = 0;
    virtual std::vector<Coordinate> getValidMoves() = 0;
    virtual bool makeMove(Coordinate dest) = 0;
    virtual bool canTargetSquare(Coordinate square) = 0;
private:
    Coordinate position;
    Colour colour;
    PieceType pieceType;
    Board* board;
};

#endif
