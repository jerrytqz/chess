#ifndef QUEEN_H
#define QUEEN_H

#include "../pieceClonable.h"
#include "../../shared/colour.h"

class Queen : public PieceClonable<Queen> {
private:

public:
    static const char SYMBOL = 'Q';
    static const int VALUE = 9;

    Queen(Coordinate::Coordinate position, Colour colour, Board* board);

    virtual ~Queen() = default;

    std::vector<Coordinate::Coordinate> getValidMoves() const override;
};

#endif
