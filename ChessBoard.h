#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "Matrix.h"
#include "ChessPiece.h"
#include <string>
#include <vector>
#include <functional>

class ChessPiece;

struct Move {
    int fromRow;
    int fromCol;
    int toRow;
    int toCol;
};

class ChessBoard : public Matrix<ChessPiece*>{
public:
ChessBoard();
ChessBoard(const ChessBoard& other);
ChessBoard& operator=(const ChessBoard& other);
ChessBoard(ChessBoard&& other);
ChessBoard& operator =(ChessBoard&& other);
~ChessBoard();


void placePiece(ChessPiece* piece, int row, int col) {
    ChessPiece* p = get(row,col);
    if(p) { delete p; set(row,col,nullptr); }
    set(row,col,piece);
}

bool isKingInDanger(const std::string& color) const;
void movePiece(int fromRow, int fromCol, int toRow, int toCol);
void setupDefault();
void printBoard() const;
bool isValidBoard() const;
std::vector<Move> getAllPossibleMoves(const std::string& color) const;
void simulateMove(const Move& move, std::function<void()> callback) const;
void analyze(const std::string& colorToMove) const;
};

#endif //CHESSBOARD_H