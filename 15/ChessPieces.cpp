#include "ChessPieces.h"

BasePiece::BasePiece(ConsoleColor color, coord position, char sml_) {
    clr = color;
    pos = position;
    sml = sml_;
}

bool BasePiece::isPossibleMove(coord newPos, std::unordered_map<coord, IChessPiece *> &figures) {
    if (figures.find(newPos) != figures.end() && figures[newPos]->color() == color()) {
        return false;
    }
    return (newPos.letter >= 0 && newPos.letter < FIELD_SIZE && newPos.number >= 0 && newPos.number < FIELD_SIZE);
}
ConsoleColor BasePiece::color() {
    return clr;
}

void BasePiece::kill() {
    delete this;
}

void BasePiece::setPosition(coord newPos) {
    if (newPos.letter >= 0 and newPos.number >= 0 and newPos.letter < FIELD_SIZE and newPos.number < FIELD_SIZE) {
        pos = newPos;
    } else {
        throw std::runtime_error("Wrong position!");
    }
}

void BasePiece::movePiece(coord from, coord to, std::unordered_map<coord, IChessPiece *> &figures) {
    if (figures.find(to) != figures.end()) {
        figures[to]->kill();
    }
    figures[to] = figures[from];
    figures.erase(from);
    setPosition(to);
}

coord BasePiece::getPosition() {
    return pos;
}

char BasePiece::symbol() {
    return sml;
}

int King::move(coord to, std::unordered_map<coord, IChessPiece *> &figures) {
    auto nowPos = getPosition();
    if (isPossibleMove(to, figures) && to != nowPos && abs(to.letter - nowPos.letter) <= 1 &&
        abs(to.number - nowPos.number) <= 1) {
        movePiece(nowPos, to, figures);
        return 0;
    } else {
        return 1;
    }
}

int Pawn::move(coord to, std::unordered_map<coord, IChessPiece *> &figures) {
    auto nowPos = getPosition();
    if (isPossibleMove(to, figures)) {
        if (color() == White) {
            if (nowPos.letter + 1 == to.letter && nowPos.number == to.number && figures.find(to) == figures.end()) {
                movePiece(nowPos, to, figures);
                return 0;
            }
            if (nowPos.letter + 2 == to.letter && nowPos.number == to.number && nowPos.letter == 'b' - 'a' &&
                figures.find(to) == figures.end() &&
                figures.find(coord{static_cast<byte>(nowPos.letter + 1), nowPos.number}) == figures.end()) {
                movePiece(nowPos, to, figures);
                return 0;
            }
            if (nowPos.letter + 1 == to.letter &&
                (nowPos.number + 1 == to.number || nowPos.number - 1 == to.number) &&
                figures.find(to) != figures.end()) {
                movePiece(nowPos, to, figures);
                return 0;
            }
            return 1;
        } else {
            if (nowPos.letter - 1 == to.letter && nowPos.number == to.number && figures.find(to) == figures.end()) {
                movePiece(nowPos, to, figures);
                return 0;
            }
            if (nowPos.letter - 2 == to.letter && nowPos.number == to.number && nowPos.letter == 'g' - 'a' &&
                figures.find(to) == figures.end() &&
                figures.find(coord{static_cast<byte>(nowPos.letter - 1), nowPos.number}) == figures.end()) {
                movePiece(nowPos, to, figures);
                return 0;
            }
            if (nowPos.letter - 1 == to.letter &&
                (nowPos.number + 1 == to.number || nowPos.number - 1 == to.number) &&
                figures.find(to) != figures.end()) {
                movePiece(nowPos, to, figures);
                return 0;
            }
            return 1;
        }
    } else {
        return 1;
    }
}

int Horse::move(coord to, std::unordered_map<coord, IChessPiece *> &figures) {
    auto nowPos = getPosition();
    if (isPossibleMove(to, figures) &&
        (abs(nowPos.letter - to.letter) == 2 && abs(nowPos.number - to.number) == 1 ||
         abs(nowPos.letter - to.letter) == 1 && abs(nowPos.number - to.number) == 2)) {
        movePiece(nowPos, to, figures);
        return 0;
    } else {
        return 1;
    }
}

int Queen::move(coord to, std::unordered_map<coord, IChessPiece *> &figures) {
    auto nowPos = getPosition();
    if (isPossibleMove(to, figures) && (abs(nowPos.letter - to.letter) == abs(nowPos.number - to.number) ||
                                        (nowPos.number == to.number) && (nowPos.letter != to.letter) ||
                                        (nowPos.number != to.number) && (nowPos.letter == to.letter))) {
        if (!isPieceOnTheWay(nowPos, to, figures)) {
            movePiece(nowPos, to, figures);
            return 0;
        } else {
            return 1;
        }
    } else {
        return 1;
    }
}


int Rook::move(coord to, std::unordered_map<coord, IChessPiece *> &figures) {
    auto nowPos = getPosition();
    if (isPossibleMove(to, figures) && (nowPos.number == to.number) && (nowPos.letter != to.letter) ||
        (nowPos.number != to.number) && (nowPos.letter == to.letter)) {
        if (!isPieceOnTheWay(nowPos, to, figures)) {
            movePiece(nowPos, to, figures);
            return 0;
        } else {
            return 1;
        }
    } else {
        return 1;
    }
}

int Bishop::move(coord to, std::unordered_map<coord, IChessPiece *> &figures) {
    auto nowPos = getPosition();
    if (isPossibleMove(to, figures) && abs(nowPos.letter - to.letter) == abs(nowPos.number - to.number)) {
        if (!isPieceOnTheWay(nowPos, to, figures)) {
            movePiece(nowPos, to, figures);
            return 0;
        } else {
            return 1;
        }
    } else {
        return 1;
    }
}
