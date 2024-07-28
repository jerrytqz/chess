#include "queen.h"

char Queen::toChar() const {
    if (colour == Colour::Black) {
        return 'q';
    }
    else {
        return 'Q';
    }
}
