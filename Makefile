all: main.c key.c key.h
	gcc main.c key.c xor.c -o bin/xolo
