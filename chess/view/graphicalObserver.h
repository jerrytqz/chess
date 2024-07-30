#ifndef GRAPHICALOBSERVER_H
#define GRAPHICALOBSERVER_H

#include "observer.h"
#include "window.h"

class GraphicalObserver : public Observer {
    Xwindow* window;
public:
    static const int SQUARE_SIZE = 75;
    static const int WINDOW_WIDTH = 700;
    static const int WINDOW_HEIGHT = 700;

    GraphicalObserver(Game* game);
    ~GraphicalObserver();

    void notify() override final;
};

#endif
