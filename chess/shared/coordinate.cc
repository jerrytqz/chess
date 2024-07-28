#include "coordinate.h"

Coordinate::Coordinate Coordinate::chessToCartesian(std::string chessCoordinate) {
    if (!checkValidChess(chessCoordinate)) { //not valid chess coordinate
        return Coordinate{-1, -1};
    }
    int col = chessCoordinate[0] - 'a';
    int row = chessCoordinate[1] - '1';
    return Coordinate{row, col};
}

std::string Coordinate::cartesianToChess(Coordinate cartesianCoordinate) {
    std::string chessCoord = "";
    chessCoord.push_back(cartesianCoordinate.col + 'a');
    chessCoord.push_back(cartesianCoordinate.row + '1');
    return chessCoord;
}

bool Coordinate::checkValidChess(std::string str) {
    if (str.length() == 2 && str[0] >= 'a' && str[0] <= 'h' && str[1] >= '1' && str[1] <= '8') {
        return true;
    }

    return false;
}

bool Coordinate::checkBounds(Coordinate coord, int dimension) {
    return coord.row >= 0 && coord.row < dimension && coord.col >= 0 && coord.col < dimension;
}
