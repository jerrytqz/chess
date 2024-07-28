#ifndef KNIGHT_H
#define KNIGHT_H

#include "../pieceClonable.h"
#include "../../shared/colour.h"

class Knight : public PieceClonable<Knight> {
private:

public:
    Knight(Coordinate::Coordinate position, Colour colour, Board* board);

    virtual ~Knight() = default;
    char toChar() const override final;

    virtual std::vector<Coordinate::Coordinate> getValidMoves() const override;
    virtual bool canTargetSquare(Coordinate::Coordinate square) const override;
    virtual bool makeMove(Coordinate::Coordinate dest) override;
};

#endif
