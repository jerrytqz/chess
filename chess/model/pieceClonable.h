#include "piece.h"

template <typename T> class PieceClonable : public Piece {
public:
    std::unique_ptr<T> clone() const override {
        return std::make_unique<T>(*static_cast<T*>(this));
    }

    virtual ~PieceClonable() = 0;
private:

};
