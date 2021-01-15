CXX = g++
CXXFLAGS = -Wall -ggdb -Iinclude
RM = rm -f
AR = /usr/bin/ar -r

src := $(wildcard src/*.cpp)
obj := $(subst src, build, $(src:.cpp=.o))

all: directories libmorse.a morse

morse: main.cpp libmorse.a
	$(CXX) $(CXXFLAGS) $^ -o $@

libmorse.a: $(obj)
	$(AR) $@ $^

build/MorsCode.o: src/MorsCode.cpp include/MorsCode.h include/BinTree.h include/BinTree_impl.h

build/%.o: src/%.cpp include/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

directories: build
build:
	mkdir -p $@

clean:
	$(RM) libmorse.a morse
	rm -r build