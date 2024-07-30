#include <iostream>
#include <memory>
#include "game.h"
#include "../shared/coordinate.h"
#include "../model/board.h"
#include "../view/observer.h"
#include "computer.h"
#include "human.h"

Game::Game(Board* board, Player::PlayerType whitePlayerType, Player::PlayerType blackPlayerType):
    board{board}, 
    currentTurn{Colour::White} {
        if (whitePlayerType == Player::PlayerType::Human)
            whitePlayer = new HumanPlayer{board, Colour::White};
        else
            whitePlayer = new ComputerPlayer{board, Colour::White};

        if (blackPlayerType == Player::PlayerType::Human)
            blackPlayer = new HumanPlayer{board, Colour::Black};
        else
            blackPlayer = new ComputerPlayer{board, Colour::Black}; 
    }

Game::~Game() {
    delete board;
    delete whitePlayer;
    delete blackPlayer;
}

Game::GameState::GameState(float whiteScore, float blackScore, Colour currentTurn, int boardDimension, std::unique_ptr<Piece>** board, Board::BoardState boardState):
    whiteScore{whiteScore}, blackScore{blackScore}, currentTurn{currentTurn}, boardDimension{boardDimension}, board{board}, boardState{boardState} {}

Game::GameState::~GameState() {
    for (int i = 0; i < boardDimension; i++) {
        delete[] board[i];
    }
    delete[] board;
}

void Game::setUp() { //this method interfaces with std::cout
    if (gameInProgress) {
        return;
    }

    //delete current board and initialize new board
    board->reset();
    notifyObservers();

    //command handling
    std::string command;
    while (std::cin >> command) {
        if (command == "+") { //add piece
            std::string pieceCode;
            std::string chessCoords;
            std::cin >> pieceCode >> chessCoords;
            if (!board->addPiece(pieceCode, Coordinate::chessToCartesian(chessCoords))) {
                std::cout << "Add failed. Invalid piece code or position.\n";
                continue;
            };
            notifyObservers();
        }
        else if (command == "-") { //remove piece
            std::string chessCoords;
            std::cin >> chessCoords;
            if (!board->removePiece(Coordinate::chessToCartesian(chessCoords))) {
                std::cout << "Remove failed. Invalid position.\n";
                continue;
            };
            notifyObservers();
        }
        else if (command == "=") { //set turn
            std::string colour;
            std::cin >> colour;
            if (colour == "black") {
                currentTurn = Colour::Black;
            }
            else if (colour == "white") {
                currentTurn = Colour::White;
            }
        }
        else if (command == "done") {
            if (board->verifyBoard(currentTurn)) {
                notifyObservers();
                return;
            }
            else {
                std::cout << "Invalid board: unable to leave setup mode.\n";
            }
        } else {
            std::cout << "Invalid command.\n";
        }
    }
}

void Game::play() {
    while (true) {
        notifyObservers();

        bool hasEnded = false;

        //make a move (DETECT RESIGN)
        if (currentTurn == Colour::White) {
            if (!whitePlayer->takeTurn()) {
                ++blackScore;
                std::cout << "Black wins!\n";
                hasEnded = true;
            }
        } else {
            if (!blackPlayer->takeTurn()) {
                ++whiteScore;
                std::cout << "White wins!\n";
                hasEnded = true;
            }
        }

        //next turn and recompute boardState
        currentTurn = currentTurn == Colour::White ? Colour::Black : Colour::White;
        board->computeBoardState(currentTurn);
        if (board->getBoardState() == Board::BoardState::WhiteCheckmated) {
            ++blackScore;
            hasEnded = true;
        } else if (board->getBoardState() == Board::BoardState::BlackCheckmated) {
            ++whiteScore;
            hasEnded = true;
        } else if (board->getBoardState() == Board::BoardState::Stalemate) {
            whiteScore += 0.5;
            blackScore += 0.5;
            hasEnded = true;
        }

        if (hasEnded) {
            notifyObservers();
            board->resetDefaultChess();
            return;
        }
    }
}

void Game::updatePlayer(Colour colour, Player::PlayerType playerType, int computerLevel) {
    Player* newPlayer;
    if (playerType == Player::PlayerType::Human) {
        newPlayer = new HumanPlayer{board, colour};
    }
    else {
        newPlayer = new ComputerPlayer{board, colour, computerLevel};
    }

    if (colour == Colour::Black) {
        if (blackPlayer) {
            delete blackPlayer;
        }
        blackPlayer = newPlayer;
    }
    else { //replace white player
        if (whitePlayer) {
            delete whitePlayer;
        }
        whitePlayer = newPlayer;
    }
}

void Game::detachObserver(Observer* obs) {
    observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
}

void Game::attachObserver(Observer* obs) {
    observers.emplace_back(obs); //not our fault if observer is included more than once
}

Game::GameState Game::getGameState() {
    return GameState{
        whiteScore,
        blackScore,
        currentTurn,
        board->getBoardDimension(),
        board->cloneBoard(),
        board->getBoardState()
    };
}

void Game::notifyObservers() {
    for (auto it : observers) {
        it->notify();
    }
}
