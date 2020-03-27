#ifndef STRUCT_H
#define STRUCT_H
#define N1 512
#pragma pack(1)  //���ýṹ��ı߽����Ϊһ���ֽڣ����ṹ��������ݰ���n��n���ֽڴ�ţ�#pragma pack (n)��
typedef struct
{
	unsigned char lenh;
	unsigned char lenl;
	unsigned char id;
	unsigned char mode;
}cmd_head;//size: 4 byte

typedef struct
{
	unsigned char h; //ʱ
	unsigned char m; //��
	unsigned char s; //��
}time_s;

typedef struct
{
	short start_freq;// start frequency
	short stop_freq;//  stop frequency
	short scan_accu;//  scanning accuracy ɨ�辫��

}scan_plan_s;

typedef struct
{
	int num;//ɨ�����
	int scan_cycle;//ɨ����
	scan_plan_s* head;//ɨ��ƻ��б�

}scan_plan_list_s;

//ע������Э��֡
typedef struct
{
	unsigned char lenh;
	unsigned char lenl;
	unsigned char id;
	unsigned char mode;
	unsigned char seg_num;   //ɨ�����
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
//ע��ack֡
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

//Ƶ�׼������֡
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
	long long bw_hz; // Analog bandwidth in Hz   ģ�����  long long����8�ֽڳ���
	long long fs_hz; // Baseband sample rate in Hz   ����������
	long long lo_hz; // Local oscillator frequency in Hz  ����Ƶ��
	const char* rfport; // Port name 
};
#endif
