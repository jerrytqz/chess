#ifndef BISHOP_H
#define BISHOP_H

#include "../pieceClonable.h"
#include "../../shared/colour.h"

class Bishop : public PieceClonable<Bishop> {
private:

public:
    Bishop(Coordinate::Coordinate position, Colour colour, Board* board);

    virtual ~Bishop() = default;
    char toChar() const override final;

    virtual std::vector<Coordinate::Coordinate> getValidMoves() const override;
    virtual bool canTargetSquare(Coordinate::Coordinate square) const override;
    virtual bool makeMove(Coordinate::Coordinate dest) override;
};

#endif
