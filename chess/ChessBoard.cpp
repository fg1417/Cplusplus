
#include "ChessPiece.h"
#include "ChessBoard.h"
#include <iostream>
#include <cstring>

using namespace std;
void ChessBoard:: setBoard(){
  count = 0;
  game_status[0][0] = new Castle("A8", Black);
  game_status[0][1] = new Knight("B8", Black);
  game_status[0][2] = new Bishop("C8", Black);
  game_status[0][3] = new Queen("D8", Black);
  black_king = new King("E8", Black);
  game_status[0][4] = black_king;
  game_status[0][5] = new Bishop("F8", Black);
  game_status[0][6] = new Knight("G8", Black);
  game_status[0][7] = new Castle("H8", Black);

  for (int i = 0; i < BoardSize; i++){
    char square[SquareSize];
    square[0] = File[i];
    square[1] = Rank[1];
    game_status[1][i] = new Pawn(square, Black);  }

  for (int i = 2; i < BoardSize - 2; i++)
    for(int j = 0; j< BoardSize; j++)
      game_status[i][j] = NULL;

  for (int i = 0; i < BoardSize; i++){
    char square[SquareSize];
    square[0] = File[i];
    square[1] = Rank[6];
    game_status[6][i] = new Pawn(square, White);  }

  game_status[7][0] = new Castle("A1", White);
  game_status[7][1] = new Knight("B1", White);
  game_status[7][2] = new Bishop("C1", White);
  game_status[7][3] = new Queen("D1", White);
  white_king = new King("E1", White);
  game_status[7][4] = white_king;
  game_status[7][5] = new Bishop("F1", White);
  game_status[7][6] = new Knight("G1", White);
  game_status[7][7] = new Castle("H1", White);

  cout<< "A new chess game is started!"<< endl;

}

void ChessBoard:: clearBoard(){
  for (int i = 0; i < BoardSize; i++)
  for (int j = 0; j < BoardSize; j++)
  if(game_status[i][j] )
  delete game_status[i][j];
}

bool ChessBoard:: validateMove(const int* const source_square, const int* const destination_square){
  if (game_status[source_square[0]][source_square[1]]->validateMove(destination_square, game_status))
    return true;
  else
    return false;

}

void ChessBoard:: movePiece(const int* const source_square, const int* const destination_square){
  if(game_status[destination_square[0]][destination_square[1]])
  delete game_status[destination_square[0]][destination_square[1]];
  game_status[destination_square[0]][destination_square[1]] = game_status[source_square[0]][source_square[1]];
  game_status[destination_square[0]][destination_square[1]]->resetSquare(destination_square);
  game_status[source_square[0]][source_square[1]] = NULL;

}

bool ChessBoard:: searchMove(const ChessColor my_color){
  bool flag = false;
  int next_square[SquareSize] = {0,0};
  King* my_king = (my_color == White)? white_king: black_king;
  for(int i = 0; i < BoardSize && !flag; i++)
    for(int j = 0; j < BoardSize && !flag; j++)
      if(game_status[i][j] && game_status[i][j]->getColor() == my_color && game_status[i][j]->searchMove(next_square, game_status)){
            int start_square[SquareSize] = {i, j};
            ChessPiece* temp = game_status[next_square[0]][next_square[1]];
            movePiece(start_square, next_square);
            if(my_king->detectStatus(game_status) == IN_CHECK)
              continue;
            else
              flag = true;
            cancelMove(start_square, next_square, temp);  }
  return flag;

}

void ChessBoard:: cancelMove(const int* source, const int* destination, ChessPiece* temp){
  game_status[source[0]][source[1]] = game_status[destination[0]][destination[1]];
  game_status[destination[0]][destination[1]] = temp;
  game_status[source[0]][source[1]]->resetSquare(source);

}

void ChessBoard:: detectStatus(){
  if(count % 2 == 0){
    switch (white_king->detectStatus(game_status)) {
      case IN_CHECKMATE:
        cout<< white_king->printColor()<< " is in checkmate"<< endl;
        break;
      case IN_CHECK:
        cout<< white_king->printColor()<< " is in check"<< endl;
        break;
      case NOT_IN_CHECK:{
        switch (black_king->detectStatus(game_status)) {
          case IN_CHECKMATE:
            cout<< black_king->printColor()<< " is in checkmate"<< endl;
            break;
          case IN_CHECK:
            cout<< black_king->printColor()<< " is in checkmate"<< endl;
            break;
          case NOT_IN_CHECK:{
            if(searchMove(White)|| searchMove(Black))
              break;
            else
              cout<< "The game ends in a stalemate"<< endl; } } } } }

  if(count % 2 == 1){
    switch (black_king->detectStatus(game_status)) {
      case IN_CHECKMATE:
        cout<< black_king->printColor()<< " is in checkmate"<< endl;
        break;
      case IN_CHECK:
        cout<< black_king->printColor()<< " is in check"<< endl;
        break;
      case NOT_IN_CHECK:{
        switch (white_king->detectStatus(game_status)) {
        case IN_CHECKMATE:
          cout<< white_king->printColor()<< " is in checkmate"<< endl;
          break;
        case IN_CHECK:
          cout<< white_king->printColor()<< " is in check"<< endl;
          break;
        case NOT_IN_CHECK:{
          if(searchMove(Black) || searchMove(White))
            break;
          else
            cout<< "The game ends in a stalemate"<< endl; } } } } }

  }

ChessBoard:: ChessBoard(){
  setBoard();
}

ChessBoard:: ~ ChessBoard(){
  clearBoard();
}


void ChessBoard:: resetBoard(){
  clearBoard();
  setBoard();
}

void ChessBoard:: submitMove(const char* const source_square, const char* const destination_square){
  int source[2] = {0, 0}, destination[2] = {0, 0};
  count ++;

  if(!findSquare(source_square, source[0], source[1])){
    cerr<< "Invalid square!"<< endl;
    return; }

  if(game_status[source[0]][source[1]] == NULL){
    cerr<< "There is no piece at position "<< source_square<< endl;
    return; }

  if(!(count % 2 == 0 && game_status[source[0]][source[1]]->getColor() == Black) && !(count % 2 == 1 && game_status[source[0]][source[1]]->getColor() == White)){
    cerr<< "It is not "<< game_status[source[0]][source[1]]->printColor()<< "’s turn to move!"<< endl;
    return; }

  if(!findSquare(destination_square, destination[0], destination[1])){
    cerr<< "Invalid square!"<< endl;
    return; }

  if(!validateMove(source, destination)) {
    cerr<< game_status[source[0]][source[1]]->printColor()<< "’s "<< game_status[source[0]][source[1]]->getName()<< " cannot move to "<< destination_square<< "!"<< endl;
    return; }

  ChessPiece* temp = NULL;
  if(game_status[destination[0]][destination[1]])
  temp = game_status[destination[0]][destination[1]];

  movePiece(source, destination);

  if(count % 2 == 1){
    if(white_king->detectStatus(game_status) == IN_CHECK){
      cancelMove(source, destination, temp);
      cerr<< "It is illegal to make a move that would put or leave White king in check."<< endl;
      return ;
    }
  }

  if(count % 2 == 0){
    if(black_king->detectStatus(game_status) == IN_CHECK){
      cancelMove(source, destination, temp);
      cerr<< "It is illegal to make a move that would put or leave Black king in check."<< endl;
      return ;
    }
  }

  game_status[destination[0]][destination[1]]->resetTag();

  if(temp == NULL)
    cout<< game_status[destination[0]][destination[1]]->printColor()<< "'s "<< game_status[destination[0]][destination[1]]->getName()<< " moves from "<<source_square<< " to "<< destination_square<< endl;
  else
    cout<< game_status[destination[0]][destination[1]]->printColor()<< "'s "<< game_status[destination[0]][destination[1]]->getName()<< " moves from "<<source_square<< " to "<< destination_square
    << " taking "<< temp->printColor()<< "'s "<< temp->getName()<< endl;

  detectStatus();
  return;

}


 bool ChessBoard:: validateCastling(const int* const source_1, const int* const destination_1, const int* const source_2, const int* const destination_2){
   if((game_status[source_1[0]][source_1[1]]->getTag() == 1) || game_status[source_2[0]][source_2[1]]->getTag() == 1 )
    return false;

   King* current_king = (game_status[source_1[0]][source_1[1]]->getColor() == White)? white_king: black_king;
   if(current_king->detectStatus(game_status) == IN_CHECKMATE)
    return false;

   int opponent_color = (game_status[source_1[0]][source_1[1]]->getColor() == White) ? Black: White;
   int operation = 1;
   int vertical_distance = source_2[0] - source_1[0];
   int horizontal_distance = source_2[1] - source_1[1];
   int K_vertical_distance = destination_1[0] - source_1[0];
   int C_vertical_distance = destination_2[0] - source_2[0];

   if(horizontal_distance < 0)
    operation = -1;

   if(!(vertical_distance == 0 && K_vertical_distance == 0 && C_vertical_distance == 0))
    return false;

   if(!(destination_1[1] == source_1[1] + operation*2) && (destination_2[1] == (destination_1[1] - operation)))
    return false;

   for(int i = source_1[1]; i != source_1[1] + operation*3; i = i + operation){
     int next_square[SquareSize] = {source_1[0], i};
     if(game_status[next_square[0]][next_square[1]])
      return false;
     for(int i = 0; i < BoardSize; i++)
       for(int j = 0; j < BoardSize; j++)
         if(game_status[i][j] && game_status[i][j]->getColor() == opponent_color && game_status[i][j]->validateMove(next_square, game_status))
          return false; }

   return true;

 }

 void ChessBoard:: castling(const char* const source_square_1, const char* const destination_square_1, const char* const source_square_2, const char* const destination_square_2){
   int source_1[2] = {0, 0}, source_2[2] = {0, 0}, destination_1[2] = {0, 0}, destination_2[2] = {0, 0};
   count ++;

   if(!findSquare(source_square_1, source_1[0], source_1[1])){
     cerr<< "Invalid square!"<< endl;
     return; }

   if(game_status[source_1[0]][source_1[1]] == NULL){
     cerr<< "There is no piece at position "<< source_square_1<< endl;
     return; }

   if(!findSquare(source_square_2, source_2[0], source_2[1])){
     cerr<< "Invalid square!"<< endl;
     return; }

   if(game_status[source_2[0]][source_2[1]] == NULL){
     cerr<< "There is no piece at position "<< source_square_2<< endl;
     return; }

   if(!(count % 2 == 0 && game_status[source_1[0]][source_1[1]]->getColor() == Black) && !(count % 2 == 1 && game_status[source_1[0]][source_1[1]]->getColor() == White)){
     cerr<< "It is not "<< game_status[source_1[0]][source_1[1]]->printColor()<< "’s turn to move!"<< endl;
     return; }

   if(game_status[source_1[0]][source_1[1]]->getColor() != game_status[source_2[0]][source_2[1]]->getColor()){
     cerr<< "Invalid castling!"<< endl;
     return;  }

    if(!(!strcmp(game_status[source_1[0]][source_1[1]]->getName(), "King") && !strcmp(game_status[source_2[0]][source_2[1]]->getName(), "Castle"))){
      cerr<< "Invalid castling!"<< endl;
      return; }

    if(!validateCastling(source_1, destination_1, source_2, destination_2)){
      cerr<< "Invalid castling!"<< endl;
      return; }

     cout<< game_status[source_1[0]][source_1[1]]->printColor()<< "'s King moves from "<< source_square_1<< " to "<< destination_square_1<<endl;
     movePiece(source_1, destination_1);
     cout<< game_status[source_2[0]][source_2[1]]->printColor()<<"'s Castle moves from "<< source_square_2<< " to "<< destination_square_2<< endl;
     movePiece(source_2, destination_2);
     detectStatus();
     return;
   }
