#ifndef GAME_H
#define GAME_H

#include <vector>
#include "../shared/colour.h"
#include "../model/board.h"
#include "player.h"

class Piece;
class Observer;

class Game {
    public:
        class GameState { //passed on to observers
            public:
                GameState(float whiteScore, float blackScore, Colour currentTurn, int boardDimension, std::unique_ptr<Piece>** board, Board::BoardState boardState); //CTOR
                GameState(const GameState& other); //copy CTOR
                ~GameState();
                float whiteScore;
                float blackScore;
                Colour currentTurn;
                int boardDimension;
                std::unique_ptr<Piece>** board;
                Board::BoardState boardState;
        };

        Game(Board* board, Player::PlayerType whitePlayerType, Player::PlayerType blackPlayerType); //CTOR
        ~Game(); //DTOR

        void setUp();
        void play();
        void updatePlayer(Colour colour, Player::PlayerType playerType, int computerLevel = 1);
        void detachObserver(Observer* obs);
        void attachObserver(Observer* obs);
        GameState getGameState();
        void notifyObservers();

    protected:

    private:
        Board* const board;
        Player* whitePlayer;
        Player* blackPlayer;
        float whiteScore = 0;
        float blackScore = 0;
        std::vector<Observer*> observers;
        Colour currentTurn;
        bool gameInProgress = false;
};

#endif
