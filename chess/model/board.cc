#include "board.h"
#include "../shared/colour.h"

Board::Board(int boardDimension): board{new Piece**[boardDimension]}, boardDimension{boardDimension}, boardState{Default} {
    //this is needed since C++ does not support 2D dynamic array initialization (e.g. new Piece*[boardDimension][boardDimension])
    for (int i = 0; i < boardDimension; i++) { //initialize 2D array (rows)
        board[i] = new Piece*[boardDimension];
    }
}

Board::~Board() {
    for (int i = 0; i < boardDimension; i++) {
        delete[] board[i];
    }
    delete[] board;
}

// void Board::computeBoardState(Colour turn) {

// }

Board::BoardState Board::getBoardState() {
    return boardState;
}

std::unique_ptr<Piece> Board::getPiece(Coordinate pos) {
    return board[pos.row][pos.col]->clone();
}

// int Board::getBoardDimension() {

// }

// bool Board::takeTurn(Coordinate from, Coordinate to, Colour col) {

// }

// bool Board::promote(Coordinate pos, Piece::PieceType pieceType, Colour col) {

// }

// bool Board::addPiece(Coordinate pos, Piece* piece) {

// }

// bool Board::removePiece(Coordinate pos) {

// }
