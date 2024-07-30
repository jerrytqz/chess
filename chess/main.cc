#include "controller/game.h"
#include "model/board.h"
#include "controller/player.h"
#include "view/textObserver.h"

int main() {
    Game game{
        new Board{8}, 
        Player::PlayerType::Human,
        Player::PlayerType::Human
    };

    Observer* textObs = new TextObserver{&game};

    game.setUp();

    game.play();

    delete textObs;
    
    return 0;
}
