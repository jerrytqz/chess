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

Board::BoardState Board::getBoardState() const {
    return boardState;
}

std::unique_ptr<Piece> Board::getPiece(Coordinate pos) const {
    return board[pos.row][pos.col]->clone();
}

int Board::getBoardDimension() const {
    return boardDimension;
}

void Board::computeBoardState(Colour turn) {

}

bool Board::takeTurn(Coordinate from, Coordinate to, Colour col) {
    Piece* piece = board[from.row][from.col];

    // First stage of checks: is there a piece at the from coordinate and is it the correct colour?
    if (nullptr == piece || piece->getColour() != col) {
        return false;
    }

    // Second stage of checks: does the board state allow the move?
    computeBoardState(col);
    if (boardState == WhiteCheckmated || boardState == BlackCheckmated || boardState == Stalemate) {
        return false;
    }

    // Third stage of checks: can the piece make the move?
    if (piece->makeMove(to)) {
        delete board[to.row][to.col];
        board[to.row][to.col] = piece;
        board[from.row][from.col] = nullptr;
        return true;
    }
    return false;
}

// bool Board::promote(Coordinate pos, Piece::PieceType pieceType, Colour col) {

// }

bool Board::addPiece(Piece* piece) {
    Coordinate pos = piece->getPosition();
    if (nullptr == board[pos.row][pos.col]) {
        board[pos.row][pos.col] = piece;
        return true;
    }
    return false;
}

bool Board::removePiece(Coordinate pos) {
    if (nullptr != board[pos.row][pos.col]) {
        delete board[pos.row][pos.col];
        board[pos.row][pos.col] = nullptr;
        return true;
    }
    return false;
}
