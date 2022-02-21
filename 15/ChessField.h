#ifndef CPPPROJ_CHESSFIELD_H
#define CPPPROJ_CHESSFIELD_H

#include <iostream>
#include "IChessPiece.h"

class ChessField {
public:
    ChessField();

    ~ChessField();

    bool cellUnderAttack(coord cell, ConsoleColor color);

    void outField();

    /**Enter move from keyboard and check if it a-h, 1-8.*/
    void moveFigure(ConsoleColor playerColor);

    IChessPiece *operator[](coord pos) const;

private:
    std::unordered_map<coord, IChessPiece *> figures;

    void setDefaultField();

    static void outEmptyCell(coord pos) {
        if ((pos.letter + pos.number) % 2 == 0) {
            SetCursorColor(DarkGrey, Black);
        } else {
            SetCursorColor(LightGrey, Black);
        }
        std::cout << "   ";
    }

    static void SetCursorColor(ConsoleColor background, ConsoleColor text = Black) {
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdOut, (WORD) ((background << 4) | text));
    }

    void outCell(coord pos);
};


#endif//CPPPROJ_CHESSFIELD_H
