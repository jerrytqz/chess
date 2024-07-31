#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H

#include "observer.h"

class TextObserver : public Observer {
    public:
        TextObserver(Game* game);
        ~TextObserver() = default;
        void notify() override final;

    protected:

    private:

};

#endif
