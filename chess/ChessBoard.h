#ifndef CHESSBOARD_H

#include "ChessPiece.h"
#include <iostream>

using namespace std;

class ChessBoard{
private:

  ChessPiece* game_status[BoardSize][BoardSize];
  King* white_king;
  King* black_king;
  int count;

  // to set a completely new game status
  void setBoard();

  // to clear current game status
  void clearBoard();

  //to determine if the move is  legal
  bool validateMove(const int* const source_square, const int* const destination_square);

  // to execute the legal move
  void movePiece(const int* const source_square, const int* const destination_square);

  // to search if there is any legal move
  bool searchMove(const ChessColor my_color);

  // to cancel the last move
  void cancelMove(const int* source, const int* destination, ChessPiece* temp);

  // to detect the status of Kings in the game
  void detectStatus();

  // to determine if castling is legal
  bool validateCastling(const int* const source_1, const int* const destination_1, const int* const source_2, const int* const destination_2);

public:

  ChessBoard();

  ~ChessBoard();

  void resetBoard();

  void submitMove(const char* const source_square, const char* const destination_square);

  // to execute castling
  void castling(const char* const source_square_1, const char* const destination_square_1, const char* const source_square_2, const char* const destination_square_2);

};

#define CHESSBOARD_H
#endif
