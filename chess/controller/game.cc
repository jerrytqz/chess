#include "game.h"
#include <iostream>
#include "../shared/coordinate.h"
#include "../model/pieces/pawn.h"

Game::Game(Board* board, Player* whitePlayer, Player* blackPlayer): board{board}, whitePlayer{whitePlayer}, blackPlayer{blackPlayer} {
    //no need for implementation
}

Game::~Game() {
    delete board;
    delete whitePlayer;
    delete blackPlayer;
}

bool isCapital(char c) { //setup helper
    return (c >= 'A' && c <= 'Z');
}
Piece* generatePiece(std::string pieceCode, Coordinate::Coordinate coords, Board* board) { //setup helper
    Colour colour = isCapital(pieceCode[0]) ? Colour::White : Colour::Black;
    char lcPieceCode = pieceCode[0];
    if (pieceCode[0] >= 'A') {
        lcPieceCode = 'a' + (lcPieceCode - 'A');
    }

    if (lcPieceCode == 'r') { //rook

    }
    else if (lcPieceCode == 'n') { //knight

    }
    else if (lcPieceCode == 'b') { //bishop

    }
    else if (lcPieceCode == 'q') { //queen

    }
    else if (lcPieceCode == 'k') { //king

    }
    else if (lcPieceCode == 'p') { //pawn
        return new Pawn{coords, colour, board};
    }

    return nullptr;
}
void Game::setUp() { //this method interfaces with std::cout
    if (gameHasStarted) {
        return;
    }

    //delete current board and initialize new board
    if (board) {
        delete board;
    }
    board = new Board{defaultBoardDimension};

    //command handling
    std::string command;
    while (std::cin >> command) {
        if (command == "+") { //add piece
            std::string pieceCode;
            std::string chessCoords;
            std::cin >> pieceCode >> chessCoords;
            board->addPiece(generatePiece(pieceCode, Coordinate::chessToCartesian(chessCoords), board));
            notifyObservers(); //redisplay board
        }
        else if (command == "-") { //remove piece
            std::string chessCoords;
            std::cin >> chessCoords;
            board->removePiece(Coordinate::chessToCartesian(chessCoords));
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
                return;
            }
            else {
                std::cout << "Invalid board: unable to leave setup mode.\n";
            }
        }
    }
}

void Game::play() {
    while (true) {
        if (currentTurn == Colour::White) {
            if (!whitePlayer->takeTurn()) {
                std::cout << "White resigns. Black wins.\n";
                return;
            }
        } else {
            if (!blackPlayer->takeTurn()) {
                std::cout << "Black resigns. White wins.\n";
                return;
            }
        }

        if (board->getBoardState() == Board::BoardState::WhiteChecked) {
            std::cout << "White is in check.\n";
        }
        else if (board->getBoardState() == Board::BoardState::BlackChecked) {
            std::cout << "Black is in check.\n";
        }
        else if (board->getBoardState() == Board::BoardState::WhiteCheckmated) {
            std::cout << "White is checkmated. Black wins.\n";
            return;
        }
        else if (board->getBoardState() == Board::BoardState::BlackCheckmated) {
            std::cout << "Black is checkmated. White wins.\n";
            return;
        }
        else if (board->getBoardState() == Board::BoardState::Stalemate) {
            std::cout << "Stalemate.\n";
            return;
        }
        
        notifyObservers();
    }
}

void Game::updatePlayer(Colour colour, Player* player) {
    if (colour == Colour::Black) {
        if (blackPlayer) {
            delete blackPlayer;
        }
        blackPlayer = player;
    }
    else { //replace white player
        if (whitePlayer) {
            delete whitePlayer;
        }
        whitePlayer = player;
    }
}

void Game::detachObserver(Observer* obs) {
    //find where observer is in list and delete it
    for (auto it = observers.begin(); it != observers.end(); it++) {
        if (*it == obs) {
            observers.erase(it);
            return;
        }
    }
}

void Game::attachObserver(Observer* obs) {
    observers.push_back(obs); //not our fault if observer is included more than once
}

Game::GameState Game::getGameState() {
    // return GameState {
    //     whiteScore,
    //     blackScore,
    //     currentTurn,
    //     board->getBoardDimension(),

    //     board->getBoardState(),
    // };
}

void Game::notifyObservers() {

}
