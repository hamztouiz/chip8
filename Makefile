main := src/chip8.c
display := $(wildcard src/display/*.c)
cpu := src/cpu/*.c
memory := src/memory/*
keyboards := src/keyboards/*.c
CFLAGS := -Wall -Wextra -Werror -pedantic -std=c99 -g -lncurses
test := src/test.c

all: display.o cpu.o memory.o keyboards.o
	gcc $(main) $(wildcard build/*.o)  -o bin/main -DDEBUG=1 `sdl2-config --cflags --libs`

test: display.o cpu.o memory.o keyboards.o
	gcc $(test) $(wildcard build/*.o)  -o bin/test -DDEBUG=1 -lncurses `sdl2-config --cflags --libs`

prod: display.o cpu.o memory.o keyboards.o
	gcc $(main) -o bin/main -DDEBUG=0 `sdl2-config --cflags --libs`

display.o: src/display/*.c
	gcc $(display) -o build/display.o -c `sdl2-config --cflags --libs`

cpu.o: src/cpu/*.c
	gcc $(cpu) -o build/cpu.o -c `sdl2-config --cflags --libs`

memory.o: src/memory/*
	for folder in $(memory); do \
		for file in $$folder/*.c; do \
			echo $$file; \
			gcc $$file -o build/$$(basename $$file .c).o -c  -lncurses `sdl2-config --cflags --libs`; \
		done \
	done

keyboards.o: src/keyboards/*.c
	gcc $(keyboards) -o build/keyboards.o -c `sdl2-config --cflags --libs`

clean:
	rm build/*