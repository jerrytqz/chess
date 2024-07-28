#ifndef PAWN_H
#define PAWN_H

#include "../pieceClonable.h"
#include "../../shared/colour.h"

class Pawn : public PieceClonable<Pawn> {
private:
    bool hasMoved;
    bool justMovedTwice;
public:
    static const char SYMBOL = 'P';

    Pawn(Coordinate::Coordinate position, Colour colour, Board* board);

    virtual ~Pawn() = default;

    virtual std::vector<Coordinate::Coordinate> getValidMoves() const override;
    virtual bool canTargetSquare(Coordinate::Coordinate square) const override;
    virtual bool makeMove(Coordinate::Coordinate dest) override;
};

#endif
