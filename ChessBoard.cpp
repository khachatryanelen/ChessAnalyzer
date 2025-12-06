#include <iostream>
#include "ChessBoard.h"
#include "Matrix.h"

ChessBoard::ChessBoard() : Matrix(8,8){}
ChessBoard::ChessBoard(const ChessBoard& other): Matrix<char>(other){}
ChessBoard& ChessBoard::operator=(const ChessBoard& other) {
    Matrix<char>:: operator=(other);
    return *this;
}
ChessBoard::ChessBoard(ChessBoard&& other): Matrix<char>(std::move(other)){ }
ChessBoard& ChessBoard::operator =(ChessBoard&& other){
    if(this!=&other){
        Matrix<char>::operator=(std::move(other));
    }
    return *this;
}
ChessBoard::~ChessBoard(){}

