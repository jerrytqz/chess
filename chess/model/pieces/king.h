#ifndef KING_H
#define KING_H

#include "../pieceClonable.h"
#include "../../shared/colour.h"

class King : public PieceClonable<King> {
private:
    bool hasMoved;
public:
    static const char SYMBOL = 'K';

    King(Coordinate::Coordinate position, Colour colour, Board* board);

    virtual ~King() = default;

    virtual std::vector<Coordinate::Coordinate> getValidMoves() const override;
    virtual bool makeMove(Coordinate::Coordinate dest) override;
};

#endif
