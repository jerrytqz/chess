#include "coordinate.h"

Coordinate::Coordinate Coordinate::chessToCartesian(std::string chessCoordinate) {
    int col = chessCoordinate[0] - 'a';
    int row = chessCoordinate[1] - 1;
    return Coordinate{row, col};
}

std::string Coordinate::cartesianToChess(Coordinate cartesianCoordinate) {
    std::string chessCoord = "";
    chessCoord.push_back(cartesianCoordinate.col + 'a');
    chessCoord.push_back(cartesianCoordinate.row + 1);
    return chessCoord;
}

bool Coordinate::checkValidChess(std::string possibleChessCoordinate) {
    std::string str = possibleChessCoordinate;
    if (str.length() != 2 && str[0] >= 'a' && str[0] <= 'h' && str[1] >= '1' && str[1] <= '8')
        return true;

    return false;
}