#ifndef BISHOP_H
#define BISHOP_H

#include "../pieceClonable.h"
#include "../../shared/colour.h"

class Bishop : public PieceClonable<Bishop> {
private:

public:
    static const char SYMBOL = 'B';
    static const int VALUE = 3;

    Bishop(Coordinate::Coordinate position, Colour colour, Board* board);

    ~Bishop() = default;

    std::vector<Coordinate::Coordinate> getValidMoves() const override;
};

#endif
