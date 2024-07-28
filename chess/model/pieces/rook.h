#ifndef ROOK_H
#define ROOK_H

#include "../pieceClonable.h"
#include "../../shared/colour.h"

class Rook : public PieceClonable<Rook> {
private:
    bool hasMoved;
public:
    Rook(Coordinate::Coordinate position, Colour colour, Board* board);

    virtual ~Rook() = default;
    char toChar() const override final;

    virtual std::vector<Coordinate::Coordinate> getValidMoves() const override;
    virtual bool canTargetSquare(Coordinate::Coordinate square) const override;
    virtual bool makeMove(Coordinate::Coordinate dest) override;
};

#endif
