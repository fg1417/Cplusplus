#ifndef CHESSPIECE_H
#include <string>
#include <iostream>
using namespace std;

enum ChessColor {White, Black};
const int BoardSize = 8;
const int SquareSize = 2;
const char Rank[] = {'8', '7', '6', '5', '4', '3', '2', '1'};
const char File[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

const int IN_CHECK = 3;
const int NOT_IN_CHECK = 4;
const int IN_CHECKMATE = 5;

// helper function, to transfer the representation of parameter "square" from character array into integer array
bool findSquare(const char* square, int &i, int &j);

// helper function, to determine if the position of square is on the board
bool validSquare(const int * square);

class ChessPiece{
protected:

  int square[SquareSize];
  const ChessColor color;
  const char* name;
  int tag;

public:

  ChessPiece(const char* new_square, const ChessColor new_color, const char* new_name);

  virtual ~ ChessPiece(){};

  ChessColor getColor() const;

  const char* printColor() const;

  const int getTag() const;

  void resetTag();

  const char* getName() const;

  const int* getSquare() const;

  // to change the square of the chesspiece after moving
  void resetSquare(const int* destination_square);

  // to determine if it's legal for the chesspiece to move to the destination_square under the status
  bool validateMove(const int* const destination_square, ChessPiece* const game_status[BoardSize][BoardSize]) const ;

  // to search if there is any legal move for the chesspiece
  virtual bool searchMove(int* next_square, ChessPiece* const game_status[BoardSize][BoardSize]) const = 0;

  // if the move to the destination_square is illegal, the validator will be false; if it's legal, validator will be true and return moving path
  virtual int** printPath(const int* const destination_square, ChessPiece* const game_status[BoardSize][BoardSize], int &count_square, bool &validator) const  = 0;

};


class King: public ChessPiece {
public:
  King(const char* new_square, const ChessColor new_color);
  ~ King(){};
  bool searchMove(int* next_square, ChessPiece* const game_status[BoardSize][BoardSize]) const ;
  int** printPath(const int* const destination_square, ChessPiece* const game_status[BoardSize][BoardSize], int &count_square, bool &validator) const ;
  int detectStatus(ChessPiece* const game_status[BoardSize][BoardSize]) const ;

};


class Castle: public ChessPiece {
public:
  Castle(const char* new_square, const ChessColor new_color);
  ~ Castle(){};
  bool searchMove(int* next_square, ChessPiece* const game_status[BoardSize][BoardSize]) const ;
  int** printPath(const int* const destination_square, ChessPiece* const game_status[BoardSize][BoardSize], int &count_square, bool &validator) const ;

};


class Bishop: public ChessPiece {
public:
  ~ Bishop(){};
  Bishop(const char* new_square, const ChessColor new_color);
  bool searchMove(int* next_square, ChessPiece* const game_status[BoardSize][BoardSize]) const ;
  int** printPath(const int* const destination_square, ChessPiece* const game_status[BoardSize][BoardSize], int &count_square, bool &validator) const ;

};


class Queen: public ChessPiece {
public:
  ~ Queen(){};
  Queen(const char* new_square, const ChessColor new_color);
  bool searchMove(int* next_square, ChessPiece* const game_status[BoardSize][BoardSize]) const ;
  int** printPath(const int* const destination_square, ChessPiece* const game_status[BoardSize][BoardSize], int &count_square, bool &validator) const ;

};

class Knight: public ChessPiece {
public:
  ~ Knight(){};
  Knight(const char* new_square, const ChessColor new_color);
  bool searchMove(int* next_square, ChessPiece* const game_status[BoardSize][BoardSize]) const ;
  int** printPath(const int* const destination_square, ChessPiece* const game_status[BoardSize][BoardSize], int &count_square, bool &validator) const ;

};


class Pawn: public ChessPiece {
public:
  ~ Pawn(){};
  Pawn(const char* new_square, const ChessColor new_color);
  bool searchMove(int* next_square, ChessPiece* const game_status[BoardSize][BoardSize]) const ;
  int** printPath(const int* const destination_square, ChessPiece* const game_status[BoardSize][BoardSize], int &count_square, bool &validator) const ;

};

#define CHESSPIECE_H
#endif
