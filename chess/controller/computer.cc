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

std::mt19937 ComputerPlayer::rng{std::random_device{}()};

ComputerPlayer::ComputerPlayer(Board* board, Colour colour, int level)
    : Player{board, colour}, level{level} {}

ComputerPlayer::ComputerPlayer(Board* board, Colour colour)
    : Player{board, colour}, level{0} {
        std::cout << "Choose level for " << (colour == Colour::Black ? "black" : "white") << " AI opponent: ";
        while (level < 1 || level > 4)
        {
            std::cin >> level;
        }
    }

bool ComputerPlayer::takeTurn() {
    if (colour == Colour::White) {
        std::cout << "White's turn: ";
    }
    else {
        std::cout << "Black's turn: ";
    }

    bool turnTaken;

    switch (level)
    {
    case 4:
        turnTaken = levelFour();
        break;
    case 3:
        turnTaken = levelThree();
        break;
    case 2:
        turnTaken = levelTwo();
        break;
    default:
        turnTaken = levelOne();
        break;
    }

    return turnTaken;
}

bool ComputerPlayer::levelOne() {
    std::vector<std::unique_ptr<Piece>> myPieces {};

    for (int i = 0; i < board->getBoardDimension(); ++i) {
        for (int j = 0; j < board->getBoardDimension(); ++j) {
            if (board->getPiece(i, j) != nullptr && board->getPiece(i, j)->getColour() == colour) {
                myPieces.push_back(std::move(board->getPiece(i, j)));
            }
        }
    }

    while (myPieces.size() > 0)
    {
        int randPiece = std::uniform_int_distribution<int>(0, myPieces.size() - 1)(rng);

        std::vector<Coordinate::Coordinate> validMoves = myPieces[randPiece]->getValidLegalMoves();

        if (validMoves.size() == 0) {
            myPieces.erase(myPieces.begin() + randPiece);
            continue;
        }

        int randMove = std::uniform_int_distribution<int>(0, validMoves.size() - 1)(rng);

        bool turnTaken = board->takeTurn(myPieces[randPiece]->getPosition(), validMoves[randMove], colour);

        if (turnTaken)
        {
            int promotionRow = colour == Colour::White ? 7 : 0;
            if (myPieces[randPiece]->getPieceType() == Piece::PieceType::Pawn && validMoves[randMove].row == promotionRow) {
                board->promote(validMoves[randMove], Piece::PieceType::Queen, colour);
                std::cout << "move " << Coordinate::cartesianToChess(myPieces[randPiece]->getPosition()) << " "
                    << Coordinate::cartesianToChess(validMoves[randMove]) << " Q" << std::endl;
            }
            else {
                std::cout << "move " << Coordinate::cartesianToChess(myPieces[randPiece]->getPosition()) << " "
                    << Coordinate::cartesianToChess(validMoves[randMove]) << std::endl;
            }

            return true;
        }
    }

    return false;
}

bool ComputerPlayer::levelTwo() {
    std::vector<std::unique_ptr<Piece>> myPieces {};

    Coordinate::Coordinate enemyKingPos;

    for (int i = 0; i < board->getBoardDimension(); ++i) {
        for (int j = 0; j < board->getBoardDimension(); ++j) {
            if (board->getPiece(i, j) != nullptr) {
                if (board->getPiece(i, j)->getColour() == colour) {
                    myPieces.push_back(std::move(board->getPiece(i, j)));
                }
                else if (board->getPiece(i, j)->getColour() != colour && board->getPiece(i, j)->getPieceType() == Piece::PieceType::King) {
                    enemyKingPos = board->getPiece(i, j)->getPosition();
                }
            }
        }
    }

    std::vector<ChessMove> moves = {};

    for (auto& piece : myPieces) {
        std::vector<Coordinate::Coordinate> validMoves = piece->getValidLegalMoves();

        for (auto& coord : validMoves) {
            std::unique_ptr<Piece> enemy = board->getPiece(coord);

            int checkBonus = piece->canTargetSquareFrom(coord, enemyKingPos) ? 3 : 0;
            int takePoints = enemy == nullptr ? 0 : enemy->toValue();

            moves.push_back(ChessMove{piece->getPosition(), coord, checkBonus + takePoints});
        }
    }

    std::shuffle(moves.begin(), moves.end(), rng);

    std::sort(moves.begin(), moves.end(), [](const ChessMove& a, const ChessMove& b) {
        return a.point < b.point;
    });

    while (moves.size() > 0) {
        bool turnTaken = board->takeTurn(moves.back().from, moves.back().to, colour);

        if (turnTaken) {
            int promotionRow = colour == Colour::White ? 7 : 0;
            if (board->getPiece(moves.back().to)->getPieceType() == Piece::PieceType::Pawn && moves.back().to.row == promotionRow) {
                board->promote(moves.back().to, Piece::PieceType::Queen, colour);
                std::cout << "move " << Coordinate::cartesianToChess(moves.back().from) << " "
                            << Coordinate::cartesianToChess(moves.back().to) << " Q" << std::endl;
            }
            else {
                std::cout << "move " << Coordinate::cartesianToChess(moves.back().from) << " "
                            << Coordinate::cartesianToChess(moves.back().to) << std::endl;
            }

            return true;
        }

        moves.pop_back();
    }

    return false;
}

bool ComputerPlayer::levelThree() {
    std::vector<std::unique_ptr<Piece>> myPieces {};
    std::vector<std::unique_ptr<Piece>> enemyPieces {};

    Coordinate::Coordinate enemyKingPos;

    for (int i = 0; i < board->getBoardDimension(); ++i) {
        for (int j = 0; j < board->getBoardDimension(); ++j) {
            if (board->getPiece(i, j) != nullptr) {
                if (board->getPiece(i, j)->getColour() == colour) {
                    myPieces.push_back(std::move(board->getPiece(i, j)));
                }
                else {
                    if (board->getPiece(i, j)->getPieceType() == Piece::PieceType::King) {
                        enemyKingPos = board->getPiece(i, j)->getPosition();
                    }
                    enemyPieces.push_back(std::move(board->getPiece(i, j)));
                }
            }
        }
    }

    std::vector<bool> dangerZones = std::vector<bool>(board->getBoardDimension() * board->getBoardDimension());

    for (auto& enemy : enemyPieces) {
        std::vector<Coordinate::Coordinate> enemyMoves = enemy->getValidLegalMoves();

        for (auto& danger : enemyMoves) {
            dangerZones[danger.row * board->getBoardDimension() + danger.col] = true;
        }
    }

    std::vector<ChessMove> moves = {};

    for (auto& piece : myPieces) {
        std::vector<Coordinate::Coordinate> validMoves = piece->getValidLegalMoves();

        for (auto& coord : validMoves) {
            std::unique_ptr<Piece> enemy = board->getPiece(coord);
            Coordinate::Coordinate pos = piece->getPosition();
            bool inDanger = dangerZones[pos.row * board->getBoardDimension() + pos.col];
            bool willBeInDanger = dangerZones[coord.row * board->getBoardDimension() + coord.col];

            int checkBonus = piece->canTargetSquareFrom(coord, enemyKingPos) && !willBeInDanger ? 3 : 0;
            int takePoints = enemy == nullptr ? 0 : enemy->toValue();
            int escOrTrade = inDanger == true && willBeInDanger == false ? piece->toValue() :
                (inDanger == false && willBeInDanger == true ? -piece->toValue() : 0);

            moves.push_back(ChessMove{piece->getPosition(), coord, checkBonus + takePoints + escOrTrade});
        }
    }

    std::shuffle(moves.begin(), moves.end(), rng);

    std::sort(moves.begin(), moves.end(), [](const ChessMove& a, const ChessMove& b) {
        return a.point < b.point;
    });

    while (moves.size() > 0) {
        bool turnTaken = board->takeTurn(moves.back().from, moves.back().to, colour);

        if (turnTaken) {
            int promotionRow = colour == Colour::White ? 7 : 0;
            if (board->getPiece(moves.back().to)->getPieceType() == Piece::PieceType::Pawn && moves.back().to.row == promotionRow) {
                board->promote(moves.back().to, Piece::PieceType::Queen, colour);
                std::cout << "move " << Coordinate::cartesianToChess(moves.back().from) << " "
                            << Coordinate::cartesianToChess(moves.back().to) << " Q" << std::endl;
            }
            else {
                std::cout << "move " << Coordinate::cartesianToChess(moves.back().from) << " "
                            << Coordinate::cartesianToChess(moves.back().to) << std::endl;
            }

            return true;
        }

        moves.pop_back();
    }

    return false;
}

bool ComputerPlayer::levelFour() {
    std::vector<std::unique_ptr<Piece>> myPieces {};

    for (int i = 0; i < board->getBoardDimension(); ++i) {
        for (int j = 0; j < board->getBoardDimension(); ++j) {
            if (board->getPiece(i, j) != nullptr) {
                if (board->getPiece(i, j)->getColour() == colour)
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

    Board *testBoard = new Board{*board};

    int max = std::numeric_limits<int>::min();
    ChessMove maxMove{};

    for (auto chessMove : legalMoves) {
        testBoard->takeTurn(chessMove.from, chessMove.to, colour);
        int score = minimax(testBoard, 1, true);
        if (score > max) {
            max = score;
            maxMove = chessMove;
        }
        testBoard->undoTurn();
    }

    std::cout << "move " << Coordinate::cartesianToChess(maxMove.from) << " "
        << Coordinate::cartesianToChess(maxMove.to) << std::endl;
    board->takeTurn(maxMove.from, maxMove.to, colour);

    delete testBoard;

    return true;
}
