#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include "../shared/coordinate.h"
#include "../shared/colour.h"
#include <memory>
#include <stack>
#include <string>
#include <utility>

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
        Board(const Board& other); //COPY CTOR
        ~Board(); //DTOR

        void computeBoardState(Colour turn);
        BoardState getBoardState() const;
        std::unique_ptr<Piece> getPiece(Coordinate::Coordinate pos) const;
        std::unique_ptr<Piece> getPiece(int i, int j) const;
        std::unique_ptr<Piece> getPiece(std::string pos) const;
        int getBoardDimension() const;
        std::unique_ptr<Piece>** cloneBoard();
        bool takeTurn(Coordinate::Coordinate from, Coordinate::Coordinate to, Colour col, bool simulate = false, bool incrementTurn = true);
        void undoTurn();
        bool canTargetSquare(Coordinate::Coordinate square, Colour colour) const; //can any of colour's piece target the square?
        bool promote(Coordinate::Coordinate pos, Piece::PieceType pieceType, Colour col);
        bool addPiece(std::string pieceCode, Coordinate::Coordinate pos);
        bool addPiece(Colour colour, Piece::PieceType type, Coordinate::Coordinate pos);
        bool removePiece(Coordinate::Coordinate pos);
        bool verifyBoard(); //called by Game during setup
        void resetDefaultChess();
        void reset(); //called by Game during setup

    protected:

    private:
        struct History {
            Piece* oldPiece;
            Piece* newPiece;
            Piece* capturedPiece;
            int turnNumber;
        };

        Piece*** board;
        int boardDimension;
        BoardState boardState;
        std::stack<History> moveHistories;
        int turnNumber;
        bool isKingInCheck(Colour kingColour) const;
};

#endif
