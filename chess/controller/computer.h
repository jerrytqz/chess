#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include <vector>
#include "../shared/colour.h"
#include "./player.h"
class Board;

class ComputerPlayer : public Player {
    public:
        ComputerPlayer(Board* board, Colour colour, int level);
        ~ComputerPlayer() = default; //DTOR

        bool takeTurn() override;

    protected:

    private:
        int level;

        void levelOne();
        void levelTwo();
        void levelThree();
        void levelFour();
};

#endif
