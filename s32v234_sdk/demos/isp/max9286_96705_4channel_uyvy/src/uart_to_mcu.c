#include "stdio.h"
#include "string.h"

#include "fcntl.h"
#include "errno.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "stdlib.h"
#include "stdarg.h"
#include "termios.h"

#include "uart_to_mcu.h"

#define McuOk  1
#define McuErr 2

pthread_mutex_t mcu_data_mutex; 

PCREADDATA 		McuSend_PcReadData;
PCREADDATA 	    McuSend_PcReadData_Pc;
PCWRITEDATA 	McuReceive_PcWriteData;
TARGETPLACEDATA ToMcuTargetData;

extern BasicData *BasicData_Ptr;
extern ParkingPlace *ParkingPlace_Ptr;
extern McuSendDada *McuSendDada_Ptr;
extern PCWRITEDATA *PCWRITEDATA_Ptr;
extern LanelineData *LanelineData_Ptr;
extern ObstacleData *ObstacleData_Ptr;

//extern int Car_Parking_Status;
//extern int Car_Speed_Flag;
int Car_Parking_Status;
int Car_Speed_Flag;

unsigned int McuTimeData; 
unsigned long long Mcu_tt;
int num;
short int McuSendOffset[10*3];
unsigned int McuSendCounter[10];
 

unsigned long long GetNowTimeUs(void);


int direction;  //0x01 --> left   0x02 --> right

char parking_mode_ok;
int  parking_mode_ok_flag;

char printf_flag = 0;
char printf_flag_ext = 0;

char Mcu_receive_FLAG_tmp; 
char Mcu_receive_FLAG = 1;
char Mcu_receive_FLAG_02 = 1;
char Mcu_receive_FLAG_03 = 1;
char Mcu_receive_FLAG_04 = 1;


char Pc_Tx_Mcu_Nums   	 =0;
char Pc_Tx_Mcu_Nums_02   =0;
char Pc_Tx_Mcu_Nums_03   =0;
char Pc_Tx_Mcu_Nums_04   =0;


int gear_show_flag;
int fd_uart;
unsigned char connect_success_flag;
unsigned char txBuffer[40];//10//= {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa};//0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99
unsigned char tx2Buffer[40];
unsigned char tx3Buffer[40];
unsigned char tx4Buffer[38];
unsigned char tx5Buffer[60];


unsigned char rxBuffer[180];//30
int count;
int heart_beat_rev_flag;

int reset_chang_flag;
int reset_chang_flagtmp;
int reset_status_changed_num;
int reset_new_value_cnt;
int reset_new_value_cnt_flag;
int lane_TimeStamp_bak;
int obstacle_TimeStamp_bak;

void frame_get_data(unsigned char *r_buffer, unsigned char len);

volatile unsigned int CounterTick;

//below is for mcu --->pc  :20180622------PC---communication
//up is for mcu--->PC

//below is for PC---->MCU
//up is for pc------>mcu
unsigned char Add_Verify(unsigned char *p,unsigned char length);

PCREADDATA 	* get_data_from_mcu(void)
{
//	McuSend_PcReadData.Pc_Read_Flag = 1;
//	usleep(40000);//20ms
	pthread_mutex_lock(&mcu_data_mutex);
	McuSend_PcReadData_Pc = McuSend_PcReadData;
	pthread_mutex_unlock(&mcu_data_mutex);
//	McuSend_PcReadData.Pc_Read_Flag = 0;
	return &McuSend_PcReadData_Pc;
}

void write_data_into_mcu(PCWRITEDATA *p,unsigned char Write_Flag)
{
	McuReceive_PcWriteData = *p;
	McuReceive_PcWriteData.Pc_Write_Flag = Write_Flag;
//	write_data();
	usleep(5000);//40000//600000//200000//100000
//	sleep(1);
}
#if 0
int uart_thread_create(void)
{
	int ret;
	pthread_t id7,id8;
#if 1	
	pthread_attr_t thread_attr;
	struct sched_param schedule_param;

	pthread_attr_init(&thread_attr);
	schedule_param.sched_priority = 99;
	pthread_attr_setinheritsched(&thread_attr, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&thread_attr, SCHED_RR);
	pthread_attr_setschedparam(&thread_attr, &schedule_param); 
#endif

	ret = pthread_create(&id7, NULL, Uart_meg_thread,NULL);
	if(ret)
	{		
		printf("Create Uart_meg_thread error!\n");
		return -1;
	}
#if 1
	ret = pthread_create(&id8, NULL, Uart_TX_thread,NULL);
	if(ret)	
	{		
		printf("Create Uart_TX_thread error!\n");		
		return -1;	
	}
#endif
	return 0;
}
#endif


void *Uart_meg_thread(void *t) 
{
	int i;
	int rd_count = 0;
	//fd_set fds;
	//struct timeval tv;
	//tv.tv_sec = 0;
 	// tv.tv_usec = 0;
    struct termios tty_attributes;
	
	static int nn;

    if (
		((fd_uart = open("/dev/ttyLF1",O_RDWR|O_NOCTTY&~O_NONBLOCK))>=0)
		//((fd_uart = open("/dev/ttyLF1",O_RDWR|O_NOCTTY |O_NONBLOCK))>=0)
		//||((fd_uart = open("/dev/ttyUSB1",O_RDWR|O_NOCTTY&~O_NONBLOCK))>=0)
		//||((fd_uart = open("/dev/ttyUSB2",O_RDWR|O_NOCTTY&~O_NONBLOCK))>=0)
	   )	
	{
        tcgetattr(fd_uart, &tty_attributes);
 
        // c_cflag
        // Enable receiver
        tty_attributes.c_cflag |= CREAD;        
 
        // 8 data bit
        tty_attributes.c_cflag |= CS8;          
 
        // c_iflag
        // Ignore framing errors and parity errors. 
        tty_attributes.c_iflag |= IGNPAR;  
		tty_attributes.c_iflag &=~(ICRNL|IXON);
 
        // c_lflag
        // DISABLE canonical mode.
        // Disables the special characters EOF, EOL, EOL2, 
        // ERASE, KILL, LNEXT, REPRINT, STATUS, and WERASE, and buffers by lines.
 
        // DISABLE this: Echo input characters.
        tty_attributes.c_lflag &= ~(ICANON);     
 
        tty_attributes.c_lflag &= ~(ECHO);      
 
        // DISABLE this: If ICANON is also set, the ERASE character erases the preceding input  
        // character, and WERASE erases the preceding word.
        tty_attributes.c_lflag &= ~(ECHOE);     
 
        // DISABLE this: When any of the characters INTR, QUIT, SUSP, or DSUSP are received, generate the corresponding signal. 
        tty_attributes.c_lflag &= ~(ISIG);  
		
		
		tty_attributes.c_oflag &= ~OPOST;   //ADDED BY CHE
 
        // Minimum number of characters for non-canonical read.
        tty_attributes.c_cc[VMIN]= 32;//29;//16;            
 
        // Timeout in deciseconds for non-canonical read.
        tty_attributes.c_cc[VTIME]=0;           
 
        // Set the baud rate
        cfsetospeed(&tty_attributes,B230400);     
        cfsetispeed(&tty_attributes,B230400);
		
//		cfsetospeed(&tty_attributes,B19200);     
//        cfsetispeed(&tty_attributes,B19200);
 
        tcsetattr(fd_uart, TCSANOW, &tty_attributes);
		//tcflush(fd_uart,TCIFLUSH);

		//McuSend_PcReadData.Pc_Read_Flag = 0;//for test to be del 

		printf("**********************uart inint ok__201904091358\n");
		McuSend_PcReadData.Steering_Wheel_angle = 31;
		
		while(1)
		{		
			rd_count = read(fd_uart, rxBuffer,32);
					tcflush(fd_uart,TCIFLUSH);
			if(printf_flag)
			printf("rd_count = %d\n", rd_count);

          	if ((rd_count > 0)&&(printf_flag))
			{
				for (i=0; i<rd_count; i++)
				//for (i=0; i<2; i++)
				{
					printf("%x ", rxBuffer[i]);
				}
				printf("\n");

			}
			//pthread_mutex_lock(&mcu_data_mutex);
			frame_get_data(rxBuffer, rd_count);
			//pthread_mutex_unlock(&mcu_data_mutex);		
		}
    } 
	else 
	{
        fprintf (stderr,"Open error on %s\n", strerror(errno));
        //exit(EXIT_FAILURE);
    } 	
 
    close(fd_uart);  

}


void frame_get_data(unsigned char *r_buffer, unsigned char len)
{
	int i,j=0;
	unsigned char tmpi = 0;//added 
	mcu_soc_frame_t	mcu_frame;
	mcu_soc_frame_t	soc_frame;
	unsigned char 	t_buffer;
	
	short int tmp = 0;//added by che 
	short int tmp2 = 0;//added by che 
	unsigned int tmp3 = 0;
	unsigned int tmp4 = 0;
	
	mcu_frame.f_start = r_buffer[0];
	mcu_frame.id_flag = r_buffer[1];
    mcu_frame.d_len   = r_buffer[2];
	mcu_frame.data	  = &r_buffer[3];
	//mcu_frame.xor_flag= r_buffer[len-2];

	if((mcu_frame.f_start == F_START_MCU)&&(r_buffer[3+mcu_frame.d_len]==Add_Verify(&r_buffer[3],mcu_frame.d_len)))
	{
		if(printf_flag_ext)
		{
			printf("id_flag = %x \n", mcu_frame.id_flag);
		
			for (i=0; i<mcu_frame.d_len; i++)
			{
				printf("%x ", mcu_frame.data[i]);
			}
			printf("\n");	
		}

		switch (mcu_frame.id_flag)
		{
			case 0x54:
		
				tmp4	 	 = 0;
				tmp4 	|=  r_buffer[3];
				tmp4      =  tmp4<<8;
				tmp4 	|=  r_buffer[4];				
				tmp3 	= tmp4;
				
				
				tmp4	 	 = 0;
				tmp4 	|=  r_buffer[5];
				tmp4      =  tmp4<<8;
				tmp4 	|=  r_buffer[6];				
				tmp3	= tmp4 | (tmp3<<16);
				McuSend_PcReadData.Timer_Couter	= tmp3+3;

				tmp	 	 = 0;
				tmp 	|=  r_buffer[7];
				tmp      =  tmp<<8;
				tmp 	|=  r_buffer[8];				
				McuSend_PcReadData.WheelSpeed[0] = tmp;	

				tmp	 	 = 0;
				tmp 	|=  r_buffer[9];
				tmp      =  tmp<<8;
				tmp 	|=  r_buffer[10];				
				McuSend_PcReadData.WheelSpeed[1] = tmp;	

				tmp	 	 = 0;
				tmp 	|=  r_buffer[11];
				tmp      =  tmp<<8;
				tmp 	|=  r_buffer[12];				
				McuSend_PcReadData.WheelSpeed[2] = tmp;	

				tmp	 	 = 0;
				tmp 	|=  r_buffer[13];
				tmp      =  tmp<<8;
				tmp 	|=  r_buffer[14];				
				McuSend_PcReadData.WheelSpeed[3] = tmp;	

				tmp	 	 = 0;
				tmp 	|=  r_buffer[15];
				tmp      =  tmp<<8;
				tmp 	|=  r_buffer[16];				
				McuSend_PcReadData.WheelSpeed[4] = tmp;

				reset_chang_flag = r_buffer[17];
				
				tmp	 	 = 0;
				tmp 	|=  r_buffer[19];
				tmp      =  tmp<<8;
				tmp 	|=  r_buffer[20];				
				McuSend_PcReadData.TimeStampex[0] = tmp;						

				tmp	 	 = 0;
				tmp 	|=  r_buffer[21];
				tmp      =  tmp<<8;
				tmp 	|=  r_buffer[22];				
				McuSend_PcReadData.TimeStampex[1] = tmp;	
					
				tmp	 	 = 0;
				tmp 	|=  r_buffer[23];
				tmp      =  tmp<<8;
				tmp 	|=  r_buffer[24];				
				McuSend_PcReadData.TimeStampex[2] = tmp;		

				tmp4	 	 = 0;
				tmp4 	|=  r_buffer[25];
				tmp4      =  tmp4<<8;
				tmp4 	|=  r_buffer[26];				
				tmp3 	= tmp4;
				
				tmp4	 	 = 0;
				tmp4 	|=  r_buffer[27];
				tmp4      =  tmp4<<8;
				tmp4 	|=  r_buffer[28];				
				tmp3	= tmp4 | (tmp3<<16);
				McuSend_PcReadData.TimeStampex_Couter=tmp3;
				

				McuSend_PcReadData.Steering_Wheel_angle=r_buffer[29];
				
				McuTimeData = McuSend_PcReadData.Timer_Couter;
				Mcu_tt=GetNowTimeUs();
				Mcu_tt=Mcu_tt/1000;
				//printf("&&&&&&&&&&&&&&&&&McuTimeData=%u\n", McuTimeData);
				///////////////////////////////////////////2019.6.29 added///////////////////////////////////////////////////
				if(reset_chang_flag != reset_chang_flagtmp)  //RESET signal received
				{
					reset_status_changed_num = num;      //记录RESET时的NUM值
					reset_chang_flagtmp = reset_chang_flag;
					reset_new_value_cnt_flag = 1;
					reset_new_value_cnt = 0;
					McuSendOffset[(num-1)*3]   = 0;
					McuSendOffset[(num-1)*3+1] = 0;
					McuSendOffset[(num-1)*3+2] = 0;
					//McuSendCounter[(num-1)]    = 0;
					//printf("*************0x54 Reset FLAG RECEIVED ,current num=%d\n",num);
				}
				/////////////////////////////////////////////////////////////////////////////////////////////////////////
				McuSendOffset[num*3]   = McuSend_PcReadData.TimeStampex[0];
				McuSendOffset[num*3+1] = McuSend_PcReadData.TimeStampex[1];
				McuSendOffset[num*3+2] = McuSend_PcReadData.TimeStampex[2];
				McuSendCounter[num]    = McuSend_PcReadData.TimeStampex_Couter;
				//printf("**0x54 McuSendCounter[%d]=%d,McuSendOffset[%d*3]=%d\n",num,McuSendCounter[num],num,McuSendOffset[num*3]);
				if(  reset_new_value_cnt_flag == 1 )
				{
					if(reset_new_value_cnt<10)
					{
						reset_new_value_cnt ++;
					}
					else 
					{
						reset_new_value_cnt_flag = 0;
					}
				}
				num++;
				if(num == 10)
					num = 0;
				break;	
			case 0x53:

				tmp	 	 = 0;
				tmp 	|=  r_buffer[3];
				tmp      =  tmp<<8;
				tmp 	|=  r_buffer[4];				
				McuSend_PcReadData.parking_rect_point0_x	= tmp;
				//printf("McuSend_PcReadData.parking_rect_point0_x=%d\n",McuSend_PcReadData.parking_rect_point0_x);
				tmp	 	 = 0;
				tmp 	|=  r_buffer[5];
				tmp      =  tmp<<8;
				tmp 	|=  r_buffer[6];				
				McuSend_PcReadData.parking_rect_point0_y	= tmp;
				//printf("McuSend_PcReadData.parking_rect_point0_y=%d\n",McuSend_PcReadData.parking_rect_point0_y);
				tmp	 	 = 0;
				tmp 	|=  r_buffer[7];
				tmp      =  tmp<<8;
				tmp 	|=  r_buffer[8];				
				McuSend_PcReadData.parking_rect_point1_x	= tmp;
				//printf("McuSend_PcReadData.parking_rect_point1_x=%d\n",McuSend_PcReadData.parking_rect_point1_x);
				tmp	 	 = 0;
				tmp 	|=  r_buffer[9];
				tmp      =  tmp<<8;
				tmp 	|=  r_buffer[10];				
				McuSend_PcReadData.parking_rect_point1_y	= tmp;
				//printf("McuSend_PcReadData.parking_rect_point1_y=%d\n",McuSend_PcReadData.parking_rect_point1_y);
				tmp	 	 = 0;
				tmp 	|=  r_buffer[11];
				tmp      =  tmp<<8;
				tmp 	|=  r_buffer[12];				
				McuSend_PcReadData.parking_rect_point2_x	= tmp;
				//printf("McuSend_PcReadData.parking_rect_point2_x=%d\n",McuSend_PcReadData.parking_rect_point2_x);
				tmp	 	 = 0;
				tmp 	|=  r_buffer[13];
				tmp      =  tmp<<8;
				tmp 	|=  r_buffer[14];				
				McuSend_PcReadData.parking_rect_point2_y	= tmp;	
				//printf("McuSend_PcReadData.parking_rect_point2_y=%d\n",McuSend_PcReadData.parking_rect_point2_y);
				tmp	 	 = 0;
				tmp 	|=  r_buffer[15];
				tmp      =  tmp<<8;
				tmp 	|=  r_buffer[16];				
				McuSend_PcReadData.parking_rect_point3_x	= tmp;
				//printf("McuSend_PcReadData.parking_rect_point3_x=%d\n",McuSend_PcReadData.parking_rect_point3_x);
				tmp	 	 = 0;
				tmp 	|=  r_buffer[17];
				tmp      =  tmp<<8;
				tmp 	|=  r_buffer[18];				
				McuSend_PcReadData.parking_rect_point3_y	= tmp;											
				//printf("McuSend_PcReadData.parking_rect_point3_y=%d\n",McuSend_PcReadData.parking_rect_point3_y);	
				tmp	 	 = 0;
				tmp 	|=  r_buffer[19];
				tmp      =  tmp<<8;
				tmp 	|=  r_buffer[20];				
				McuSend_PcReadData.TimeStampex[0] = tmp;						

				tmp	 	 = 0;
				tmp 	|=  r_buffer[21];
				tmp      =  tmp<<8;
				tmp 	|=  r_buffer[22];				
				McuSend_PcReadData.TimeStampex[1] = tmp;	
					
				tmp	 	 = 0;
				tmp 	|=  r_buffer[23];
				tmp      =  tmp<<8;
				tmp 	|=  r_buffer[24];				
				McuSend_PcReadData.TimeStampex[2] = tmp;		

				tmp      = r_buffer[25];
				McuSend_PcReadData.gear_status_actual 		= (tmp & 0xf0) >> 4;
				McuSend_PcReadData.gear_status_pre 	  		= tmp & 0x0f;	
				//McuSend_PcReadData.gear_status_actual 		= r_buffer[25];
				//McuSend_PcReadData.gear_status_pre 	  		= r_buffer[26];				

				reset_chang_flag = r_buffer[26];
				
				tmp4	 	 = 0;
				tmp4 	|=  r_buffer[27];
				tmp4      =  tmp4<<8;
				tmp4 	|=  r_buffer[28];				
				tmp3 	= tmp4;
				
				tmp4	 	 = 0;
				tmp4 	|=  r_buffer[29];
				tmp4      =  tmp4<<8;
				tmp4 	|=  r_buffer[30];				
				tmp3	= tmp4 | (tmp3<<16);
				McuSend_PcReadData.TimeStampex_Couter=tmp3;

				///////////////////////////////////////////2019.6.29 added///////////////////////////////////////////////////
				if(reset_chang_flag != reset_chang_flagtmp)  //RESET signal received
				{
					reset_status_changed_num = num;      //记录RESET时的NUM值
					reset_chang_flagtmp = reset_chang_flag;
					reset_new_value_cnt_flag = 1;
					reset_new_value_cnt = 0;
					McuSendOffset[(num-1)*3]   = 0;
					McuSendOffset[(num-1)*3+1] = 0;
					McuSendOffset[(num-1)*3+2] = 0;
					//McuSendCounter[(num-1)]    = 0;
					//printf("*************0x53Reset FLAG RECEIVED ,current num=%d\n",num);
				}
				McuSendOffset[num*3]   = McuSend_PcReadData.TimeStampex[0];
				McuSendOffset[num*3+1] = McuSend_PcReadData.TimeStampex[1];
				McuSendOffset[num*3+2] = McuSend_PcReadData.TimeStampex[2];
				McuSendCounter[num]    = McuSend_PcReadData.TimeStampex_Couter;
				//printf("**0x53 McuSendCounter[%d]=%d,McuSendOffset[%d*3]=%d\n",num,McuSendCounter[num],num,McuSendOffset[num*3]);
				if(  reset_new_value_cnt_flag == 1 )
				{
					if(reset_new_value_cnt<10)
					{
						reset_new_value_cnt ++;
					}
					else 
					{
						reset_new_value_cnt_flag = 0;
					}
				}
				num++;
				if(num == 10)
					num = 0;
				break;		
								
			case ID_WHEELSPEED: //0x52
		
				tmp      =   0;
				tmp 	|=  r_buffer[3];
				tmp      =  tmp<<8;
				tmp 	|=  r_buffer[4];				

				McuSend_PcReadData.TimeStampex[0] = tmp;	
				
				tmp      =  0;
				tmp 	|=  r_buffer[5];
				tmp      =  tmp<<8;
				tmp 	|=  r_buffer[6];				

				McuSend_PcReadData.TimeStampex[1] = tmp;			
				
				tmp	 	 = 0;
				tmp 	|=  r_buffer[7];
				tmp      =  tmp<<8;
				tmp 	|=  r_buffer[8];				

				McuSend_PcReadData.TimeStampex[2] = tmp;


				tmp4	 	 = 0;
				tmp4 	|=  r_buffer[9];
				tmp4      =  tmp4<<8;
				tmp4 	|=  r_buffer[10];				
				tmp3 	= tmp4;
				
				tmp4	 	 = 0;
				tmp4 	|=  r_buffer[11];
				tmp4      =  tmp4<<8;
				tmp4 	|=  r_buffer[12];				
				tmp3	= tmp4 | (tmp3<<16);
				McuSend_PcReadData.TimeStampex_Couter=tmp3;	
				
				McuSend_PcReadData.rader1_alarm_level		= r_buffer[13]&0x0f;
				McuSend_PcReadData.rader2_alarm_level		= r_buffer[13]>>4;
				McuSend_PcReadData.rader3_alarm_level		= r_buffer[14]&0x0f;
				McuSend_PcReadData.rader4_alarm_level		= r_buffer[14]>>4;
				McuSend_PcReadData.rader5_alarm_level		= r_buffer[15]&0x0f;
				McuSend_PcReadData.rader6_alarm_level		= r_buffer[15]>>4;
				McuSend_PcReadData.rader7_alarm_level		= r_buffer[16]&0x0f;
				McuSend_PcReadData.rader8_alarm_level		= r_buffer[16]>>4;
				McuSend_PcReadData.rader9_alarm_level		= r_buffer[17]&0x0f;
				McuSend_PcReadData.rader10_alarm_level		= r_buffer[17]>>4;
				McuSend_PcReadData.rader11_alarm_level		= r_buffer[18]&0x0f;
				McuSend_PcReadData.rader12_alarm_level		= r_buffer[18]>>4;
				McuSend_PcReadData.rader13_alarm_level		= r_buffer[19]&0x0f;
				McuSend_PcReadData.rader14_alarm_level		= r_buffer[19]>>4;
				McuSend_PcReadData.rader15_alarm_level		= r_buffer[20]&0x0f;
				McuSend_PcReadData.rader16_alarm_level		= r_buffer[20]>>4;	

				McuSend_PcReadData.switchCannelnum = r_buffer[21];

				tmp	 	 = 0;
				tmp 	|=  r_buffer[22];
				tmp      =  tmp<<8;
				tmp 	|=  r_buffer[23];				
				McuSend_PcReadData.CarSpeed= tmp;
				
				tmp	 	 = 0;
				tmp 	|=  r_buffer[24];
				tmp      =  tmp<<8;
				tmp 	|=  r_buffer[25];				
				McuSend_PcReadData.trail_arc_radius 		= tmp;					
				
				tmp	 	 = 0;
				tmp 	|=  r_buffer[26];
				tmp      =  tmp<<8;
				tmp 	|=  r_buffer[27];				
				McuSend_PcReadData.trail_arc_angle			= tmp;
	
				tmp       =    0;
			    tmp      |=   r_buffer[28];			
				McuSend_PcReadData.McuKey 	  		  		= (tmp&0xf0)>>4;
				McuSend_PcReadData.car_paring_status        = tmp&0x0f;		

				Mcu_receive_FLAG_tmp = r_buffer[29];

				reset_chang_flag = r_buffer[30];
				
				if((Mcu_receive_FLAG_tmp&0x01)==1)
				{
					Mcu_receive_FLAG = McuOk;
					Pc_Tx_Mcu_Nums = 0;		
				}
				if((Mcu_receive_FLAG_tmp&0x02)==2)
				{
					Mcu_receive_FLAG_02 = McuOk;
					Pc_Tx_Mcu_Nums_02 = 0;		
				}					
				if((Mcu_receive_FLAG_tmp&0x04)==4)
				{
					Mcu_receive_FLAG_03 = McuOk;
					Pc_Tx_Mcu_Nums_03 = 0;		
				}
				if((Mcu_receive_FLAG_tmp&0x08)==8)
				{
					Mcu_receive_FLAG_04 = McuOk;
					Pc_Tx_Mcu_Nums_04 = 0;		
				}					
				///////////////////////////////////////////2019.6.29 added///////////////////////////////////////////////////
				if(reset_chang_flag != reset_chang_flagtmp)  //RESET signal received
				{
					reset_status_changed_num = num;      //记录RESET时的NUM值
					reset_chang_flagtmp = reset_chang_flag;
					reset_new_value_cnt_flag = 1;
					reset_new_value_cnt = 0;
					McuSendOffset[(num-1)*3]   = 0;
					McuSendOffset[(num-1)*3+1] = 0;
					McuSendOffset[(num-1)*3+2] = 0;
					//McuSendCounter[(num-1)]    = 0;
					//printf("*************0x52 Reset FLAG RECEIVED ,current num=%d\n",num);
				}
				McuSendOffset[num*3]   = McuSend_PcReadData.TimeStampex[0];
				McuSendOffset[num*3+1] = McuSend_PcReadData.TimeStampex[1];
				McuSendOffset[num*3+2] = McuSend_PcReadData.TimeStampex[2];
				McuSendCounter[num]    = McuSend_PcReadData.TimeStampex_Couter;
				//printf("**0x52 McuSendCounter[%d]=%d,McuSendOffset[%d*3]=%d\n",num,McuSendCounter[num],num,McuSendOffset[num*3]);
				if(  reset_new_value_cnt_flag == 1 )
				{
					if(reset_new_value_cnt<10)
					{
						reset_new_value_cnt ++;
					}
					else 
					{
						reset_new_value_cnt_flag = 0;
					}
				}
				num++;
				if(num == 10)
					num = 0;
				break;
									
			case 0x55:
				
				tmp 	 =	 0;
				tmp 	|=	r_buffer[3];
				tmp 	 =	tmp<<8;
				tmp 	|=	r_buffer[4];				
			
				McuSend_PcReadData.TimeStampex[0] = tmp;	
				
				tmp 	 =	0;
				tmp 	|=	r_buffer[5];
				tmp 	 =	tmp<<8;
				tmp 	|=	r_buffer[6];				
			
				McuSend_PcReadData.TimeStampex[1] = tmp;			
				
				tmp 	 = 0;
				tmp 	|=	r_buffer[7];
				tmp 	 =	tmp<<8;
				tmp 	|=	r_buffer[8];				
			
				McuSend_PcReadData.TimeStampex[2] = tmp;
			
			
				tmp4		 = 0;
				tmp4	|=	r_buffer[9];
				tmp4	  =  tmp4<<8;
				tmp4	|=	r_buffer[10];				
				tmp3	= tmp4;
				
				tmp4		 = 0;
				tmp4	|=	r_buffer[11];
				tmp4	  =  tmp4<<8;
				tmp4	|=	r_buffer[12];				
				tmp3	= tmp4 | (tmp3<<16);
				McuSend_PcReadData.TimeStampex_Couter=tmp3; 
				
				
				tmp 	 = 0;
				tmp 	|=	r_buffer[13];
				tmp 	 =	tmp<<8;
				tmp 	|=	r_buffer[14];				
				McuSend_PcReadData.yaw_rate= tmp;
				
				tmp 	 = 0;
				tmp 	|=	r_buffer[15];
				tmp 	 =	tmp<<8;
				tmp 	|=	r_buffer[16];				
				McuSend_PcReadData.acceleration_x  = tmp;					
				
				tmp 	 = 0;
				tmp 	|=	r_buffer[17];
				tmp 	 =	tmp<<8;
				tmp 	|=	r_buffer[18];				
				McuSend_PcReadData.acceleration_y = tmp;

				tmp 	 = 0;
				tmp 	|=	r_buffer[27];
				tmp 	 =	tmp<<8;
				tmp 	|=	r_buffer[28];				
				McuSend_PcReadData.actual_steering_wheel_angle	= tmp;
	
			
				reset_chang_flag = r_buffer[30];
									
				///////////////////////////////////////////2019.6.29 added///////////////////////////////////////////////////
				if(reset_chang_flag != reset_chang_flagtmp)  //RESET signal received
				{
					reset_status_changed_num = num; 	 //记录RESET时的NUM值
					reset_chang_flagtmp = reset_chang_flag;
					reset_new_value_cnt_flag = 1;
					reset_new_value_cnt = 0;
					McuSendOffset[(num-1)*3]   = 0;
					McuSendOffset[(num-1)*3+1] = 0;
					McuSendOffset[(num-1)*3+2] = 0;
					//McuSendCounter[(num-1)]    = 0;
					//printf("*************0x55 Reset FLAG RECEIVED ,current num=%d\n",num);
				}
				McuSendOffset[num*3]   = McuSend_PcReadData.TimeStampex[0];
				McuSendOffset[num*3+1] = McuSend_PcReadData.TimeStampex[1];
				McuSendOffset[num*3+2] = McuSend_PcReadData.TimeStampex[2];
				McuSendCounter[num]    = McuSend_PcReadData.TimeStampex_Couter;
				//printf("**0x52 McuSendCounter[%d]=%d,McuSendOffset[%d*3]=%d\n",num,McuSendCounter[num],num,McuSendOffset[num*3]);
				if(  reset_new_value_cnt_flag == 1 )
				{
					if(reset_new_value_cnt<10)
					{
						reset_new_value_cnt ++;
					}
					else 
					{
						reset_new_value_cnt_flag = 0;
					}
				}
				num++;
				if(num == 10)
					num = 0;
				break;

			default:
				break;
		}

		//McuSend_PcReadData.car_paring_status = 1;
		
		McuSendDada_Ptr->car_paring_status  = McuSend_PcReadData.car_paring_status;
		
		McuSendDada_Ptr->TimeStampex[0]     = McuSend_PcReadData.TimeStampex[0];
		McuSendDada_Ptr->TimeStampex[1]     = McuSend_PcReadData.TimeStampex[1];
		McuSendDada_Ptr->TimeStampex[2]     = McuSend_PcReadData.TimeStampex[2];
		McuSendDada_Ptr->TimeStampex_Couter = McuSend_PcReadData.TimeStampex_Couter;
		McuSendDada_Ptr->trail_arc_radius   = McuSend_PcReadData.trail_arc_radius;
		McuSendDada_Ptr->trail_arc_angle    = McuSend_PcReadData.trail_arc_angle;
		McuSendDada_Ptr->WheelSpeed[0]      = McuSend_PcReadData.WheelSpeed[0];
		McuSendDada_Ptr->WheelSpeed[1]      = McuSend_PcReadData.WheelSpeed[1];
		McuSendDada_Ptr->WheelSpeed[2]      = McuSend_PcReadData.WheelSpeed[2];
		McuSendDada_Ptr->WheelSpeed[3]      = McuSend_PcReadData.WheelSpeed[3];
		McuSendDada_Ptr->WheelSpeed[4]      = McuSend_PcReadData.WheelSpeed[4];
		McuSendDada_Ptr->CarSpeed           = McuSend_PcReadData.CarSpeed;
		McuSendDada_Ptr->yaw_rate           = McuSend_PcReadData.yaw_rate;
		McuSendDada_Ptr->acceleration_x           		= McuSend_PcReadData.acceleration_x;
		McuSendDada_Ptr->acceleration_y           		= McuSend_PcReadData.acceleration_y;
		McuSendDada_Ptr->actual_steering_wheel_angle    = McuSend_PcReadData.actual_steering_wheel_angle;


		//printf("McuSendDada_Ptr->CarSpeed=%d,yaw_rate=%d,actual_steering_wheel_angle=%d\n",McuSendDada_Ptr->CarSpeed,McuSendDada_Ptr->yaw_rate,McuSendDada_Ptr->actual_steering_wheel_angle);
		//if(McuSend_PcReadData.CarSpeed < 1) //  MG <0.01  ROEWE <6 ，除去MG和ROEWE车，自2019.3.21日起，新装车型，MCU上传车速CarSpeed为0（停止状态）和1（运动状态）两种状态量
		//	Car_Speed_Flag = 0; //车停止状态
		//else 
		//	Car_Speed_Flag = 1; //车在运动状态
		//Car_Speed_Flag = 1;
		//McuSendDada_Ptr->CarSpeed  = Car_Speed_Flag;

		//printf("Car_Speed_Flag=%d McuSend_PcReadData.CarSpeed=%u\n",Car_Speed_Flag,McuSend_PcReadData.CarSpeed);
		//printf("McuSend_PcReadData.Steering_Wheel_angle=%d\n",McuSend_PcReadData.Steering_Wheel_angle);
		//printf("@@@@@@@@McuSend_PcReadData.TimeStampex_Couter=%u\n",McuSendCounter[num] = McuSend_PcReadData.TimeStampex_Couter);
		//printf("McuSendDada_Ptr->TimeStampex %d,%d,%d\n",McuSend_PcReadData.TimeStampex[0],McuSend_PcReadData.TimeStampex[1],McuSend_PcReadData.TimeStampex[2]);
	}	
	else
	{	if(printf_flag)
		printf("error:f_start = %x\n", mcu_frame.f_start);
	}
	
}

void *Uart_TX_thread(void *t) 
{
//	static int cnt;
//	char i =0;//for test 
	//static int cnt2;
	McuReceive_PcWriteData.Pc_Write_Flag = 0;//for test to be del 
	printf("*************************Uart_TX_thread ok_201907108\n");
	int i;
	//McuReceive_PcWriteData = *PCWRITEDATA_Ptr;
	//memcpy(&McuReceive_PcWriteData,PCWRITEDATA_Ptr,sizeof(PCWRITEDATA));
	
	while(1)
	{
		//static int ss1;
		//	printf("txthread11%d\n",ss1);
		//	ss1++;
		usleep(1000);////0
		
		//printf("PCWRITEDATA_Ptr->Pc_Write_FLag=%d\n",PCWRITEDATA_Ptr->Pc_Write_Flag);
		if(((Mcu_receive_FLAG != McuOk)&&(Pc_Tx_Mcu_Nums <= 30))||((PCWRITEDATA_Ptr->Pc_Write_Flag&0x01) == 1))
		{
			if((PCWRITEDATA_Ptr->Pc_Write_Flag&0x01) == 1)
			{
				Pc_Tx_Mcu_Nums = 0;
				PCWRITEDATA_Ptr->Pc_Write_Flag &= 0xfe;
				Mcu_receive_FLAG = McuErr;
			}
			else
			{
				Pc_Tx_Mcu_Nums++;		
				if(Pc_Tx_Mcu_Nums>30)
					Pc_Tx_Mcu_Nums = 200;
			}
			txBuffer[0] = 	F_START_SOC;//0x01
			txBuffer[1] = 	0x80;       
			txBuffer[2] = 	34;
			txBuffer[3] = 	PCWRITEDATA_Ptr->PC_CarPark_P0Point[0]>>8;
			txBuffer[4] = 	PCWRITEDATA_Ptr->PC_CarPark_P0Point[0];
			txBuffer[5] = 	PCWRITEDATA_Ptr->PC_CarPark_P0Point[1]>>8;
			txBuffer[6] = 	PCWRITEDATA_Ptr->PC_CarPark_P0Point[1];
			txBuffer[7] = 	PCWRITEDATA_Ptr->PC_CarPark_P1Point[0]>>8;
			txBuffer[8] = 	PCWRITEDATA_Ptr->PC_CarPark_P1Point[0];
			txBuffer[9] = 	PCWRITEDATA_Ptr->PC_CarPark_P1Point[1]>>8;
			txBuffer[10] = 	PCWRITEDATA_Ptr->PC_CarPark_P1Point[1];
			txBuffer[11] = 	PCWRITEDATA_Ptr->PC_CarPark_P2Point[0]>>8;
			txBuffer[12] = 	PCWRITEDATA_Ptr->PC_CarPark_P2Point[0];
			txBuffer[13] = 	PCWRITEDATA_Ptr->PC_CarPark_P2Point[1]>>8;
			txBuffer[14] = 	PCWRITEDATA_Ptr->PC_CarPark_P2Point[1];
			txBuffer[15] = 	PCWRITEDATA_Ptr->PC_CarPark_P3Point[0]>>8;
			txBuffer[16] = 	PCWRITEDATA_Ptr->PC_CarPark_P3Point[0];
			txBuffer[17] = 	PCWRITEDATA_Ptr->PC_CarPark_P3Point[1]>>8;
			txBuffer[18] = 	PCWRITEDATA_Ptr->PC_CarPark_P3Point[1];
			txBuffer[19] = 	PCWRITEDATA_Ptr->PC_ZhiXinDu;
			txBuffer[20] = 	PCWRITEDATA_Ptr->PC_TimeStampeX>>8;
			txBuffer[21] = 	PCWRITEDATA_Ptr->PC_TimeStampeX;
			txBuffer[22] = 	PCWRITEDATA_Ptr->PC_TimeStampeY>>8;
			txBuffer[23] = 	PCWRITEDATA_Ptr->PC_TimeStampeY;					
			txBuffer[24] = 	PCWRITEDATA_Ptr->PC_TimeStampeZ>>8;
			txBuffer[25] = 	PCWRITEDATA_Ptr->PC_TimeStampeZ;
			txBuffer[26] = 	0;
			txBuffer[27] = 	0;
			txBuffer[28] = 	0;
			txBuffer[29] = 	0;
			txBuffer[30] = 	0;
			txBuffer[31] = 	0;
			txBuffer[32] = 	0;
			txBuffer[33] = 	0;			
			txBuffer[34] = 	0;
			txBuffer[35] = 	0;
			txBuffer[36] = 	0;				
			
			txBuffer[37] = Add_Verify(&txBuffer[3],34);
			//tcflush(fd_uart,TCOFLUSH);
			write(fd_uart, txBuffer, 38);	
			//printf("&&&&&&&DNN p0:%d %d  P1:%d,%d  P2:%d,%d  P3:%d,%d \n",PCWRITEDATA_Ptr->PC_CarPark_P0Point[0],PCWRITEDATA_Ptr->PC_CarPark_P0Point[1],PCWRITEDATA_Ptr->PC_CarPark_P1Point[0],PCWRITEDATA_Ptr->PC_CarPark_P1Point[1],PCWRITEDATA_Ptr->PC_CarPark_P2Point[0],PCWRITEDATA_Ptr->PC_CarPark_P2Point[1],PCWRITEDATA_Ptr->PC_CarPark_P3Point[0],PCWRITEDATA_Ptr->PC_CarPark_P3Point[1]);
			//printf("&&&&&&&DNN %d,%d,%d\n",PCWRITEDATA_Ptr->PC_TimeStampeX,PCWRITEDATA_Ptr->PC_TimeStampeY,PCWRITEDATA_Ptr->PC_TimeStampeZ);

			usleep(45000);	//24500		
		}
		else if(((Mcu_receive_FLAG_02 != McuOk)&&(Pc_Tx_Mcu_Nums_02 <= 30))||((McuReceive_PcWriteData.Pc_Write_Flag&0x02) == 2))
		{
			if((McuReceive_PcWriteData.Pc_Write_Flag&0x02) == 2)
			{
				Pc_Tx_Mcu_Nums_02 = 0;
				McuReceive_PcWriteData.Pc_Write_Flag &= 0xfd;
				Mcu_receive_FLAG_02 = McuErr;
			}
			else
			{
				Pc_Tx_Mcu_Nums_02++;		
				if(Pc_Tx_Mcu_Nums_02>30)
					Pc_Tx_Mcu_Nums_02 = 200;
			}			
	
			tx2Buffer[0] = 	F_START_SOC;//0x01
			tx2Buffer[1] = 	0x81;       
			tx2Buffer[2] = 	34;			
			tx2Buffer[3] = 	McuReceive_PcWriteData.PC_CarFront_Ear_X>>8;
			tx2Buffer[4] = 	McuReceive_PcWriteData.PC_CarFront_Ear_X;
			tx2Buffer[5] = 	McuReceive_PcWriteData.PC_CarFront_Ear_Y>>8;
			tx2Buffer[6] = 	McuReceive_PcWriteData.PC_CarFront_Ear_Y;
			
			tx2Buffer[7] = 	McuReceive_PcWriteData.PC_FrontNear_TyreGound_X>>8;
			tx2Buffer[8] =  McuReceive_PcWriteData.PC_FrontNear_TyreGound_X;
			tx2Buffer[9] = 	McuReceive_PcWriteData.PC_FrontNear_TyreGound_Y>>8;
			tx2Buffer[10] = McuReceive_PcWriteData.PC_FrontNear_TyreGound_Y;
			tx2Buffer[11] = McuReceive_PcWriteData.PC_FrontFar_TyreGound_X>>8;
			tx2Buffer[12] = McuReceive_PcWriteData.PC_FrontFar_TyreGound_X;
			tx2Buffer[13] = McuReceive_PcWriteData.PC_FrontFar_TyreGound_Y>>8;
			tx2Buffer[14] = McuReceive_PcWriteData.PC_FrontFar_TyreGound_Y;
			
			tx2Buffer[15] = McuReceive_PcWriteData.PC_Front_Bumper_X1>>8;
			tx2Buffer[16] = McuReceive_PcWriteData.PC_Front_Bumper_X1;
			tx2Buffer[17] = McuReceive_PcWriteData.PC_Front_Bumper_Y1>>8;
			tx2Buffer[18] = McuReceive_PcWriteData.PC_Front_Bumper_Y1;
			tx2Buffer[19] = McuReceive_PcWriteData.PC_Front_Bumper_X2>>8;
			tx2Buffer[20] = McuReceive_PcWriteData.PC_Front_Bumper_X2;
			tx2Buffer[21] = McuReceive_PcWriteData.PC_Front_Bumper_Y2>>8;
			tx2Buffer[22] = McuReceive_PcWriteData.PC_Front_Bumper_Y2;
			tx2Buffer[23] = McuReceive_PcWriteData.PC_Front_Bumper_X3>>8;
			tx2Buffer[24] = McuReceive_PcWriteData.PC_Front_Bumper_X3;
			tx2Buffer[25] = McuReceive_PcWriteData.PC_Front_Bumper_Y3>>8;
			tx2Buffer[26] = McuReceive_PcWriteData.PC_Front_Bumper_Y3;
			tx2Buffer[27] = McuReceive_PcWriteData.PC_Front_Bumper_X4>>8;
			tx2Buffer[28] = McuReceive_PcWriteData.PC_Front_Bumper_X4;
			tx2Buffer[29] = McuReceive_PcWriteData.PC_Front_Bumper_Y4>>8;
			tx2Buffer[30] = McuReceive_PcWriteData.PC_Front_Bumper_Y4;
			tx2Buffer[31] = McuReceive_PcWriteData.PC_Front_Bumper_TimeStampeX>>8;
			tx2Buffer[32] = McuReceive_PcWriteData.PC_Front_Bumper_TimeStampeX;
			tx2Buffer[33] = McuReceive_PcWriteData.PC_Front_Bumper_TimeStampeY>>8;
			tx2Buffer[34] = McuReceive_PcWriteData.PC_Front_Bumper_TimeStampeY;
			tx2Buffer[35] = McuReceive_PcWriteData.PC_Front_Bumper_TimeStampeZ>>8;
			tx2Buffer[36] = McuReceive_PcWriteData.PC_Front_Bumper_TimeStampeZ;
			
			tx2Buffer[37] = Add_Verify(&tx2Buffer[3],34);
			//tcflush(fd_uart,TCOFLUSH);
			write(fd_uart, tx2Buffer, 38);	
			usleep(45000);	//27500					
		}
		else if(((Mcu_receive_FLAG_03 != McuOk)&&(Pc_Tx_Mcu_Nums_03 <= 30))||((McuReceive_PcWriteData.Pc_Write_Flag&0x04) == 4))
		{
			if((McuReceive_PcWriteData.Pc_Write_Flag&0x04) == 4)
			{
				Pc_Tx_Mcu_Nums_03 = 0;
				McuReceive_PcWriteData.Pc_Write_Flag &= 0xfb;
				Mcu_receive_FLAG_03 = McuErr;
			}
			else
			{
				Pc_Tx_Mcu_Nums_03++;		
				if(Pc_Tx_Mcu_Nums_03>30)
					Pc_Tx_Mcu_Nums_03 = 200;
			}		
								
			tx3Buffer[0] = 	F_START_SOC;//0x01
			tx3Buffer[1] = 	0x82;       
			tx3Buffer[2] = 	34;		
			tx3Buffer[3] = 	McuReceive_PcWriteData.PC_Back_Bumper_X1>>8;
			tx3Buffer[4] =  McuReceive_PcWriteData.PC_Back_Bumper_X1;
			tx3Buffer[5] = 	McuReceive_PcWriteData.PC_Back_Bumper_Y1>>8;
			tx3Buffer[6] = 	McuReceive_PcWriteData.PC_Back_Bumper_Y1;
			tx3Buffer[7] = 	McuReceive_PcWriteData.PC_Back_Bumper_X2>>8;
			tx3Buffer[8] = 	McuReceive_PcWriteData.PC_Back_Bumper_X2;
			tx3Buffer[9] = 	McuReceive_PcWriteData.PC_Back_Bumper_Y2>>8;
			tx3Buffer[10] = McuReceive_PcWriteData.PC_Back_Bumper_Y2;
			tx3Buffer[11] = McuReceive_PcWriteData.PC_Back_Bumper_X3>>8;
			tx3Buffer[12] = McuReceive_PcWriteData.PC_Back_Bumper_X3;
			tx3Buffer[13] = McuReceive_PcWriteData.PC_Back_Bumper_Y3>>8;
			tx3Buffer[14] = McuReceive_PcWriteData.PC_Back_Bumper_Y3;
			tx3Buffer[15] = McuReceive_PcWriteData.PC_Back_Bumper_X4>>8;
			tx3Buffer[16] = McuReceive_PcWriteData.PC_Back_Bumper_X4;
			tx3Buffer[17] = McuReceive_PcWriteData.PC_Back_Bumper_Y4>>8;
			tx3Buffer[18] = McuReceive_PcWriteData.PC_Back_Bumper_Y4;
			
			tx3Buffer[19] = McuReceive_PcWriteData.PC_CarBack_Ear_X>>8;
			tx3Buffer[20] = McuReceive_PcWriteData.PC_CarBack_Ear_X;
			tx3Buffer[21] = McuReceive_PcWriteData.PC_CarBack_Ear_Y>>8;
			tx3Buffer[22] = McuReceive_PcWriteData.PC_CarBack_Ear_Y;
				
			tx3Buffer[23] = McuReceive_PcWriteData.PC_BackNear_TyreGound_X>>8;
			tx3Buffer[24] = McuReceive_PcWriteData.PC_BackNear_TyreGound_X;
			tx3Buffer[25] = McuReceive_PcWriteData.PC_BackNear_TyreGound_Y>>8;
			tx3Buffer[26] = McuReceive_PcWriteData.PC_BackNear_TyreGound_Y;
			tx3Buffer[27] = McuReceive_PcWriteData.PC_BackFar_TyreGound_X>>8;
			tx3Buffer[28] = McuReceive_PcWriteData.PC_BackFar_TyreGound_X;
			tx3Buffer[29] = McuReceive_PcWriteData.PC_BackFar_TyreGound_Y>>8;
			tx3Buffer[30] = McuReceive_PcWriteData.PC_BackFar_TyreGound_Y;

			tx3Buffer[31] = McuReceive_PcWriteData.PC_Back_Bumper_TimeStampeX>>8;
			tx3Buffer[32] = McuReceive_PcWriteData.PC_Back_Bumper_TimeStampeX;
			tx3Buffer[33] = McuReceive_PcWriteData.PC_Back_Bumper_TimeStampeY>>8;
			tx3Buffer[34] = McuReceive_PcWriteData.PC_Back_Bumper_TimeStampeY;	
			tx3Buffer[35] = McuReceive_PcWriteData.PC_Back_Bumper_TimeStampeZ>>8;
			tx3Buffer[36] = McuReceive_PcWriteData.PC_Back_Bumper_TimeStampeZ;	
			
			tx3Buffer[37] = Add_Verify(&tx3Buffer[3],34);
			//tcflush(fd_uart,TCOFLUSH);
			write(fd_uart, tx3Buffer, 38);	
			usleep(45000);	//27500	
		}
		if(Car_Parking_Status==1)
		{							
			tx4Buffer[0] = 	F_START_SOC;//0x01
			tx4Buffer[1] = 	0x85;       
			tx4Buffer[2] = 	34;
			tx4Buffer[3] = 	ToMcuTargetData.Target_CarPark_P0Point[0]>>8;
			tx4Buffer[4] = 	ToMcuTargetData.Target_CarPark_P0Point[0];
			tx4Buffer[5] = 	ToMcuTargetData.Target_CarPark_P0Point[1]>>8;
			tx4Buffer[6] = 	ToMcuTargetData.Target_CarPark_P0Point[1]&0xff;
			tx4Buffer[7] = 	ToMcuTargetData.Target_CarPark_P1Point[0]>>8;
			tx4Buffer[8] = 	ToMcuTargetData.Target_CarPark_P1Point[0];
			tx4Buffer[9] = 	ToMcuTargetData.Target_CarPark_P1Point[1]>>8;
			tx4Buffer[10] = ToMcuTargetData.Target_CarPark_P1Point[1];
			tx4Buffer[11] = ToMcuTargetData.Target_CarPark_P2Point[0]>>8;
			tx4Buffer[12] = ToMcuTargetData.Target_CarPark_P2Point[0];
			tx4Buffer[13] = ToMcuTargetData.Target_CarPark_P2Point[1]>>8;
			tx4Buffer[14] = ToMcuTargetData.Target_CarPark_P2Point[1];
			tx4Buffer[15] = ToMcuTargetData.Target_CarPark_P3Point[0]>>8;
			tx4Buffer[16] = ToMcuTargetData.Target_CarPark_P3Point[0];
			tx4Buffer[17] = ToMcuTargetData.Target_CarPark_P3Point[1]>>8;
			tx4Buffer[18] = ToMcuTargetData.Target_CarPark_P3Point[1];
			tx4Buffer[19] = ToMcuTargetData.TargetConfidence;
			tx4Buffer[20] = 0;
			tx4Buffer[21] = 0;
			tx4Buffer[22] = 0;
			tx4Buffer[23] = ToMcuTargetData.Targetx>>8;
			tx4Buffer[24] = ToMcuTargetData.Targetx;
			tx4Buffer[25] = ToMcuTargetData.Targety>>8;
			tx4Buffer[26] = ToMcuTargetData.Targety;					
			tx4Buffer[27] = ToMcuTargetData.Targetz>>8;
			tx4Buffer[28] = ToMcuTargetData.Targetz;
			tx4Buffer[29] = ToMcuTargetData.Dnn_Scan_Ok_Flag;
			tx4Buffer[30] = ToMcuTargetData.Customer_Select_Ok_Flag;
			tx4Buffer[31] = 0;
			tx4Buffer[32] = 0;
			tx4Buffer[33] = 0;			
			tx4Buffer[34] = 0;
			tx4Buffer[35] = 0;
			tx4Buffer[36] = 0;				
			
			tx4Buffer[37] = Add_Verify(&tx4Buffer[3],34);
			//tcflush(fd_uart,TCOFLUSH);
			write(fd_uart, tx4Buffer, 38);	
			//printf("tx4Buffer[19]=%d\n",tx4Buffer[19]);
			//printf("Customer_Select_Ok_Flag=%d\n",ToMcuTargetData.Customer_Select_Ok_Flag);
			//printf("ToMcuTargetData.Target x y z %d,%d,%d\n",ToMcuTargetData.Targetx,ToMcuTargetData.Targety,ToMcuTargetData.Targetz);
			//printf("TxPoint:P0 %d,%d,p1 %d,%d, P2 %d,%d, P3 %d,%d\n",ToMcuTargetData.Target_CarPark_P0Point[0],ToMcuTargetData.Target_CarPark_P0Point[1],ToMcuTargetData.Target_CarPark_P1Point[0],ToMcuTargetData.Target_CarPark_P1Point[1],ToMcuTargetData.Target_CarPark_P2Point[0],ToMcuTargetData.Target_CarPark_P2Point[1],ToMcuTargetData.Target_CarPark_P3Point[0],ToMcuTargetData.Target_CarPark_P3Point[1]);
			usleep(45000);	//27500
		}

		if(LanelineData_Ptr->TimeStampex_Couter != lane_TimeStamp_bak)
		{
			lane_TimeStamp_bak = LanelineData_Ptr->TimeStampex_Couter;
			tx5Buffer[0] = 	F_START_SOC;//0x01
			tx5Buffer[1] = 	0xa0;       
			tx5Buffer[2] = 	36;		
			tx5Buffer[3] =  2;		//frame total 
			tx5Buffer[4] =  0;		//current frame
			tx5Buffer[5] = 	LanelineData_Ptr->TimeStampex_Couter >> 24;
			tx5Buffer[6] =  LanelineData_Ptr->TimeStampex_Couter >> 16;
			tx5Buffer[7] = 	LanelineData_Ptr->TimeStampex_Couter >> 8;
			tx5Buffer[8] =  LanelineData_Ptr->TimeStampex_Couter ;
			
			tx5Buffer[9] = 	LanelineData_Ptr->TimeStampex[0] >> 8;
			tx5Buffer[10] = LanelineData_Ptr->TimeStampex[0] ;
			tx5Buffer[11] = LanelineData_Ptr->TimeStampex[1] >> 8;
			tx5Buffer[12] = LanelineData_Ptr->TimeStampex[1] ;
			tx5Buffer[13] = LanelineData_Ptr->TimeStampex[2] >> 8;
			tx5Buffer[14] = LanelineData_Ptr->TimeStampex[2] ;

			tx5Buffer[15] = LanelineData_Ptr->lane_width >> 8;
			tx5Buffer[16] = LanelineData_Ptr->lane_width ;

			memcpy(tx5Buffer+17,(unsigned char*)&LanelineData_Ptr->left_a0,4);
			memcpy(tx5Buffer+21,(unsigned char*)&LanelineData_Ptr->left_a1,4);
			memcpy(tx5Buffer+25,(unsigned char*)&LanelineData_Ptr->left_a2,4);
			memcpy(tx5Buffer+29,(unsigned char*)&LanelineData_Ptr->left_a3,4);

			tx5Buffer[33] = LanelineData_Ptr->left_width >> 8;
			tx5Buffer[34] = LanelineData_Ptr->left_width ;
			tx5Buffer[35] = LanelineData_Ptr->left_type ;
			tx5Buffer[36] = LanelineData_Ptr->left_length >> 8 ;
			tx5Buffer[37] = LanelineData_Ptr->left_length ;
			tx5Buffer[38] = LanelineData_Ptr->left_confidence ;
			
			tx5Buffer[39] = Add_Verify(&tx5Buffer[3],36);
			write(fd_uart, tx5Buffer, 40);					//send frame 1

			tx5Buffer[0] = 	F_START_SOC;//0x01
			tx5Buffer[1] = 	0xa0;       
			tx5Buffer[2] = 	24;		
			tx5Buffer[3] =  2;		//frame total 
			tx5Buffer[4] =  1;		//current frame
			memcpy(tx5Buffer+5,(unsigned char*)&LanelineData_Ptr->right_a0,4);
			memcpy(tx5Buffer+9,(unsigned char*)&LanelineData_Ptr->right_a1,4);
			memcpy(tx5Buffer+13,(unsigned char*)&LanelineData_Ptr->right_a2,4);
			memcpy(tx5Buffer+17,(unsigned char*)&LanelineData_Ptr->right_a3,4);

			tx5Buffer[21] = LanelineData_Ptr->right_width >> 8 ;
			tx5Buffer[22] = LanelineData_Ptr->right_width ;
			tx5Buffer[23] = LanelineData_Ptr->right_type ;
			tx5Buffer[24] = LanelineData_Ptr->right_length >> 8 ;
			tx5Buffer[25] = LanelineData_Ptr->right_length ;
			tx5Buffer[26] = LanelineData_Ptr->right_confidence ;
			
			tx5Buffer[27] = Add_Verify(&tx5Buffer[3],24);
			write(fd_uart, tx5Buffer, 28);						//send frame 2
			
			//printf("left_a0=%f,_a1=%f,_a2=%f,_a3=%f\n",LanelineData_Ptr->left_a0,LanelineData_Ptr->left_a1,LanelineData_Ptr->left_a2,LanelineData_Ptr->left_a3);
			//printf("right_a0=%f,_a1=%f,_a2=%f,_a3=%f\n",LanelineData_Ptr->right_a0,LanelineData_Ptr->right_a1,LanelineData_Ptr->right_a2,LanelineData_Ptr->right_a3);
			//printf("left_width=%d,left_type=%d,left_length=%d,left_confidence=%d\n",LanelineData_Ptr->left_width,LanelineData_Ptr->left_type,LanelineData_Ptr->left_length,LanelineData_Ptr->left_confidence);
			//printf("right_width=%d,right_type=%d,right_length=%d,right_confidence=%d\n",LanelineData_Ptr->right_width,LanelineData_Ptr->right_type,LanelineData_Ptr->right_length,LanelineData_Ptr->right_confidence);
			usleep(10000);
		}
		if(ObstacleData_Ptr->TimeStampex_Couter != obstacle_TimeStamp_bak)
		{ 
			//printf("obstacle num =%d\n",ObstacleData_Ptr->num);
			//printf("obstacle cnt =%d\n",ObstacleData_Ptr->TimeStampex_Couter);
			obstacle_TimeStamp_bak = ObstacleData_Ptr->TimeStampex_Couter;
			tx5Buffer[0] = 	F_START_SOC;//0x01
			tx5Buffer[1] = 	0xa1;       
			tx5Buffer[2] = 	13;		
			tx5Buffer[3] =  ObstacleData_Ptr->num+1;		//frame total 
			tx5Buffer[4] =  0;							// frame 1
			tx5Buffer[5] = 	ObstacleData_Ptr->TimeStampex_Couter >> 24;
			tx5Buffer[6] =  ObstacleData_Ptr->TimeStampex_Couter >> 16;
			tx5Buffer[7] = 	ObstacleData_Ptr->TimeStampex_Couter >> 8;
			tx5Buffer[8] =  ObstacleData_Ptr->TimeStampex_Couter ;
			
			tx5Buffer[9] = 	ObstacleData_Ptr->TimeStampex[0] >> 8;
			tx5Buffer[10] = ObstacleData_Ptr->TimeStampex[0] ;
			tx5Buffer[11] = ObstacleData_Ptr->TimeStampex[1] >> 8;
			tx5Buffer[12] = ObstacleData_Ptr->TimeStampex[1] ;
			tx5Buffer[13] = ObstacleData_Ptr->TimeStampex[2] >> 8;
			tx5Buffer[14] = ObstacleData_Ptr->TimeStampex[2] ;

			tx5Buffer[15] = ObstacleData_Ptr->num;
			tx5Buffer[16] = Add_Verify(&tx5Buffer[3],13);
			write(fd_uart, tx5Buffer, 17);						//send frame 1
			///*
			for(int i=0;i<ObstacleData_Ptr->num;i++)
			{
				tx5Buffer[0] = 	F_START_SOC;//0x01
				tx5Buffer[1] = 	0xa1;       
				tx5Buffer[2] = 	40;		
				tx5Buffer[3] =  ObstacleData_Ptr->num+1;		//frame total   ;		//frame total 
				tx5Buffer[4] =  i+1;							// frame 1
				tx5Buffer[5] = 	ObstacleData_Ptr->objarray[i].objectid >> 8 ;
				tx5Buffer[6] =  ObstacleData_Ptr->objarray[i].objectid;
				tx5Buffer[7] = 	ObstacleData_Ptr->objarray[i].objecttype;
				tx5Buffer[8] =  ObstacleData_Ptr->objarray[i].confidence ;
				printf("obstacle[i] id =%d\n",	i,ObstacleData_Ptr->objarray[i].objectid);
				
				tx5Buffer[9] = 	ObstacleData_Ptr->objarray[i].P1_x >> 8;
				tx5Buffer[10] = ObstacleData_Ptr->objarray[i].P1_x ;
				tx5Buffer[11] = ObstacleData_Ptr->objarray[i].P1_y >> 8;
				tx5Buffer[12] = ObstacleData_Ptr->objarray[i].P1_y ;
				
				tx5Buffer[13] = ObstacleData_Ptr->objarray[i].P2_x >> 8;
				tx5Buffer[14] = ObstacleData_Ptr->objarray[i].P2_x ;
				tx5Buffer[15] = ObstacleData_Ptr->objarray[i].P2_y >> 8;
				tx5Buffer[16] = ObstacleData_Ptr->objarray[i].P2_y ;
				
				tx5Buffer[17] = ObstacleData_Ptr->objarray[i].P3_x >> 8;
				tx5Buffer[18] = ObstacleData_Ptr->objarray[i].P3_x ;
				tx5Buffer[19] = ObstacleData_Ptr->objarray[i].P3_y >> 8;
				tx5Buffer[20] = ObstacleData_Ptr->objarray[i].P3_y ;
				
				tx5Buffer[21] = ObstacleData_Ptr->objarray[i].P4_x >> 8;
				tx5Buffer[22] = ObstacleData_Ptr->objarray[i].P4_x ;
				tx5Buffer[23] = ObstacleData_Ptr->objarray[i].P4_y >> 8;
				tx5Buffer[24] = ObstacleData_Ptr->objarray[i].P4_y ;

				tx5Buffer[25] = ObstacleData_Ptr->objarray[i].P1_real_x >> 8;
				tx5Buffer[26] = ObstacleData_Ptr->objarray[i].P1_real_x ;
				tx5Buffer[27] = ObstacleData_Ptr->objarray[i].P1_real_y >> 8;
				tx5Buffer[28] = ObstacleData_Ptr->objarray[i].P1_real_y ;

				tx5Buffer[29] = ObstacleData_Ptr->objarray[i].P2_real_x >> 8;
				tx5Buffer[30] = ObstacleData_Ptr->objarray[i].P2_real_x ;
				tx5Buffer[31] = ObstacleData_Ptr->objarray[i].P2_real_y >> 8;
				tx5Buffer[32] = ObstacleData_Ptr->objarray[i].P2_real_y ;

				tx5Buffer[33] = ObstacleData_Ptr->objarray[i].height >> 8;
				tx5Buffer[34] = ObstacleData_Ptr->objarray[i].height ;
				tx5Buffer[35] = ObstacleData_Ptr->objarray[i].status;
				float tmpvalue = ObstacleData_Ptr->objarray[i].velocity;
				memcpy(tx5Buffer+36,(unsigned char*)&tmpvalue,4);
				tx5Buffer[40] = ObstacleData_Ptr->objarray[i].direction >> 8;
				tx5Buffer[41] = ObstacleData_Ptr->objarray[i].direction ;
				tx5Buffer[42] = ObstacleData_Ptr->objarray[i].validity;

				tx5Buffer[43] = Add_Verify(&tx5Buffer[3],40);
				write(fd_uart, tx5Buffer, 44);	
			}//*/
			usleep(10000);
		}
		//printf("lanewidth=%d\n",LanelineData_Ptr->lane_width);
		//printf("left_a0=%f,left_width=%d\n",LanelineData_Ptr->left_a0,LanelineData_Ptr->left_width);
		//printf("right_a0=%f,right_width=%d\n",LanelineData_Ptr->right_a0,LanelineData_Ptr->right_width);
	}
}

unsigned char Add_Verify(unsigned char *p,unsigned char length)
{
	unsigned char  i,tmp=0;

	for(i=0;i<length;i++)
	{
		tmp += p[i];
	}
	tmp = 0-tmp;//~tmp;
	return tmp;
}
unsigned long long GetNowTimeUs(void)
{  
	 struct timeval tv; 
	 gettimeofday(&tv, NULL);	 
	 return (unsigned long long)tv.tv_sec * 1000000 + tv.tv_usec;
}


