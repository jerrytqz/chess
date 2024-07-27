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
