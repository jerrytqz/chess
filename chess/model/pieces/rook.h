#ifndef ROOK_H
#define ROOK_H

#include "../pieceClonable.h"
#include "../../shared/colour.h"

class Rook : public PieceClonable<Rook> {
private:
    bool hasMoved;
public:
    static const char SYMBOL = 'R';
    static const int VALUE = 5;

    Rook(Coordinate::Coordinate position, Colour colour, Board* board);

    ~Rook() = default;

    std::vector<Coordinate::Coordinate> getValidMoves() const override;
    void adjustAfterMove(Coordinate::Coordinate dest, bool simulate = false) override;
    int getMovementData() override;
};

#endif
