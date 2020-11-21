CC=gcc

all: myshell

myshell: myshell.c islem tekrar
	$(CC) -o myshell myshell.c -lreadline

islem : islem.c topla cikar
	$(CC) -o islem  islem.c

tekrar: tekrar.c 
	$(CC) -o tekrar tekrar.c

topla : topla.c 
	$(CC) -o topla topla.c

cikar : cikar.c 
	$(CC) -o cikar cikar.c

clean:
	rm beraShell	islem	tekrar	topla	cikar myShell