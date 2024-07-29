#ifndef BISHOP_H
#define BISHOP_H

#include "../pieceClonable.h"
#include "../../shared/colour.h"

class Bishop : public PieceClonable<Bishop> {
private:

public:
    static const char SYMBOL = 'B';

    Bishop(Coordinate::Coordinate position, Colour colour, Board* board);

    ~Bishop() = default;

    std::vector<Coordinate::Coordinate> getValidMoves() const override;
    bool makeMove(Coordinate::Coordinate dest) override;
};

#endif
