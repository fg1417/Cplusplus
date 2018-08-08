
chess: ChessMain.o ChessBoard.o ChessPiece.o
	g++ ChessMain.o ChessBoard.o ChessPiece.o -o chess

ChessMain.o: ChessMain.cpp ChessBoard.h
	g++ -Wall -g -c ChessMain.cpp

ChessBoard.o: ChessBoard.cpp ChessBoard.h ChessPiece.h
	g++ -Wall -g -c ChessBoard.cpp

ChessPiece.o: ChessPiece.cpp ChessPiece.h
	g++ -Wall -g -c ChessPiece.cpp

clean:
	rm -f ChessMain.o ChessBoard.o ChessPiece.o chess
