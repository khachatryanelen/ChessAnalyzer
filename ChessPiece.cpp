#include <iostream>
#include <string>
#include "ChessPiece.h"
#include "ChessBoard.h"

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

bool Pawn::canMoveTo(int targetRow,int targetCol,const ChessBoard& board){
    if(targetRow < 0 || targetRow >= board.getRows() || targetCol < 0 || targetCol >= board.getColumns())
        return false;

    int direction=(color=="white")? -1 : 1;
    int row=-1,col=-1;

    for(int i=0;i<board.getRows();i++){
        for(int j=0;j<board.getColumns();j++){
            if(board.get(i,j)==this) row=i,col=j;
        }
    }
    
    if(row==-1) return false;

    if(targetRow == row && targetCol == col)
        return false;

    if(targetRow==row+direction &&(targetCol==col+1 || targetCol==col-1))
        return board.get(targetRow,targetCol)!=nullptr;

    if(targetRow==row+direction && targetCol==col && board.get(targetRow,targetCol)==nullptr)
        return true;

    if((color=="white" && row==6) || (color=="black" && row==1)){
        if(targetRow==row+2*direction && targetCol==col){
            if(board.get(row+direction,col)==nullptr && board.get(targetRow,col)==nullptr)
                return true;
        }
    }
    
    return false;
}

bool Rook::canMoveTo(int targetRow, int targetCol, const ChessBoard& board) {
    if(targetRow < 0 || targetRow >= board.getRows() || targetCol < 0 || targetCol >= board.getColumns())
        return false;

    int row=-1, col=-1;

    for(int i=0;i<board.getRows();i++){
        for(int j=0;j<board.getColumns();j++){
            if(board.get(i,j)==this) row=i,col=j;
        }
    }

    if(row==-1) return false;

    if(targetRow == row && targetCol == col)
        return false;

    if(row!=targetRow && col!=targetCol) return false; 

    if(row==targetRow){
        int step = (targetCol>col)?1:-1;
        for(int c=col+step;c!=targetCol;c+=step)
            if(board.get(row,c)) return false;
    } 
    else {
        int step = (targetRow>row)?1:-1;
        for(int r=row+step;r!=targetRow;r+=step)
            if(board.get(r,col)) return false;
    }

    return true;
}

bool Bishop::canMoveTo(int targetRow, int targetCol, const ChessBoard& board) {
    if(targetRow < 0 || targetRow >= board.getRows() || targetCol < 0 || targetCol >= board.getColumns())
        return false;

    int row=-1,col=-1;

    for(int i=0;i<board.getRows();i++){
        for(int j=0;j<board.getColumns();j++){
            if(board.get(i,j)==this) row=i,col=j;
        }
    }
    
    if(row==-1) return false;

    if(targetRow == row && targetCol == col)
        return false;

    if(abs(targetRow-row)!=abs(targetCol-col)) return false;

    int rStep = (targetRow>row)?1:-1;
    int cStep = (targetCol>col)?1:-1;
    int r=row+rStep, c=col+cStep;
    while(r!=targetRow && c!=targetCol){
        if(board.get(r,c)) return false;
        r+=rStep; c+=cStep;
    }
    return true;
}

bool Queen::canMoveTo(int targetRow, int targetCol, const ChessBoard& board) {
    if(targetRow < 0 || targetRow >= board.getRows() || targetCol < 0 || targetCol >= board.getColumns())
        return false;

    int row=-1,col=-1;

    for(int i=0;i<board.getRows();i++){
        for(int j=0;j<board.getColumns();j++){
            if(board.get(i,j)==this) row=i,col=j;
        }
    }
    
    if(row==-1) return false;

    if(targetRow == row && targetCol == col) 
        return false; 

    if(row == targetRow || col == targetCol) {
        if(row == targetRow){
            int step = (targetCol > col) ? 1 : -1;
            for(int c = col + step; c != targetCol; c += step)
                if(board.get(row,c)) return false;
        } else {
            int step = (targetRow > row) ? 1 : -1;
            for(int r = row + step; r != targetRow; r += step)
                if(board.get(r,col)) return false;
        }
        return true;
    }

    if(abs(targetRow - row) == abs(targetCol - col)) {
        int rStep = (targetRow > row) ? 1 : -1;
        int cStep = (targetCol > col) ? 1 : -1;
        int r = row + rStep, c = col + cStep;
        while(r != targetRow && c != targetCol){
            if(board.get(r,c)) return false;
            r += rStep; c += cStep;
        }
        return true;
    }

    return false;
}

bool King::canMoveTo(int targetRow,int targetCol,const ChessBoard& board) {
    if(targetRow < 0 || targetRow >= board.getRows() || targetCol < 0 || targetCol >= board.getColumns())
        return false;

    int row=-1,col=-1;

    for(int i=0;i<board.getRows();i++){
        for(int j=0;j<board.getColumns();j++){
            if(board.get(i,j)==this) row=i,col=j;
        }
    }
    
    if(row==-1) return false;
    
    if(targetRow == row && targetCol == col)
        return false;

    return std::abs(row-targetRow)<=1 && std::abs(col-targetCol)<=1;
}

bool Knight::canMoveTo(int targetRow,int targetCol,const ChessBoard& board) {
    if(targetRow < 0 || targetRow >= board.getRows() || targetCol < 0 || targetCol >= board.getColumns())
        return false;

    int row=-1,col=-1;

    for(int i=0;i<board.getRows();i++){
        for(int j=0;j<board.getColumns();j++){
            if(board.get(i,j)==this) row=i,col=j;
        }
    }
    
    if(row==-1) return false;
    
    if(targetRow == row && targetCol == col)
        return false;

    int dirRow = std::abs(row-targetRow);
    int dirCol = std::abs(col-targetCol);
    return (dirRow==2 && dirCol==1) || (dirRow==1 && dirCol==2);
}