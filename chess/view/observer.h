#ifndef OBSERVER_H
#define OBSERVER_H

#include "../controller/game.h"

class Observer {
    public:
        Observer(Game* game): game{game} {
            game->attachObserver(this);
        };
        virtual ~Observer() {
            game->detachObserver(this);
        };
        virtual void notify() = 0;

    protected:
        Game* game;
    private:

};

#endif
