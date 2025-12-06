#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "Matrix.h"


class ChessBoard : public Matrix<char>{
public:
ChessBoard();
ChessBoard(const ChessBoard& other);
ChessBoard& operator=(const ChessBoard& other);
ChessBoard(ChessBoard&& other);
ChessBoard& operator =(ChessBoard&& other);
~ChessBoard();

};

#endif //CHESSBOARD_H