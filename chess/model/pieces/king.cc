#include "king.h"
#include "../board.h"
#include <utility>

King::King(Coordinate::Coordinate position, Colour colour, Board* board):
    PieceClonable{position, colour, Piece::PieceType::King, board}, hasMoved{false} {}

std::vector<Coordinate::Coordinate> King::getValidLegalMoves() const {
    std::vector<Coordinate::Coordinate> validLegalMoves;
    for (Coordinate::Coordinate nextPos : getValidMoves()) {
        if (abs(nextPos.col - position.col) > 1) { //castling move
            bool checked = (colour == Colour::Black
                ? (board->getBoardState() == Board::BoardState::BlackChecked)
                : (board->getBoardState() == Board::BoardState::WhiteChecked));
            if (checked) {
                continue;
            }
            
            bool validCastle = true;
            if (nextPos.col == 2) { //QUEEN SIDE CASTLE
                for (int i = 1; i < 4; ++i) {
                    if (board->canTargetSquare({position.row, i}, colour == Colour::Black ? Colour::White : Colour::Black)) {
                        validCastle = false;
                        break;
                    }
                }
            }
            else { //KING SIDE CASTLE
                for (int i = 5; i < 7; ++i) {
                    if (board->canTargetSquare({position.row, i}, colour == Colour::Black ? Colour::White : Colour::Black)) {
                        validCastle = false;
                        break;
                    }
                }
            }
            if (validCastle) {
                validLegalMoves.push_back(nextPos);
            }
        }
        else if (board->takeTurn(position, nextPos, colour, true)) {
            validLegalMoves.push_back(nextPos);
        }
    }
    return validLegalMoves;
}

std::vector<Coordinate::Coordinate> King::getValidMoves() const {
    std::vector<Coordinate::Coordinate> validMoves;

    // Possible relative moves for a king
    std::vector<std::pair<int, int>> directions = {{
        {1, 0},
        {1, 1},
        {0, 1},
        {-1, 1},
        {-1, 0},
        {-1, -1},
        {0, -1},
        {1, -1}
    }};

    for (const auto& dir : directions) {
        Coordinate::Coordinate nextPos{position.row + dir.first, position.col + dir.second};

        // Check if the move is within bounds and doesn't leave the king in check
        if (Coordinate::checkBounds(nextPos, board->getBoardDimension())) {
            std::unique_ptr<Piece> targetPiece = board->getPiece(nextPos);
            bool canMove = !targetPiece || targetPiece->getColour() != this->getColour();

            if (canMove) {
                validMoves.push_back(nextPos);
            }
        }
    }

    //CASTLING LOGIC
    if (
        !hasMoved &&
        position.col == 4 &&
        (position.row == 0 || position.row == 7)
    ) {
        std::unique_ptr<Piece> queenSideRook = board->getPiece(position.row, 0);
        if (
            queenSideRook != nullptr &&
            queenSideRook->getPieceType() == Piece::PieceType::Rook &&
            queenSideRook->getColour() == colour &&
            queenSideRook->getMovementData() == 0
        ) {
            bool canReach = true;
            for (int i = 1; i < 4; ++i) {
                if (board->getPiece(position.row, i) != nullptr) {
                    canReach = false;
                    break;
                }
            }

            if (canReach) {
                validMoves.push_back(Coordinate::Coordinate{position.row, 2});
            }
        }

        std::unique_ptr<Piece> kingSideRook = board->getPiece(position.row, 7);
        if (
            kingSideRook != nullptr &&
            kingSideRook->getPieceType() == Piece::PieceType::Rook &&
            kingSideRook ->getColour() == colour &&
            kingSideRook->getMovementData() == 0
        ) {
            bool canReach = true;
            for (int i = 5; i < 7; ++i) {
                if (board->getPiece(position.row, i) != nullptr) {
                    canReach = false;
                    break;
                }
            }

            if (canReach) {
                validMoves.push_back(Coordinate::Coordinate{position.row, 6});
            }
        }
    }

    return validMoves;
}

bool King::canTargetSquare(Coordinate::Coordinate square) const {
    if (abs(square.col - position.col) > 1) { //can not target pieces greater than 1 away
        return false;
    }
    std::vector<Coordinate::Coordinate> validMoves = getValidMoves();
    if (std::find(validMoves.begin(), validMoves.end(), square) == validMoves.end()) { //square is not in valid moves
        return false;
    }
    else {
        return true;
    }
}

void King::adjustAfterMove(Coordinate::Coordinate dest, bool simulate) {
    bool checked = colour == Colour::Black
        ? (board->getBoardState() == Board::BoardState::BlackChecked)
        : (board->getBoardState() == Board::BoardState::WhiteChecked);
    if (
        !hasMoved && !checked &&
        position.col == 4 &&
        (position.row == 0 || position.row == 7)
    ) {
        std::unique_ptr<Piece> queenSideRook = board->getPiece(position.row, 0);
        std::unique_ptr<Piece> kingSideRook = board->getPiece(position.row, 7);
        if ( //queen side castle
            dest == Coordinate::Coordinate{position.row, 2} &&
            queenSideRook != nullptr &&
            queenSideRook->getPieceType() == Piece::PieceType::Rook &&
            queenSideRook->getColour() == colour &&
            queenSideRook->getMovementData() == 0
        ) {
            board->takeTurn(queenSideRook->getPosition(), Coordinate::Coordinate{position.row, 3}, colour, simulate, false);
        }
        else if ( //king side castle
            dest == Coordinate::Coordinate{position.row, 6} &&
            kingSideRook != nullptr &&
            kingSideRook->getPieceType() == Piece::PieceType::Rook &&
            kingSideRook->getColour() == colour &&
            kingSideRook->getMovementData() == 0
        ) {
            board->takeTurn(kingSideRook->getPosition(), Coordinate::Coordinate{position.row, 5}, colour, simulate, false);
        }
    }
    
    hasMoved = true;
}
