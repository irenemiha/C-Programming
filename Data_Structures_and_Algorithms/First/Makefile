all: build

build:
	gcc -o tema1 functii.c main.c -lm -g -std=c99

clean:
	rm tema1

run: build	
	./tema1 --c < tests/inputs/test4_gaps10k