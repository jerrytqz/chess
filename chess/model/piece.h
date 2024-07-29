#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <memory>
#include <algorithm>
#include "../shared/colour.h"
#include "../shared/coordinate.h"

class Board;

class Piece {
public:
    enum class PieceType {
        King,
        Queen,
        Bishop,
        Rook,
        Knight,
        Pawn
    };

    Piece(Coordinate::Coordinate position, Colour colour, PieceType pieceType, Board* board);

    virtual ~Piece() = default;

    std::unique_ptr<Piece> clone();

    PieceType getPieceType() const;
    virtual char toChar() const = 0;
    Coordinate::Coordinate getPosition() const;
    Colour getColour() const;
    
    virtual std::vector<Coordinate::Coordinate> getValidMoves() const = 0;
    virtual bool canTargetSquare(Coordinate::Coordinate square) const = 0;
    virtual bool makeMove(Coordinate::Coordinate dest) = 0;
protected:
    Coordinate::Coordinate position;
    Colour colour;
    Board* const board;

    virtual Piece* cloneImpl() = 0;
private:
    PieceType pieceType;
};

#endif
