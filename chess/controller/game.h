#ifndef GAME_H
#define GAME_H

#include <vector>
#include "../shared/colour.h"
#include "../model/board.h"
#include "../controller/player.h"

class Piece;
class Observer;

int defaultBoardDimension = 8;

class Game {
    public:
        class GameState { //passed on to observers
            public:
                GameState(float whiteScore, float blackScore, Colour currentTurn, int boardDimension, std::unique_ptr<Piece>** board, Board::BoardState boardState);
                ~GameState();
                float whiteScore;
                float blackScore;
                Colour currentTurn;
                int boardDimension;
                std::unique_ptr<Piece>** board;
                Board::BoardState boardState;
        };

        Game(Board* board, Player* whitePlayer, Player* blackPlayer); //CTOR
        ~Game(); //DTOR

        void setUp();
        void play();
        void updatePlayer(Colour colour, Player* player);
        void detachObserver(Observer* obs);
        void attachObserver(Observer* obs);
        GameState getGameState();
        void notifyObservers();

    protected:

    private:
        Board* board;
        Player* whitePlayer;
        Player* blackPlayer;
        float whiteScore = 0;
        float blackScore = 0;
        std::vector<Observer*> observers;
        Colour currentTurn;
        bool gameHasStarted = false;
};

#endif
