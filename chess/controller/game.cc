#include "game.h"
#include <iostream>
#include <memory>
#include "../shared/coordinate.h"
#include "../model/board.h"
#include "../view/observer.h"

Game::Game(Board* board, Player* whitePlayer, Player* blackPlayer):
    board{board}, whitePlayer{whitePlayer}, blackPlayer{blackPlayer} {}

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
        return Board::initializePiece(coords, colour, Piece::PieceType::Rook, board);
    }
    else if (lcPieceCode == 'n') { //knight
        return Board::initializePiece(coords, colour, Piece::PieceType::Knight, board);
    }
    else if (lcPieceCode == 'b') { //bishop
        return Board::initializePiece(coords, colour, Piece::PieceType::Bishop, board);
    }
    else if (lcPieceCode == 'q') { //queen
        return Board::initializePiece(coords, colour, Piece::PieceType::Queen, board);
    }
    else if (lcPieceCode == 'k') { //king
        return Board::initializePiece(coords, colour, Piece::PieceType::King, board);
    }
    else if (lcPieceCode == 'p') { //pawn
        return Board::initializePiece(coords, colour, Piece::PieceType::Pawn, board);
    }

    return nullptr;
}

void Game::setUp() { //this method interfaces with std::cout
    if (gameInProgress) {
        return;
    }

    //delete current board and initialize new board
    if (board) {
        delete board;
    }
    board = new Board{8};

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
    gameInProgress = true;
    while (true) {
        if (currentTurn == Colour::White) {
            if (!whitePlayer->takeTurn()) {
                std::cout << "Black wins!\n";
                gameInProgress = false;
                return;
            }
        } else {
            if (!blackPlayer->takeTurn()) {
                std::cout << "White wins!\n";
                gameInProgress = false;
                return;
            }
        }   
        notifyObservers();

        if (board->getBoardState() == Board::BoardState::WhiteCheckmated 
            || board->getBoardState() == Board::BoardState::BlackCheckmated 
            || board->getBoardState() == Board::BoardState::Stalemate) {
            gameInProgress = false;
            return;
        }
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
    for (const auto it : observers) {
        it->notify();
    }
}
