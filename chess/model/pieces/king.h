#ifndef KING_H
#define KING_H

#include "../pieceClonable.h"
#include "../../shared/colour.h"

class King : public PieceClonable<King> {
private:
    bool hasMoved;
public:
    static const char SYMBOL = 'K';
    static const int VALUE = 1000;

    King(Coordinate::Coordinate position, Colour colour, Board* board);

    ~King() = default;

    std::vector<Coordinate::Coordinate> getValidMoves() const override;
    bool makeMove(Coordinate::Coordinate dest) override;
};

#endif
