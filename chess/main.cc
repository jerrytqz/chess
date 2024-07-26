#include "model/pieces/pawn.h"

#include <iostream>

int main() {
    std::cout << "Hello world!" << std::endl;
    Piece* pawn = new Pawn{Coordinate{0, 0}, Piece::Colour::White, Piece::PieceType::Pawn, nullptr};
    std::unique_ptr<Piece> pawnClone = pawn->clone();
    delete pawn;
    
    return 0;
}
