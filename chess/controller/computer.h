#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H
#include <vector>
#include <tuple>
#include <random>
#include "../shared/colour.h"
#include "../shared/coordinate.h"
#include "./player.h"
class Board;

class ComputerPlayer : public Player {
    public:
        ComputerPlayer(Board* board, Colour colour, int level);
        ComputerPlayer(Board* board, Colour colour);
        ~ComputerPlayer() = default; //DTOR

        bool takeTurn() override;

    protected:

    private:
        static std::mt19937 rng;

        struct ChessMove {
            Coordinate::Coordinate from;
            Coordinate::Coordinate to;
            int point;
        };

        int level;

        bool levelOne();
        bool levelTwo();
        bool levelThree();
        bool levelFour();
        int minimax(Board *b, int depth, bool maximizing);
        int evaluate(Board *b);
};

#endif
