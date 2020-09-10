run: InnerSquareList.o SquareList.o Proj1Test.o
		g++ -Wall -std=c++11 -o run InnerSquareList.o SquareList.o Proj1Test.o
		./run

InnerSquareList.o: InnerSquareList.cpp InnerSquareList.h SquareList.h
		g++ -Wall -std=c++11 -c InnerSquareList.cpp

SquareList.o: SquareList.cpp SquareList.h InnerSquareList.h
		g++ -Wall -std=c++11 -c SquareList.cpp

Proj1Test.o: Proj1Test.cpp InnerSquareList.h SquareList.h
		g++ -Wall -std=c++11 -c Proj1Test.cpp

clean:
		rm *.o
		rm run