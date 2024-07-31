#include "graphicalObserver.h"
#include <string>
#include <sstream>
#include <iomanip>

GraphicalObserver::GraphicalObserver(Game* game): Observer{game}, window{new Xwindow{WINDOW_WIDTH, WINDOW_HEIGHT}} {}

void GraphicalObserver::notify() {
    Game::GameState gameState = game->getGameState();

    //draw board
    for (int i = 0; i < gameState.boardDimension; i++) {
        for (int j = 0; j < gameState.boardDimension; j++) {
            bool isEvenRank = (i % 2 == 0);
            bool isEvenFile = (j % 2 == 0);

            if ((isEvenRank && isEvenFile) || (!isEvenRank && !isEvenFile)) {
                window->fillRectangle(j * SQUARE_SIZE, i * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, Xwindow::Orange);
            } else {
                window->fillRectangle(j * SQUARE_SIZE, i * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, Xwindow::Brown);
            }
            if (gameState.board[gameState.boardDimension - 1 - i][j] != nullptr) { //piece exists
                // window->fillRectangle(j * SQUARE_SIZE + SQUARE_SIZE / 4, i * SQUARE_SIZE + SQUARE_SIZE / 4, SQUARE_SIZE / 2, SQUARE_SIZE / 2, Xwindow::White);
                window->drawString(
                    j * SQUARE_SIZE + SQUARE_SIZE / 2, i * SQUARE_SIZE + SQUARE_SIZE / 2, 
                    std::string(1, gameState.board[gameState.boardDimension - 1 - i][j]->toChar()), 
                    gameState.board[gameState.boardDimension - 1 - i][j]->getColour() == Colour::White ? Xwindow::White : Xwindow::Black
                );
            }
        }
        window->drawString(gameState.boardDimension * SQUARE_SIZE + SQUARE_SIZE / 4, i * SQUARE_SIZE + SQUARE_SIZE / 2, std::string(1, gameState.boardDimension - i + '0'));
    }

    for (int i = 0; i < gameState.boardDimension; i++) {
        window->drawString(i * SQUARE_SIZE + SQUARE_SIZE / 2, gameState.boardDimension * SQUARE_SIZE + SQUARE_SIZE / 2, std::string(1, 'a' + i));
    }

    std::string boardState;
    switch(gameState.boardState) {
        case Board::BoardState::Default:
            boardState = "Default";
            break;
        case Board::BoardState::WhiteChecked:
            boardState = "White Checked";
            break;
        case Board::BoardState::BlackChecked:
            boardState = "Black Checked";
            break;
        case Board::BoardState::WhiteCheckmated:
            boardState = "White Checkmated";
            break;
        case Board::BoardState::BlackCheckmated:
            boardState = "Black Checkmated";
            break;
        case Board::BoardState::Stalemate:
            boardState = "Stalemate";
            break;
    }

    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << "White: " << gameState.whiteScore << " Black: " << gameState.blackScore;

    window->fillRectangle(
        SQUARE_SIZE / 2, 
        gameState.boardDimension * SQUARE_SIZE + SQUARE_SIZE / 2 + 25, 
        gameState.boardDimension * SQUARE_SIZE, SQUARE_SIZE, Xwindow::White
    );
    window->drawString(
        SQUARE_SIZE / 2, 
        gameState.boardDimension * SQUARE_SIZE + SQUARE_SIZE, 
        gameState.currentTurn == Colour::White ? "White to move" : "Black to move"
    );
    window->drawString(
        SQUARE_SIZE / 2 + 2 * SQUARE_SIZE, 
        gameState.boardDimension * SQUARE_SIZE + SQUARE_SIZE, 
        "State: " + boardState
    );
    window->drawString(
        SQUARE_SIZE / 2 + 4 * SQUARE_SIZE, 
        gameState.boardDimension * SQUARE_SIZE + SQUARE_SIZE, 
        ss.str()
    );
}

GraphicalObserver::~GraphicalObserver() {
    delete window;
    window = nullptr;
}
