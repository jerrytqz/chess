#include "controller/game.h"
#include "model/board.h"
#include "controller/human.h"
#include "view/textObserver.h"

int main() {
    Board* board = new Board{8};
    Game game{
        board, 
        new HumanPlayer{board, Colour::White}, 
        new HumanPlayer{board, Colour::Black}
    };

    TextObserver* textObs = new TextObserver{&game};
    game.notifyObservers();

    game.setUp();

    game.notifyObservers();

    delete textObs;
    return 0;
}
