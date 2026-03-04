igds: Objects/main.o Objects/ler_arquivo.o Objects/inserir_lista.o Objects/input.o
	gcc Objects/main.o Objects/ler_arquivo.o Objects/inserir_lista.o Objects/input.o -o igds

Objects/main.o: Source/main.c
	gcc -c Source/main.c -o Objects/main.o

Objects/inserir_lista.o: Source/inserir_lista.c
	gcc -c Source/inserir_lista.c -o Objects/inserir_lista.o

Objects/ler_arquivo.o: Source/ler_arquivo.c
	gcc -c Source/ler_arquivo.c -o Objects/ler_arquivo.o

Objects/input.o: Source/input.c
	gcc -c Source/input.c -o Objects/input.o