#include <iostream>
#include <string>
#include <cmath>
#include "ChessBoard.h"
#include "ChessPiece.h"

ChessPiece::ChessPiece(const std::string& color) : color(color) { }
ChessPiece::~ChessPiece() { }
std::string ChessPiece::getColor() const { return color; }

Pawn::Pawn(const std::string& color) : ChessPiece(color) {}
std::string Pawn::name() const { return "Pawn"; }

bool Pawn::canMoveTo(int targetRow,int targetCol,const ChessBoard& board){
    if(targetRow < 0 || targetRow >= 8 || targetCol < 0 || targetCol >= 8) return false;

    int row=-1,col=-1;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            if(board.get(i,j) == this){ row=i; col=j; }
    if(row==-1) return false;

    int dir = (color=="white")?-1:1;

    if(targetRow==row+dir && (targetCol==col+1 || targetCol==col-1)){
        if(targetRow < 0 || targetRow >= 8 || targetCol < 0 || targetCol >= 8) return false;
        ChessPiece* dest = board.get(targetRow,targetCol);
        if(dest && dest->getColor()!=color) return true;
    }

    if(targetCol==col){
        if(targetRow < 0 || targetRow >=8) return false;
        if(board.get(targetRow,targetCol)==nullptr){
            if(targetRow==row+dir) return true;
            if((row==6 && color=="white") || (row==1 && color=="black"))
                if(row+dir >=0 && row+dir <8 && board.get(row+dir,col)==nullptr)
                    if(targetRow==row+2*dir) return true;
        }
    }

    return false;
}

Rook::Rook(const std::string& color) : ChessPiece(color) {}
std::string Rook::name() const { return "Rook"; }

bool Rook::canMoveTo(int targetRow,int targetCol,const ChessBoard& board){
    if(targetRow<0||targetRow>=8||targetCol<0||targetCol>=8) return false;
    int row=-1,col=-1;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            if(board.get(i,j)==this){ row=i; col=j; }
    if(row==-1) return false;
    if(row!=targetRow && col!=targetCol) return false;

    if(row==targetRow){
        int step = (targetCol>col)?1:-1;
        for(int c=col+step;c!=targetCol;c+=step){
            if(c<0 || c>=8) return false;
            if(board.get(row,c)!=nullptr) return false;
        }
    } else {
        int step = (targetRow>row)?1:-1;
        for(int r=row+step;r!=targetRow;r+=step){
            if(r<0 || r>=8) return false;
            if(board.get(r,col)!=nullptr) return false;
        }
    }
    ChessPiece* dest = board.get(targetRow,targetCol);
    return (!dest || dest->getColor()!=color);
}

Knight::Knight(const std::string& color) : ChessPiece(color) {}
std::string Knight::name() const { return "Knight"; }

bool Knight::canMoveTo(int targetRow,int targetCol,const ChessBoard& board){
    if(targetRow<0||targetRow>=8||targetCol<0||targetCol>=8) return false;
    int row=-1,col=-1;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            if(board.get(i,j)==this){ row=i; col=j; }
    if(row==-1) return false;
    
    int dr = abs(row-targetRow);
    int dc = abs(col-targetCol);
    if((dr==2 && dc==1) || (dr==1 && dc==2)){
        ChessPiece* dest = board.get(targetRow,targetCol);
        return (!dest || dest->getColor()!=color);
    }
    return false;
}

Bishop::Bishop(const std::string& color) : ChessPiece(color) {}
std::string Bishop::name() const { return "Bishop"; }

bool Bishop::canMoveTo(int targetRow,int targetCol,const ChessBoard& board){
    if(targetRow<0||targetRow>=8||targetCol<0||targetCol>=8) return false;
    int row=-1,col=-1;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            if(board.get(i,j)==this){ row=i; col=j; }
    if(row==-1) return false;

    if(abs(targetRow-row)!=abs(targetCol-col)) return false;

    int rstep = (targetRow>row)?1:-1;
    int cstep = (targetCol>col)?1:-1;
    int r=row+rstep,c=col+cstep;
    while(r!=targetRow && c!=targetCol){
        if(r<0 || r>=8 || c<0 || c>=8) return false;
        if(board.get(r,c)) return false;
        r+=rstep; c+=cstep;
    }
    ChessPiece* dest = board.get(targetRow,targetCol);
    return (!dest || dest->getColor()!=color);
}

Queen::Queen(const std::string& color) : ChessPiece(color) {}
std::string Queen::name() const { return "Queen"; }

bool Queen::canMoveTo(int targetRow,int targetCol,const ChessBoard& board){
    if(targetRow<0||targetRow>=8||targetCol<0||targetCol>=8) return false;
    int row=-1,col=-1;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            if(board.get(i,j)==this){ row=i; col=j; }
    if(row==-1) return false;

    if(row==targetRow || col==targetCol){
        if(row==targetRow){
            int step = (targetCol>col)?1:-1;
            for(int c=col+step;c!=targetCol;c+=step){
                if(c<0||c>=8) return false;
                if(board.get(row,c)) return false;
            }
        } else {
            int step = (targetRow>row)?1:-1;
            for(int r=row+step;r!=targetRow;r+=step){
                if(r<0||r>=8) return false;
                if(board.get(r,col)) return false;
            }
        }
        ChessPiece* dest = board.get(targetRow,targetCol);
        return (!dest || dest->getColor()!=color);
    }

    if(abs(targetRow-row)==abs(targetCol-col)){
        int rstep = (targetRow>row)?1:-1;
        int cstep = (targetCol>col)?1:-1;
        int r=row+rstep, c=col+cstep;
        while(r!=targetRow && c!=targetCol){
            if(r<0 || r>=8 || c<0 || c>=8) return false;
            if(board.get(r,c)) return false;
            r+=rstep; c+=cstep;
        }
        ChessPiece* dest = board.get(targetRow,targetCol);
        return (!dest || dest->getColor()!=color);
    }

    return false;
}

King::King(const std::string& color) : ChessPiece(color) {}
std::string King::name() const { return "King"; }

bool King::canMoveTo(int targetRow,int targetCol,const ChessBoard& board){
    if(targetRow<0||targetRow>=8||targetCol<0||targetCol>=8) return false;
    int row=-1,col=-1;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            if(board.get(i,j)==this){ row=i; col=j; }
    if(row==-1) return false;

    int dr = abs(row-targetRow);
    int dc = abs(col-targetCol);
    if(dr<=1 && dc<=1){
        if(targetRow<0 || targetRow>=8 || targetCol<0 || targetCol>=8) return false;
        ChessPiece* dest = board.get(targetRow,targetCol);
        return (!dest || dest->getColor()!=color);
    }
    return false;
}