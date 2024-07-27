#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include "../shared/coordinate.h"
#include "../shared/colour.h"
#include <memory>

class Board {
    public:
        enum BoardState {
            Default,
            WhiteChecked,
            BlackChecked,
            WhiteCheckmated,
            BlackCheckmated,
            Stalemate
        };

        Board(int boardDimension); //CTOR
        ~Board(); //DTOR

        void computeBoardState(Colour turn);
        BoardState getBoardState() const;
        std::unique_ptr<Piece> getPiece(Coordinate::Coordinate pos) const;
        int getBoardDimension() const;
        bool takeTurn(Coordinate::Coordinate from, Coordinate::Coordinate to, Colour col);
        bool promote(Coordinate::Coordinate pos, Piece::PieceType pieceType, Colour col);
        bool addPiece(Piece* piece);
        bool removePiece(Coordinate::Coordinate pos);

    protected:

    private:
        Piece*** board;
        int boardDimension;
        BoardState boardState;
};

#endif
