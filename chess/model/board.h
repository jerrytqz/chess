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
        BoardState getBoardState();
        std::unique_ptr<Piece> getPiece(Coordinate pos);
        int getBoardDimension();
        bool takeTurn(Coordinate from, Coordinate to, Colour col);
        bool promote(Coordinate pos, Piece::PieceType pieceType, Colour col);
        bool addPiece(Coordinate pos, Piece* piece);
        bool removePiece(Coordinate pos);

    protected:

    private:
        Piece*** board;
        int boardDimension;
        BoardState boardState;
};

#endif
