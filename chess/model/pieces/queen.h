#ifndef QUEEN_H
#define QUEEN_H

#include "../pieceClonable.h"
#include "../../shared/colour.h"

class Queen : public PieceClonable<Queen> {
private:

public:
    Queen(Coordinate::Coordinate position, Colour colour, Board* board);

    virtual ~Queen() = default;
    char toChar() const override final;

    virtual std::vector<Coordinate::Coordinate> getValidMoves() const override;
    virtual bool canTargetSquare(Coordinate::Coordinate square) const override;
    virtual bool makeMove(Coordinate::Coordinate dest) override;
};

#endif
