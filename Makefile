main := src/chip8.c
display := $(wildcard src/display/*.c)
cpu := src/cpu/*.c
memory := src/memory/*.c
keyboards := src/keyboards/*.c
CFLAGS := -Wall -Wextra -Werror -pedantic -std=c99 -g
all: display.o cpu.o memory.o keyboards.o
	gcc $(main) $(wildcard build/*.o)  -o bin/main -DDEBUG=1 `sdl2-config --cflags --libs`

prod: display.o cpu.o memory.o keyboards.o
	gcc $(main) -o bin/main -DDEBUG=0 `sdl2-config --cflags --libs`

display.o: src/display/*.c
	gcc $(display) -o build/display.o -c `sdl2-config --cflags --libs`

cpu.o: src/cpu/*.c
	gcc $(cpu) -o build/cpu.o -c `sdl2-config --cflags --libs`

memory.o: src/memory/*.c
	gcc $(memory) -o build/memory.o -c `sdl2-config --cflags --libs`

keyboards.o: src/keyboards/*.c
	gcc $(keyboards) -o build/keyboards.o -c `sdl2-config --cflags --libs`

clean:
	rm build/*