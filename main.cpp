#include <iostream>
#include <fstream>
#include "ChessBoard.h"
#include "ChessPiece.h"

int main(int argc,const char* argv[]) {

    ChessBoard board;

    std::ifstream file("chess.txt");

    if (!file) {
        std::cout << "File not found"<<std::endl;
        return 0;
    }

    std::string name;
    std::string color;
    int row;
    int col;

    while (file >> name >> color >> row >> col) {

        ChessPiece* piece = nullptr;

        if (name == "Pawn")   piece = new Pawn(color);
        else if (name == "Rook")   piece = new Rook(color);
        else if (name == "Knight") piece = new Knight(color);
        else if (name == "Bishop") piece = new Bishop(color);
        else if (name == "Queen")  piece = new Queen(color);
        else if (name == "King")   piece = new King(color);

        if (piece != nullptr)
            board.placePiece(piece, row, col);
    }

    board.analyze("white");
    board.printBoard();

    return 0;
}