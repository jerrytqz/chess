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
    static const int VALUE = 1;

    Pawn(Coordinate::Coordinate position, Colour colour, Board* board);

    ~Pawn() = default;

    std::vector<Coordinate::Coordinate> getValidMoves() const override;
    bool canTargetSquare(Coordinate::Coordinate square) const override;
    bool makeMove(Coordinate::Coordinate dest) override;
};

#endif
