#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "../shared/colour.h"
class Board;

class Player {
    public:
        Player(Board* board, Colour colour); //CTOR
        virtual ~Player() = default; //DTOR

        virtual bool takeTurn() = 0;

    protected:
        Board* const board;
        Colour colour;
    private:
};

#endif
