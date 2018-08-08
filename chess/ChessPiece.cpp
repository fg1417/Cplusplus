
#include "ChessPiece.h"
#include <iostream>
#include <cstring>
#include <stdlib.h>


using namespace std;

bool findSquare(const char* square, int &i, int &j){
  for(i = 0; i < BoardSize; i++){
    if(Rank[i] == square[1])
    break; }

  for(j = 0; j < BoardSize; j++){
    if(File[j] == square[0])
    break; }

  if(i == BoardSize || j == BoardSize)
    return false;
  else
    return true;

}


bool validSquare(const int * square){
  if(square[0]>=0 && square[0]< BoardSize && square[1]>=0 && square[1]< BoardSize)
    return true;
  else
    return false;
}


ChessPiece:: ChessPiece(const char* new_square, const ChessColor new_color, const char* new_name): color(new_color), name(new_name){
  if(! findSquare(new_square, square[0], square[1])){
    cerr<< "Invalid square!"<< endl;
    return ;  }
  tag = 0;

}

ChessColor ChessPiece:: getColor() const{
  return color;

}

const char* ChessPiece:: printColor() const{
  if(color == Black)
  return "Black";
  else
  return "White";

}

const int ChessPiece:: getTag() const{
  return tag;
}

void ChessPiece:: resetTag() {
  tag = 1;
}

const char* ChessPiece:: getName() const{
  return name;

}

const int* ChessPiece:: getSquare() const{
  return square;

}

void ChessPiece:: resetSquare(const int* destination_square){
  square[0] = destination_square[0];
  square[1] = destination_square[1];

}

bool ChessPiece:: validateMove(const int* const destination_square, ChessPiece* const game_status[BoardSize][BoardSize]) const {
  if(!validSquare(destination_square))
  return false;

  int count_square = 0;
  bool validator = true;
  int** path = NULL;

  if(game_status[destination_square[0]][destination_square[1]] && (game_status[destination_square[0]][destination_square[1]]->getColor() == color))
    return false;
  else
    path = printPath(destination_square, game_status, count_square, validator);

  if(path)
  delete [] path;
  return validator;

}

// definations of member function for class King
King:: King(const char* new_square, const ChessColor new_color): ChessPiece(new_square, new_color, "King"){};

bool King:: searchMove(int* next_square, ChessPiece* const game_status[BoardSize][BoardSize]) const {

  next_square[0] = square[0];
  next_square[1] = square[1]-1;
  if(validateMove(next_square, game_status))
  return true;

  next_square[0] = square[0];
  next_square[1] = square[1]+1;
  if(validateMove(next_square, game_status))
  return true;

  next_square[0] = square[0]-1;
  next_square[1] = square[1];
  if(validateMove(next_square, game_status))
  return true;

  next_square[0] = square[0]+1;
  next_square[1] = square[1];
  if(validateMove(next_square, game_status))
  return true;

  next_square[0] = square[0]-1;
  next_square[1] = square[1]-1;
  if(validateMove(next_square, game_status))
  return true;

  next_square[0] = square[0]-1;
  next_square[1] = square[1]+1;
  if(validateMove(next_square, game_status))
  return true;

  next_square[0] = square[0]+1;
  next_square[1] = square[1]+1;
  if(validateMove(next_square, game_status))
  return true;

  next_square[0] = square[0]+1;
  next_square[1] = square[1]-1;
  if(validateMove(next_square, game_status))
  return true;

  return false;

}

int** King:: printPath(const int* const destination_square, ChessPiece* const game_status[BoardSize][BoardSize], int &count_square, bool &validator) const {
  int** path = NULL;
  int vertical_distance = abs(destination_square[0] - square[0]);
  int horizontal_distance = abs(destination_square[1] - square[1]);

  if((vertical_distance == 1 || vertical_distance == 0) && (horizontal_distance == 1 || horizontal_distance == 0))
    validator = true;
  else
    validator = false;

  count_square = 0;
  return path;

}

int King:: detectStatus(ChessPiece* const game_status[BoardSize][BoardSize]) const {
  ChessColor opponent_color = White;
  if(color == White)
  opponent_color = Black;
  int count_attack = 0;
  int flag_1 = true;
    for(int i = 0; i < BoardSize; i++)
      for(int j = 0; j < BoardSize; j++)
        if(game_status[i][j] && game_status[i][j]->getColor() == opponent_color && game_status[i][j]->validateMove(square, game_status)){
          flag_1 = false;
          count_attack++;

          switch (count_attack){

            case 1:{
              for(int k = 0; k < BoardSize && !flag_1; k++)
                for(int m = 0; m < BoardSize && !flag_1; m++)
                if(game_status[k][m] && game_status[k][m]->getColor() == color && game_status[k][m]->validateMove(game_status[i][j]->getSquare(), game_status))
                  flag_1 = true;
              if(flag_1)
                break;

              if(!strcmp(game_status[i][j]->getName(), "Knight")){
                int count_square;
                bool validator = true;
                int** path = game_status[i][j]->printPath(square, game_status, count_square, validator);
                for(int step = 0; step < count_square && !flag_1; step++)
                  for(int k = 0; k < BoardSize && !flag_1; k++)
                    for(int m = 0; m < BoardSize && !flag_1; m++)
                    if(game_status[k][m] != NULL && game_status[k][m]->getColor() == color && game_status[k][m]->validateMove(path[step], game_status))
                    flag_1 = true;
              if(path)
              delete [] path;  }
              if(flag_1)
              break; }

            default:{
              int next_square[SquareSize];
              if(searchMove(next_square, game_status)){
              bool flag_2 = false;
              next_square[0] = square[0];
              next_square[1] = square[1]-1;

              if(validateMove(next_square, game_status)){
              int flag_3 = true;
                for(int k = 0; k < BoardSize && flag_3; k++)
                  for(int m = 0; m < BoardSize && flag_3; m++)
                  if(game_status[k][m] != NULL && game_status[k][m]->getColor() == opponent_color && game_status[k][m]->validateMove(next_square, game_status))
                    flag_3 = false;
              if(flag_3)
              flag_2 = true; }

              if(flag_2){
                flag_1 = true;
                break; }

              next_square[0] = square[0];
              next_square[1] = square[1]+1;
              if(validateMove(next_square, game_status)){
              int flag_3 = true;
                for(int k = 0; k < BoardSize && flag_3; k++)
                  for(int m = 0; m < BoardSize && flag_3; m++)
                  if(game_status[k][m] != NULL && game_status[k][m]->getColor() == opponent_color && game_status[k][m]->validateMove(next_square, game_status))
                    flag_3 = false;
              if(flag_3)
              flag_2 = true; }

              if(flag_2){
                flag_1 = true;
                break; }

              next_square[0] = square[0]-1;
              next_square[1] = square[1];
              if(validateMove(next_square, game_status)){
              int flag_3 = true;
                for(int k = 0; k < BoardSize && flag_3; k++)
                  for(int m = 0; m < BoardSize && flag_3; m++)
                  if(game_status[k][m] != NULL && game_status[k][m]->getColor() == opponent_color && game_status[k][m]->validateMove(next_square, game_status))
                    flag_3 = false;
              if(flag_3)
              flag_2 = true; }

              if(flag_2){
                flag_1 = true;
                break; }

              next_square[0] = square[0]+1;
              next_square[1] = square[1];
              if(validateMove(next_square, game_status)){
              int flag_3 = true;
                for(int k = 0; k < BoardSize && flag_3; k++)
                  for(int m = 0; m < BoardSize && flag_3; m++)
                  if(game_status[k][m] != NULL && game_status[k][m]->getColor() == opponent_color && game_status[k][m]->validateMove(next_square, game_status))
                    flag_3 = false;
              if(flag_3)
              flag_2 = true;
                    flag_2 = false;  }

              if(flag_2){
                flag_1 = true;
                break; }

              next_square[0] = square[0]-1;
              next_square[1] = square[1]-1;
              if(validateMove(next_square, game_status)){
              int flag_3 = true;
                for(int k = 0; k < BoardSize && flag_3; k++)
                  for(int m = 0; m < BoardSize && flag_3; m++)
                  if(game_status[k][m] != NULL && game_status[k][m]->getColor() == opponent_color && game_status[k][m]->validateMove(next_square, game_status))
                    flag_3 = false;
              if(flag_3)
              flag_2 = true; }

              if(flag_2){
                flag_1 = true;
                break; }

              next_square[0] = square[0]-1;
              next_square[1] = square[1]+1;
              if(validateMove(next_square, game_status)){
              int flag_3 = true;
                for(int k = 0; k < BoardSize && flag_3; k++)
                  for(int m = 0; m < BoardSize && flag_3; m++)
                  if(game_status[k][m] != NULL && game_status[k][m]->getColor() == opponent_color && game_status[k][m]->validateMove(next_square, game_status))
                    flag_3 = false;
              if(flag_3)
              flag_2 = true; }

              if(flag_2){
                flag_1 = true;
                break; }

              next_square[0] = square[0]+1;
              next_square[1] = square[1]+1;
              if(validateMove(next_square, game_status)){
              int flag_3 = true;
                for(int k = 0; k < BoardSize && flag_3; k++)
                  for(int m = 0; m < BoardSize && flag_3; m++)
                  if(game_status[k][m] != NULL && game_status[k][m]->getColor() == opponent_color && game_status[k][m]->validateMove(next_square, game_status))
                    flag_3 = false;
              if(flag_3)
              flag_2 = true; }

              if(flag_2){
                flag_1 = true;
                break; }

              next_square[0] = square[0]+1;
              next_square[1] = square[1]-1;
              if(validateMove(next_square, game_status)){
              int flag_3 = true;
                for(int k = 0; k < BoardSize && flag_3; k++)
                  for(int m = 0; m < BoardSize && flag_3; m++)
                  if(game_status[k][m] != NULL && game_status[k][m]->getColor() == opponent_color && game_status[k][m]->validateMove(next_square, game_status))
                    flag_3 = false;
              if(flag_3)
              flag_2 = true; } } } } }

   if(!flag_1)
     return IN_CHECKMATE;
   else if(count_attack != 0 && flag_1)
     return IN_CHECK;
   else
     return NOT_IN_CHECK;

}


// definations of member function for class Castle
Castle:: Castle(const char* new_square, const ChessColor new_color): ChessPiece(new_square, new_color, "Castle"){};

bool Castle:: searchMove(int* next_square, ChessPiece* const game_status[BoardSize][BoardSize]) const {

  next_square[0] = square[0];
  next_square[1] = square[1]-1;
  if(validateMove(next_square, game_status))
  return true;

  next_square[0] = square[0];
  next_square[1] = square[1]+1;
  if(validateMove(next_square, game_status))
  return true;

  next_square[0] = square[0]-1;
  next_square[1] = square[1];
  if(validateMove(next_square, game_status))
  return true;

  next_square[0] = square[0]+1;
  next_square[1] = square[1];
  if(validateMove(next_square, game_status))
  return true;

  return false;

}

int** Castle:: printPath(const int* const destination_square, ChessPiece* const game_status[BoardSize][BoardSize], int &count_square, bool &validator) const {
    int operation_1 = 1, operation_2 = 1;
    int vertical_distance = destination_square[0] - square[0];
    int horizontal_distance = destination_square[1] - square[1];
    int** path = NULL;

    if(vertical_distance < 0)
    operation_1 = -1;
    if(horizontal_distance < 0)
    operation_2 = -1;

    if((vertical_distance != 0 && horizontal_distance == 0)){
        path= new int*[abs(vertical_distance)-1] ;
      for(int i = square[0] + operation_1; i != destination_square[0]; i = i + operation_1){
        if (game_status[i][square[1]] != NULL){
            validator = false;
            return path;  }
        else {
          path[count_square] = new int[SquareSize];
          path[count_square][0] = i;
          path[count_square][1] = square[1];
          count_square++; } } }

    else if(vertical_distance == 0 && horizontal_distance != 0){
        path= new int*[abs(horizontal_distance)-1];
      for(int i = square[1] + operation_2; i < destination_square[1]; i = i + operation_2)
        if (game_status[square[0]][i] != NULL){
          validator = false;
          return path;  }
        else{
          path[count_square] = new int[SquareSize];
          path[count_square][0] = i;
          path[count_square][1] = square[1];
          count_square++; } }

    else {
        validator = false;
        return path;  }

    validator = true;
    return path;

}


// definations of member function for class Bishop
Bishop:: Bishop(const char* new_square, const ChessColor new_color): ChessPiece(new_square, new_color, "Bishop"){};

bool Bishop:: searchMove(int* next_square, ChessPiece* const game_status[BoardSize][BoardSize]) const {

  next_square[0] = square[0]-1;
  next_square[1] = square[1]-1;
  if(validateMove(next_square, game_status))
  return true;

  next_square[0] = square[0]-1;
  next_square[1] = square[1]+1;
  if(validateMove(next_square, game_status))
  return true;

  next_square[0] = square[0]+1;
  next_square[1] = square[1]+1;
  if(validateMove(next_square, game_status))
  return true;

  next_square[0] = square[0]+1;
  next_square[1] = square[1]-1;
  if(validateMove(next_square, game_status))
  return true;

  return false;

}

int** Bishop:: printPath(const int* const destination_square, ChessPiece* const game_status[BoardSize][BoardSize], int &count_square, bool &validator) const {
    int** path = NULL;
    int operation_1 = 1, operation_2 = 1;
    int vertical_distance = destination_square[0] - square[0];
    int horizontal_distance = destination_square[1] - square[1];

    if(vertical_distance < 0)
    operation_1 = -1;
    if(horizontal_distance < 0)
    operation_2 = -1;

    if(abs(vertical_distance) == abs(horizontal_distance)){
        path= new int*[abs(vertical_distance)-1];
      int i = square[0] + operation_1, j = square[1] + operation_2;
      while((i != destination_square[0]) && (j != destination_square[1])){
        if(game_status[i][j]){
          validator = false;
          return path;  }
        else{
          path[count_square] = new int[SquareSize];
          path[count_square][0] = i;
          path[count_square][1] = j;
          count_square++;}
        i = i + operation_1;
        j = j + operation_2;  } }

    else {
      validator = false;
      return path;  }

    validator = true;
    return path;

  }


// definations of member function for class Queen
Queen:: Queen(const char* new_square, const ChessColor new_color): ChessPiece(new_square, new_color, "Queen"){};

bool Queen:: searchMove(int* next_square, ChessPiece* const game_status[BoardSize][BoardSize]) const {

    next_square[0] = square[0];
    next_square[1] = square[1]-1;
    if(validateMove(next_square, game_status))
    return true;

    next_square[0] = square[0];
    next_square[1] = square[1]+1;
    if(validateMove(next_square, game_status))
    return true;

    next_square[0] = square[0]-1;
    next_square[1] = square[1];
    if(validateMove(next_square, game_status))
    return true;

    next_square[0] = square[0]+1;
    next_square[1] = square[1];
    if(validateMove(next_square, game_status))
    return true;

    next_square[0] = square[0]-1;
    next_square[1] = square[1]-1;
    if(validateMove(next_square, game_status))
    return true;

    next_square[0] = square[0]-1;
    next_square[1] = square[1]+1;
    if(validateMove(next_square, game_status))
    return true;

    next_square[0] = square[0]+1;
    next_square[1] = square[1]+1;
    if(validateMove(next_square, game_status))
    return true;

    next_square[0] = square[0]+1;
    next_square[1] = square[1]-1;
    if(validateMove(next_square, game_status))
    return true;

    return false;

  }

  int** Queen:: printPath(const int* const destination_square, ChessPiece* const game_status[BoardSize][BoardSize], int &count_square, bool &validator)  const {
      int operation_1 = 1, operation_2 = 1;
      int vertical_distance = destination_square[0] - square[0];
      int horizontal_distance = destination_square[1] - square[1];
      int** path = NULL;

      if(vertical_distance < 0)
      operation_1 = -1;
      if(horizontal_distance < 0)
      operation_2 = -1;

      if((vertical_distance != 0 && horizontal_distance == 0)){
          path= new int*[abs(vertical_distance)-1] ;
        for(int i = square[0] + operation_1; i != destination_square[0]; i = i + operation_1)
          if (game_status[i][square[1]] != NULL){
              validator = false;
              return path;
          }
          else {
            path[count_square] = new int[SquareSize];
            path[count_square][0] = i;
            path[count_square][1] = square[1];
            count_square++; } }

      else if(vertical_distance == 0 && horizontal_distance != 0){
          path= new int*[abs(horizontal_distance)-1];
        for(int i = square[1] + operation_2; i != destination_square[1]; i = i + operation_2)
          if (game_status[square[0]][i] != NULL){
            validator = false;
            return path;  }
          else{
            path[count_square] = new int[SquareSize];
            path[count_square][0] = i;
            path[count_square][1] = square[1];
            count_square++; } }

      else if(abs(vertical_distance) == abs(horizontal_distance)){
          path= new int*[abs(vertical_distance)-1];
        int i = square[0] + operation_1, j = square[1] + operation_2;
        while((i != destination_square[0]) && (j != destination_square[1])){
          if(game_status[i][j]){
            validator = false;
            return path;  }
          else{
            path[count_square] = new int[SquareSize];
            path[count_square][0] = i;
            path[count_square][1] = j;
            count_square++; }
          i = i + operation_1;
          j = j + operation_2;  } }

      else {
        validator = false;
        return path;  }

      validator = true;
      return path;

    }


// definations of member function for class Knight
Knight:: Knight(const char* new_square, const ChessColor new_color): ChessPiece(new_square, new_color, "Knight"){};

bool Knight:: searchMove(int* next_square, ChessPiece* const game_status[BoardSize][BoardSize]) const {

  next_square[0] = square[0]-1;
  next_square[1] = square[1]-2;
  if(validateMove(next_square, game_status))
  return true;

  next_square[0] = square[0]-1;
  next_square[1] = square[1]+2;
  if(validateMove(next_square, game_status))
  return true;

  next_square[0] = square[0]+2;
  next_square[1] = square[1]+1;
  if(validateMove(next_square, game_status))
  return true;

  next_square[0] = square[0]+2;
  next_square[1] = square[1]-1;
  if(validateMove(next_square, game_status))
  return true;

  return false;

}

int** Knight:: printPath(const int* const destination_square, ChessPiece* const game_status[BoardSize][BoardSize], int &count_square, bool &validator)  const {
  int** path = NULL;
  int vertical_distance = abs(destination_square[0] - square[0]);
  int horizontal_distance = abs(destination_square[1] - square[1]);

  if((vertical_distance == 2 && horizontal_distance == 1) ||(vertical_distance == 1 && horizontal_distance == 2))
    validator = true;
  else
    validator = false;

  count_square = 0;
  return path;

}


// definations of member function for class Pawn
Pawn:: Pawn(const char* new_square, const ChessColor new_color): ChessPiece(new_square, new_color, "Pawn"){};

bool Pawn:: searchMove(int* next_square, ChessPiece* const game_status[BoardSize][BoardSize]) const {

  switch (color) {
    case Black:{
      next_square[0] = square[0]+2;
      next_square[1] = square[1];
      if(validateMove(next_square, game_status))
      return true;
      next_square[0] = square[0]+1;
      next_square[1] = square[1];
      if(validateMove(next_square, game_status))
      return true;
      next_square[0] = square[0]+1;
      next_square[1] = square[1]-1;
      if(validateMove(next_square, game_status))
      return true;
      next_square[0] = square[0]+1;
      next_square[1] = square[1]+1;
      if(validateMove(next_square, game_status))
      return true;  }

    case White:{
      next_square[0] = square[0]-2;
      next_square[1] = square[1];
      if(validateMove(next_square, game_status))
      return true;
      next_square[0] = square[0]-1;
      next_square[1] = square[1];
      if(validateMove(next_square, game_status))
      return true;
      next_square[0] = square[0]-1;
      next_square[1] = square[1]-1;
      if(validateMove(next_square, game_status))
      return true;
      next_square[0] = square[0]-1;
      next_square[1] = square[1]+1;
      if(validateMove(next_square, game_status))
      return true;  } }

  return false;

}

int** Pawn:: printPath(const int* const destination_square, ChessPiece* const game_status[BoardSize][BoardSize], int &count_square, bool &validator)  const {
  int vertical_distance = destination_square[0] - square[0];
  int horizontal_distance = destination_square[1] - square[1];
  int** path = NULL;
  validator = false;

  if(horizontal_distance ==0 && game_status[destination_square[0]][destination_square[1]] == NULL){
      if(color == Black){
        if(tag == 0){
          if(vertical_distance == 2 && game_status[square[0]+1][square[1]] == NULL){
            validator = true;
            path= new int*[abs(vertical_distance)-1];
            path[count_square] = new int[SquareSize];
            path[count_square][0] = destination_square[0]+1;
            path[count_square][1] = destination_square[1];
            count_square++;}
          if(vertical_distance == 1){
              validator = true;
              return path;  }
           }

        else if(vertical_distance == 1){
          validator = true;
          return path;  } }

      if(color == White){
        if(tag == 0){
          if(vertical_distance == -2 && game_status[square[0]-1][square[1]] == NULL){
            validator = true;
            path= new int*[abs(vertical_distance)-1];
            path[count_square] = new int[SquareSize];
            path[count_square][0] = destination_square[0]-1;
            path[count_square][1] = destination_square[1];
            count_square++;  }
            if(vertical_distance == -1){
              validator = true;
              return path;  }
           }

        else if(vertical_distance == -1){
          validator = true;
          return path;  } } }

  else if(abs(horizontal_distance) == 1 && game_status[destination_square[0]][destination_square[1]] != NULL){
    if((color == White && vertical_distance == -1) || (color == Black && vertical_distance == 1)){
      validator = true;
      return path;  } }

  return path;

 }
