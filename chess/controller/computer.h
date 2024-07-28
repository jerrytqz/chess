#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include <vector>
#include "../shared/colour.h"
#include "./player.h"
class Board;
class Piece;

class ComputerPlayer : Player {
    public:
        ComputerPlayer(Board* board, Colour colour, int level);
        ~ComputerPlayer(); //DTOR

        void takeTurn() override;

    protected:

    private:
        Board* board;
        Colour colour;
        int level;
};

#endif