correct:correct.o main.o
	g++ -Wall -g main.o correct.o -o correct

main.o:main.cpp correct.h
	g++ -Wall -g -c main.cpp

correct.o:correct.cpp correct.h
	g++ -Wall -g -c correct.cpp

clean:
	rm -f *.o correct
