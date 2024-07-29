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

    Observer* textObs = new TextObserver{&game};

    // game.setUp();

    game.notifyObservers();
    game.play();

    delete textObs;
    
    return 0;
}
