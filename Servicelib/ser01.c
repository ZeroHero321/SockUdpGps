#include "SockUdp.h"
int main(void)
{
    int sock,temp;
    if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
	{
		printf("Socket Failed!\n");
		exit(0);
	}
    
    struct sockaddr_in servaddr,CliAddr;
    memset(&servaddr, 0, sizeof(servaddr));
	memset(&CliAddr, 0, sizeof(CliAddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(MYPORT);	//板子
    servaddr.sin_addr.s_addr = inet_addr("192.168.0.113");
	CliAddr.sin_family = AF_INET;	//电脑
    CliAddr.sin_port = htons(1242);
    CliAddr.sin_addr.s_addr = inet_addr("192.168.0.112");
    
    printf("监听%d端口\n",MYPORT);
    if (bind(sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        {printf("Bind Failed!\n");exit(0);}
    scanf("%d",&temp);//输入一个数后 然后开始
    echo_ser(sock,CliAddr);// 发送主体函数

    return 0;
}
