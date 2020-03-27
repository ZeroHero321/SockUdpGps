gps:gps.o Myuart.o
	gcc gps.o Myuart.o -o gps
gps.o:gps.c
	gcc -c gps.c -o gps.o
Myuart.o:Myuart.c
	gcc -c Myuart.c -o Myuart.o
.PHONY:clean
clean:
	rm -rf *o
