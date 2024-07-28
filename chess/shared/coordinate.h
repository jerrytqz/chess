#ifndef COORDINATE_H
#define COORDINATE_H

#include <string>
#include <iostream>

namespace Coordinate {
    // NOTE: Origin for coordinates is the bottom left corner of the board
    struct Coordinate {
        int row;
        int col;

        bool operator==(const Coordinate& other) const {
            return (row == other.row && col == other.col);
        }
    };

    bool checkValidChess(std::string possibleChessCoordinate);
    bool checkBounds(Coordinate coord, int dimension);

    Coordinate chessToCartesian(std::string chessCoordinate);

    std::string cartesianToChess(Coordinate cartesianCoordinate);
}

std::ostream& operator<<(std::ostream& os, const Coordinate::Coordinate& coord);

#endif
