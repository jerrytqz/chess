#include "knight.h"

char Knight::toChar() const {
    if (colour == Colour::Black) {
        return 'n';
    }
    else {
        return 'N';
    }
}
