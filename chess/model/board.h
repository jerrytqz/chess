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
        ~Board(); //DTOR

        void computeBoardState(Colour turn);
        BoardState getBoardState() const;
        std::unique_ptr<Piece> getPiece(Coordinate::Coordinate pos) const;
        std::unique_ptr<Piece> getPiece(int i, int j) const;
        std::unique_ptr<Piece> getPiece(std::string pos) const;
        int getBoardDimension() const;
        std::unique_ptr<Piece>** cloneBoard();
        bool takeTurn(Coordinate::Coordinate from, Coordinate::Coordinate to, Colour col);
        void undoTurn();
        bool verifyNoCheckAfterMove(Coordinate::Coordinate from, Coordinate::Coordinate to); //called by Piece
        bool promote(Coordinate::Coordinate pos, Piece::PieceType pieceType, Colour col);
        bool addPiece(std::string pieceCode, Coordinate::Coordinate pos);
        bool addPiece(Colour colour, Piece::PieceType type, Coordinate::Coordinate pos);
        bool removePiece(Coordinate::Coordinate pos);
        bool verifyBoard(Colour currentTurn); //called by Game during setup
        void reset(); //called by Game during setup

    protected:

    private:
        struct History {
            std::pair<std::string, Coordinate::Coordinate> oldPiece;
            std::pair<std::string, Coordinate::Coordinate> newPiece;
            std::pair<std::string, Coordinate::Coordinate> capturedPiece;
        };

        Piece*** board;
        int boardDimension;
        BoardState boardState;
        std::stack<History> moveHistories;
        bool canTargetSquare(Coordinate::Coordinate square, Colour colour) const; //can any of colour's piece target the square?
        bool isKingInCheck(Colour kingColour) const;
};

#endif
