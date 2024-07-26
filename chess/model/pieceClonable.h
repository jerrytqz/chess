#ifndef PIECECLONABLE_H
#define PIECECLONABLE_H

#include "piece.h"

template <typename T> class PieceClonable : public Piece {
public:
    using Piece::Piece;

    virtual ~PieceClonable() = 0;
protected:
    Piece* cloneImpl() override {
        return new T{*static_cast<T*>(this)};
    }
};

template <typename T> PieceClonable<T>::~PieceClonable() {}

#endif
