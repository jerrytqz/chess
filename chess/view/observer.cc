#include "observer.h"

Observer::Observer(Game* game): game{game} {
    game->attachObserver(this);
}

Observer::~Observer() {
    game->detachObserver(this);
}
