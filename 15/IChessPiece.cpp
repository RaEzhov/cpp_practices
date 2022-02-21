#include "IChessPiece.h"

bool operator==(const coord& lhs, const coord& rhs) {
    return lhs.letter == rhs.letter && lhs.number == rhs.number;
}

bool operator!=(const coord& lhs, const coord& rhs) {
    return !(lhs == rhs);
}

