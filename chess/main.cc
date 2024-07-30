#include "controller/game.h"
#include "model/board.h"
#include "controller/player.h"
#include "view/textObserver.h"
#include <limits>

bool updateGamePlayer(Game& game, Colour colour, std::string player) {
    if (player == "human") {
        game.updatePlayer(colour, Player::PlayerType::Human);
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
    while (true) {
        std::cout << "Please specify a command: ";
        std::cin >> command;
        if (std::cin.eof() || command == "quit") {
            std::cout << "\nFINAL SCORES\n";
            std::cout << "White: " << game.getWhiteScore() << "\n";
            std::cout << "Black: " << game.getBlackScore() << "\n\n";
            break;
        }
        else if (command == "game") {
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
        } else {
            std::cout << "Invalid command.\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    delete textObs;
    
    return 0;
}
