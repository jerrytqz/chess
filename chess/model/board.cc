#include "board.h"
#include "./pieces/pawn.h"
#include "./pieces/rook.h"
#include "./pieces/knight.h"
#include "./pieces/bishop.h"
#include "./pieces/queen.h"
#include "./pieces/king.h"
#include "../shared/colour.h"
#include "../shared/coordinate.h"

#include <cctype>
#include <string>

Board::Board(int boardDimension): board{new Piece**[boardDimension]}, boardDimension{boardDimension}, boardState{Default} {
    //this is needed since C++ does not support 2D dynamic array initialization (e.g. new Piece*[boardDimension][boardDimension])
    for (int i = 0; i < boardDimension; i++) { //initialize 2D array (rows) to nullptr
        board[i] = new Piece*[boardDimension]{0};
    }

    resetDefaultChess();
}

Board::Board(const Board& other): board{new Piece**[other.boardDimension]}, boardDimension{other.boardDimension}, boardState{other.boardState} {
    //this is needed since C++ does not support 2D dynamic array initialization (e.g. new Piece*[boardDimension][boardDimension])
    for (int i = 0; i < boardDimension; i++) { //initialize 2D array (rows) to nullptr
        board[i] = new Piece*[boardDimension]{0};
    }

    for (int i = 0; i < other.boardDimension; ++i) {
        for (int j = 0; j < other.boardDimension; ++j) {
            if (other.board[i][j] != nullptr) {
                board[i][j] = other.board[i][j]->cloneToBoard(this);
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
    while (!moveHistories.empty()) {
        History lastMove = moveHistories.top();
        delete lastMove.oldPiece;
        delete lastMove.newPiece;
        delete lastMove.capturedPiece;
        moveHistories.pop();
    }
}

Board::BoardState Board::getBoardState() const {
    return boardState;
}

std::unique_ptr<Piece> Board::getPiece(Coordinate::Coordinate pos) const {
    if (nullptr == board[pos.row][pos.col]) {
        return nullptr;
    }
    return board[pos.row][pos.col]->clone();
}

std::unique_ptr<Piece> Board::getPiece(int x, int y) const {
    return getPiece(Coordinate::Coordinate{x, y});
}

std::unique_ptr<Piece> Board::getPiece(std::string pos) const {
    return getPiece(Coordinate::chessToCartesian(pos));
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

bool Board::canTargetSquare(Coordinate::Coordinate square, Colour colour) const {
    for (int i = 0; i < boardDimension; i++) {
        for (int j = 0; j < boardDimension; j++) {
            if (board[i][j] && board[i][j]->getColour() == colour && board[i][j]->canTargetSquare(square)) {
                return true;
            }
        }
    }
    return false;
}
bool Board::isKingInCheck(Colour kingColour) const {
    Coordinate::Coordinate kingPos;
    for (int i = 0; i < boardDimension; ++i) {
        for (int j = 0; j < boardDimension; ++j) {
            Piece* piece = board[i][j];
            if (piece && piece->getColour() == kingColour && piece->getPieceType() == Piece::PieceType::King) {
                kingPos = {i, j};
                break;
            }
        }
    }

    Colour opponentColour = (kingColour == Colour::White) ? Colour::Black : Colour::White;
    return canTargetSquare(kingPos, opponentColour);
}
void Board::computeBoardState(Colour turn) {
    //check for check
    bool whiteInCheck = isKingInCheck(Colour::White);
    bool blackInCheck = isKingInCheck(Colour::Black);

    // does player have any valid moves?
    bool hasValidMoves = false;
    for (int i = 0; i < boardDimension; i++) {
        for (int j = 0; j < boardDimension; j++) {
            Piece* piece = board[i][j];
            if (piece != nullptr && piece->getColour() == turn) {
                std::vector<Coordinate::Coordinate> validMoves = piece->getValidLegalMoves();
                if (!validMoves.empty()) {
                    hasValidMoves = true;
                    break;
                }
            }
        }
        if (hasValidMoves) break;
    }

    if (turn == Colour::White) {
        if (whiteInCheck) {
            if (hasValidMoves) {
                boardState = BoardState::WhiteChecked;
            } else {
                boardState = BoardState::WhiteCheckmated;
            }
        } else {
            if (hasValidMoves) {
                boardState = BoardState::Default;
            } else {
                boardState = BoardState::Stalemate;
            }
        }
    } else {
        if (blackInCheck) {
            if (hasValidMoves) {
                boardState = BoardState::BlackChecked;
            } else {
                boardState = BoardState::BlackCheckmated;
            }
        } else {
            if (hasValidMoves) {
                boardState = BoardState::Default;
            } else {
                boardState = BoardState::Stalemate;
            }
        }
    }
}

bool Board::takeTurn(Coordinate::Coordinate from, Coordinate::Coordinate to, Colour col, bool simulate) {
    // First step: is there a piece at the from coordinate and is it the correct colour?
    Piece* fromPiece = board[from.row][from.col];
    if (nullptr == fromPiece || fromPiece->getColour() != col) {
        return false;
    }

    std::unique_ptr<Piece> oldPiece = fromPiece->clone();
    std::unique_ptr<Piece> capturedPiece = board[to.row][to.col] ? board[to.row][to.col]->clone() : nullptr;

    // Second step: can the piece make the move?
    if (!fromPiece->makeMove(to, simulate)) {
        return false;
    }

    delete board[to.row][to.col];
    board[from.row][from.col] = nullptr;
    board[to.row][to.col] = fromPiece;

    std::unique_ptr<Piece> newPiece = fromPiece->clone();

    // Third step: add move to history
    moveHistories.push(
        History{oldPiece.release(), newPiece.release(), capturedPiece.release()}
    );

    // Fourth step: has player moved into check?
    if (isKingInCheck(col)) {
        undoTurn();
        return false;
    }

    if (simulate) {
        undoTurn();
    }
    return true;
}

void Board::undoTurn() {
    if (moveHistories.empty()) {
        return;
    }

    History lastMove = moveHistories.top();
    Coordinate::Coordinate oldPosition = lastMove.oldPiece->getPosition();
    Coordinate::Coordinate newPosition = lastMove.newPiece->getPosition();

    //delete new piece
    delete board[newPosition.row][newPosition.col];
    board[newPosition.row][newPosition.col] = nullptr;
    delete lastMove.newPiece;

    //restore old piece
    board[oldPosition.row][oldPosition.col] = lastMove.oldPiece;

    //restore captured piece if there is one
    if (nullptr != lastMove.capturedPiece) {
        board[lastMove.capturedPiece->getPosition().row][lastMove.capturedPiece->getPosition().col] = lastMove.capturedPiece;
    }

    moveHistories.pop();
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

void Board::resetDefaultChess() {
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

void Board::reset() {
    for (int i = 0; i < boardDimension; i++) {
        for (int j = 0; j < boardDimension; j++) {
            if (board[i][j] != nullptr) {
                delete board[i][j];
                board[i][j] = nullptr;
            }
        }
    }
}
