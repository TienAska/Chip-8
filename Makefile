INCLUDES= -I ./include
FRAMEWORKS= -F /Library/Frameworks -framework SDL2 -framework AudioUnit
FLASG= -g

OBJECTS= ./build/chip8memory.o ./build/chip8stack.o ./build/chip8keyboard.o ./build/chip8.o ./build/chip8screen.o
all: ${OBJECTS}
	clang ${FLASG} ${INCLUDES} ${FRAMEWORKS} ./src/main.c ${OBJECTS} -o ./bin/Chip-8

./build/chip8memory.o: ./src/chip8memory.c
	clang ${FLASG} ${INCLUDES} ./src/chip8memory.c  -c -o ./build/chip8memory.o

./build/chip8stack.o: ./src/chip8stack.c
	clang ${FLASG} ${INCLUDES} ./src/chip8stack.c  -c -o ./build/chip8stack.o

./build/chip8keyboard.o: ./src/chip8keyboard.c
	clang ${FLASG} ${INCLUDES} ./src/chip8keyboard.c  -c -o ./build/chip8keyboard.o

./build/chip8.o: ./src/chip8.c
	clang ${FLASG} ${INCLUDES} ./src/chip8.c  -c -o ./build/chip8.o

./build/chip8screen.o: ./src/chip8screen.c
	clang ${FLASG} ${INCLUDES} ./src/chip8screen.c  -c -o ./build/chip8screen.o

clean:
	rm -rf build/*
	rm -rf bin/*