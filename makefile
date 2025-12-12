CXX = g++
CXXFLAGS = -std=c++17

OBJ = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

library: $(OBJ)
	$(CXX) -o $@ $^

clean:
	rm -f *.o library
