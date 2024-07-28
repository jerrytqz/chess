#ifndef COORDINATE_H
#define COORDINATE_H

#include <string>

namespace Coordinate {

    struct Coordinate {
        int row;
        int col;
    };

    Coordinate chessToCartesian(std::string chessCoordinate);

    std::string cartesianToChess(Coordinate cartesianCoordinate);

    bool checkValidChess(std::string possibleChessCoordinate);
}

#endif
