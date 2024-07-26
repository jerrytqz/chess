#ifndef PAWN_H
#define PAWN_H

#include "../pieceClonable.h"

class Pawn : public PieceClonable<Pawn> {
private:
    bool hasMoved;
    bool justMovedTwice;
public:
    Pawn(Coordinate position, Colour colour, Board* board);

    virtual ~Pawn() = default;

    virtual std::vector<Coordinate> getValidMoves() const override;
    virtual bool canTargetSquare(Coordinate square) const override;
    virtual bool makeMove(Coordinate dest) override;
};

#endif
