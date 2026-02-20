#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "Matrix.h"
#include <string>

class ChessPiece;

class ChessBoard : public Matrix<ChessPiece*>{
public:
ChessBoard();
ChessBoard(const ChessBoard& other);
ChessBoard& operator=(const ChessBoard& other);
ChessBoard(ChessBoard&& other);
ChessBoard& operator =(ChessBoard&& other);
~ChessBoard();


void placePiece(ChessPiece* piece, int row, int col) {
    set(row,col,piece);
}

bool isKingInDanger(const std::string& color);

};

#endif //CHESSBOARD_H