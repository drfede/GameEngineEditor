build:
	g++ -w -std=c++14 -Wfatal-errors \
	./src/*.cpp \
	-o ./bin/game \
	-lSDL2 \
	-lSDL2_image \
	-lSDL2_ttf \
	-lSDL2_mixer;

clean:
	rm ./bin/game;

run:
	./bin/game;
