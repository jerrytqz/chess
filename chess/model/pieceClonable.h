#include "piece.h"

template <typename T> class PieceClonable : public Piece {
public:
    T& clone() override {
        return *new T{*static_cast<T*>(this)};
    }

    virtual ~PieceClonable() = 0;
};
