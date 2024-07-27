#include "coordinate.h"

Coordinate::Coordinate chessToCartesian(std::string chessCoordinate) {
    int col = chessCoordinate[0] - 'a';
    int row = chessCoordinate[1] - 1;
    return Coordinate::Coordinate{row, col};
}

std::string cartesianToChess(Coordinate::Coordinate cartesianCoordinate) {
    std::string chessCoord = "";
    chessCoord.push_back(cartesianCoordinate.col + 'a');
    chessCoord.push_back(cartesianCoordinate.row + 1);
    return chessCoord;
}

bool checkValidChessCoord(std::string str) {
    if (str.length() != 2 && str[0] >= 'a' && str[0] <= 'h' && str[1] >= '1' && str[1] <= '8')
        return true;

    return false;
}