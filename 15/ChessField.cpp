#include "ChessField.h"
#include "ChessPieces.h"

ChessField::ChessField() {
    setDefaultField();
}

ChessField::~ChessField() {
    for (auto i: figures) {
        delete figures[i.first];
    }
}

void ChessField::outField() {
    system("CLS");
    SetCursorColor(Black, White);
    std::cout << "  ";
    for (byte i = 1; i < FIELD_SIZE + 1; i++) {
        std::cout << ' ' << int(i) << ' ';
    }
    std::cout << '\n';

    for (byte i_ = FIELD_SIZE; i_ > 0; i_--) {
        byte i = i_ - 1;
        std::cout << char('a' + i) << ' ';
        for (byte j = 0; j < FIELD_SIZE; j++) {
            if (figures.find(coord{i, j}) != figures.end()) {
                outCell(coord{i, j});
            } else {
                outEmptyCell(coord{i, j});
            }
        }
        SetCursorColor(Black, White);
        std::cout << ' ' << char('a' + i) << std::endl;
    }
    std::cout << "  ";
    for (byte i = 1; i < FIELD_SIZE + 1; i++) {
        std::cout << ' ' << int(i) << ' ';
    }
    std::cout << '\n';
}

void ChessField::moveFigure(ConsoleColor playerColor) {
    std::string from, to;
    coord fromCoord{}, toCoord{};
    int isSuccess = 1;
    while (isSuccess) {
        std::cout << "Enter move.\n";
        std::cin >> from >> to;
        if (from[0] >= 'a' && from[0] <= 'h' && to[0] >= 'a' && to[0] <= 'h' &&
            from[1] >= '1' && from[1] <= '8' && to[1] >= '1' && to[1] <= '8' &&
            from.size() == 2 && to.size() == 2) {
            fromCoord = coord{static_cast<byte>(from[0] - 'a'), static_cast<byte>(from[1] - '1')};
            toCoord = coord{static_cast<byte>(to[0] - 'a'), static_cast<byte>(to[1] - '1')};
            if (figures[fromCoord]->color() == playerColor) {
                isSuccess = figures[fromCoord]->move(toCoord, figures);
            }
        }
        std::cout << "Wrong move!\n";
    }
}

IChessPiece* ChessField::operator[](coord pos) const {
    if (figures.find(pos) != figures.end()) {
        return figures.find(pos)->second;
    } else {
        throw std::runtime_error("invalid index " + std::to_string(pos.letter) + " " + std::to_string(pos.number));
    }
}

void ChessField::setDefaultField() {
    figures[coord{0, 0}] = new Rook(White, coord{0, 0});
    figures[coord{0, 1}] = new Horse(White, coord{0, 1});
    figures[coord{0, 2}] = new Bishop(White, coord{0, 2});
    figures[coord{0, 3}] = new Queen(White, coord{0, 3});
    figures[coord{0, 4}] = new King(White, coord{0, 4});
    figures[coord{0, 5}] = new Bishop(White, coord{0, 5});
    figures[coord{0, 6}] = new Horse(White, coord{0, 6});
    figures[coord{0, 7}] = new Rook(White, coord{0, 7});
    figures[coord{7, 0}] = new Rook(Black, coord{7, 0});
    figures[coord{7, 1}] = new Horse(Black, coord{7, 1});
    figures[coord{7, 2}] = new Bishop(Black, coord{7, 2});
    figures[coord{7, 3}] = new Queen(Black, coord{7, 3});
    figures[coord{7, 4}] = new King(Black, coord{7, 4});
    figures[coord{7, 5}] = new Bishop(Black, coord{7, 5});
    figures[coord{7, 6}] = new Horse(Black, coord{7, 6});
    figures[coord{7, 7}] = new Rook(Black, coord{7, 7});
    for (byte i = 0; i < FIELD_SIZE; i++) {
        figures[coord{1, i}] = new Pawn(White, coord{1, i});
        figures[coord{6, i}] = new Pawn(Black, coord{6, i});
    }
}

void ChessField::outCell(coord pos) {
    ConsoleColor posColor;
    if ((pos.letter + pos.number) % 2 == 0) {
        posColor = DarkGrey;
    } else {
        posColor = LightGrey;
    }
    SetCursorColor(posColor, figures[pos]->color());
    std::cout << ' ' << figures[pos]->symbol() << ' ';
}
