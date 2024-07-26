#ifndef PAWN_H
#define PAWN_H

#include "../piece.h"

class Pawn : public Piece {
private:
    bool hasMoved;
    bool justMovedTwice;
public:
    Pawn(Coordinate position, Colour colour, PieceType pieceType, Board* board);


    Pawn* clone() override;
    virtual ~Pawn() = default;

    virtual PieceType getPieceType() override;
    virtual std::vector<Coordinate> getValidMoves() override;
    virtual bool makeMove(Coordinate dest) override;
    virtual bool canTargetSquare(Coordinate square) override;
};

#endif
