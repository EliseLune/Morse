CXX = g++
CXXFLAGS = -Wall -ggdb
RM = rm -f

all: morse

morse: main.o MorsCode.o
	$(CXX) $(CXXFLAGS) $^ -o $@

main.o: main.cpp MorsCode.h
MorsCode.o: MorsCode.cpp BinTree.h BinTree_impl.h

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) MorsCode.o main.o morse