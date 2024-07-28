#ifndef KING_H
#define KING_H

#include "../pieceClonable.h"
#include "../../shared/colour.h"

class King : public PieceClonable<King> {
private:
    bool hasMoved;
public:
    King(Coordinate::Coordinate position, Colour colour, Board* board);

    virtual ~King() = default;
    char toChar() const override final;

    virtual std::vector<Coordinate::Coordinate> getValidMoves() const override;
    virtual bool canTargetSquare(Coordinate::Coordinate square) const override;
    virtual bool makeMove(Coordinate::Coordinate dest) override;
};

#endif
