default: main
	g++ build/main.o build/graphics.o build/game.o -o bin/play -I include -L lib -l SDL2

main: src/main.cpp graphics game
	g++ -c src/main.cpp -o build/main.o -I include 

graphics: src/graphics.cpp
	g++ -c src/graphics.cpp -o build/graphics.o -I include

game: src/game.cpp
	g++ -c src/game.cpp -o build/game.o -I include

play: default
	./bin/play
