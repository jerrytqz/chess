#include "controller/game.h"
#include "model/board.h"
#include "controller/player.h"
#include "view/textObserver.h"

int main() {
    Game game{
        new Board{8}, 
        Player::PlayerType::Human,
        Player::PlayerType::Computer
    };

    Observer* textObs = new TextObserver{&game};

    // game.setUp();

    game.notifyObservers();
    game.play();

    delete textObs;
    
    return 0;
}
