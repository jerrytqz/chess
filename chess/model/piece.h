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
    virtual int toValue() const = 0;
    Coordinate::Coordinate getPosition() const;
    Colour getColour() const;
    
    virtual std::vector<Coordinate::Coordinate> getValidMoves() const = 0; //does not check if move will put Colour in check
    std::vector<Coordinate::Coordinate> getValidLegalMoves() const; //uses virtual method getValidMoves()
    virtual bool canTargetSquare(Coordinate::Coordinate square) const; //uses virtual method getValidMoves()
    virtual bool canTargetSquareFrom(Coordinate::Coordinate from, Coordinate::Coordinate square); //uses virtual method canTargetSquare()
    bool makeMove(Coordinate::Coordinate dest, bool simulate = false);
    virtual void adjustAfterMove(Coordinate::Coordinate dest);
protected:
    Coordinate::Coordinate position;
    Colour colour;
    Board* const board;

    virtual Piece* cloneImpl() = 0;
private:
    PieceType pieceType;
};

#endif
