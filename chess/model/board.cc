#include "board.h"
#include "./pieces/pawn.h"
#include "./pieces/rook.h"
#include "./pieces/knight.h"
#include "./pieces/bishop.h"
#include "./pieces/queen.h"
#include "./pieces/king.h"
#include "../shared/colour.h"

#include <cctype>

Board::Board(int boardDimension): board{new Piece**[boardDimension]}, boardDimension{boardDimension}, boardState{Default} {
    //this is needed since C++ does not support 2D dynamic array initialization (e.g. new Piece*[boardDimension][boardDimension])
    for (int i = 0; i < boardDimension; i++) { //initialize 2D array (rows) to nullptr
        board[i] = new Piece*[boardDimension]{0};
    }

    //if board dimension is 8 initialize with default chessboard
    if (boardDimension == 8) {
        for (int j = 0; j < 8; j++) { //pawns
            addPiece(Colour::White, Piece::PieceType::Pawn, Coordinate::Coordinate{1, j});
            addPiece(Colour::Black, Piece::PieceType::Pawn, Coordinate::Coordinate{6, j});
        }

        const std::vector<Piece::PieceType> pieceOrder = {
            Piece::PieceType::Rook, Piece::PieceType::Knight, Piece::PieceType::Bishop, Piece::PieceType::Queen, Piece::PieceType::King
        };

        for (int j = 0; j < pieceOrder.size(); j++) {
            //initialize white pieces
            addPiece(Colour::White, pieceOrder[j], Coordinate::Coordinate{0, j});
            if (pieceOrder[j] != Piece::PieceType::Queen && pieceOrder[j] != Piece::PieceType::King) {
                addPiece(Colour::White, pieceOrder[j], Coordinate::Coordinate{0, 7 - j});
            }

            //initialize black pieces
            addPiece(Colour::Black, pieceOrder[j], Coordinate::Coordinate{7, j});
            if (pieceOrder[j] != Piece::PieceType::Queen && pieceOrder[j] != Piece::PieceType::King) {
                addPiece(Colour::Black, pieceOrder[j], Coordinate::Coordinate{7, 7 - j});
            }
        }
    }
}

Board::~Board() {
    for (int i = 0; i < boardDimension; i++) {
        for (int j = 0; j < boardDimension; j++) {
            delete board[i][j];
        }
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

std::unique_ptr<Piece>** Board::cloneBoard() {
    std::unique_ptr<Piece>** clonedBoard = new std::unique_ptr<Piece>*[boardDimension];
    for (int i = 0; i < boardDimension; i++) {
        clonedBoard[i] = new std::unique_ptr<Piece>[boardDimension]{0};
    }

    //populate cloned array
    for (int i = 0; i < boardDimension; i++) {
        for (int j = 0; j < boardDimension; j++) {
            if (board[i][j] != nullptr) { //piece exists
                clonedBoard[i][j] = board[i][j]->clone();
            }
        }
    }

    return clonedBoard;
}

void Board::computeBoardState(Colour turn) {
    //IMPLEMENTATION NOT DONE
    boardState = BoardState::Default;
}

bool Board::takeTurn(Coordinate::Coordinate from, Coordinate::Coordinate to, Colour col) {
    Piece* fromPiece = board[from.row][from.col];
    std::unique_ptr<Piece> toPiece = nullptr;
    if (nullptr != board[to.row][to.col]) {
        toPiece = board[to.row][to.col]->clone();
    }

    // First stage of checks: is there a piece at the from coordinate and is it the correct colour?
    if (nullptr == fromPiece || fromPiece->getColour() != col) {
        return false;
    }

    // Second stage of checks: does the board state allow moving?
    computeBoardState(col);
    if (boardState == WhiteCheckmated || boardState == BlackCheckmated || boardState == Stalemate) {
        return false;
    }

    // Third stage of checks: can the piece make the move?
    if (!fromPiece->makeMove(to)) {
        return false;
    }
    delete board[to.row][to.col];
    board[to.row][to.col] = fromPiece;
    board[from.row][from.col] = nullptr;

    // Fourth stage of checks: is the board state still valid after the move?
    computeBoardState(col);
    if ((col == Colour::White && boardState == WhiteChecked) || (col == Colour::Black && boardState == BlackChecked)) {
        // Undo move if player is still in check or have moved themselves into a check
        board[from.row][from.col] = fromPiece;
        if (nullptr != toPiece) {
            board[to.row][to.col] = toPiece.release();
        }
        return false;
    }

    return true;
}

// bool Board::promote(Coordinate pos, Piece::PieceType pieceType, Colour col) {

// }

bool Board::addPiece(Colour colour, Piece::PieceType type, Coordinate::Coordinate pos) {
    //check if piece is in bounds
    if (!Coordinate::checkBounds(pos, boardDimension)) {
        return false;
    }

    Piece* newPiece = nullptr;

    switch (type) {
        case Piece::PieceType::Pawn:
            newPiece = new Pawn{pos, colour, this};
            break;
        case Piece::PieceType::Rook:
            newPiece = new Rook{pos, colour, this};
            break;
        case Piece::PieceType::Knight:
            newPiece = new Knight{pos, colour, this};
            break;
        case Piece::PieceType::Bishop:
            newPiece = new Bishop{pos, colour, this};
            break;
        case Piece::PieceType::Queen:
            newPiece = new Queen{pos, colour, this};
            break;
        case Piece::PieceType::King:
            newPiece = new King{pos, colour, this};
            break;
    }

    if (nullptr != board[pos.row][pos.col]) {
        delete board[pos.row][pos.col]; //delete existing piece
    }
    board[pos.row][pos.col] = newPiece;
    return true;
}

bool Board::addPiece(std::string pieceCode, Coordinate::Coordinate pos) {
    //check if piece code has length 1 before processing it
    if (pieceCode.length() != 1) {
        return false;
    }

    Colour colour = std::isupper(pieceCode[0]) ? Colour::White : Colour::Black;
    char lcPieceCode = pieceCode[0];
    if (lcPieceCode >= 'A' && lcPieceCode <= 'Z') {
        lcPieceCode = 'a' + (lcPieceCode - 'A');
    }

    Piece::PieceType newPieceType;

    switch(lcPieceCode) {
        case 'r':
            newPieceType = Piece::PieceType::Rook;
            break;
        case 'n':
            newPieceType = Piece::PieceType::Knight;
            break;
        case 'b':
            newPieceType = Piece::PieceType::Bishop;
            break;
        case 'q':
            newPieceType = Piece::PieceType::Queen;
            break;
        case 'k':
            newPieceType = Piece::PieceType::King;
            break;
        case 'p':
            newPieceType = Piece::PieceType::Pawn;
            break;
        default:
            return false;
    }

    return addPiece(colour, newPieceType, pos);
}

bool Board::removePiece(Coordinate::Coordinate pos) {
    if (!Coordinate::checkBounds(pos, boardDimension)) {
        return false;
    }

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
                    else if (board[i][j]->getColour() == Colour::White && ++numWhiteKing > 1) {
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
    if (numWhiteKing != 1 || numBlackKing != 1) {
        return false;
    }

    //neither king is in check
    computeBoardState(currentTurn);
    if (boardState != BoardState::Default && boardState != BoardState::Stalemate) {
        return false;
    }

    return true;
}
