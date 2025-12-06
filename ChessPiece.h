#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <string>

class ChessPiece {
protected:
    std::string color; 
public:
    ChessPiece(const std::string& color);
    virtual ~ChessPiece();

    std::string getColor() const;

    virtual std::string name() const = 0;
};

class Pawn : public ChessPiece {
public:
    Pawn(const std::string& color);
    std::string name() const override;
};

class Rook : public ChessPiece {
public:
    Rook(const std::string& color);
    std::string name() const override;
};

class Knight : public ChessPiece {
public:
    Knight(const std::string& color);
    std::string name() const override;
};

class Bishop : public ChessPiece {
public:
    Bishop(const std::string& color);
    std::string name() const override;
};

class Queen : public ChessPiece {
public:
    Queen(const std::string& color);
    std::string name() const override;
};

class King : public ChessPiece {
public:
    King(const std::string& color);
    std::string name() const override;
};

#endif // CHESSPIECE_H