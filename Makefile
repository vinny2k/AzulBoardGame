.default: all

all: azul

clean:
	rm -rf azul azul.dSYM *.o

azul: main.o CentralFactory.o LinkedList.o Mosaic.o Player.o Tile.o NewGame.o SaveGame.o LoadGame.o BinarySearchTree.o BSTFactory.o BoxLid.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^