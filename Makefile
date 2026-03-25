CXX = g++
CXXFLAGS = -Wall -std=c++17
tictactoe: main.o
	$(CXX) $(CXXFLAGS) -o tactactoe main.o
main.o : main.cpp tictac.h
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f *.o tictactoe
