#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <memory>
#include "coordinate.h"

class Board;

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

    Piece(Coordinate position, Colour colour, PieceType pieceType, Board* board);

    virtual ~Piece() = default;

    std::unique_ptr<Piece> clone();

    virtual PieceType getPieceType() const = 0;
    virtual std::vector<Coordinate> getValidMoves() const = 0;
    virtual bool canTargetSquare(Coordinate square) const = 0;
    virtual bool makeMove(Coordinate dest) = 0;
protected:
    Coordinate position;
    Colour colour;
    Board* board;

    virtual Piece* cloneImpl() = 0;
private:
    PieceType pieceType;
};

#endif
