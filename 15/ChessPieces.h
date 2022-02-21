#ifndef CPPPROJ_CHESSPIECES_H
#define CPPPROJ_CHESSPIECES_H

#include "IChessPiece.h"

class BasePiece: public IChessPiece {
private:
    ConsoleColor clr;
    coord pos{};
    char sml;
public:
    BasePiece(ConsoleColor color, coord position, char cml_);

    ~BasePiece() override = default;

    /**If newPos in field (a-h 1-8) and in newPos not stay same-color piece*/
    bool isPossibleMove(coord newPos, std::unordered_map<coord, IChessPiece *> &figures);

    ConsoleColor color() override;

    void kill() override;

    void setPosition(coord newPos) override;

    coord getPosition() override;

    void movePiece(coord from, coord to, std::unordered_map<coord, IChessPiece *> &figures);

    char symbol() override;

    static bool isPieceOnTheWay(coord from, coord to, std::unordered_map<coord, IChessPiece *> figures) {
        coord temp = from;
        while (temp != to) {
            if (temp.number != to.number) {
                temp.number = temp.number + ((temp.number < to.number) ? 1 : -1);
            }
            if (temp.letter != to.letter) {
                temp.letter = temp.letter + ((temp.letter < to.letter) ? 1 : -1);
            }
            if (temp != to && figures.find(temp) != figures.end()) {
                return true;
            }
        }
        if (figures.find(to) == figures.end()) {
            return false;
        } else {
            if (figures[to]->color() == figures[from]->color()) {
                return true;
            } else {
                return false;
            }
        }
    }
};

class King: public BasePiece {
public:
    King(ConsoleColor color, coord position, char sml = 'K') : BasePiece(color, position, sml) {}

    int move(coord to, std::unordered_map<coord, IChessPiece *> &figures) override;
};

class Pawn: public BasePiece {
public:
    Pawn(ConsoleColor color, coord position, char sml = 'P') : BasePiece(color, position, sml) {}

    int move(coord to, std::unordered_map<coord, IChessPiece *> &figures) override;
};

class Horse: public BasePiece {
public:
    Horse(ConsoleColor color, coord position, char sml = 'H') : BasePiece(color, position, sml) {}

    int move(coord to, std::unordered_map<coord, IChessPiece *> &figures) override;
};

class Queen: public BasePiece {
public:
    Queen(ConsoleColor color, coord position, char sml = 'Q') : BasePiece(color, position, sml) {}

    int move(coord to, std::unordered_map<coord, IChessPiece *> &figures) override;
};

class Rook: public BasePiece {
public:
    Rook(ConsoleColor color, coord position, char sml = 'R') : BasePiece(color, position, sml) {}

    int move(coord to, std::unordered_map<coord, IChessPiece *> &figures) override;
};

class Bishop: public BasePiece {
public:
    Bishop(ConsoleColor color, coord position, char sml = 'B') : BasePiece(color, position, sml) {}

    int move(coord to, std::unordered_map<coord, IChessPiece *> &figures) override;
};

#endif//CPPPROJ_CHESSPIECES_H
