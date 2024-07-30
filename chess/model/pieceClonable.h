#ifndef PIECECLONABLE_H
#define PIECECLONABLE_H

#include "piece.h"
#include <cctype>

template <typename T> class PieceClonable : public Piece {
public:
    using Piece::Piece;

    char toChar() const override {
        if (colour == Colour::White) {
            return T::SYMBOL;
        } else {
            return std::tolower(T::SYMBOL);
        }
    }

    int toValue() const override {
        return T::VALUE;
    }   

    virtual ~PieceClonable() = 0;
protected:
    Piece* cloneImpl() override {
        return new T{*static_cast<T*>(this)};
    }
};

template <typename T> PieceClonable<T>::~PieceClonable() {}

#endif
