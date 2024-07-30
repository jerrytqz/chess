#include "graphicalObserver.h"
#include <string>

GraphicalObserver::GraphicalObserver(Game* game): Observer{game}, window{new Xwindow{WINDOW_WIDTH, WINDOW_HEIGHT}} {}

void GraphicalObserver::notify() {
    Game::GameState gameState = game->getGameState();

    //print board
    for (int i = 0; i < gameState.boardDimension; i++) {
        for (int j = 0; j < gameState.boardDimension; j++) {
            bool isEvenRank = (i % 2 == 0);
            bool isEvenFile = (j % 2 == 0);

            if ((isEvenRank && isEvenFile) || (!isEvenRank && !isEvenFile)) {
                window->fillRectangle(j * SQUARE_SIZE, i * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, Xwindow::Red);
            } else {
                window->fillRectangle(j * SQUARE_SIZE, i * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, Xwindow::Blue);
            }
            if (gameState.board[gameState.boardDimension - 1 - i][j] != nullptr) { //piece exists
                window->fillRectangle(j * SQUARE_SIZE + SQUARE_SIZE / 4, i * SQUARE_SIZE + SQUARE_SIZE / 4, SQUARE_SIZE / 2, SQUARE_SIZE / 2, Xwindow::White);
                window->drawString(j * SQUARE_SIZE + SQUARE_SIZE / 2, i * SQUARE_SIZE + SQUARE_SIZE / 2, std::string(1, gameState.board[gameState.boardDimension - 1 - i][j]->toChar()));
            }
        }
        window->drawString(gameState.boardDimension * SQUARE_SIZE, i * SQUARE_SIZE, "HELLO");
    }
}

GraphicalObserver::~GraphicalObserver() {
    delete window;
    window = nullptr;
}
