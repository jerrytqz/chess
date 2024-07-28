#include "bishop.h"

char Bishop::toChar() const {
    if (colour == Colour::Black) {
        return 'b';
    }
    else {
        return 'B';
    }
}
