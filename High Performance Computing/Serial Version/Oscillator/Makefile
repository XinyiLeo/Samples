all: oscillator run

oscillator: main.c
	gcc -o oscillator main.c -lblas -lm 

run: oscillator
	./oscillator 1 0.5 1000 3000

