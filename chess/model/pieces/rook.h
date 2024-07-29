#ifndef ROOK_H
#define ROOK_H

#include "../pieceClonable.h"
#include "../../shared/colour.h"

class Rook : public PieceClonable<Rook> {
private:
    bool hasMoved;
public:
    static const char SYMBOL = 'R';

    Rook(Coordinate::Coordinate position, Colour colour, Board* board);

    virtual ~Rook() = default;

    virtual std::vector<Coordinate::Coordinate> getValidMoves() const override;
    virtual bool makeMove(Coordinate::Coordinate dest) override;
};

#endif
