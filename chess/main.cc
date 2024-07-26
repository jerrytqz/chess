#include "model/pieces/pawn.h"

#include <iostream>

int main() {
    std::cout << "Hello world!" << std::endl;
    Piece* pawn = new Pawn(Coordinate{0, 0}, Piece::Colour::White, Piece::PieceType::Pawn, nullptr);
    delete pawn;
    
    return 0;
}
