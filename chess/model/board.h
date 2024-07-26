#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include "coordinate.h"
#include "memory.h"

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

        void computeBoardState(Piece::Colour turn);
        BoardState getBoardState();
        std::unique_ptr<Piece> getPiece(Coordinate pos);
        int getBoardDimension();
        bool takeTurn(Coordinate from, Coordinate to, Piece::Colour col);
        bool promote(Coordinate pos, Piece::PieceType pieceType, Piece::Colour col);
        bool addPiece(Coordinate pos, Piece* piece);
        bool removePiece(Coordinate pos);

    protected:

    private:
        Piece*** board;
        int boardDimension;
        BoardState boardState;
};

#endif
