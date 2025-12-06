#include <iostream>
#include <string>
#include "ChessPiece.h"

ChessPiece::ChessPiece(const std::string& color) : color(color) { }

ChessPiece::~ChessPiece() { }

std::string ChessPiece::getColor() const {
    return color;
}

Pawn::Pawn(const std::string& color) : ChessPiece(color) { }

std::string Pawn::name() const {
    return "Pawn";
}

Rook::Rook(const std::string& color) : ChessPiece(color) { }

std::string Rook::name() const {
    return "Rook";
}

Knight::Knight(const std::string& color) : ChessPiece(color) { }

std::string Knight::name() const {
    return "Knight";
}

Bishop::Bishop(const std::string& color) : ChessPiece(color) { }

std::string Bishop::name() const {
    return "Bishop";
}

Queen::Queen(const std::string& color) : ChessPiece(color) { }

std::string Queen::name() const {
    return "Queen";
}

King::King(const std::string& color) : ChessPiece(color) { }

std::string King::name() const {
    return "King";
}
