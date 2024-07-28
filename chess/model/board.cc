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

std::unique_ptr<Piece> Board::getPiece(Coordinate::Coordinate pos) const {
    return board[pos.row][pos.col]->clone();
}

int Board::getBoardDimension() const {
    return boardDimension;
}

void Board::computeBoardState(Colour turn) {

}

bool Board::takeTurn(Coordinate::Coordinate from, Coordinate::Coordinate to, Colour col) {
    Piece* piece = board[from.row][from.col];

    // First stage of checks: is there a piece at the from coordinate and is it the correct colour?
    if (nullptr == piece || piece->getColour() != col) {
        return false;
    }

    // Second stage of checks: does the board state allow moving?
    computeBoardState(col);
    if (boardState == WhiteCheckmated || boardState == BlackCheckmated || boardState == Stalemate) {
        return false;
    }

    // Third stage of checks: can the piece make the move?
    bool moved = piece->makeMove(to);
    if (!moved) {
        return false;
    }

    // Fourth stage of checks: is the board state still valid after the move?
    computeBoardState(col);
    if ((col == Colour::White && boardState == WhiteChecked) || (col == Colour::Black && boardState == BlackChecked)) {
        return false;
    }

    return true;
}

// bool Board::promote(Coordinate pos, Piece::PieceType pieceType, Colour col) {

// }

bool Board::addPiece(Piece* piece) {
    Coordinate::Coordinate pos = piece->getPosition();
    if (nullptr != board[pos.row][pos.col]) {
        delete board[pos.row][pos.col]; //delete existing piece
    }
    board[pos.row][pos.col] = piece;
    return true;
}

bool Board::removePiece(Coordinate::Coordinate pos) {
    if (nullptr != board[pos.row][pos.col]) {
        delete board[pos.row][pos.col];
        board[pos.row][pos.col] = nullptr;
        return true;
    }
    return false;
}

bool Board::verifyBoard(Colour currentTurn) {
    int numWhiteKing = 0, numBlackKing = 0;
    for (int i = 0; i < boardDimension; i++) {
        for (int j = 0; j < boardDimension; j++) {
            if (board[i][j] != nullptr) {
                if (board[i][j]->getPieceType() == Piece::PieceType::King) {
                    //check if more than one white/black king
                    if (board[i][j]->getColour() == Colour::Black && ++numBlackKing > 1) {
                        return false;
                    }
                    else if (++numWhiteKing > 1) {
                        return false;
                    }
                }
                else if ((i == 0 || i == boardDimension - 1) && board[i][j]->getPieceType() == Piece::PieceType::Pawn) {
                    //no pawn on the first or last ranks
                    return false;
                }
            }
        }
    }
    //exactly one white and one black king
    if (numWhiteKing != 1 && numBlackKing != 1) {
        return false;
    }

    //neither king is in check
    computeBoardState(currentTurn);
    if (boardState != BoardState::Default || boardState != BoardState::Stalemate) {
        return false;
    }

    return true;
}
