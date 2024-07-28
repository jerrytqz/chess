#include "controller/game.h"
#include "model/board.h"
#include "controller/human.h"

int main() {
    Board* board = new Board{8};
    Game game{
        board, 
        new HumanPlayer{board, Colour::White}, 
        new HumanPlayer{board, Colour::Black}
    };

    game.setUp();

    return 0;
}
