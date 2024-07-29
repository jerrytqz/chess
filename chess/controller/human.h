#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include <vector>
#include "../shared/colour.h"
#include "./player.h"
class Board;

class HumanPlayer : public Player {
    public:
        HumanPlayer(Board* board, Colour colour);
        ~HumanPlayer() = default; //DTOR

        bool takeTurn() override;

    protected:

    private:
};

#endif
