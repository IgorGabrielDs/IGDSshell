igds: Objects/main.o
	gcc Objects/main.o -o igds

Objects/main.o: Source/main.c
	gcc -c Source/main.c -o Objects/main.o