multitap:main.o multitap.o
	g++ -Wall -g main.o multitap.o -o multitap

main.o: main.cpp multitap.h
	g++ -Wall -g -c main.cpp

multitap.o:multitap.cpp multitap.h
	g++ -Wall -g -c multitap.cpp

clean:
	rm -f *.o multitap
