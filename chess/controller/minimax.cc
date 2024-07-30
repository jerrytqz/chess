#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <random>
#include "computer.h"
#include "../model/board.h"
#include "../shared/colour.h"
#include "../shared/coordinate.h"

int ComputerPlayer::minimax(Board *b, int depth, bool maximizingPlayer) {
    if (depth == 0) {
        return evaluate(b);
    }

    Colour myColour = maximizingPlayer ? colour : (colour == Colour::Black ? Colour::White : Colour::Black);
    std::vector<std::unique_ptr<Piece>> myPieces {};

    for (int i = 0; i < board->getBoardDimension(); ++i) {
        for (int j = 0; j < board->getBoardDimension(); ++j) {
            if (board->getPiece(i, j) != nullptr) {
                if (board->getPiece(i, j)->getColour() == myColour)
                    myPieces.push_back(std::move(board->getPiece(i, j)));
            }
        }
    }
    
    std::vector<ChessMove> legalMoves{};

    for (auto& piece : myPieces) {
        std::vector<Coordinate::Coordinate> validMoves = piece->getValidLegalMoves();
        for (auto& coord : validMoves) {
            legalMoves.push_back(ChessMove{piece->getPosition(), coord, 0});
        }
    }

    if (legalMoves.empty()) {
        return evaluate(b);
    }

    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();
        for (ChessMove& move : legalMoves) {
            b->takeTurn(move.from, move.to, myColour);
            int eval = minimax(board, depth - 1, false);
            b->undoTurn();
            maxEval = std::max(maxEval, eval);
        }
        return maxEval;
    } else {
        int minEval = std::numeric_limits<int>::max();
        for (ChessMove& move : legalMoves) {
            b->takeTurn(move.from, move.to, myColour);
            int eval = minimax(board, depth - 1, true);
            b->undoTurn();
            minEval = std::min(minEval, eval);
        }
        return minEval;
    }
}

int ComputerPlayer::evaluate(Board *b) {
    Board::BoardState bs = b->getBoardState();
    
    if (colour == Colour::Black) {
        if (bs == Board::BoardState::BlackCheckmated) {
            return std::numeric_limits<int>::min();
        }
        else if (bs == Board::BoardState::WhiteCheckmated) {
            return std::numeric_limits<int>::max();
        }
    }
    else {
        if (bs == Board::BoardState::BlackCheckmated) {
            return std::numeric_limits<int>::max();
        }
        else if (bs == Board::BoardState::WhiteCheckmated) {
            return std::numeric_limits<int>::min();
        }
    }

    int score = 0;

    std::vector<std::unique_ptr<Piece>> myPieces {};
    std::vector<std::unique_ptr<Piece>> enemyPieces {};

    for (int i = 0; i < board->getBoardDimension(); ++i) {
        for (int j = 0; j < board->getBoardDimension(); ++j) {
            if (board->getPiece(i, j) != nullptr) {
                if (board->getPiece(i, j)->getColour() == colour)
                    myPieces.push_back(std::move(board->getPiece(i, j)));
                else
                    enemyPieces.push_back(std::move(board->getPiece(i, j)));
            }
        }
    }

    for (auto& piece : myPieces) {
        score += piece->toValue() * 10;
    }

    for (auto& piece : enemyPieces) {
        score -= piece->toValue() * 10;
    }

    if (colour == Colour::Black) {
        if (bs == Board::BoardState::BlackChecked) {
            score -= 30;
        }
        else if (bs == Board::BoardState::WhiteChecked) {
            score += 30;
        }
    }
    else {
        if (bs == Board::BoardState::BlackChecked) {
            score += 30;
        }
        else if (bs == Board::BoardState::WhiteChecked) {
            score -= 30;
        }
    }

    return score;
}
