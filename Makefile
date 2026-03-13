CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = chess

SRC = ChessBoard.cpp ChessPiece.cpp main.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
