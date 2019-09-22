.PHONY: all clean

all: my_melody.cpp

clean:
	rm -f generator my_melody.cpp

generator: generator.cpp rtttl_player.cpp notes_to_cpp.cpp
	g++ -std=c++17 generator.cpp rtttl_player.cpp notes_to_cpp.cpp -o generator

my_melody.cpp: generator
	./generator my_melody.cpp
