#ifndef KNIGHT_H
#define KNIGHT_H

#include "../pieceClonable.h"
#include "../../shared/colour.h"

class Knight : public PieceClonable<Knight> {
private:

public:
    static const char SYMBOL = 'N';

    Knight(Coordinate::Coordinate position, Colour colour, Board* board);

    ~Knight() = default;

    std::vector<Coordinate::Coordinate> getValidMoves() const override;
    bool makeMove(Coordinate::Coordinate dest) override;
};

#endif
