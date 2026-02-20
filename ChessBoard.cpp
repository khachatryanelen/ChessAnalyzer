#include <iostream>
#include "ChessBoard.h"
#include "ChessPiece.h"

ChessBoard::ChessBoard() : Matrix<ChessPiece*>(8,8){}
ChessBoard::ChessBoard(const ChessBoard& other): Matrix<ChessPiece*>(other){}
ChessBoard& ChessBoard::operator=(const ChessBoard& other) {
    Matrix<ChessPiece*>:: operator=(other);
    return *this;
}
ChessBoard::ChessBoard(ChessBoard&& other): Matrix<ChessPiece*>(std::move(other)){ }
ChessBoard& ChessBoard::operator =(ChessBoard&& other){
    if(this!=&other){
        Matrix<ChessPiece*>::operator=(std::move(other));
    }
    return *this;
}
ChessBoard::~ChessBoard(){}

bool ChessBoard::isKingInDanger(const std::string& color) {
    int kingRow=-1, kingCol=-1;

    for(int i=0;i<getRows();i++){
        for(int j=0;j<getColumns();j++){
            ChessPiece* piece = get(i,j);
            if(piece && piece->name()=="King" && piece->getColor()==color){
                kingRow=i; kingCol=j;
            }
        }
    }

    if(kingRow==-1) return false;

    for(int i=0;i<getRows();i++){
        for(int j=0;j<getColumns();j++){
            ChessPiece* piece = get(i,j);
            if(piece && piece->getColor()!=color){
                if(piece->canMoveTo(kingRow,kingCol,*this))
                    return true;
            }
        }
    }
    return false;
}

