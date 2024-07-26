#ifndef PIECECLONABLE_H
#define PIECECLONABLE_H

#include "piece.h"

template <typename T> class PieceClonable : public Piece {
public:
    using Piece::Piece;

    Piece* clone() override {
        return new T{*static_cast<T*>(this)};
    }

    virtual ~PieceClonable() = 0;
private:
};

template <typename T> PieceClonable<T>::~PieceClonable() {}

#endif
