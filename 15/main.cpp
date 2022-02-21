#include <iostream>
#include "ChessPieces.h"
#include "ChessField.h"

int main() {
    ChessField field;
    field.outField();
    std::string from, to;
    ConsoleColor player = White;
    while (true) {
        field.outField();
        std::cout << ((player == White) ? "Whites" : "Black");
        std::cout << " go!\n";
        field.moveFigure(player);
        if (player == White) {
            player = Black;
        } else {
            player = White;
        }
    }
    return 0;
}
