build: tema1.c
	gcc -o tema1 tema1.c -Wall

run: tema1
	./tema1

clean:
	rm -f *.o tema1
