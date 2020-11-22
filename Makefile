all:
	g++ -Wall -O3 -o GA GA.cpp

clean:
	rm -f main *.o
