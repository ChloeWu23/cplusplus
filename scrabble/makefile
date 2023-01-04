scrabble:scrabble.o main.o
	g++ -Wall -g scrabble.o main.o -o scrabble

main.o: main.cpp scrabble.h
	g++ -Wall -g -c main.cpp

scrabble.o:scrabble.cpp scrabble.h
	g++ -Wall -g -c scrabble.cpp

clean:
	rm -f *.o scrabble
