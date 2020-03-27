#ifndef STRUCT_H
#define STRUCT_H
#define N1 512
#pragma pack(1)  //设置结构体的边界对齐为一个字节，将结构体里的数据按照n个n个字节存放（#pragma pack (n)）
typedef struct
{
	unsigned char lenh;
	unsigned char lenl;
	unsigned char id;
	unsigned char mode;
}cmd_head;//size: 4 byte

typedef struct
{
	unsigned char h; //时
	unsigned char m; //分
	unsigned char s; //秒
}time_s;

typedef struct
{
	short start_freq;// start frequency
	short stop_freq;//  stop frequency
	short scan_accu;//  scanning accuracy 扫描精度

}scan_plan_s;

typedef struct
{
	int num;//扫描段数
	int scan_cycle;//扫描间隔
	scan_plan_s* head;//扫描计划列表

}scan_plan_list_s;

//注册请求协议帧
typedef struct
{
	unsigned char lenh;
	unsigned char lenl;
	unsigned char id;
	unsigned char mode;
	unsigned char seg_num;   //扫描段数
	unsigned char freq_starth;
	unsigned char freq_startl;
	unsigned char freq_stoph;
	unsigned char freq_stopl;
	unsigned char freq_accuh;
	unsigned char freq_accul;
	unsigned char now;
	unsigned char h;
	unsigned char m;
	unsigned char s;
}reg_pck;
//注册ack帧
typedef struct
{
	unsigned char lenh;
	unsigned char lenl;
	unsigned char id;
	unsigned char mode;
	unsigned char h;
	unsigned char m;
	unsigned char s;
}reg_ack;

//频谱检测数据帧
typedef struct
{
	unsigned char lenh;
	unsigned char lenl;
	unsigned char id;
	unsigned char mode;
	unsigned char freq_starth;
	unsigned char freq_startl;
	unsigned char freq_stoph;
	unsigned char freq_stopl;
	unsigned char seg_num;
	signed char fft_buffer[N1];
	unsigned char h;
	unsigned char m;
	unsigned char s;
}fft_data_pack_s;



struct stream_cfg {
	long long bw_hz; // Analog bandwidth in Hz   模拟带宽  long long代表8字节长度
	long long fs_hz; // Baseband sample rate in Hz   基带采样率
	long long lo_hz; // Local oscillator frequency in Hz  本振频率
	const char* rfport; // Port name 
};
#endif
