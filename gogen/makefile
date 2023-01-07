gogen:main.o gogen.o
	g++ -Wall -g main.o gogen.o -o gogen

main.o:main.cpp gogen.h common.h mask.h
	g++ -Wall -g -c main.cpp

gogen.o:gogen.cpp gogen.h
	g++ -Wall -g -c gogen.cpp

clean:
	rm -f *.o gogen
