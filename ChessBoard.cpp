#include <iostream>
#include <vector>
#include <functional>
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

ChessBoard::~ChessBoard() {
    for (int i = 0; i < getRows(); i++) {
        for (int j = 0; j < getColumns(); j++) {
            ChessPiece* p = get(i,j);
            if(p) { delete p; set(i,j,nullptr); }
        }
    }
}

bool ChessBoard::isKingInDanger(const std::string& color) const {
    int kingRow = -1, kingCol = -1;

    for(int i = 0; i < getRows(); i++){
        for(int j = 0; j < getColumns(); j++){
            ChessPiece* p = get(i,j);
            if(p && p->name() == "King" && p->getColor() == color){
                kingRow = i;
                kingCol = j;
                break;
            }
        }
        if(kingRow != -1) break;
    }

    if(kingRow == -1) return false; 

    std::string opponent = (color == "white") ? "black" : "white";

    for(int i = 0; i < getRows(); i++){
        for(int j = 0; j < getColumns(); j++){
            ChessPiece* p = get(i,j);
            if(p && p->getColor() == opponent){
                if(p->canMoveTo(kingRow, kingCol, *this)){
                    return true;
                }
            }
        }
    }

    return false;
}

void ChessBoard::movePiece(int fromRow, int fromCol, int toRow, int toCol) {
    ChessPiece* piece = get(fromRow, fromCol);
    if(piece && piece->canMoveTo(toRow, toCol, *this)) {
        set(toRow, toCol, piece);
        set(fromRow, fromCol, nullptr);
    }
}

void ChessBoard::setupDefault() {

    placePiece(new Rook("black"), 0, 0);
    placePiece(new Knight("black"), 0, 1);
    placePiece(new Bishop("black"), 0, 2);
    placePiece(new Queen("black"), 0, 3);
    placePiece(new King("black"), 0, 4);
    placePiece(new Bishop("black"), 0, 5);
    placePiece(new Knight("black"), 0, 6);
    placePiece(new Rook("black"), 0, 7);
    for(int j=0;j<8;j++) placePiece(new Pawn("black"), 1, j);


    placePiece(new Rook("white"), 7, 0);
    placePiece(new Knight("white"), 7, 1);
    placePiece(new Bishop("white"), 7, 2);
    placePiece(new Queen("white"), 7, 3);
    placePiece(new King("white"), 7, 4);
    placePiece(new Bishop("white"), 7, 5);
    placePiece(new Knight("white"), 7, 6);
    placePiece(new Rook("white"), 7, 7);
    for(int j=0;j<8;j++) placePiece(new Pawn("white"), 6, j);
}

void ChessBoard::printBoard() const {

    for(int i=0;i<getRows();i++){
        for(int j=0;j<getColumns();j++){

            ChessPiece* piece = get(i,j);

            if(piece==nullptr){
                std::cout << ".  ";
                continue;
            }

            std::string n = piece->name();
            char letter;

            if(n=="Pawn") letter='P';
            else if(n=="Rook") letter='R';
            else if(n=="Knight") letter='N';
            else if(n=="Bishop") letter='B';
            else if(n=="Queen") letter='Q';
            else if(n=="King") letter='K';

            char color = (piece->getColor()=="white") ? 'w' : 'b';

            std::cout << letter << color << " ";
        }

        std::cout << std::endl;
    }
}

bool ChessBoard::isValidBoard() const {
    int whiteKings = 0;
    int blackKings = 0;

    for (int i = 0; i < getRows(); i++) {
        for (int j = 0; j < getColumns(); j++) {
            ChessPiece* p = get(i,j);
            if (p) {
                if (p->name() == "King") {
                    if (p->getColor() == "white") whiteKings++;
                    else if (p->getColor() == "black") blackKings++;
                }
            }
        }
    }

    return (whiteKings == 1 && blackKings == 1);
}

std::vector<Move> ChessBoard::getAllPossibleMoves(const std::string& color) const {
    std::vector<Move> moves;
    for(int i = 0; i < getRows(); i++){
        for(int j = 0; j < getColumns(); j++){
            ChessPiece* piece = get(i,j);
            if(piece && piece->getColor() == color){
                for(int r = 0; r < getRows(); r++){
                    for(int c = 0; c < getColumns(); c++){
                        if(piece->canMoveTo(r,c,*this)){

                            simulateMove({i,j,r,c}, [&](){
                                if(!isKingInDanger(color)){
                                    moves.push_back({i,j,r,c});
                                }
                            });
                        }
                    }
                }
            }
        }
    }
    return moves;
}

void ChessBoard::simulateMove(const Move& move, std::function<void()> callback) const {
    if(move.fromRow<0 || move.fromRow>=getRows() || move.fromCol<0 || move.fromCol>=getColumns() ||
       move.toRow<0 || move.toRow>=getRows() || move.toCol<0 || move.toCol>=getColumns())
        return;

    ChessPiece* origDest = get(move.toRow, move.toCol);
    ChessPiece* movingPiece = get(move.fromRow, move.fromCol);

    const_cast<ChessBoard*>(this)->set(move.toRow, move.toCol, movingPiece);
    const_cast<ChessBoard*>(this)->set(move.fromRow, move.fromCol, nullptr);

    callback();

    const_cast<ChessBoard*>(this)->set(move.fromRow, move.fromCol, movingPiece);
    const_cast<ChessBoard*>(this)->set(move.toRow, move.toCol, origDest);
}

void ChessBoard::analyze(const std::string& colorToMove) const {
    if (!isValidBoard()) {
        std::cout << "Invalid board: each side must have exactly one king." <<std::endl;
        return;
    }

    std::string opponent = (colorToMove == "white") ? "black" : "white";
    auto moves = getAllPossibleMoves(colorToMove);

    for (const Move& m : moves) {
        bool givesCheckmate = false;
        simulateMove(m, [&]() {
            if (isKingInDanger(opponent)) {

                std::vector<Move> legalOppMoves;
                auto oppMovesRaw = getAllPossibleMoves(opponent);
                for (const Move& om : oppMovesRaw) {
                    simulateMove(om, [&]() {
                        if (!isKingInDanger(opponent)) legalOppMoves.push_back(om);
                    });
                }

                bool kingCanEscape = false;
                for (const Move& om : legalOppMoves) {
                    simulateMove(om, [&]() {
                        if (!isKingInDanger(opponent)) kingCanEscape = true;
                    });
                    if (kingCanEscape) break;
                }
                if (!kingCanEscape) givesCheckmate = true;
            }
        });
        if (givesCheckmate) {
            std::cout << colorToMove << " can end the game after 1 move!" <<std::endl;
            std::cout << "Move: (" << m.fromRow << "," << m.fromCol << ") -> (" 
                      << m.toRow << "," << m.toCol << ")" <<std::endl;
            return;
        }
    }

    for (const Move& m : moves) {
        bool firstMoveLeadsToWin = true;
        simulateMove(m, [&]() {
            
            std::vector<Move> legalOppMoves;
            auto oppMovesRaw = getAllPossibleMoves(opponent);
            for (const Move& om : oppMovesRaw) {
                simulateMove(om, [&]() {
                    if (!isKingInDanger(opponent)) legalOppMoves.push_back(om);
                });
            }

            for (const Move& om : legalOppMoves) {
                bool secondWhiteCannotMate = true;
                simulateMove(om, [&]() {
                    auto secondWhiteMoves = getAllPossibleMoves(colorToMove);

                    for (const Move& wm : secondWhiteMoves) {
                        bool leadsToCheckmate = false;
                        simulateMove(wm, [&]() {

                            if (isKingInDanger(opponent)) {
                                auto escapeMoves = getAllPossibleMoves(opponent);
                                bool kingCanEscape = false;
                                
                                for (const Move& em : escapeMoves) {
                                    simulateMove(em, [&]() {
                                        if (!isKingInDanger(opponent)) kingCanEscape = true;
                                    });
                                    if (kingCanEscape) break;
                                }
                                if (!kingCanEscape) leadsToCheckmate = true;
                            }
                        });
                        if (leadsToCheckmate) {
                            secondWhiteCannotMate = false;
                            break;
                        }
                    }
                });
                if (secondWhiteCannotMate) {
                    firstMoveLeadsToWin = false;
                    break;
                }
            }
        });
        if (firstMoveLeadsToWin) {
            std::cout << colorToMove << " can force game over in 2 moves!" <<std::endl;
            std::cout << "First move to start: (" << m.fromRow << "," << m.fromCol << ") -> (" 
                      << m.toRow << "," << m.toCol << ")" <<std::endl;
            return;
        }
    }

    std::cout << "No win in 2 moves." <<std::endl;
}