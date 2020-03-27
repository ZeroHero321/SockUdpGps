#include "SockUdp.h"
void echo_ser(int sock,struct sockaddr_in peeraddr)
{
    char recvbuf[1024] ="1234567";
    socklen_t peerlen;
    int n=7;
    peerlen = sizeof(peeraddr);
    while (1)
    {
        
            printf("TX的数据：%s\n",recvbuf);
            sendto(sock, recvbuf, n, 0,(struct sockaddr *)&peeraddr, peerlen); 
	    sleep(1);   
    }
    close(sock);
}
