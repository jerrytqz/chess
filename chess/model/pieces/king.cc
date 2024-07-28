#include "king.h"

char King::toChar() const {
    if (colour == Colour::Black) {
        return 'k';
    }
    else {
        return 'K';
    }
}
