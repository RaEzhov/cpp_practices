#ifndef CPPPROJ_ICHESSPIECE_H
#define CPPPROJ_ICHESSPIECE_H

#include <Windows.h>
#include <unordered_map>

const int FIELD_SIZE = 8;

struct coord {
    byte letter;
    byte number;
};

bool operator==(const coord& lhs, const coord& rhs);

bool operator!=(const coord& lhs, const coord& rhs);

template<>
struct std::hash<coord> {
    std::size_t operator()(coord pos) const noexcept{
        return std::hash<unsigned char>()(pos.letter) ^ std::hash<unsigned char>()(pos.number);
    }
};

enum ConsoleColor {
    Black = 0,
    LightGrey = 7,
    DarkGrey = 8,
    White = 15
};

class IChessPiece {
public:
    virtual int move(coord, std::unordered_map<coord, IChessPiece *> &) = 0;

    virtual ConsoleColor color() = 0;

    virtual char symbol() = 0;

    virtual coord getPosition() = 0;

    virtual void setPosition(coord) = 0;

    virtual void kill() = 0;

    virtual ~IChessPiece() = default;
};

#endif//CPPPROJ_ICHESSPIECE_H
