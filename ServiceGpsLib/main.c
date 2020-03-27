#include "Myuart.h"
#include "SockUdp.h"
int speed_arr[] = { B38400, B19200, B9600, B4800, B2400, B1200, B300,
	    B38400, B19200, B9600, B4800, B2400, B1200, B300, };
int name_arr[] = {38400,  19200,  9600,  4800,  2400,  1200,  300,
	    38400,  19200,  9600, 4800, 2400, 1200,  300, };
int main(int argc, char **argv)
{
	int fd,temp1,nread,sock,startgo;
	socklen_t SendAddLen;//发送的目标地址的长度
	char *sendmsg="UART:";
	int SIZE=sizeof(sendmsg);
	char buf1[512],GPSdata[64];
	char *GpH,*GpT,*dev ="/dev/ttyUSB0";//串口的设备名 若提示错误打不开端口的话 更改设备名 
//------------------串口部分---------------		或者是要用root用户才能打开 sudo su
	fd = OpenDev(dev);
	if (fd>0)
    set_speed(fd,9600);
	else
		{
		printf("Can't Open Serial Port!\n");
		exit(0);
		}
  if (set_Parity(fd,8,1,'N')== FALSE)
  {
    printf("Set Parity Error\n");
    exit(1);
  }
  bzero(buf1, SIZE);
//--------------------------------------------
//------------------UDP部分-------------------
if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0)//开启sock
	{printf("Socket Failed!\n");exit(0);}
	
    struct sockaddr_in servaddr,CliAddr;	//定义两个地址结构
    memset(&servaddr, 0, sizeof(servaddr));//两个地址结构清零
	memset(&CliAddr, 0, sizeof(CliAddr));
	
    servaddr.sin_family = AF_INET;		//板子的地址初始化
    servaddr.sin_port = htons(MYPORT);	
    servaddr.sin_addr.s_addr = inet_addr("192.168.0.113");
	
	CliAddr.sin_family = AF_INET;	//电脑的地址初始化
    CliAddr.sin_port = htons(1242);
    CliAddr.sin_addr.s_addr = inet_addr("192.168.0.112");
	SendAddLen=sizeof(CliAddr);//地址的长度(sendto时需要)
	
	printf("监听%d端口\n",MYPORT);//绑定并监听板子自己的端口
	if (bind(sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        {printf("Bind Failed!\n");exit(0);}
	printf("Input A Number then start\n");
	scanf("%d",&startgo);//输入一个数后 然后开始
//--------------------------------------------
  while(1)  //this is output part
  	{	
		sleep(1);		
		//for(int ii=0;ii<10;ii++) write(fd,sendmsg,sizeof(sendmsg));//向串口发送数据
        	printf("%s\n",sendmsg);
   		nread = read(fd,buf1,512); //读取数据
   		if(-1 == nread)
        		{
            		perror("Read Data Error!\n");
            		break;
        		}
        if(0 < nread)
        	{
            	buf1[nread] = 0;			//GPH means GPS HEADER GPT means GPS TAIL
            	//printf("Recv Data: %s\n", buf1);
			if ((GpH= strstr(buf1, "$GNGGA,")) != NULL||(GpH= strstr(buf1, "$GNGGA,")) != NULL)
				{
					if (((GpT = strstr(GpH, "\r\n")) != NULL) && (GpH<GpT))
						{
							memcpy(GPSdata, GpH, GpT-GpH);
							GPSdata[GpT-GpH]=0;
							printf("%s\n",GPSdata);
							sendto(sock,GPSdata,GpT-GpH, 0,(struct sockaddr *)&CliAddr,SendAddLen); 
						}
				}
		}   	 	
  	}
    close(fd);exit(0);
}
