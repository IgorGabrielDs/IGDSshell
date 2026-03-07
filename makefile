igds: Objects/main.o Objects/arquivo.o Objects/inserir_lista.o Objects/input.o Objects/executar_comandos.o
	gcc Objects/main.o Objects/arquivo.o Objects/inserir_lista.o Objects/input.o Objects/executar_comandos.o -o igds

Objects/main.o: Source/main.c
	gcc -IInclude -c Source/main.c -o Objects/main.o

Objects/inserir_lista.o: Source/inserir_lista.c
	gcc -IInclude -c Source/inserir_lista.c -o Objects/inserir_lista.o

Objects/arquivo.o: Source/arquivo.c
	gcc -IInclude -c Source/arquivo.c -o Objects/arquivo.o

Objects/input.o: Source/input.c
	gcc -IInclude -c Source/input.c -o Objects/input.o

Objects/executar_comandos.o: Source/executar_comandos.c
	gcc -IInclude -c Source/executar_comandos.c -o Objects/executar_comandos.o