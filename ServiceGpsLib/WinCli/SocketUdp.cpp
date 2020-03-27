// SocketUdp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include "pch.h"//visual studio 建立工程时自己生成的 
#include"main.h"
#include <windows.h>
int main()
{
	FILE *fp;
	int ret, i;
	static char buf[600] = {0};
	static char msg[20] = "654321";
	char longitude[11] = { 0 }, Dimension[11] = { 0 };
	WSADATA s;
	if (WSAStartup(MAKEWORD(2, 2), &s) != 0) // 通过连接两个给定的无符号参数,首个参数为低字节
	{
		printf("Init Windows Socket Failed! Error: %d\n");
		getchar();
		return -1;
	}
	SOCKET sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	sockaddr_in dev;
	sockaddr_in addr;
	int len = sizeof(dev),GpsDaLen=0;//收到的数据的长度
	memset(&dev, 0, sizeof(dev));
	memset(&addr, 0, sizeof(addr));
	memset(buf, 0, sizeof(buf));
	dev.sin_family = PF_INET; //使用internet协议 板子的地址初始化
	dev.sin_port = htons(1241);
	dev.sin_addr.s_addr = inet_addr("192.168.0.113");
	addr.sin_family = PF_INET;			//电脑的地址初始化
	addr.sin_port = htons(1242);
	addr.sin_addr.s_addr = inet_addr("192.168.0.112");

	//bind address
	ret = bind(sockfd, (SOCKADDR*)&addr, sizeof(SOCKADDR));  //绑定socket到特定端口，地址
	if (ret < 0)
	{
		printf("bind addr failed \n");
		return 0;
	}
	if ((fp = fopen("GPSdata.txt", "a+")) == NULL) {
		printf("Cannot open file, press any key to exit!\n");
		exit(1);
	}
	printf("程序已经启动...\n");
	while (1)
	{
		GpsDaLen=recvfrom(sockfd, buf,50, 0, (struct sockaddr*)&dev,&len);
		printf("RX DATA:%s\n", buf);	
			strncpy(Dimension, buf + 18, 9);//对于$GNGGA这一行来说的第18位开始的9个字符 
			strncpy(longitude, buf + 30,10);//第30位开始的10个字符
			fputs(Dimension,fp);fputs(" ", fp);fputs(longitude, fp);fputs("\n", fp);
		
		//Sleep(1000);
		fflush(fp);//起到刷新作用 不加的话 输入文件无效 显示不出来
	}
	closesocket(sockfd);
	WSACleanup();
	return 1;
}
