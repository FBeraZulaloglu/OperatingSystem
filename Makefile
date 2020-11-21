CC=gcc

all: beraShell

beraShell: myshell.c islem
	$(CC) -lreadline -o beraShell myshell.c

islem : islem.c topla cikar
	$(CC) -o islem  islem.c

tekrar.o: tekrar.c 
	$(CC) -o tekrar tekrar.c

topla : topla.c 
	$(CC) -o topla topla.c

cikar : cikar.c 
	$(CC) -o cikar cikar.c

clean:
	rm myshell.o	topla.o	cikar.o	islem.o