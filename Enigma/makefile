enigma: enigma.o class.o
	g++ -g enigma.o class.o -o enigma

enigma.o: enigma.cpp class.h
	g++ -Wall -g -c enigma.cpp

class.o: class.cpp class.h
	g++ -Wall -g -c class.cpp

clean:
	rm -f *.o enigma
