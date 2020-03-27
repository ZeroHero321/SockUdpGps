main:main.o Myuart.o
	gcc main.o Myuart.o -o main
main.o:main.c
	gcc -c main.c -o main.o
Myuart.o:Myuart.c
	gcc -c Myuart.c -o Myuart.o
.PHONY:clean
clean:
	rm -rf *o
