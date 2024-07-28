#include "rook.h"

char Rook::toChar() const {
    if (colour == Colour::Black) {
        return 'r';
    }
    else {
        return 'R';
    }
}
