#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include <random>
#include <vector>
#include "../shared/colour.h"
#include "./player.h"
class Board;

class ComputerPlayer : public Player {
    public:
        ComputerPlayer(Board* board, Colour colour, int level);
        ~ComputerPlayer(); //DTOR

        bool takeTurn() override;

    protected:

    private:
        int level;
        std::random_device rd; 
        std::mt19937 gen;

        void levelOne();
        void levelTwo();
        void levelThree();
        void levelFour();
};

#endif
