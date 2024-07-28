#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include <vector>
#include "../shared/colour.h"
#include "./player.h"
class Board;
class Piece;

class HumanPlayer : Player {
    public:
        HumanPlayer(Board* board, Colour colour);
        ~HumanPlayer() = default; //DTOR

        void takeTurn() override;

    protected:

    private:
        Board* board;
        Colour colour;
};

#endif