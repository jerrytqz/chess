#include "controller/game.h"
#include "model/board.h"
#include "controller/player.h"
#include "view/textObserver.h"

bool updateGamePlayer(Game& game, Colour colour, std::string player) {
    if (player == "human") {
        game.updatePlayer(Colour::White, Player::PlayerType::Human);
        return true;
    }
    else if (player.size() == 9 && player.substr(0, 8) == "computer" && player[8] >= '1' && player[8] <= '4') { //valid: e.g. "computer1"
        game.updatePlayer(colour, Player::PlayerType::Computer, player[8] - '0');
        return true;
    }
    return false;
}
int main() {
    Game game{
        new Board{8}, 
        Player::PlayerType::Human,
        Player::PlayerType::Human
    };
    Observer* textObs = new TextObserver{&game};

    std::string command;
    while (std::cout << "Please specify a command: " && std::cin >> command) {
        if (command == "game") {
            std::string whitePlayer, blackPlayer;
            std::cin >> whitePlayer >> blackPlayer;
            if (updateGamePlayer(game, Colour::White, whitePlayer) && updateGamePlayer(game, Colour::Black, blackPlayer)) {
                std::cout << "Starting new game.\n";
                game.play();
            }
            else {
                std::cout << "Invalid game parameters.\n";
            }
        }
        else if (command == "setup") {
            game.setUp();
            std::cout << "Exiting setup mode.\n";
        }
    }

    delete textObs;
    
    return 0;
}
