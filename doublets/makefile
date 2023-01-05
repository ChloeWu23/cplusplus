doublets:main.o doublets.o
	g++ -Wall -g main.o doublets.o -o doublets

main.o: main.cpp doublets.h
	g++ -Wall -g main.cpp -c

doublets.o:doublets.cpp doublets.h
	g++ -Wall -g -c doublets.cpp

clean:
	rm -f *.o clean
