#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "../shared/colour.h"
class Board;

class Player {
    public:
        virtual ~Player() = default; //DTOR

        virtual bool takeTurn() = 0;

    protected:

    private:
        Board* board;
        Colour colour;
};

#endif
