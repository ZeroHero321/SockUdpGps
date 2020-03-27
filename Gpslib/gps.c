#include "Myuart.h"
int speed_arr[] = { B38400, B19200, B9600, B4800, B2400, B1200, B300,
	    B38400, B19200, B9600, B4800, B2400, B1200, B300, };
int name_arr[] = {38400,  19200,  9600,  4800,  2400,  1200,  300,
	    38400,  19200,  9600, 4800, 2400, 1200,  300, };
int main(int argc, char **argv)
{
	int fd,temp1;
	int nread;
	char *sendmsg="abcd111";
	int SIZE=sizeof(sendmsg);
	char buff[512];
	char *GpH,*GpT;
	char GPSdata[64];
	char *dev ="/dev/ttyUSB0";	//
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
  bzero(buff, SIZE);
  while(1)  //this is output part
  	{	
		sleep(1);		
		//for(int ii=0;ii<10;ii++) write(fd,sendmsg,sizeof(sendmsg));//向串口发送数据
        	printf("%s\n",sendmsg);
   		nread = read(fd,buff,512); //读取数据
   		if(-1 == nread)
        		{
            		perror("Read Data Error!\n");
            		break;
        		}
        if(0 < nread)
        	{
            	buff[nread] = 0;			//GPH means GPS HEADER GPT means GPS TAIL
            	//printf("Recv Data: %s\n", buff);
			if ((GpH= strstr(buff, "$GNGGA,")) != NULL||(GpH= strstr(buff, "$GNGGA,")) != NULL)
				{
					if (((GpT = strstr(GpH, "\r\n")) != NULL) && (GpH<GpT))
						{
							memcpy(GPSdata, GpH, GpT-GpH);
							GPSdata[GpT-GpH]=0;
							printf("%s\n",GPSdata);
						}
				}
		}
   	 	
  	}
    close(fd);
    exit(0);
}
