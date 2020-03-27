service:ser01.o SockUdp.o
	gcc ser01.o SockUdp.o -o service
ser01.o:ser01.c
	gcc -c ser01.c -o ser01.o
SockUdp.o:SockUdp.c
	gcc -c SockUdp.c -o SockUdp.o
.PHONY:clean
clean:
	rm -rf *o
