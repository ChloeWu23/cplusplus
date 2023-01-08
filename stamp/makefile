stamp:stamp.o main.o
	g++ -Wall -g  stamp.o main.o -o stamp -lcrypto

stamp.o:stamp.h stamp.cpp
	g++ -Wall -g  -c stamp.cpp -lcrypto

main.o:main.cpp stamp.h
	g++ -Wall -g  -c main.cpp

clean:
	rm -f *.o stamp
