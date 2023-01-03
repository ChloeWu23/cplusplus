words:words.o main.o
	g++ -Wall -g main.o words.o -o words

words.o: words.cpp words.h
	g++ -Wall -g -c words.cpp

main.o: main.cpp words.h
	g++ -Wall -g -c main.cpp

clean:
	rm -f *.o clean
