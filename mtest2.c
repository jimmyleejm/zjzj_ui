#define MWINCLUDECOLORS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <windows.h>
#include "wintern.h"
#include "wintools.h"
#include <signal.h>
#include <sys/fcntl.h>

#include <sys/mman.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>


#include <sys/socket.h>  
#include <netinet/if_ether.h>  
#include <net/if_arp.h>  
#include <netinet/in.h>  

#include <net/if_arp.h>  
#include <net/if.h>  
#include <arpa/inet.h>  
#include <sys/ioctl.h>  
#include <math.h>


#include <net/route.h>  
#include <fcntl.h>

#include <limits.h>
#include <netdb.h>
#include <ctype.h>
#include<linux/input.h>


#include <linux/rtc.h>

//extern MWIMAGEHDR image_car8;



#include     <termios.h>    
#include     <errno.h>     


#include "kpd.h"
#include "max3100.h"
#include "print.h"


#define DATE 36
#define PRIN 35
#define MAP 34




#define FALSE  -1
#define PORT 6666

//#define __DEBUG__  
#ifdef __DEBUG__  

//#define DEBUG(format,...) printf("File: "__FILE__", Line: %05d: "format"/n", __LINE__, ##__VA_ARGS__)  
#define DEBUG(format,...) printf("Line: %05d: "format"\n", __LINE__, ##__VA_ARGS__)  
#else  
#define DEBUG(format,...)  
#endif 

#define MCAST_PORT_ZJ 8866
#define MCAST_ADDR_ZJ "224.0.0.66"

#define MCAST_PORT_ZH 8877
#define MCAST_ADDR_ZH "224.0.0.77"




#define ID_TIMER    1 

#define  ID_NEW    301
#define  ID_CONNECT    310

#define  WIDTH_FACE      30
#define  HEIGHT_FACE     30



#define  State_Dfend      1
#define  State_Pa_Dfend     2
#define  State_Un_Dfend     3


#define  ALARM      1
#define  Dfend     2
#define  Part_Dfend     3
#define  Withdraw     4
#define  Linedown     5
#define  Zhq_down    6






#define uint unsigned int 
#define uchar unsigned char

#define RETRY_NUM 4
#define Function_set 111
#define Iput_pw 121
#define Pass_pw 122
#define Set_pw 123
#define Set_ip 124
#define Change_time 125
#define Set_suc 126
#define Set_fal 127
#define Clen_buf 128

#define Set_type 129
#define Set_time 130
#define Set_delay  131
#define Set_defend 132
#define Set_check 133
#define Set_print 134
#define Set_maner 135
#define Set_auto 136
#define Set_auto_one 161
#define Set_auto_two 162


#define Set_recover 137
#define Set_com_pw 138
#define Set_use_pw 139
#define Set_home 140
#define Set_cycle 141
#define Set_defend_one 142
#define Set_defend_two 143
#define Passwd_error 144


#define defend_set 150
#define defend_part 151
#define Iput_usewd 152
#define ret_defend 153
#define ret_defend_part 154

#define  Check_Choice_Type 155
#define  Check_Set_Time 156
#define  Check_Show_Date 157
#define  Check_Show_up 158
#define  Check_Show_down 159
#define  back_part_defend 160

//170+
#define  Print_now 170
#define  alarm_come 171



#define APPCLASS	"Mtest2"

#define APPCHILD	"test2"


//#define ZHU_JI


pthread_mutex_t Device_mutex ;
extern MWIMAGEHDR image_logo;



char *month[12]={"Jan","Feb","Mar","Apr","May ","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};

int prin_flag=0;

HWND main_hwnd;
//HWND child_hwnd;
HDC hdc;
RECT rect_right[9];



char state=State_Un_Dfend;
int kpd_state=0;
int set_page=0;

int  wirte_erg_flag=1;
int  erg_zone[200];
int  defend_zone[200];
int  def_num=0;
int  erg_num=0;

int time_change_flag=0;

int check_type;
char check_getdate[256][128];
int check_point=0;

char device[] = "/dev/kpdcdev";

static int fd_kp= -1;
int call_state_flag=0;
int times_no_do=0;
int times_set=0;
int jf_line_num=0;
int jiafang_state_flag=0;
int zj_line_num=0;


char show_door_alarm_ip[4];
char show_door_close_ip[4];

int state_alarm=0;
char buf_show[15];
char check_logs_name[30];
int  state_call_ins_rom=0;
char call_door_num[4];
char call_room_num[5];
//int heart_search_reset=0;
int  Thread_heart_s=0;
int re_times=0;
//int set_times=0;

char heart_rec[600][30];
//char heart_set[600][30];
int send_broadcast_times=0;
int glj_num=3;
int door_alarm_flag=0;
int show_door_alarm_flag=0;
int rec_flag=0;
int after_media_flag=0;
int glj_type=1;
int print_flag=0;


int data_num[30];
int data_pint=0;

int auto_defend_flag=0;
int auto_dzwl_flag=0;

typedef struct {  
    struct tm start;
    struct tm end;
    int address[256];
    int opint;
}def_rec;  

def_rec store;
def_rec dzwl;

int jfcycle_num=0;
int zj_delay=20;
int rec_device_check_flag=0;
char rec_device_address;
int kap_time_out_flag=0;

int alarm_flag=0;
int zhufu_num=1;

int flag_connect=0; 

int laset_state=301;
char alarm_date[128];
int not_delay_flag=0;

int speed_arr[] = { B38400, B19200, B9600, B4800, B2400, B1200, B300,
                    B38400, B19200, B9600, B4800, B2400, B1200, B300, };
int name_arr[] = {38400,  19200,  9600,  4800,  2400,  1200,  300, 38400,  
                    19200,  9600, 4800, 2400, 1200,  300, };





int OpenDev(char *Dev)
{
    int fd = open( Dev, O_RDWR | O_NOCTTY | O_NDELAY );         //| O_NOCTTY | O_NDELAY 
    fcntl(fd, F_SETFL, 0);   
   // fp=fdopen(fd,"r+");
  //  setvbuf(fp, NULL, _IONBF, 0);
    if (-1 == fd)   
    {           
        perror("Can't Open Serial Port");
        return -1;      
    }   
    else    
        return fd;
    
}



void set_speed(int fd, int speed)
{
    int   i; 
    int   status; 
    struct termios   Opt;
    tcgetattr(fd, &Opt); 
    for ( i= 0;  i < sizeof(speed_arr) / sizeof(int);  i++) { 
        if  (speed == name_arr[i]) {     
            tcflush(fd, TCIOFLUSH);     
            cfsetispeed(&Opt, speed_arr[i]);  
            cfsetospeed(&Opt, speed_arr[i]);   
            status = tcsetattr(fd, TCSANOW, &Opt);  
            if  (status != 0) {        
                perror("tcsetattr fd1");  
                return;     
            }    
            tcflush(fd,TCIOFLUSH);   
        }  
    }
}

int set_Parity(int fd,int databits,int stopbits,int parity)
{ 
    struct termios options; 
    options.c_lflag  &= ~(ICANON | ECHO | ECHOE | ISIG);  /*Input*/
    options.c_oflag  &= ~OPOST;   /*Output*/
    if  ( tcgetattr( fd,&options)  !=  0) { 
        perror("SetupSerial 1");     
        return(FALSE);  
    }
    //options.c_cflag &= ~CSIZE; 
    options.c_cflag     |= (CLOCAL | CREAD);
    switch (databits) /*设置数据位数*/
    {   
    case 7:     
        options.c_cflag |= CS7; 
        break;
    case 8:     
        options.c_cflag |= CS8;
        break;   
    default:    
        fprintf(stderr,"Unsupported data size/n"); return (FALSE);  
    }
    switch (parity) 
    {   
        case 'n':
        case 'N':    
            options.c_cflag &= ~PARENB;   /* Clear parity enable */
            options.c_iflag &= ~INPCK;     /* Enable parity checking */ 
            break;  
        case 'o':   
        case 'O':     
            options.c_cflag |= (PARODD | PARENB); /* 设置为奇效验*/  
            options.c_iflag |= INPCK;             /* Disnable parity checking */ 
            break;  
        case 'e':  
        case 'E':   
            options.c_cflag |= PARENB;     /* Enable parity */    
            options.c_cflag &= ~PARODD;   /* 转换为偶效验*/     
            options.c_iflag |= INPCK;       /* Disnable parity checking */
            break;
        case 'S': 
        case 's':  /*as no parity*/   
            options.c_cflag &= ~PARENB;
            options.c_cflag &= ~CSTOPB;break;  
        default:   
            fprintf(stderr,"Unsupported parity/n");    
            return (FALSE);  
    }  
    /* 设置停止位*/  
    switch (stopbits)
    {   
        case 1:    
            options.c_cflag &= ~CSTOPB;  
            break;  
        case 2:    
            options.c_cflag |= CSTOPB;  
           break;
        default:    
             fprintf(stderr,"Unsupported stop bits/n");  
             return (FALSE); 
    } 
    /* Set input parity option */ 
    if (parity != 'n')   
        options.c_iflag |= INPCK; 
    tcflush(fd,TCIFLUSH);
    options.c_cc[VTIME] = 10; /* 设置超时15 seconds*/   
    options.c_cc[VMIN] = 0; /* Update the options and do it NOW */
    if (tcsetattr(fd,TCSANOW,&options) != 0)   
    { 
        perror("SetupSerial 3");   
        return (FALSE);  
    } 
    return (TRUE);  
}

int init_uart()
{
    
    int fd;
    char *dev  = "/dev/ttyS1"; //串口二 jimmy 0 is net
  // char *dev  = "/dev/ttyS0";
    fd = OpenDev(dev);
  //  DEBUG("fd main is %d\n",fd);
    set_speed(fd,9600);
   // if (set_Parity(fd,8,1,'N') == FALSE)  
   if (set_Parity(fd,8,1,'S') == FALSE)  
    {
        DEBUG("Set Parity Error/n");
       // exit (0);
       return -1;
    }

            
    DEBUG("sent data.\n");

    close(fd); 
    
     //exit (0);
   
}




int sound_gpio_init()
{
	FILE *fp_sound;
	
	if ((fp_sound = fopen("/sys/class/gpio/export", "w")) == NULL) {
				printf("Cannot open export file.\n");
				return -1;
			}
			fprintf(fp_sound, "%d", 167);
			fclose(fp_sound);
			
		
			// equivalent shell command "echo out > direction" to set the port as an input	
			if ((fp_sound = fopen("/sys/class/gpio/gpio167/direction", "rb+")) == NULL) {
				printf("Cannot open direction file.\n");
			  return -1;
			}
			fprintf(fp_sound, "out");
			fclose(fp_sound);

}

int sound_gpio_set(int toggle)
{
	FILE *fp_sound;
	char buffer[10];
	
		memset(buffer, 0, sizeof(buffer));

	if ((fp_sound = fopen("/sys/class/gpio/gpio167/value", "rb+")) == NULL) {
				printf("buzzer_run Cannot open value file.\n");
				//exit(1);
			} else {
			
				if(toggle)
					strcpy(buffer,"1");
				else
					strcpy(buffer,"0");
			
				fwrite(buffer, sizeof(char), sizeof(buffer) - 1, fp_sound); 		
				//printf("buzzer_run ste out value: %c\n", buffer[0]);
				fclose(fp_sound);
			}
	return 0;
}

int gpio_init()
{

  FILE *fp_phone;

			if ((fp_phone = fopen("/sys/class/gpio/export", "w")) == NULL) {
			DEBUG("Cannot open export file.\n");
			return -1;
		}
		fprintf(fp_phone, "%d", 15);
		fclose(fp_phone);
		
		if ((fp_phone = fopen("/sys/class/gpio/gpio15/direction", "rb+")) == NULL) {
			DEBUG("Cannot open direction file.\n");
			 return -1;
		}
		fprintf(fp_phone, "in");
		fclose(fp_phone);
		return 0;
}

int gpio_read()
{
FILE *fp_phone;
char buffer[10];
int  value;

	if ((fp_phone = fopen("/sys/class/gpio/gpio15/value", "rb")) == NULL) {
				DEBUG("Cannot open value file.\n");
				 return -1;
			} else {
				fread(buffer, sizeof(char), sizeof(buffer) - 1, fp_phone);
				value = atoi(buffer);
				//DEBUG("value gpio68: %d\n", value);
				fclose(fp_phone);
				}
			return value;
}


int buzzer_gpio_init()
{
	
  FILE *fp_buzzer;
//  char filename[50];
		// equivalent shell command "echo 32 > export" to export the port 
		if ((fp_buzzer = fopen("/sys/class/gpio/export", "w")) == NULL) {
			DEBUG("Cannot open export file.\n");
			return -1;
		}
		fprintf(fp_buzzer, "%d", 46);
		fclose(fp_buzzer);
		
	
		// equivalent shell command "echo out > direction" to set the port as an input  
		if ((fp_buzzer = fopen("/sys/class/gpio/gpio46/direction", "rb+")) == NULL) {
			DEBUG("Cannot open direction file.\n");
		  return -1;
		}
		fprintf(fp_buzzer, "out");
		fclose(fp_buzzer);
			//usleep(500000);		
		
		
  	return 0;
}




int buzzer_run(int toggle)
{
	FILE *fp;
	char buffer[10];
	
		memset(buffer, 0, sizeof(buffer));

	if ((fp = fopen("/sys/class/gpio/gpio46/value", "rb+")) == NULL) {
				DEBUG("Cannot open value file.\n");
				 return -1;
			} else {
			
				if(toggle)
					strcpy(buffer,"1");
				else
					strcpy(buffer,"0");
			
				fwrite(buffer, sizeof(char), sizeof(buffer) - 1, fp);			
				//DEBUG("buzzer_run ste out value: %c\n", buffer[0]);
				fclose(fp);
			}
			
}
int init_device_kapd(void)
{

	

	fd_kp = open(device, O_RDWR); 

	if (-1 == fd_kp) {
		DEBUG("cannot open file./n");
		 return -1;
	}


  return 0;
}


#define FD_SETSIZE 600


		int zhq_downline_alarm(char* address)
		{
			int zhq_num;
			printf(" alarm ok\n");
										
			sprintf(alarm_date,"		转换器 %s防区掉线",address);
			PostMessage (main_hwnd, WM_COMMAND, alarm_come, 0);
			alarm_flag=1;
			zhq_num=atoi(address);
			write_zj_alarm(zhq_num,Zhq_down,1);
		
		
		}



		int comparison_address()
		{
				FILE*fp_r ;
				char date[10];
				int i;
				int find_flag=0;
				char comp_date[3];
				if((fp_r=fopen("/mnt/nand1-1/config/zhq_address","r"))==NULL)
					{
					printf("can not open the file.\n");
					return -1;
					}
				
				while(!feof(fp_r))
					{
						memset(date,0,sizeof(date));
						fgets(date,sizeof(date),fp_r);
						
						if(strlen(date)<3)
						{
						fclose(fp_r);				
						memset(heart_rec,0,sizeof(heart_rec));
						re_times=0;
						printf("comparison nothing find\n");
						return -1;
						}
						
						//printf("get dateis %s \n",date);	
						find_flag=0;
						for(i=0;i<re_times;i++)
							{	
								//printf("size is %d",strlen(heart_rec[i]) );
								if(strlen(heart_rec[i])==12)
									{
									comp_date[0]=(heart_rec[i][8]-'7')*2+'0';
									comp_date[1]=heart_rec[i][10];
									comp_date[2]=heart_rec[i][11];

									}
								else
									{
									comp_date[0]=(heart_rec[i][8]-'7')*2+'0'+1;
									comp_date[1]=heart_rec[i][11];
									comp_date[2]=heart_rec[i][12];
										
									}
								
								//printf("comp_date[0] comp_date[1] comp_date[2] %c %c %c\n",comp_date[0], comp_date[1] ,comp_date[2]);
								if(comp_date[0]== date[0]  && comp_date[1]== date[1] && comp_date[2]== date[2])
									{
										printf("have date%s\n",date);
										printf("heart_rec re_times is %d,%s\n",i,heart_rec[i]);
										find_flag=1;

										break;
									}
							}
						
						if(find_flag==0)
							{

								printf("alarmssss date is %s\n",date);
								if(alarm_flag==0)
									{
								zhq_downline_alarm(date);
									}

							}
					}
				fclose(fp_r);
				
				memset(heart_rec,0,sizeof(heart_rec));
				re_times=0;

				
		}
		int Thread_heart_search()
		{
			int ser_sockfd,cli_sockfd,con_sockfd;
			int err,n;
			int addlen;
			struct sockaddr_in ser_addr;
			struct sockaddr_in cli_addr;
			struct sockaddr_in sa_cli_addr;
			char recvline[200];
			int ret,maxfd,maxi;
			int nready, client[FD_SETSIZE];
			int i=0;
			fd_set rset, allset;
			
			Thread_heart_s=1;

			
			ser_sockfd=socket(AF_INET,SOCK_STREAM,0);
			if(ser_sockfd==-1)
			{
				printf("socket error\n");
				return -1;
			}
			
			bzero(&ser_addr,sizeof(ser_addr));
			ser_addr.sin_family=AF_INET;
			ser_addr.sin_addr.s_addr=htonl(INADDR_ANY);
			ser_addr.sin_port=htons(PORT);
			err=bind(ser_sockfd,(struct sockaddr *)&ser_addr,sizeof(ser_addr));
			if(err==-1)
			{
				printf("bind error\n");
				return -1;
			}
			
			err=listen(ser_sockfd,200);
			if(err==-1)
			{
				printf("listen error\n");
				return -1;
			}
			maxfd = ser_sockfd;			/* initialize */
			maxi = -1;					/* index into client[] array */
			for (i = 0; i < FD_SETSIZE; i++)
			client[i] = -1;			/* -1 indicates available entry */
			FD_ZERO(&allset);
			FD_SET(ser_sockfd, &allset);

	
			while(1)
			{
			rset = allset;		/* structure assignment */
			nready = select(maxfd+1, &rset, NULL, NULL, NULL);
			
			if (nready <= 0)
						continue;	

			
			if (FD_ISSET(ser_sockfd, &rset)) {	/* new client connection */
					addlen = sizeof(cli_addr);
					cli_sockfd=accept(ser_sockfd,(struct sockaddr *)&cli_addr,&addlen);
					if(cli_sockfd<0)
					  {
						  printf("accept error/n");
						  continue ;
					  }


					for (i = 0; i < FD_SETSIZE; i++)
						if (client[i] < 0) {
							client[i] = cli_sockfd;	/* save descriptor */
							break;
						}
						
					if (i == FD_SETSIZE)
						{
						printf("too many clients\n");
						//FD_CLR(ser_sockfd, &allset);
						close(cli_sockfd);
						continue;
						}

					FD_SET(cli_sockfd, &allset);	/* add new descriptor to set */
					if (cli_sockfd > maxfd)
						{
						maxfd = cli_sockfd;			/* for select */
						//printf("maxfd is %d\n",maxfd);
						}
					if (i > maxi)
						{
						maxi = i;				/* max index in client[] array */
						//printf("maxi is %d\n",maxi);
						}
					if (--nready <= 0)
						continue;				/* no more readable descriptors */
				}
			
			for (i = 0; i <= maxi; i++) {	/* check all clients for data */
					if ( (con_sockfd = client[i]) < 0)
						continue;
					if (FD_ISSET(con_sockfd, &rset)) {
						memset(recvline,0 ,sizeof(recvline));
						//n=recv(cli_sockfd,recvline,sizeof(recvline),0);
						
						if ( (n=recv(con_sockfd,recvline,sizeof(recvline),0))> 0) {
								/*4connection closed by client */

				  // printf("recv data is:%s\n",recvline);

				
					   addlen = sizeof(sa_cli_addr);

					   
					   if(!getpeername(con_sockfd, (struct sockaddr *)&sa_cli_addr, &addlen))
							{
								if(re_times<=600)
									{
								sprintf(heart_rec[re_times],"%s",inet_ntoa (sa_cli_addr.sin_addr));
								//printf("heart_rec re_times is %d,%s\n",re_times,heart_rec[re_times]);
								re_times++;
									}
		
							}


							// printf("maxi is %d!!!!!\n",maxi);
							// printf("maxfd is %d!!!!\n",maxfd);
							close(con_sockfd);
							FD_CLR(con_sockfd, &allset);
							client[i] = -1;
						} 
						else
							{
							close(con_sockfd);
							FD_CLR(con_sockfd, &allset);
							client[i] = -1;
							printf("Select read error\n");
						}
			
						if (--nready <= 0)
							break;				/* no more readable descriptors */
					}
				}


			

			}
			
			close(ser_sockfd);
			
			return 0;  
		}	



		
	int heart_search_init()
		{
		pthread_t id_heart;
		int ret=0;

		   ret = pthread_create(&id_heart,NULL, (void*)Thread_heart_search, NULL);
		   if (ret)
		   {
		   DEBUG("Create pthread error!/n");
		   return -1;
		   } 
		   pthread_detach(id_heart);

			 
			return 0;

		}


		void * 	heart_search_start()
		{
				int ret=0;
				

				int sock = -1;
				//char ip_buf[30];
				const int opt = 1;
				int nb = 0;
				struct sockaddr_in addrto;
				char heart_buf[30];
			//	static int heart_start_flag=0;


				
				 //printf("heart_search_start!!!\n");
				 
				if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1) 
				{ 
					printf("socket error\n");
					//cout<<"socket error"<<endl;	
					return 0;
				}	
				
				
				nb = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt));
				if(nb == -1)
				{
					printf("set socket error...\n");
					//cout<<"set socket error..."<<endl;
					return 0;
				}
			
		
				bzero(&addrto, sizeof(struct sockaddr_in));
				addrto.sin_family=AF_INET;
				addrto.sin_addr.s_addr=htonl(INADDR_BROADCAST);
				addrto.sin_port=htons(6001);
				int nlen=sizeof(addrto);
			
				//getip(ip_buf);
				//printf("ip_buf is %s\n",ip_buf);
					//从广播地址发送消息
					//char smsg[] = {"abcdef"};
				memset(heart_buf,0,sizeof(heart_buf));
				sprintf(heart_buf,"herat serarch check%d\0",glj_num);
				DEBUG("heart_buf %s\n",heart_buf);
				ret=sendto(sock, heart_buf, strlen( heart_buf), 0, (struct  sockaddr*)&addrto, nlen);
				if(ret<0)
				{
					printf("send error....\n");
					//cout<<"send error...."<<ret<<endl;
				}
				else
				{		
					//printf("send broadcast ok \n");	
				}
				
				close(sock);

				
				return NULL;
		}		

		void * 	Thread_time(void *  iCmdShow)
			{ 
			int clean_flag=0;
			static int show_times=0;
			while(1)
				{
					
			
					show_times++;
					
					if(alarm_flag==1)
						{
						buzzer_run(1);
						}
					sleep(1);
					if(alarm_flag==1)
						{
						buzzer_run(0);

						}
					
					if(show_times>=60)
						{
						PostMessage (main_hwnd, WM_COMMAND, Change_time, 0);
						show_times=0;
						}

					if(kpd_state!=5 && kpd_state!=9 && kpd_state!=0)
						{

							kap_time_out_flag++;
							printf("kap_time_out_flag is %d \n",kap_time_out_flag);	
						
						if(kap_time_out_flag>120)
							{
							if(kpd_state == 1 || kpd_state == 2 || kpd_state == 3 || kpd_state == 7 || kpd_state == 8 || kpd_state == 10
								|| kpd_state == 11 || kpd_state == 12 || kpd_state == 13)
								{
								clean_flag=1;
								kpd_state = 0;
								set_page=0;
								PostMessage(main_hwnd,WM_COMMAND,ID_NEW,0);

								}
							if(kpd_state == 6)
								{

									clean_flag=1;
									if(state==State_Pa_Dfend)
										{
										kpd_state = 9;
										PostMessage(main_hwnd,WM_COMMAND,back_part_defend,0);
										}
									else 	if(state==State_Dfend)
										{
										kpd_state = 5;
										PostMessage(main_hwnd,WM_COMMAND,ret_defend,0);

										}

								}
							


							if(clean_flag==1)
								{
									memset(buf_show,0,sizeof(buf_show));
									PostMessage (main_hwnd, WM_COMMAND, Clen_buf, 0);
									memset(data_num,0,sizeof(data_num));
									data_pint=0;
								    clean_flag=0;
								}

								
							kap_time_out_flag=0;
							}

						}
				}
			return NULL;
			}

		int write_defend_file()
			{
				 FILE *fp_def;  
   				 int i;
				fp_def=fopen("/mnt/nand1-1/config/defend_time","w");  
				if(!fp_def)  
				{  
				printf("errror write_defend_file!\n");  
				return -1;
				}  
				printf("sb:sh=%d,sm=%d,eh=%d,em=%d,opint=%d\n",store.start.tm_hour,store.start.tm_min
    ,store.end.tm_hour,store.end.tm_min,store.opint); 
				fwrite(&store,sizeof(store),1,fp_def);  

				fclose(fp_def);  
				return 0;
			}
		

		

			int read_defend_file()
			{
				 FILE *fp_def;  
   				 int i;
				fp_def=fopen("/mnt/nand1-1/config/defend_time","r");  
				if(!fp_def)  
				{  
				printf("errror read_defend_file!\n");  
				return -1;
				}  
				fread(&store,sizeof(store),1,fp_def);  
				printf("sb:sh=%d,sm=%d,eh=%d,em=%d,opint=%d\n",store.start.tm_hour,store.start.tm_min
					,store.end.tm_hour,store.end.tm_min,store.opint); 
				
				fclose(fp_def);  

				if(store.opint==0)
					auto_defend_flag=0;
				else
					auto_defend_flag=1;


				fp_def=fopen("/mnt/nand1-1/config/dzwl_time","r");  
				if(!fp_def)  
				{  
				printf("errror read_defend_file!\n");  
				return -1;
				}  
				fread(&dzwl,sizeof(dzwl),1,fp_def);  
				printf("sb:sh=%d,sm=%d,eh=%d,em=%d,opint=%d\n",dzwl.start.tm_hour,dzwl.start.tm_min
					,dzwl.end.tm_hour,dzwl.end.tm_min,dzwl.opint); 
				
				fclose(fp_def);  

				if(dzwl.opint==0)
					auto_dzwl_flag=0;
				else
					auto_dzwl_flag=1;

				
				return 0;
			}


		int close_auto_defend()
			{
			memset(store.address,0,sizeof(store.address));
			store.opint=0;
			write_defend_file();
			auto_defend_flag=0;

			}

		int open_auto_defend()
			{
			write_defend_file();
			auto_defend_flag=1;
			time_change_flag=1;
			}



			int write_dzwl_file()
			{
				 FILE *fp_def;  
   				 int i;
				fp_def=fopen("/mnt/nand1-1/config/dzwl_time","w");  
				if(!fp_def)  
				{  
				printf("errror write_defend_file!\n");  
				return -1;
				}  
				printf("sb:sh=%d,sm=%d,eh=%d,em=%d,opint=%d\n",dzwl.start.tm_hour,dzwl.start.tm_min
    ,dzwl.end.tm_hour,dzwl.end.tm_min,dzwl.opint); 
				fwrite(&dzwl,sizeof(dzwl),1,fp_def);  

				fclose(fp_def);  
				return 0;
			}

			
		int close_auto_dzwl()
			{
			memset(dzwl.address,0,sizeof(dzwl.address));
			dzwl.opint=0;
			write_dzwl_file();
			auto_dzwl_flag=0;

			}

		int open_auto_dzwl()
			{
			write_dzwl_file();
			auto_dzwl_flag=1;
			//time_change_flag=1;
			}

		

		int write_to_file(char *date)
			{
				FILE*fp_w;
				char file_buffer[128]; 
				int i;
				if((fp_w=fopen("/mnt/nand1-1/config/jiafang_record","r+"))==NULL)
					{
					printf("can not open the file.\n");
					return -1;
					}
				
				for(i=0;i<jf_line_num;i++)
					{
					fgets(file_buffer,sizeof(file_buffer),fp_w);
					}

				
				fputs(date,fp_w);
				fputs("\n",fp_w);
				jf_line_num++;


				if(jf_line_num>1000)
					{
					jf_line_num=0;
					}

				
				fclose(fp_w);



					if(print_flag==1)
					{
					print_punch(date,1,1);

					}

			}

		int read_file_line()
			{
				FILE*fp_r;
				char file_buffer[128]; 
				
				if((fp_r=fopen("/mnt/nand1-1/config/jiafang_record","r"))==NULL)
					{
					printf("can not open the file.\n");
					return -1;
					}

				while(!feof(fp_r))
						{
						memset(file_buffer,0,sizeof(file_buffer));
						fgets(file_buffer,sizeof(file_buffer),fp_r);
						if(strlen(file_buffer)>3)
							{
						jf_line_num++;
							}
						}
				
				printf("jf_line_num is %d\n",jf_line_num);

				fclose(fp_r);


				if((fp_r=fopen("/mnt/nand1-1/config/zhoujie_record","r"))==NULL)
					{
					printf("can not open the file.\n");
					return -1;
					}

				while(!feof(fp_r))
						{
						memset(file_buffer,0,sizeof(file_buffer));
						fgets(file_buffer,sizeof(file_buffer),fp_r);
						if(strlen(file_buffer)>3)
							{
						zj_line_num++;
							}
						}
				
				printf("zj_line_num is %d\n",zj_line_num);

				fclose(fp_r);


				

			}

		int write_file(char * file,char *date)
			{
				FILE*fp_w;
				if((fp_w=fopen(file,"w"))==NULL)
					{
					printf("can not open the file.\n");
					return -1;
					}
				fputs(date,fp_w);
				 fputs("\n",fp_w);
				fclose(fp_w);
				
			}

		int read_file(char * file,char *date)
			{
				FILE*fp_r ;
				if((fp_r=fopen(file,"r"))==NULL)
					{
					printf("can not open the file.\n");
					return -1;
					}
				fgets(date,sizeof(date),fp_r);
				fclose(fp_r);
			}
			
		int set_device(char *filename,int manner,char *address)
			{
			
				int i=0;
				int j=0;
				int device_at=-1;
				int ret=1;
				char device_add[50][5];
				int  device_point=0;
				FILE *pFile=NULL;
				FILE *oFile=NULL;
				
				
				 // pFile=fopen("/mnt/nand1-1/config/erg_address","r");
				 pFile=fopen(filename,"r");
				
				if(pFile!=NULL)
				{
					while(!feof(pFile))
						{	
							memset(device_add[device_point]  , 0 , sizeof(device_add[device_point]) );
						    fgets( device_add[device_point] ,	sizeof(device_add[device_point])  , pFile );
							if(strlen( device_add[device_point])>0)
								{
						 		   device_point++;
								}
						    if(device_point>=50)
							{
								return -1;
					 		}
					    }
					 fclose(pFile);
					 
					 for(i=0;i<device_point;i++)
					 {
						
						for(j=0;j<3;j++)
						{
							if(device_add[i][j]!=address[j])
								{
									break;
								}
						}
						
						if(j==3)
							{
								//printf("device is exist!\n");
								if(manner==1)
									{
										return 0;
									}
								else
									{
									device_at=i;
								//	fprintf(cgiOut ,"<tr><td align=\"left\" width=\"20%%\">&nbsp&nbsp&nbsp&nbspis:</td><td>%d</td></tr>",device_at);
									}
							}
					 }
					 
				}
				
				
				if(manner==1)
			   {
				//oFile=fopen("/mnt/nand1-1/config/erg_address","a");
				oFile=fopen(filename,"a");
			   // fseek(oFile,0,SEEK_END);
				fputs(address,oFile);
				 fputs("\n",oFile);
				fclose(oFile);
				}
				else
				{
					if(device_at!=-1)
						{
							//oFile=fopen("/mnt/nand1-1/config/erg_address","w");
							oFile=fopen(filename,"w");
							// fseek(oFile,0,SEEK_END);
							for(i=0;i<device_point;i++)
							{
							if(device_at!=i)
								{
							fputs(device_add[i],oFile);
						//	fputs("\n",oFile);
								}
							}
						fclose(oFile);
						}
				}
				
				return 0;
			}

void dzwl_set(char address,int manner)
{
	
		pthread_mutex_lock(&Device_mutex);
		 SPI_write(0xdf,1);
	     //usleep(1000000);
	     SPI_write(0x00,0);
	    // usleep(1000000);
	     SPI_write(0x00,0);
	     //usleep(1000000);
	     SPI_write(address,0);
	    // usleep(1000000);
	    if(manner==1)
	        SPI_write(0x0c,0);
		else
		    SPI_write(0x0d,0);
		 pthread_mutex_unlock(&Device_mutex);
		
}


		
	int check_pwd(int pw_num)
	{
		 FILE *fpr_cmd;
		 char manage_password[10];
			int i;
		 if(pw_num==1)
		 	{

			 if((fpr_cmd=fopen("/mnt/nand1-1/config/command_pw","r"))==NULL)
					{
					DEBUG("can not open the file.\n");
					return 0;
					}
		 	}
		 else
		 	{

			 if((fpr_cmd=fopen("/mnt/nand1-1/config/use_pw","r"))==NULL)
					{
					DEBUG("can not open the file.\n");
					return 0;
					}
		 	}
		 	
				
			fgets(manage_password,sizeof(manage_password),fpr_cmd);
			fclose(fpr_cmd);
			
			for(i=0;i<6;i++)
			{
				if(buf_show[i]!=manage_password[i])
					{
					DEBUG("data_num[i]=%d",data_num[i]);
					DEBUG("manage_password[i]=%d",manage_password[i]);
					memset(buf_show,0,sizeof(buf_show));
					PostMessage (main_hwnd, WM_COMMAND, Clen_buf, 0);
					memset(data_num,0,sizeof(data_num));
					data_pint=0;
				  	return 1;
					}
			}
			return 0;
												

	}


	int clear_set()
		{
		memset( erg_zone,0 ,sizeof(erg_zone))	;
		erg_num=0;
						 
		wirte_erg_flag=1;
		close_auto_defend();
		zj_delay=20;
		print_flag=0;
		close_auto_dzwl();
		jiafang_state_flag=0;
		jfcycle_num=12;

		}
		//PostMessage (hwnd, WM_COMMAND, Set_time, 0);
	void * 	Thread_kp(void *  iCmdShow)
		{
	//	struct input_event data;
		int read_num[2];
		int num[20]={6,7,8,9,0,
				   16,17,18,19,20,
				   11,12,13,14,15,
				   1,2,3,4,5};
		int num_ch=0;
		int put_time=0;

		int refresh_flag=0;
		
		int retu_page=0;
		int inter_ser_flag=0;
		int rec_num;
	    int num_flag=0;
		 
		  int i;
		  int set_num=0;
		  int no_show_flag=0;
		  char tmp_ip[100];
		  char tmp_mac[50];
		  char tmp_dev[10];
		  int ret; 
		  def_rec middle_num;
		
		  
		  memset(data_num,0,sizeof(data_num));
		//	send_message("ringback /mnt/nand1-1/123.wav");
		  
		for(;;){
				START:
				    read(fd_kp,&read_num,sizeof(read_num));
					kap_time_out_flag=0;					
					printf("%d %d\n", read_num[0],read_num[1]);
				
					if(put_time==0)
						{
						buzzer_run(1);
						usleep(50000);
						buzzer_run(0);
							
						}
					
					if(read_num[1])
						{
						if( read_num[0]-1 > 19)
							{
								continue;
							}
						num_ch=num[read_num[0]-1];
       					put_time++;
			       		if(put_time>10)
			       			{
			       			
			       			}
						}
					else if(read_num[1] ==0)
				       	{
							if( read_num[0]-1 > 19)
							{
								continue;
							}

							
							if(alarm_flag==1)
							{
								if(laset_state==defend_set)
									{
									not_delay_flag=1;

									}
								PostMessage (main_hwnd, WM_COMMAND, laset_state, 0);
								alarm_flag=0;
								buzzer_run(0);
								goto START; 
							}


									
				       		if(num_ch==num[read_num[0]-1])
			       			{
			       		
			       			DEBUG("pass %d\n",num_ch);

							if(kpd_state == 0)
       							{
	       						if(num_ch == 11)
	       							{
		       							kpd_state = 1;
										PostMessage (main_hwnd, WM_COMMAND, Iput_pw, 0);
	       							}
								else if(num_ch == 20)
									{
										memset(buf_show,0,sizeof(buf_show));
										PostMessage (main_hwnd, WM_COMMAND, Clen_buf, 0);
										memset(data_num,0,sizeof(data_num));
										data_pint=0;
										kpd_state = 0;
										PostMessage(main_hwnd,WM_COMMAND,ID_NEW,0);
										

									}

								}
							else if(kpd_state == 1)
								{
									if(num_ch == 12)
	       							{
										if(data_pint==6)
										{
											   if(check_pwd(1))
											   	{
											   		
												   PostMessage (main_hwnd, WM_COMMAND, Passwd_error, 0);
											   	   sleep(2);
												    memset(buf_show,0,sizeof(buf_show));
													PostMessage (main_hwnd, WM_COMMAND, Clen_buf, 0);
													memset(data_num,0,sizeof(data_num));
													data_pint=0;
											   	   PostMessage (main_hwnd, WM_COMMAND, Iput_pw, 0);
												 
												   goto START; 

											   	}
												
												kpd_state=2;
												refresh_flag=1;
												PostMessage (main_hwnd, WM_COMMAND, Pass_pw, 0);

								   		}
										else
										{
											PostMessage (main_hwnd, WM_COMMAND, Passwd_error, 0);
											sleep(2);
											memset(buf_show,0,sizeof(buf_show));
											PostMessage (main_hwnd, WM_COMMAND, Clen_buf, 0);
											memset(data_num,0,sizeof(data_num));
											data_pint=0;
											PostMessage (main_hwnd, WM_COMMAND, Iput_pw, 0);
											
											goto START; 

										}
									}
									else if(num_ch == 20)
									{
										refresh_flag=1;
										kpd_state = 0;
										PostMessage(main_hwnd,WM_COMMAND,ID_NEW,0);
										

									}
								}
							else if(kpd_state == 2)
								{
								if(num_ch == 12)
	       							{
										if(data_pint==1)
										{
										set_num=data_num[0];
										if(zhufu_num!=1)
											{
												switch(set_num)
												{
												case 5:
													set_num=6;
												break;
												case 6:
													set_num=9;
												break;
												case 7:
													set_num=10;
												break;
												case 8:
													set_num=11;
												break;
												case 9:
													set_num=12;
												break;

												default:
												break;
												}
											}
										kpd_state=3;
										}
										else if(data_pint==2)
										{
										set_num=data_num[0]*10+data_num[1];
										kpd_state=3;

										}
								//		DEBUG("set_num=%d",set_num);
										switch(set_num)
											{
												case  1 :
												PostMessage(main_hwnd,WM_COMMAND,Set_type,0);
												refresh_flag=1;
												break;
												case  2 :
												PostMessage(main_hwnd,WM_COMMAND,Set_time,0);
												refresh_flag=1;
												break;
												case  3 :
												PostMessage(main_hwnd,WM_COMMAND,Set_delay,0);
												refresh_flag=1;
												break;
												case  4 :
												PostMessage(main_hwnd,WM_COMMAND,Set_defend,0);
												refresh_flag=1;
												break;
												case  5 :
												PostMessage(main_hwnd,WM_COMMAND,Set_check,0);
												refresh_flag=1;
												break;
												case  6 :
												PostMessage(main_hwnd,WM_COMMAND,Set_print,0);
												refresh_flag=1;
												break;
												case  7 :
												PostMessage(main_hwnd,WM_COMMAND,Set_maner,0);
												refresh_flag=1;
												break;
												case  8 :
												PostMessage(main_hwnd,WM_COMMAND,Set_auto,0);
												refresh_flag=1;
												break;
												case  9 :
												PostMessage(main_hwnd,WM_COMMAND,Set_recover,0);
												//refresh_flag=1;
												system("cp  /mnt/nand1-1/rec/* /mnt/nand1-1/config/");
												clear_set();

												sleep(2);
												PostMessage (main_hwnd, WM_COMMAND, Set_suc, 0);
												sleep(2);
												refresh_flag=1;
												kpd_state = 2;
												PostMessage (main_hwnd, WM_COMMAND, Pass_pw, 0);
												
												break;
												case  10 :
												PostMessage(main_hwnd,WM_COMMAND,Set_com_pw,0);
												refresh_flag=1;
												break;
												case  11 :
												PostMessage(main_hwnd,WM_COMMAND,Set_use_pw,0);
												refresh_flag=1;
												break;
												case  12 :
												PostMessage(main_hwnd,WM_COMMAND,Set_home,0);
												refresh_flag=1;
												break;
												case  13 :
												PostMessage(main_hwnd,WM_COMMAND,Set_cycle,0);
												refresh_flag=1;
												break;
												default:
												break;
												
											}

									}
								else if(num_ch == 20)
									{
										refresh_flag=1;
										kpd_state = 0;
										PostMessage(main_hwnd,WM_COMMAND,ID_NEW,0);
										

									}
								}
							else if(kpd_state == 3)
								{
								  	if(num_ch == 12)
	       							{
										switch(set_num)
											{
												case  1 :
												if(data_pint==4)
												{
												if(data_num[3]==1)
													{
														
														memset(tmp_dev,0,sizeof(tmp_dev));
														sprintf(tmp_dev,"%d%d%d",data_num[0],data_num[1],data_num[2]);
														//DEBUG("```````1``````` %s",tmp_dev);
														set_device("/mnt/nand1-1/config/erg_address",0,tmp_dev);
														wirte_erg_flag=1;
														PostMessage(main_hwnd,WM_COMMAND,Set_suc,0);
													}
												else if(data_num[3]==2)
													{
														memset(tmp_dev,0,sizeof(tmp_dev));
														sprintf(tmp_dev,"%d%d%d",data_num[0],data_num[1],data_num[2]);
														//DEBUG("```````2``````` %s",tmp_dev);
														set_device("/mnt/nand1-1/config/erg_address",1,tmp_dev);
														wirte_erg_flag=1;
														PostMessage(main_hwnd,WM_COMMAND,Set_suc,0);
													}
												else
													{
													
														PostMessage(main_hwnd,WM_COMMAND,Set_fal,0);
													}
												
										
												}
												else
													{
													
														PostMessage(main_hwnd,WM_COMMAND,Set_fal,0);
													}

													sleep(2);
													refresh_flag=1;
													kpd_state = 2;
													PostMessage (main_hwnd, WM_COMMAND, Pass_pw, 0);
												break;
												case  2 :
														if(data_pint==12)
											        	{
											        	ret=SetSystemTime(buf_show);
														//printf("time ret is %d!!!\n",ret)
														if(ret<0)
															{
															PostMessage (main_hwnd, WM_COMMAND, Set_fal, 0);
															}
														else
															{
															PostMessage (main_hwnd, WM_COMMAND, Set_suc, 0);

															}
													   	}
													   else
													   	{
														PostMessage (main_hwnd, WM_COMMAND, Set_fal, 0);

													  	}	
													   	sleep(2);
														refresh_flag=1;
														kpd_state = 2;
														PostMessage (main_hwnd, WM_COMMAND, Pass_pw, 0);
												break;
												case  3 :
														if(data_pint==3)
											        	{
											        	write_file("/mnt/nand1-1/config/delay_time",buf_show);
														PostMessage (main_hwnd, WM_COMMAND, Set_suc, 0);
													   	}
													   else
													   	{
														PostMessage (main_hwnd, WM_COMMAND, Set_fal, 0);

													  	}	
													   	sleep(2);
														refresh_flag=1;
														kpd_state = 2;
														PostMessage (main_hwnd, WM_COMMAND, Pass_pw, 0);
												break;
												case  4 :
														if(set_page==0)	
															{
																	if(data_pint==1)
														        	{
															        	if(data_num[0]==1)
															        		{
															        			set_page=1;
																				PostMessage (main_hwnd, WM_COMMAND, Set_defend_one, 0);
																				refresh_flag=1;
															        		}
																		else if(data_num[0]==2)
																			{
																				close_auto_defend();
																				PostMessage (main_hwnd, WM_COMMAND, Set_suc, 0);
																				retu_page=1;
																			}
																		else
																			{
																			PostMessage (main_hwnd, WM_COMMAND, Set_fal, 0);
																			retu_page=1;

																			}
																		
																   	}
																   else
																   	{
																		PostMessage (main_hwnd, WM_COMMAND, Set_fal, 0);
																		retu_page=1;

																  	}	
															}
														else if(set_page==1)
															{
																	if(data_pint==8)
														        	{
															        	set_page=2;
																		memset(&middle_num,0,sizeof(middle_num));
																		middle_num.start.tm_hour=data_num[0]*10+data_num[1];
																		middle_num.start.tm_min=data_num[2]*10+data_num[3];
   																		middle_num.end.tm_hour=data_num[4]*10+data_num[5];
   																		middle_num.end.tm_min=data_num[6]*10+data_num[7];
																		memset(middle_num.address,0,sizeof(middle_num.address));
																		middle_num.opint=0;
																		PostMessage (main_hwnd, WM_COMMAND, Set_defend_two, 0);
																		refresh_flag=1;
																		
																   	}
																   else
																   	{
																		PostMessage (main_hwnd, WM_COMMAND, Set_fal, 0);
																		retu_page=1;

																  	}	
															}
														else if(set_page==2)
															{
																	if(data_pint==3)
														        	{
																		middle_num.address[middle_num.opint]=data_num[0]*100+data_num[1]*10
																			+data_num[2];
																			if(middle_num.opint<256)
																				{
																				middle_num.opint++;
																				}	
																			
																			if(middle_num.address[middle_num.opint-1]==999)
																				{
																				memset(middle_num.address,0,sizeof(middle_num.address));
																				middle_num.opint=1;
																				middle_num.address[0]=999;
																				store=middle_num;
																				open_auto_defend();	
																				retu_page=1;
																				}
																			else
																				{
																				PostMessage (main_hwnd, WM_COMMAND, Set_suc, 0);
																				sleep(1);
																				PostMessage (main_hwnd, WM_COMMAND, Set_defend_two, 0);
																				refresh_flag=1;
																				}
																		
																   	}
																   else
																   	{
																		PostMessage (main_hwnd, WM_COMMAND, Set_fal, 0);
																		sleep(1);
																		PostMessage (main_hwnd, WM_COMMAND, Set_defend_two, 0);
																		refresh_flag=1;

																  	}
															}

														if(retu_page==1)
												    	{
												   			sleep(2);
															refresh_flag=1;
															kpd_state = 2;
															retu_page=0;
															set_page=0;
															
															PostMessage (main_hwnd, WM_COMMAND, Pass_pw, 0);
												    	}
												break;
												case  5 :
														if(data_pint==3)
											        	{
											        	write_file("/mnt/nand1-1/config/zj_check_time",buf_show);
														zj_delay=data_num[0]*100+data_num[1]*10+data_num[2];
														if(zj_delay<5)
															{
															zj_delay=5;
															}
														PostMessage (main_hwnd, WM_COMMAND, Set_suc, 0);
													   	}
													   else
													   	{
														PostMessage (main_hwnd, WM_COMMAND, Set_fal, 0);
													  	}	
													   	sleep(2);
														refresh_flag=1;
														kpd_state = 2;
														PostMessage (main_hwnd, WM_COMMAND, Pass_pw, 0);
												break;
												case  6 :
														if(data_pint==1)
											        	{
											        		if(data_num[0]==1)
											        			{
												        			write_file("/mnt/nand1-1/config/printf_state",buf_show);
																	PostMessage (main_hwnd, WM_COMMAND, Set_suc, 0);
																	print_flag=1;
											        			}
															else if(data_num[0]==2)
																{
																	write_file("/mnt/nand1-1/config/printf_state",buf_show);
																	PostMessage (main_hwnd, WM_COMMAND, Set_suc, 0);
																	print_flag=0;

																}
															else
																{
																PostMessage (main_hwnd, WM_COMMAND, Set_fal, 0);

																}
													   	}
													   else
													   	{
														PostMessage (main_hwnd, WM_COMMAND, Set_fal, 0);
													  	}	
													   	sleep(2);
														refresh_flag=1;
														kpd_state = 2;
														PostMessage (main_hwnd, WM_COMMAND, Pass_pw, 0);
												break;
												case  7 :
												if(data_pint==4)
											        	{
															if(data_num[3]==1 || data_num[3]==2)
																{
																	dzwl_set((char)(data_num[0]*100+data_num[1]*10+data_num[2]),data_num[3]);
																	PostMessage(main_hwnd, WM_COMMAND, Set_suc, 0);
																}
															else
																{
																PostMessage (main_hwnd, WM_COMMAND, Set_fal, 0);

																}
													   	}
													   else
													   	{
														PostMessage (main_hwnd, WM_COMMAND, Set_fal, 0);

													  	}	
													   	sleep(2);
														refresh_flag=1;
														kpd_state = 2;
														PostMessage (main_hwnd, WM_COMMAND, Pass_pw, 0);
												break;
												case  8 :
												if(set_page==0)	
													{
															if(data_pint==1)
												        	{
													        	if(data_num[0]==1)
													        		{
													        			set_page=1;
																		PostMessage (main_hwnd, WM_COMMAND, Set_auto_one, 0);
																		refresh_flag=1;
													        		}
																else if(data_num[0]==2)
																	{
																		close_auto_dzwl();
																		PostMessage (main_hwnd, WM_COMMAND, Set_suc, 0);
																		retu_page=1;
																	}
																else
																	{
																	PostMessage (main_hwnd, WM_COMMAND, Set_fal, 0);
																	retu_page=1;

																	}
																
														   	}
														   else
														   	{
																PostMessage (main_hwnd, WM_COMMAND, Set_fal, 0);
																retu_page=1;

														  	}	
													}
												else if(set_page==1)
													{
															if(data_pint==8)
												        	{
													        	set_page=2;
																memset(&middle_num,0,sizeof(middle_num));
																middle_num.start.tm_hour=data_num[0]*10+data_num[1];
																middle_num.start.tm_min=data_num[2]*10+data_num[3];
																	middle_num.end.tm_hour=data_num[4]*10+data_num[5];
																	middle_num.end.tm_min=data_num[6]*10+data_num[7];
																memset(middle_num.address,0,sizeof(middle_num.address));
																middle_num.opint=0;
																PostMessage (main_hwnd, WM_COMMAND, Set_auto_two, 0);
																refresh_flag=1;
																
														   	}
														   else
														   	{
																PostMessage (main_hwnd, WM_COMMAND, Set_fal, 0);
																retu_page=1;

														  	}	
													}
												else if(set_page==2)
													{
															if(data_pint==3)
												        	{
																middle_num.address[middle_num.opint]=data_num[0]*100+data_num[1]*10
																	+data_num[2];
																	if(middle_num.opint<256)
																		{
																		middle_num.opint++;
																		}	
																	
															
																		PostMessage (main_hwnd, WM_COMMAND, Set_suc, 0);
																		sleep(1);
																		PostMessage (main_hwnd, WM_COMMAND, Set_auto_two, 0);
																		refresh_flag=1;
																		
																
														   	}
														   else
														   	{
																PostMessage (main_hwnd, WM_COMMAND, Set_fal, 0);
																sleep(1);
																PostMessage (main_hwnd, WM_COMMAND, Set_auto_two, 0);
																refresh_flag=1;

														  	}
													}

												if(retu_page==1)
										    	{
										   			sleep(2);
													refresh_flag=1;
													kpd_state = 2;
													retu_page=0;
													set_page=0;
													
													PostMessage (main_hwnd, WM_COMMAND, Pass_pw, 0);
										    	}
												break;
												case  9 :
												//PostMessage(main_hwnd,WM_COMMAND,Set_recover,0);
												
												break;
												case  10 :
													if(data_pint==6)
											        	{
											        	write_file("/mnt/nand1-1/config/command_pw",buf_show);
														PostMessage (main_hwnd, WM_COMMAND, Set_suc, 0);
													   	}
													   else
													   	{
														PostMessage (main_hwnd, WM_COMMAND, Set_fal, 0);

													  	}	
													   	sleep(2);
														refresh_flag=1;
														kpd_state = 2;
														PostMessage (main_hwnd, WM_COMMAND, Pass_pw, 0);
												break;
												case  11 :
													if(data_pint==6)
											        	{
											        	write_file("/mnt/nand1-1/config/use_pw",buf_show);
														PostMessage (main_hwnd, WM_COMMAND, Set_suc, 0);
													   	}
													   else
													   	{
														PostMessage (main_hwnd, WM_COMMAND, Set_fal, 0);

													  	}	
													   	sleep(2);
														refresh_flag=1;
														kpd_state = 2;
														PostMessage (main_hwnd, WM_COMMAND, Pass_pw, 0);
												break;
												case  12 :
													if(data_pint==1)
											        	{
															if(data_num[0]==1 || data_num[0]==2)
																{
																	if(data_num[0]==1)
														        		{
																		jiafang_state_flag=1;
																		}
																	else
																		{
																		jiafang_state_flag=0;

																		}
																	write_file("/mnt/nand1-1/config/jiafang_state",buf_show);
																	PostMessage(main_hwnd, WM_COMMAND, Set_suc, 0);
																}
															else
																{
																PostMessage (main_hwnd, WM_COMMAND, Set_fal, 0);

																}
													   	}
													   else
													   	{
														PostMessage (main_hwnd, WM_COMMAND, Set_fal, 0);

													  	}	
													   	sleep(2);
														refresh_flag=1;
														kpd_state = 2;
														PostMessage (main_hwnd, WM_COMMAND, Pass_pw, 0);
												break;
												case  13 :
														if(data_pint==3)
											        	{
											        	write_file("/mnt/nand1-1/config/jiafang_time",buf_show);
														jfcycle_num=atoi(buf_show);
														PostMessage (main_hwnd, WM_COMMAND, Set_suc, 0);
													   	}
													   else
													   	{
														PostMessage (main_hwnd, WM_COMMAND, Set_fal, 0);
													  	}	
													   	sleep(2);
														refresh_flag=1;
														kpd_state = 2;
														PostMessage (main_hwnd, WM_COMMAND, Pass_pw, 0);
												break;
												default:
												break;
												//jimmy
												
											}

									}
								else if(num_ch == 20)
									{
										if(set_page==2)
											{
												if(set_num==4)
													{
														store=middle_num;
											 			open_auto_defend();
													}
												else if(set_num==8)
													{
														dzwl=middle_num;
														open_auto_dzwl();

													}
											}
										refresh_flag=1;
										kpd_state = 2;
										set_page=0;
										PostMessage (main_hwnd, WM_COMMAND, Pass_pw, 0);
										

									}
								}
							else if(kpd_state == 6)
								{
									if(num_ch == 12)
	       							{
										if(data_pint==6)
										{
											   if(check_pwd(2))
											   	{
											   	   PostMessage (main_hwnd, WM_COMMAND, Passwd_error, 0);
											   	   sleep(2);
												   memset(buf_show,0,sizeof(buf_show));
													PostMessage (main_hwnd, WM_COMMAND, Clen_buf, 0);
													memset(data_num,0,sizeof(data_num));
													data_pint=0;
											   	   PostMessage (main_hwnd, WM_COMMAND, Iput_usewd, 0);
												   goto START; 

											   	}
												
												kpd_state=0;
												refresh_flag=1;
												def_num=0;
												state=State_Un_Dfend;
												PostMessage (main_hwnd, WM_COMMAND, ID_NEW, 0);
												write_zj_alarm(0,Withdraw,1);
										

								   		}
										else
											{
											  PostMessage (main_hwnd, WM_COMMAND, Passwd_error, 0);
										   	   sleep(2);
											   	memset(buf_show,0,sizeof(buf_show));
												PostMessage (main_hwnd, WM_COMMAND, Clen_buf, 0);
												memset(data_num,0,sizeof(data_num));
												data_pint=0;
										   	   PostMessage (main_hwnd, WM_COMMAND, Iput_usewd, 0);
											   goto START; 

											}
									}
									else if(num_ch == 20)
									{
										refresh_flag=1;
										if(state==State_Pa_Dfend)
											{
											kpd_state = 9;
											PostMessage(main_hwnd,WM_COMMAND,back_part_defend,0);
											}
										else 	if(state==State_Dfend)
											{
											kpd_state = 5;
											PostMessage(main_hwnd,WM_COMMAND,ret_defend,0);

											}
										
										

									}
								}
							else if(kpd_state == 7 || kpd_state == 10)
								{
									if(num_ch == 12)
		       							{
											if(data_pint==6)
											{
												   if(check_pwd(2))
												   	{
													       PostMessage (main_hwnd, WM_COMMAND, Passwd_error, 0);
													   	   sleep(2);
														   memset(buf_show,0,sizeof(buf_show));
															PostMessage (main_hwnd, WM_COMMAND, Clen_buf, 0);
															memset(data_num,0,sizeof(data_num));
															data_pint=0;
													   	   PostMessage (main_hwnd, WM_COMMAND, Iput_usewd, 0);
														   goto START; 

												   	}

													
													if(kpd_state == 7)
														{
															kpd_state=8;
															inter_ser_flag=0;
															PostMessage (main_hwnd, WM_COMMAND, defend_part, 0);
														}
													else
														{
															kpd_state=11;
															PostMessage (main_hwnd, WM_COMMAND, Check_Choice_Type, 0);

														}
													refresh_flag=1;
													
													

									   		}
											else
												{
												  PostMessage (main_hwnd, WM_COMMAND, Passwd_error, 0);
											   	   sleep(2);
												   memset(buf_show,0,sizeof(buf_show));
													PostMessage (main_hwnd, WM_COMMAND, Clen_buf, 0);
													memset(data_num,0,sizeof(data_num));
													data_pint=0;
											   	   PostMessage (main_hwnd, WM_COMMAND, Iput_usewd, 0);
												   goto START; 

												}
										}
										else if(num_ch == 20)
										{
											kpd_state=0;
											refresh_flag=1;
											if(kpd_state == 7)
												{	
												state=State_Un_Dfend;
												}
											PostMessage (main_hwnd, WM_COMMAND, ID_NEW, 0);
											

										}
								}
							else if(kpd_state == 8)
								{

										if(num_ch == 12)
		       							{

											if(data_pint==4)
												{
												if(data_num[3]==1)
													{
														
														
														defend_zone[def_num]=data_num[0]*100+data_num[1]*10+data_num[2];
														def_num++;
														PostMessage(main_hwnd,WM_COMMAND,Set_suc,0);
														//state=State_Pa_Dfend;
														inter_ser_flag=1;
													}
												else if(data_num[3]==2)
													{
														rec_num=data_num[0]*100+data_num[1]*10+data_num[2];
														for(i=0;i<def_num;i++)
															{
																if(rec_num == defend_zone[i])
																	{
																	num_flag=1;
																	}

																if(num_flag==1)
																	{
																	defend_zone[i]=defend_zone[i+1];

																	}

															}
														
														if(num_flag==1)
															{
																num_flag=0;
																def_num--;
															}

														for(i=0;i<def_num;i++)
															printf("defend_zone[i] is %d\n",defend_zone[i]);

														PostMessage(main_hwnd,WM_COMMAND,Set_suc,0);
														//state=State_Pa_Dfend;
														
													}
												else
													{
													
														PostMessage(main_hwnd,WM_COMMAND,Set_fal,0);
													}
												
										
												}
												else
													{
													
														PostMessage(main_hwnd,WM_COMMAND,Set_fal,0);
													}
												sleep(1);
												refresh_flag=1;
												PostMessage (main_hwnd, WM_COMMAND, defend_part, 0);

										}
										else if(num_ch == 20)
										{
											refresh_flag=1;
											if(inter_ser_flag==1)
												{
													state=State_Pa_Dfend;
													kpd_state=9;
													PostMessage (main_hwnd, WM_COMMAND, ret_defend_part, 0);
												}
											else
												{
													kpd_state=0;
													refresh_flag=1;
													state=State_Un_Dfend;
													PostMessage (main_hwnd, WM_COMMAND, ID_NEW, 0);

												}

										}
								}
							else if(kpd_state == 11)
								{
									if(num_ch == 12)
	       							{
										if(data_pint==1)
										{
											check_type=data_num[0];
											kpd_state = 12;
											refresh_flag=1;
											PostMessage (main_hwnd, WM_COMMAND, Check_Set_Time, 0);

								   		}
									}
									else if(num_ch == 20)
									{
										kpd_state=0;
										refresh_flag=1;
										PostMessage (main_hwnd, WM_COMMAND, ID_NEW, 0);
										

									}

								}
							else if(kpd_state == 12)
								{
									if(num_ch == 12)
									{
										if(data_pint == 4)
										{

											kpd_state=13;
										
											PostMessage (main_hwnd, WM_COMMAND, Check_Show_Date, 0);
											buzzer_run(1);
											usleep(500000);
											buzzer_run(0);

											buzzer_run(1);
											usleep(500000);
											buzzer_run(0);//jimmy ++ if  refresh_flag=1 go first  show_buf will be zero.
											refresh_flag=1;
										}
									}
									else if(num_ch == 20)
									{
										kpd_state=0;
										refresh_flag=1;
										PostMessage (main_hwnd, WM_COMMAND, ID_NEW, 0);
										

									}

								}
							else if(kpd_state == 13)
								{
									if(num_ch == 12)
										{
										
										PostMessage (main_hwnd, WM_COMMAND, Print_now, 0);
										sleep(2);
										PostMessage (main_hwnd, WM_COMMAND, Check_Show_Date, 0);
										

										}
									 if(num_ch == 20)
										{
											kpd_state=0;
											refresh_flag=1;
											PostMessage (main_hwnd, WM_COMMAND, ID_NEW, 0);
											

										}
									 else if(num_ch==15)
										{
											printf("Check_Show_up 15\n");
											if(check_point-9>0) 
												{
													PostMessage (main_hwnd, WM_COMMAND, Check_Show_up, 0);
												}
										}
									else if(num_ch==14)
										{
												if(check_point-9>0)
												{
													PostMessage (main_hwnd, WM_COMMAND, Check_Show_down, 0);

												}

										}
								}

								
								

								if(num_ch>=0 && num_ch<=9)
       							{
       								
       								if(kpd_state != 0 && kpd_state != 5   && kpd_state!=9 && kpd_state!=13)
       									{
									      if(data_pint>=14)
											{
												PostMessage (main_hwnd, WM_COMMAND, Clen_buf, 0);		
												memset(buf_show,0,sizeof(buf_show));
												memset(data_num,0,sizeof(data_num));
												data_pint=0;
											}
											else
											{
							
												PostMessage (main_hwnd, WM_COMMAND, 101, num_ch);	
												data_num[data_pint]=num_ch;
												data_pint++;
												
											}

       									}
									
								
									
										
								}
							else if(num_ch==13)
								{
								if(kpd_state!=5 && kpd_state!=6 && kpd_state!=7 && kpd_state!=8 && kpd_state!=9 )
									{
										memset(buf_show,0,sizeof(buf_show));
										PostMessage (main_hwnd, WM_COMMAND, Clen_buf, 0);
										memset(data_num,0,sizeof(data_num));
										data_pint=0;
										kpd_state=10;
										PostMessage (main_hwnd, WM_COMMAND, Iput_usewd, 0);
									}
								}
							
							else if(num_ch==16)
								{

								if(kpd_state!=5 && kpd_state!=6 && kpd_state!=7 && kpd_state!=8 && kpd_state!=9 )
									{
										memset(buf_show,0,sizeof(buf_show));
										PostMessage (main_hwnd, WM_COMMAND, Clen_buf, 0);
										memset(data_num,0,sizeof(data_num));
										data_pint=0;
										kpd_state=5;
										set_page=0;
										PostMessage (main_hwnd, WM_COMMAND, defend_set, 0);
										
									}

							}
							else if(num_ch==17)
								{ 
									//printf("kpd_state is %d  state is %d\n",kpd_state,state);
									if( (kpd_state==5 && state==State_Dfend) || (kpd_state==9 && state==State_Pa_Dfend))
										{
										PostMessage (main_hwnd, WM_COMMAND, Iput_usewd, 0);
										kpd_state=6;
										}
			

							}
							else if(num_ch==18)
								{
									if(kpd_state!=5 && kpd_state!=6 && kpd_state!=7 && kpd_state!=8 && kpd_state!=9)
									{
										memset(buf_show,0,sizeof(buf_show));
										PostMessage (main_hwnd, WM_COMMAND, Clen_buf, 0);
										memset(data_num,0,sizeof(data_num));
										data_pint=0;
										kpd_state=7;
										set_page=0;
										PostMessage (main_hwnd, WM_COMMAND, Iput_usewd, 0);
									}

							}
							

							if(refresh_flag==1)
							{
								DEBUG("clean the lcd\n");
							//	lcd_clean();
								memset(buf_show,0,sizeof(buf_show));
								PostMessage (main_hwnd, WM_COMMAND, Clen_buf, 0);
								memset(data_num,0,sizeof(data_num));
								data_pint=0;
							    refresh_flag=0;
							}

								
							
							put_time=0;	
				       		}
						}
		
				}
		}		


int SetSystemTime(char *dt)  
{  
    struct rtc_time tm;  
    struct tm _tm;  
	struct tm *tm24h = NULL;
    struct timeval tv;  
    time_t timep;  
	int  fd_time = 0;
	struct rtc_time rtc_tm;
	int retval;
	
    sscanf(dt, "%4d%2d%2d%2d%2d", &tm.tm_year,  
        &tm.tm_mon, &tm.tm_mday,&tm.tm_hour,  
        &tm.tm_min); 

 	DEBUG("%d,%d,%d,%d,%d\n", tm.tm_year,  
        tm.tm_mon, tm.tm_mday,tm.tm_hour,  
        tm.tm_min); 
        
	
    _tm.tm_sec = 0;  
    _tm.tm_min = tm.tm_min;  
    _tm.tm_hour = tm.tm_hour;  
    _tm.tm_mday = tm.tm_mday;  
    _tm.tm_mon = tm.tm_mon - 1;  
    _tm.tm_year = tm.tm_year - 1900;  
  
    timep = mktime(&_tm);  
    tv.tv_sec = timep;  
    tv.tv_usec = 0;  
    if(settimeofday (&tv, (struct timezone *) 0) < 0)  
    {  
    DEBUG("Set system datatime error!/n");  
    return -1;  
    }  
	DEBUG("8 houer befor \n");
	timep -= 8*60*60;
	tm24h = localtime(&timep);
	DEBUG("8 houer befor is：%dyear %02dmount %02dday,%02dhouer %02dmin %02ds\n",
				tm24h->tm_year+1900,tm24h->tm_mon,tm24h->tm_mday,
				tm24h->tm_hour,tm24h->tm_min,tm24h->tm_sec);

	
	fd_time = open ("/dev/rtc", O_RDONLY);
	
		if (fd_time<0) {
			DEBUG("\topen /dev/rtc faild!!!\n");
			DEBUG("Try tp open /dev/rtc0\n");
			fd_time = open ("/dev/rtc0", O_RDONLY);
	
			if (fd_time<0) {
				DEBUG("\topen /dev/rtc0 faild!!!\n");
				DEBUG("Try tp open /dev/misc/rtc\n");
				fd_time = open ("/dev/misc/rtc", O_RDONLY);
				
				if (fd_time<0) {
					DEBUG("\topen /dev/misc/rtc faild!!!\n");
					return -1; 
				}
				else
					DEBUG("\trtc is /dev/misc/rtc\n");
			}
			else
				DEBUG("\trtc is /dev/rtc0\n");
		}
		else
			DEBUG("\trtc is /dev/rtc\n");
			
		DEBUG("Input the adjust time1234:\n");
		
		rtc_tm.tm_year = tm24h->tm_year;
		rtc_tm.tm_mon = tm24h->tm_mon ;
		rtc_tm.tm_mday = tm24h->tm_mday;
		rtc_tm.tm_hour = tm24h->tm_hour;
		rtc_tm.tm_min = tm24h->tm_min;
		rtc_tm.tm_sec = tm24h->tm_sec;
		DEBUG("Input the adjust time456:\n");

	retval = ioctl(fd_time, RTC_SET_TIME, &rtc_tm);
	DEBUG("Input the adjust time789:\n");
		if (retval <0) {
			DEBUG("ioctl RTC_SET_TIME	faild!!!\n");
			return -1;
		}
	

		DEBUG("Adjust current RTC time as: %04d-%02d-%02d %02d:%02d:%02d\n\n",
		rtc_tm.tm_year + 1900,
		rtc_tm.tm_mon + 1,
		rtc_tm.tm_mday,
		rtc_tm.tm_hour,
		rtc_tm.tm_min,
		rtc_tm.tm_sec);
		DEBUG("Adjust current RTC time test OK!\n");
		
		 
		 close(fd_time);

	
    return 0;  
}
	void get_time(char * time_time)
		{

			//char *wday[]={"星期天","星期一","星期二","星期三","星期四","星期五","星期六"};
			time_t timep;
			time_t timep_start;
			time_t timep_end;
			struct tm *p;
			struct tm p_start;
			struct tm p_end;
			//static char time_temp_buf[30];
			//int static num_times=0;
			FILE* fp_time;
			static int laset_time_min;
			int i; 
			
			time(&timep);
			p=localtime(&timep); 

			sprintf(time_time,"%d年%02d月%02d日 %02d:%02d",(1900+p->tm_year),(1+p->tm_mon),p->tm_mday
			,p->tm_hour,p->tm_min);

			

		}
	
	
	void cur_time(char * time_time)
	{
	char *wday[]={"星期天","星期一","星期二","星期三","星期四","星期五","星期六"};
	time_t timep;
	time_t timep_start;
	time_t timep_end;
	struct tm *p;
	struct tm p_start;
	struct tm p_end;
	static char time_temp_buf[64];
	//int static num_times=0;
	FILE* fp_time;
	static int laset_time_min;
	static int dzwl_laset_time;
	int i; 
	
	time(&timep);// jimmy ++ test bug  there  ,it possible about RTC 
	p=localtime(&timep); 
	
	
	//DEBUG("%d年%02d月%02d日",(1900+p->tm_year),(1+p->tm_mon),p->tm_mday);
	//DEBUG("%s %02d:%02d:%02d\n",wday[p->tm_wday],p->tm_hour,p->tm_min,p->tm_sec);


	if(auto_dzwl_flag==1)
			{
			printf("dzwl\n");
			if(dzwl_laset_time!=p->tm_min)
				{
					if(p->tm_min == dzwl.start.tm_min && p->tm_hour == dzwl.start.tm_hour)
						{
							for(i=0;i<dzwl.opint;i++)
							{
								dzwl_set((char)dzwl.address[i],1);
							}
							
						}
					else if(p->tm_min == dzwl.end.tm_min && p->tm_hour == dzwl.end.tm_hour)
						{
							for(i=0;i<dzwl.opint;i++)
							{
								dzwl_set((char)dzwl.address[i],0);
							}

						}
					dzwl_laset_time=p->tm_min;
				}

			}

	
	if(auto_defend_flag==1)
		{
			printf("auto_defend\n");
			if(laset_time_min!=p->tm_min || time_change_flag==1)
				{
					if(time_change_flag==1)
						{
						time_change_flag=0;

						}
					p_start=*p;
					p_start.tm_hour=store.start.tm_hour;
					p_start.tm_min=store.start.tm_min;
					timep_start=mktime(&p_start);
					if(timep < timep_start)
						{
							//printf("defend 1 time %d\n",timep_start-timep);
							sprintf(time_temp_buf,"距设防还有%02d:%02d",(timep_start-timep)/3600,(timep_start-timep)/60%60);
							sprintf(time_time,"%d年%02d月%02d日 %s %02d:%02d %s",(1900+p->tm_year),(1+p->tm_mon),p->tm_mday,wday[p->tm_wday]
							,p->tm_hour,p->tm_min,time_temp_buf);
						}
					else if(timep ==timep_start)
						{
						printf("defend!!!\n");
						if(state!=State_Pa_Dfend && state!=State_Dfend)
							{
								if(store.opint==1 && store.address[0]==999)
									{
										memset(buf_show,0,sizeof(buf_show));
										PostMessage (main_hwnd, WM_COMMAND, Clen_buf, 0);
										memset(data_num,0,sizeof(data_num));
										data_pint=0;
										kpd_state=5;
										set_page=0;
										PostMessage (main_hwnd, WM_COMMAND, defend_set, 0);
									}
								else
									{
										def_num=0;
										for(i=0;i<store.opint;i++)
											{
												defend_zone[i]=store.address[i];
												def_num++;
											}
										state=State_Pa_Dfend;
										kpd_state=9;
										PostMessage (main_hwnd, WM_COMMAND, ret_defend_part, 0);
									}
				
							
							}
							sprintf(time_temp_buf,"正在设防中          ");
							sprintf(time_time,"%d年%02d月%02d日 %s %02d:%02d %s",(1900+p->tm_year),(1+p->tm_mon),p->tm_mday,wday[p->tm_wday]
							,p->tm_hour,p->tm_min,time_temp_buf);
						
						}
					else
						{
							p_end=*p;
							p_end.tm_hour=store.end.tm_hour;
							p_end.tm_min=store.end.tm_min;
							timep_end=mktime(&p_end);
							if(timep < timep_end)
								{
								//printf("undefend 1 time %d\n",timep_end-timep);
								sprintf(time_temp_buf,"距撤防还有%02d:%02d",(timep_end-timep)/3600,(timep_end-timep)/60%60);
									sprintf(time_time,"%d年%02d月%02d日 %s %02d:%02d %s",(1900+p->tm_year),(1+p->tm_mon),p->tm_mday,wday[p->tm_wday]
							,p->tm_hour,p->tm_min,time_temp_buf);
								}
							else if(timep ==timep_end)
								{

									if(state!=State_Un_Dfend )
									{
											printf("undefend!!!\n");
											state=State_Un_Dfend;
												
											memset(buf_show,0,sizeof(buf_show));
											PostMessage (main_hwnd, WM_COMMAND, Clen_buf, 0);
											memset(data_num,0,sizeof(data_num));
											data_pint=0;
											
											kpd_state = 0;
											PostMessage(main_hwnd,WM_COMMAND,ID_NEW,0);
									}
									sprintf(time_temp_buf,"正在撤防中          ");
								sprintf(time_time,"%d年%02d月%02d日 %s %02d:%02d %s",(1900+p->tm_year),(1+p->tm_mon),p->tm_mday,wday[p->tm_wday]
								,p->tm_hour,p->tm_min,time_temp_buf);

								
								}
							else
								{
								
								timep_start=timep_start+24*60*60;
								
								//printf("defend 2 time %d\n",timep_start-timep);
								sprintf(time_temp_buf,"距设防还有%02d:%02d",(timep_start-timep)/3600,(timep_start-timep)/60%60);
							sprintf(time_time,"%d年%02d月%02d日 %s %02d:%02d %s",(1900+p->tm_year),(1+p->tm_mon),p->tm_mday,wday[p->tm_wday]
							,p->tm_hour,p->tm_min,time_temp_buf);
								}
							

						}
					laset_time_min=p->tm_min;
					
				
						
				}
			else
				{
				sprintf(time_time,"%d年%02d月%02d日 %s %02d:%02d %s",(1900+p->tm_year),(1+p->tm_mon),p->tm_mday,wday[p->tm_wday]
							,p->tm_hour,p->tm_min,time_temp_buf);
				}
	
		}
	else
		{
			sprintf(time_time,"%d年%02d月%02d日 %s %02d:%02d                ",(1900+p->tm_year),(1+p->tm_mon),p->tm_mday,wday[p->tm_wday]
			,p->tm_hour,p->tm_min);
			
			
		}
	//printf("time len is %d\n",strlen(time_time));
		
	}



int buf_check(char * data_contain)
{

	DEBUG("data_contain is %s",data_contain);
	if(strcmp(data_contain,".01.") == 0)
	{
	    return 1;
	}
	else if(strcmp(data_contain,".02.") == 0)
	{
	    return 2;
	}

	return -1;
}

int print_punch(char * allbuf,int type,int mux_flag)
{
	char func[32];
	char date[32];
	char time[32];
	char addr[32];
	int i,j;
	 int ret; 

	  
	for(i=0;allbuf[i]!=' ';i++)
		{
		date[i]=allbuf[i];
		}
		date[i]='\0';

		i++;
	
	for(j=0;allbuf[i]!=' ';j++,i++)
		{
		time[j]=allbuf[i];
		}

		time[j]='\0';
		i++;


	if(type)
		{
		for(j=0;allbuf[i]!=' ';j++,i++)
			{
			addr[j]=allbuf[i];
			}
		
			addr[j]='\0';
			i++;

		}
		
	for(j=0;allbuf[i]!='\0';j++,i++)
		{
		func[j]=allbuf[i];
		}
	    func[j]='\0';

	//printf("func is %s\n",func);
	//printf("date is %s\n",date);
	//printf("time is %s\n",time);
	if(mux_flag==1)
		{
		pthread_mutex_lock(&Device_mutex);
		}
	//prin_flag=1;
	change_set(DATE ,1 );
	change_set(PRIN ,0 );
	change_set(MAP ,1 );
	ret=SPI_Init(0xc22d);
	//printf("ret is %x\n",ret);
	print_byte(0x1b);
	print_byte(0x38);
	if(type)
		{
		print_string(addr);
		print_byte(0x0a);
		}
	print_string(func);
	print_byte(0x0a);
	print_string(date);
	print_byte(0x0a);
	print_string(time);
	print_byte(0x0a);
	print_byte(0x0a);
	print_byte(0x0a);
	print_byte(0x0d);
	ret=SPI_Init(0xc42e);//0xc22e
	//printf("ret is %x\n",ret);
	change_set(DATE ,0 );
	change_set(PRIN,1 );
	change_set(MAP ,1 );
	if(mux_flag==1)
		{
		pthread_mutex_unlock(&Device_mutex);
		}
	
	//prin_flag=0;

}




int write_zj_alarm(int address,int manner,int mux_flag)
	{
		FILE*fp_w;
		char alarm_buffer[128]; 
		int i;
		char time_alarm[128];


		get_time(time_alarm);

		if(manner==ALARM)
			{
				sprintf(alarm_buffer,"%s %d防区报警  ",time_alarm,address);
			}
		else if(manner==Dfend)
			{
				sprintf(alarm_buffer,"%s 周界主机设防",time_alarm);

			}
		else if(manner==Part_Dfend)
			{
				sprintf(alarm_buffer,"%s 周界主机局设",time_alarm);
			}
		else if(manner==Withdraw)
			{
				sprintf(alarm_buffer,"%s 周界主机撤防",time_alarm);
			}
		else if(manner==Linedown)
			{
				sprintf(alarm_buffer,"%s %d防区掉线  ",time_alarm,address);
			}
		else if(manner==Zhq_down)
			{
				sprintf(alarm_buffer,"%s 转换器%d掉线  ",time_alarm,address);
			}


		printf("bufffer is:%s\n",alarm_buffer);

		
		if((fp_w=fopen("/mnt/nand1-1/config/zhoujie_record","r+"))==NULL)
			{
			printf("can not open the file.\n");
			return -1;
			}
		
		for(i=0;i<zj_line_num;i++)
			{
			fgets(time_alarm,sizeof(time_alarm),fp_w);
			}

		
		fputs(alarm_buffer,fp_w);
		fputs("\n",fp_w);
		zj_line_num++;


		if(zj_line_num>1000)
			{
			zj_line_num=0;
			}

		
		fclose(fp_w);


		if(print_flag==1)
			{
			print_punch(alarm_buffer,0,mux_flag);

			}

	}



int whether_alarm(char rec_ch)
{
	int ret;
	char erg_addr[10];
	FILE *pFile=NULL;
	int i;
	
	if(wirte_erg_flag==1)
		{
		 erg_num=0;
		 pFile=fopen("/mnt/nand1-1/config/erg_address","r");
		 if(pFile!=NULL)    
		 	{    	
			 	while(!feof(pFile))			
					{					
					memset(erg_addr  , 0 , sizeof(erg_addr) ); 
					fgets(erg_addr ,  sizeof(erg_addr)  , pFile );    	
				//	printf("buf len is %d!!\n",strlen(erg_addr));
									
					if(erg_num<200 && strlen(erg_addr)>0)
						{
						 erg_zone[erg_num]=atoi(erg_addr); 	
						 printf("erg_zone[erg_num] is %d\n",erg_zone[erg_num]);
					 	 erg_num++;
						
						}
					}   		
				fclose(pFile);
			
			
			}
		 wirte_erg_flag=0;

		}

	for(i=0;i<erg_num;i++)
		{
			if(erg_zone[i]==rec_ch)
				{
					DEBUG("baojing alarm");
					sprintf(alarm_date,"        电子围栏 %d防区报警",rec_ch);
					PostMessage (main_hwnd, WM_COMMAND, alarm_come, 0);
					alarm_flag=1;
					write_zj_alarm((int)rec_ch,ALARM,0);
					return 1;
				}
		}

	if(state==State_Dfend)
		{
			DEBUG("baojing alarm");
			/*	
			if(alarm_window==0)
				{
			
				child_hwnd=CreateWindowEx(0L, APPCHILD, "", WS_BORDER | WS_VISIBLE,130-1,153-1, 500, 300,		NULL, (HMENU)1000, NULL, NULL);
				//SetFocus(child_hwnd);
				alarm_window=1;
				}
			else
				{
				
				}*/
				
				sprintf(alarm_date,"        电子围栏 %d防区报警",rec_ch);
				PostMessage (main_hwnd, WM_COMMAND, alarm_come, 0);
				alarm_flag=1;
				write_zj_alarm((int)rec_ch,ALARM,0);
			return 1;

		}
	else if(state==State_Pa_Dfend)
		{
		for(i=0;i<def_num;i++)
			{
			DEBUG("defend_zone[i] is %d",defend_zone[i]);
			if(defend_zone[i]==rec_ch)
				{
					DEBUG("baojing Pa_Dfend alarm");
					sprintf(alarm_date,"        电子围栏 %d防区报警",rec_ch);
					PostMessage (main_hwnd, WM_COMMAND, alarm_come, 0);
					alarm_flag=1;
					write_zj_alarm((int)rec_ch,ALARM,0);
					return 1;
				}

			}

		}
	else
		{
		
		DEBUG("baojing not alarm");
		

		}

	return -1;

	 

}


int check_send_messg(char address)
{
	pthread_mutex_lock(&Device_mutex);
	 SPI_write(0xdf,1);
     //usleep(1000000);
     SPI_write(0,0);
    // usleep(1000000);
     SPI_write(0,0);
     //usleep(1000000);
     SPI_write(address,0);
    // usleep(1000000);
     SPI_write(0x0a,0);
	 pthread_mutex_unlock(&Device_mutex);

}

int check_if_linedown(char address)
{
	printf(" alarm ok\n");
								
	sprintf(alarm_date,"		电子围栏 %d防区掉线",address);
	PostMessage (main_hwnd, WM_COMMAND, alarm_come, 0);
	alarm_flag=1;
	write_zj_alarm((int)address,Linedown,1);


}








void check_device_fun()
{
	int ret;
	char device_add[100][10];	
	int  device_point=0;	
	unsigned char a,b,c;
	int i;
	FILE *pFile=NULL;	
	
	while(1)
		{
		//printf("check_device_fun\n");
		DEV_START:

		pFile=fopen("/mnt/nand1-1/config/device_address","r");	
		device_point=0;
		if(pFile!=NULL)    
			{		
			//printf("open the file\n");
			while(!feof(pFile)) 		
				{					 
					memset(device_add[device_point]  , 0 , sizeof(device_add[device_point]) );			 
					fgets( device_add[device_point] ,  sizeof(device_add[device_point])  , pFile ); 

					//printf("len is %d\n",strlen(device_add[device_point]));
					/*
					if(strlen(device_add[device_point])<3)
						{
						fclose(pFile);		
						printf("check_device sleep\n");
						sleep(10);
						goto DEV_START;
						}*/
					if(strlen(device_add[device_point])>0)
						{
							printf("check_device num is %d\n",strlen(device_add[device_point]));
							device_point++; 		
						}
					
					 if(device_point>=100)				
						{					
						//return -1;		
						break;
						}			
				}		
			
			fclose(pFile);	

			if(device_point==0)
				{
					printf("check_device sleep\n");
					sleep(10);
					goto DEV_START;

				}

		

		for(i=0;i<device_point;i++)
			{
				a=(device_add[i][0]-'0')*100+(device_add[i][1]-'0')*10+(device_add[i][2]-'0');
				//a=65;


				// printf("zj_delay a is %d\n",zj_delay);
				if(zj_delay>=10)
			    sleep(zj_delay);
				else
				sleep(10);
				//jimmy

				//if(prin_flag==0)

					{
						check_send_messg(a);


						printf("send a is %x\n",a);

						rec_device_check_flag=1;				 
						sleep(1);

						if(rec_device_check_flag==2)
							{
							if(rec_device_address==a)
								{
								printf(" rec ok\n");

								}
							else
								{
								check_send_messg(a);
								rec_device_check_flag=1;				 
								sleep(1);
								if(rec_device_check_flag==2)
								{
								if(rec_device_address==a)
								{
								printf(" rec ok\n");

								}
								else
								{
								check_if_linedown(a);

								}
								rec_device_address=0;
								}
								else
								{
								check_if_linedown(a);

								}


								}
								rec_device_address=0;
							}
						else
							{
							check_send_messg(a);
							rec_device_check_flag=1;				 
							sleep(1);
							if(rec_device_check_flag==2)
								{
								if(rec_device_address==a)
									{
									printf(" rec ok\n");

									}
								else
									{
									check_if_linedown(a);

									}
								rec_device_address=0;
								}
							else
								{
								check_if_linedown(a);

								}

							}

						rec_device_check_flag=0;
			 		}
				//check if come 
			}
		} 
		else
			{
			sleep(10);
		}


				

		

		}
}


void check_device_precess()
{
	pthread_t pid_snj;


	if (pthread_create(&pid_snj,NULL,check_device_fun,NULL)!=0) {
				   printf("init_time_check_kapd Create thread error!\n");
				   //exit(1);
			   }
	pthread_detach(pid_snj);

}



int max3100_init()
{
	int ret=0;
	char ch=0;
	int testdev;
	char buf[128];
	char buff_rec[128];
	int num_flag=0;
	int read_flag=1;
	DEBUG("max3100dev\n");
    
    testdev = open("/dev/max3100dev", O_RDWR); 

	if (-1 == testdev) {
		printf("cannot open file.\n");
		exit(1);
	}
		
	pthread_mutex_init(&Device_mutex,NULL);
     max3100_gpio_init();
	 
     print_gpio_init();
     change_gpio_init();
     ret=SPI_Init(0xc42e);//0xc22e
	 printf("ret is %x\n",ret);
     change_set(DATE ,0 );
     change_set(PRIN,1 );
     change_set(MAP ,1 );


	 
 while(1)
 {
    ret =read(testdev,buf,sizeof(buf));
	pthread_mutex_lock(&Device_mutex);
	if(ret>0)
		{
		read_flag=1;
		num_flag=0;
		DEBUG("buf is %s\n",buf);	
		
		
		//for(ret=0;ret<6;ret++)
		
	
		while(read_flag)
		{
		
			ch=0;
			ch=SPI_read(&read_flag);

			//printf("ch2 is %x\n",ch);
			//printf("num_flag is %d\n",num_flag);
	
			if(ch == 0xbd)
			{
				num_flag=0;
				buff_rec[num_flag]=ch;
				num_flag++;
				continue;
			}	
			else if(ch == 0xdb)
			{
				num_flag=0;
				buff_rec[num_flag]=ch;
				num_flag++;
				continue;
			}
			else
			{
				if(num_flag > 0)
					{
					buff_rec[num_flag]=ch;
					num_flag++;
					}
				else
					{
					continue;
					}

		

			
			if(buff_rec[0]==0xbd && num_flag==6 )
				{

				
						switch(buff_rec[5])
						{
						/*
						case  0xaa ://she_fang
						printf("she_fang\n");
						SPI_write(0xab,1);
						break;
						case  0xbb ://ju_she
						printf("ju_she\n");
						SPI_write(0xab,1);
						break;
						case  0xcc ://che_fang
						printf("che_fang\n");
						SPI_write(0xab,1);
						break;
						case  0x09 ://qiu_zu
						printf("qiu_zu\n");
						SPI_write(0xab,1);
						//goto PRRR;
						break;*/
						case  0xa1 ://fang_chai
						printf("wei_lan fang_chai\n");
						//SPI_write(0xab,1);
						break;
						case  0xa2 ://qian_ya
						printf("wei_lan qian_ya\n");
						//SPI_write(0xab,1);
						break;
						case  0xa3 ://pan_pa
						printf("wei_lan pan_pa\n");
						//SPI_write(0xab,1);
						break;
						case  0xff ://bao_jin
						printf("wei_lan baojin\n");
						//SPI_write(0xab,1);
						whether_alarm( buff_rec[3]);
						break;

						}
					
					num_flag=0;
					continue;
				}
			
			else if(buff_rec[0]==0xdb && num_flag==5 )
				{
					printf("wei_lan check\n");
					num_flag=0;
					if(rec_device_check_flag==1)
						{
							rec_device_address=buff_rec[3];
							rec_device_check_flag=2;
						}
					continue;
				}
	
			
			if(read_flag==0)
				{
					num_flag=0;
					continue;
				}
			
			}
			

				
			
		} 		
	}
	pthread_mutex_unlock(&Device_mutex);
}	
	
		

  
pthread_mutex_destroy(&Device_mutex);






		 

}

int zhq_rec_message(){
  int s;
  int ret;
  int size;
  int ttl=1;//
  int loop=0;
  int times=0;
  char *cr_opint;
  char all_buffer[128];
  char show_buffer[64];
  char buffer[64];
   char str[64];
   char time[64];
   char right_buffer[8][64];
   int  right_num=0;
   int  right_show_num=0;
   int i;
   static int right_flag=0;
  struct sockaddr_in localaddr,fromaddr;//多播地址结构
 //建立套接字
  s=socket(AF_INET,SOCK_DGRAM,0);
  if(s<0){
   perror("socket error");
    return -1;
  }
  //多播的地址结构
  localaddr.sin_family=AF_INET;
  localaddr.sin_port=htons(MCAST_PORT_ZJ);//多播端口号
  localaddr.sin_addr.s_addr=htonl(INADDR_ANY);//接收任意地址发送的数据
 /*
	 if(inet_pton(AF_INET,MCAST,&localaddr.sin_addr)<0)
	{
	printf("fail to convert\n");
	exit(1);
	}*/
 //绑定地址结构到套接字
 ret=bind(s,(struct sockaddr*)&localaddr,sizeof(localaddr));//客户端需要绑定端口，用来接收服务器的数据，得指定接收端口，因为数据先从服务器发送过来的
if(ret<0){
  perror("bind error");
  return -1;
}
 //设置多播的TTL值
 if(setsockopt(s,IPPROTO_IP,IP_MULTICAST_TTL,&ttl,sizeof(ttl))<0){
    perror("IP_MULTICAST_TTL");
    return -1;
  }

//设置数据是否发送到本地回环接口
if(setsockopt(s,IPPROTO_IP,IP_MULTICAST_LOOP,&loop,sizeof(loop))<0){
  perror("IP_MULTICAST_LOOP");
  return -1;
 }
//客户端加入多播组
 struct ip_mreq mreq;
 mreq.imr_multiaddr.s_addr=inet_addr(MCAST_ADDR_ZJ);//多播组的IP
 mreq.imr_interface.s_addr=htonl(INADDR_ANY);//本机的默认接口IP
if(setsockopt(s,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq))<0){
  perror("IP_ADD_MEMBERSHIP");
  return -1;
}

//循环接收多播组的消息，5次退出
while(1){
  int len=sizeof(fromaddr);
  memset(buffer,0,sizeof(buffer));
  size=recvfrom(s,buffer,1024,0,(struct sockaddr*)&fromaddr,&len);
 if(size<0){
   perror("recvfrom ");
  return -1;
 }

 if(jiafang_state_flag==1)
 	{
 printf("receive message:%s\n",buffer);
// printf("Port is:%d\n",fromaddr.sin_port);
 if (inet_ntop(AF_INET, &fromaddr.sin_addr, str, sizeof(str)) == NULL)
		 	{
			printf("inet_ntop error\n");
			continue;
		 	}
		printf("ip address is:%s\n",str);	
			cr_opint=str;
		for(;*cr_opint!='.';cr_opint++);
		cr_opint++;
		for(;*cr_opint!='.';cr_opint++);
		
		get_time(time);
		if(cr_opint[1]=='7')
			{
			    sprintf(all_buffer,"%s %c%c%c防区%s",time,cr_opint[3],cr_opint[4],cr_opint[5],buffer);
			  sprintf(show_buffer,"      %c%c%c防区%s",cr_opint[3],cr_opint[4],cr_opint[5],buffer);
				
			}
		else if(cr_opint[1]=='8')
			{
			  sprintf(all_buffer,"%s %c%c%c防区%s",time,cr_opint[3]+2,cr_opint[4],cr_opint[5],buffer);
			  sprintf(show_buffer,"      %c%c%c防区%s",cr_opint[3]+2,cr_opint[4],cr_opint[5],buffer);

			}
		else if(cr_opint[1]=='9')
			{
			  sprintf(all_buffer,"%s %c%c%c防区%s",time,cr_opint[3]+4,cr_opint[4],cr_opint[5],buffer);
		      sprintf(show_buffer,"      %c%c%c防区%s",cr_opint[3]+4,cr_opint[4],cr_opint[5],buffer);

			}
		printf("bufffer is:%s\n",all_buffer);
		if((strstr(show_buffer, "报警")) != NULL)
			{	
				strcpy(alarm_date,show_buffer);
				PostMessage (main_hwnd, WM_COMMAND, alarm_come, 0);
				alarm_flag=1;
				
					
			}
		else
			{
				if(kpd_state!=1 && kpd_state!=2 && kpd_state!=3 && kpd_state!=6 && kpd_state!=7 && kpd_state!=8
					&& kpd_state!=10 && kpd_state!=11 && kpd_state!=12 && kpd_state!=13)
					{
					if(right_num>=8)
						{
						right_num=0;
						right_flag=1;

						}
					sprintf(right_buffer[right_num],"%c%c%c防区",cr_opint[3]+2,cr_opint[4],cr_opint[5]);
					strcpy(right_buffer[right_num+1],buffer);
				
						printf("right_num is %d %s",right_num,right_buffer[right_num+1]);

						if(right_flag==1)
							{
								right_show_num=right_num+2;

									for(i=0;i<8;i=i+2)
									{
									if(right_show_num>=8)
										{
										right_show_num=0;

										}
									
									DrawText(hdc,right_buffer[right_show_num], -1, &rect_right[i], DT_WORDBREAK );
									DrawText(hdc,right_buffer[++right_show_num], -1, &rect_right[i+1], DT_WORDBREAK );
									right_show_num++;
									

									}

									
							}
						else
							{

								for(i=0;i<8;i++)
									{			
									DrawText(hdc,right_buffer[i], -1, &rect_right[i], DT_WORDBREAK );
									}

							}
						
					
					

					right_num+=2;



					}
			}
		write_to_file(all_buffer);
 	}

		
// size=sendto(s,"OK",2,0,(struct sockaddr*)&fromaddr,sizeof(fromaddr));//向服务器发送数据,向服务器指定的IP与端口发送数据
}

//离开多播组
ret=setsockopt(s,IPPROTO_IP,IP_DROP_MEMBERSHIP,&mreq,sizeof(mreq));
if(ret<0){
  perror("IP_DROP_MEMBERSHIP");
  return -1;
}
close(s);
return 0;

}



int Thread_net()
{
		pthread_t id_rec;
		int ret=0;
	//int ret;
		int send_sockt;

		char buffer[8];
		struct sockaddr_in Multi_addr;//多播地址
		struct sockaddr_in client_addr;
	
		 ret = pthread_create(&id_rec,NULL, (void*)zhq_rec_message, NULL);
		 if (ret)
		 {
			 printf("Create pthread error!/n");
			 return -1;
		 } 
	
	
	
			//#ifdef ZHU_JI
							
			if(zhufu_num==1)
				{
						send_sockt=socket(AF_INET,SOCK_DGRAM,0);//建立数据报套接字
						if(send_sockt<0){
							perror("socket error");
							return -1;
						}
						Multi_addr.sin_family=AF_INET;
						Multi_addr.sin_port=htons(MCAST_PORT_ZH);//多播端口
						Multi_addr.sin_addr.s_addr=inet_addr(MCAST_ADDR_ZH);//多播地址
				

						for(;;){
								
								memset(buffer,0,sizeof(buffer));
								sprintf(buffer,"%d",jfcycle_num);
								//printf("sendto\n");
								int size=sendto(send_sockt,buffer,strlen(buffer),0,(struct sockaddr*)&Multi_addr,sizeof(Multi_addr));
								
								if(size<0){
									perror("sendto error");
									//system("route add -net 224.0.0.0 netmask 224.0.0.0 eth0");
								}
								//printf("sleep\n");
								sleep(30);
								comparison_address();

							
						       }
						close(send_sockt);
				}
			//#endif


}

LRESULT CALLBACK wproc(HWND,UINT,WPARAM,LPARAM);


LRESULT CALLBACK
ChildWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	RECT		rc;


	HDC alwid;

	HDC hdcMem,mydc; 
	HBITMAP hbmp, hbmpOrg;
	HBRUSH hbr;
	PAINTSTRUCT ps;
	RECT rect;
	HGDIOBJ oldfont; 
	HWND sibwp;  
	extern int mwpaintSerial; 
	static HANDLE font_chinese;  
	int num_time=0; 
	char num_change;
	int delay_time=0; 
	char * HeadPoint=NULL;
	int mkj_num=0;
	int i;



	printf("ChildWndProc\n");
	switch(msg) {
	 case WM_CREATE:
		font_chinese=CreateFont(48,
							48,0,0,0,0,0,0,0,0,0,0,
							FF_DONTCARE|DEFAULT_PITCH,
							"HZKFONT");
			break;
	case WM_PAINT:



			alwid=BeginPaint(hwnd, &ps);
		
			GetClientRect(hwnd, &rect);

			hdcMem = CreateCompatibleDC(ps.hdc);
			hbmp = CreateCompatibleBitmap(hdcMem, rect.right, rect.bottom);
			hbmpOrg = SelectObject(hdcMem, hbmp);

			hbr = (HBRUSH)GetClassLong(hwnd, GCL_HBRBACKGROUND);
			FillRect(hdcMem, &rect, hbr);
			//SelectObject(hdcMem, GetStockObject(DEFAULT_GUI_FONT));
			SetBkMode(hdcMem, TRANSPARENT);
		
			
				   oldfont=SelectObject(alwid,font_chinese);
				   SetBkColor(alwid, RGB(100,149,237));	
		
			
		
					
		
								
		
		
				   // DEBUG("tm.tmHeight is %d	tm.tmAveCharWidth is %d\n",tm.tmHeight,tm.tmAveCharWidth);
		
				
					//SetRect(&rect,20,150,20+200,150+ 20);
				   
		
					DrawText(alwid, "欢迎使用跃天周界主机", -1, &rect,DT_WORDBREAK  );
							
					mydc=GetDC(hwnd);
		
					DrawDIB(mydc, 570, 15, &image_logo);
					ReleaseDC(hwnd,mydc);
		
					DeleteObject(SelectObject(hdcMem, hbmpOrg));  
					DeleteDC(hdcMem);  
		break;
	default:
		return DefWindowProc( hwnd, msg, wp, lp);
	}
	return( 0);
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   PSTR szCmdLine, int iCmdShow)
{
	

        static char szAppName[]="HolaWin";
    
        int ret=0;
		char get_buf[10];
        MSG msg;
        WNDCLASS wndclass;

		int width, height;
		RECT r;
		static int nextid = 0;
		pthread_t id_max3100;
		pthread_t id_kp;
		pthread_t id_time;
		pthread_t id_net;

	    struct sched_param param;
		 pthread_attr_t attr;

		 


	    MwRegisterButtonControl(NULL);
		MwRegisterEditControl(NULL);
		MwRegisterListboxControl(NULL);
		MwRegisterProgressBarControl(NULL);
		GetWindowRect(GetDesktopWindow(), &r);
		
		width = height = r.right / 2;
        wndclass.style          = CS_DBLCLKS |CS_HREDRAW | CS_VREDRAW;
        wndclass.lpfnWndProc    = (WNDPROC)wproc;
        wndclass.cbClsExtra     =0;
        wndclass.cbWndExtra     =0;
        wndclass.hInstance      =0;
        wndclass.hIcon          =0;
        wndclass.hCursor        =0;
        wndclass.hbrBackground  =(HBRUSH)GetStockObject(WHITE_BRUSH);//DKGRAY_BRUSH
        wndclass.lpszMenuName   =NULL;
        wndclass.lpszClassName  = szAppName;

        RegisterClass(&wndclass);

		wndclass.lpfnWndProc = (WNDPROC)ChildWndProc;
		wndclass.lpszClassName =  APPCHILD;
		RegisterClass( &wndclass);


		

		//MwSetDesktopWallpaper(&image_car8);
		
		UpdateWindow(GetDesktopWindow()); 

        main_hwnd=CreateWindowEx(WS_EX_LAYERED,//0L,
                          szAppName,
                          "",
                         // WS_OVERLAPPEDWINDOW | WS_VISIBLE,
							WS_VISIBLE,
						  0,//CW_USEDEFAULT,
                          0,//CW_USEDEFAULT,
                          //width,	
                          //height,	
					      800,480,
						  NULL,
                          (HMENU)++nextid,
							//(HMENU)1,
						  NULL,
                          NULL);

		
			if(init_device_kapd()<0) {
			DEBUG("init error\n");
			return -1;
			}  
		//jimmy +++ uart speed
			//init_uart();

			//init_equipmnet();
			//sound_gpio_init();
			//sound_gpio_set(0);

			//gpio_init();

		
			buzzer_gpio_init();
		
			//heart_search_init();
			read_defend_file();
			read_file_line();
			read_file("/mnt/nand1-1/config/printf_state",get_buf);
			print_flag=atoi(get_buf);
			read_file("/mnt/nand1-1/config/jiafang_state",get_buf);
			jiafang_state_flag=atoi(get_buf);
			read_file("/mnt/nand1-1/config/jiafang_time",get_buf);
			jfcycle_num=atoi(get_buf);
			read_file("/mnt/nand1-1/config/zj_check_time",get_buf);
			zj_delay=atoi(get_buf);
			read_file("/mnt/nand1-1/config/num",get_buf);
			zhufu_num=atoi(get_buf);
			
			
		//	printf("print_flag is %d\n",print_flag);

			
			


		ret = pthread_create(&id_kp,NULL, (void*)Thread_kp, NULL);
				if (ret)
				{
				DEBUG("Create pthread error!/n");
				return 1;
				} 
	

		printf("jimmy test 1\n");
		ret = pthread_create(&id_time,NULL, (void*)Thread_time, NULL);
				if (ret)
				{
				DEBUG("Create pthread error!/n");
				return 1;
				} 
		

	


		pthread_attr_init(&attr);
		param.sched_priority = 50;
		pthread_attr_setschedpolicy(&attr,SCHED_RR);
		pthread_attr_setschedparam(&attr,&param);
		pthread_attr_setinheritsched(&attr,PTHREAD_EXPLICIT_SCHED);

		//ret = pthread_create(&id_max3100,NULL, (void*)max3100_init, NULL);
		ret = pthread_create(&id_max3100,&attr, (void*)max3100_init, NULL);
				if (ret)
				{
				DEBUG("Create pthread error!/n");
				return 1;
				} 


	

		ret = pthread_create(&id_net,NULL, (void*)Thread_net, NULL);
				if (ret)
				{
				DEBUG("Create pthread error!/n");
				return 1;
				} 

				
	if(zhufu_num==1)
		{

		//#ifdef ZHU_JI
		heart_search_init();
		//#endif
	
			
		check_device_precess();
		}
		
					

        while (GetMessage(&msg,NULL,0,0)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
				//DEBUG("GetMessage\n");
        }      
	

        return msg.wParam;
}       
HWND edit; //jimmy ?????

RECT rect_log[9];

RECT rect_top;




LRESULT CALLBACK wproc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{       
		
		HDC hdcMem,mydc; 
		HBITMAP hbmp, hbmpOrg;
		HBRUSH hbr;
        PAINTSTRUCT ps;
        RECT rect;
		HGDIOBJ oldfont; 
     	HWND sibwp;  
		extern int mwpaintSerial; 
		static HANDLE font_chinese;  
		
		int num_time=0; 
		char buf_showtime[200]; 
		char num_change;
		char buf_num[50];
		int delay_time=0; 
		char * HeadPoint=NULL;
		int mkj_num=0;
		int data_num_show;
		int i;
		static char check_time[20];
		char check_buf[100];
		FILE*fp_check ;
		static int show_num;
		//char * pHeadPtr;


        static char widName[]="alarmWin";
    
       // printf("fatherwproc!!!!!!\n");
		switch (iMsg) {
		case WM_ERASEBKGND:
		/* don't erase with screen dc, must alpha blend bkgnd*/
			return 1;
        case WM_CREATE:
			//hzks = 1;

   //close by jimmy for test

	//	SetTimer(hwnd, ID_TIMER, 1000, NULL);  
			
		font_chinese=CreateFont(48,
							48,0,0,0,0,0,0,0,0,0,0,
							FF_DONTCARE|DEFAULT_PITCH,
							"HZKFONT");


			
			break;
			  
		case WM_PAINT:

		printf("father \n");

		mwforceNCpaint = TRUE;
		/* repaint lower windows before alpha blending this window*/
		++hwnd->unmapcount; /* tricky don't clip this window*/
		SendMessage(rootwp, WM_PAINT, 0, 0);
		for(sibwp=hwnd->siblings; sibwp; sibwp=sibwp->siblings)
		SendMessage(sibwp, WM_PAINT, 0, 0);
		--hwnd->unmapcount;
		/* then queue repaint for higher windows*/
		for(sibwp=hwnd->parent->children; sibwp != hwnd;
		sibwp=sibwp->siblings)
		/* don't paint if already painted by above code*/
		if(sibwp->paintSerial != mwpaintSerial)
		PostMessage(sibwp, WM_PAINT, 0, 0);
		/* now paint this window offscreen and blend with screen*/
		hdc=BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		/* redirect painting to offscreen dc*/
		hdcMem = CreateCompatibleDC(ps.hdc);
		hbmp = CreateCompatibleBitmap(hdcMem, rect.right, rect.bottom);
		hbmpOrg = SelectObject(hdcMem, hbmp);
		/* paint window to offscreen*/
		
		hbr = (HBRUSH)GetClassLong(hwnd, GCL_HBRBACKGROUND);
		FillRect(hdcMem, &rect, hbr);
		//SelectObject(hdcMem, GetStockObject(DEFAULT_GUI_FONT));
		SetBkMode(hdcMem, TRANSPARENT);

		

               DEBUG("flag_connect is %d\n",flag_connect);
			   oldfont=SelectObject(hdc,font_chinese);
			   SetBkColor(hdc, RGB(100,149,237));	

				if(flag_connect == 0)
					{
		

				for(num_time=0;num_time<9;num_time++)
			   {
		   //  fgets(buf_log,sizeof(buf_log),fp_log);
			   SetRect(&rect_log[num_time],20,150+32*num_time,20+200,150+20+32*num_time);
			   DrawText(hdc,"                                           ", -1, &rect_log[num_time], DT_WORDBREAK );

			   }
				

	             for(num_time=0;num_time<9;num_time++)
			  {

			  SetRect(&rect_right[num_time],540,150+32*num_time,540+80,150+20+32*num_time);
			  DrawText(hdc,"                ", -1, &rect_right[num_time], DT_WORDBREAK );

			  }             
   

			   // DEBUG("tm.tmHeight is %d  tm.tmAveCharWidth is %d\n",tm.tmHeight,tm.tmAveCharWidth);

			
				//SetRect(&rect,20,150,20+200,150+ 20);
			   

				DrawText(hdc, "欢迎使用跃天周界主机", -1, &rect_log[0],
						 DT_WORDBREAK  );
			
			  cur_time(buf_showtime);
			  SetRect(&rect_top, 10,20+80,10+500,10+40);
			  DrawText(hdc,buf_showtime, -1, &rect_top, DT_WORDBREAK );
			  
				edit=CreateWindowEx(0L, "EDIT",
					"",
					WS_BORDER|WS_CHILD | WS_VISIBLE,//WS_VISIBLE,WS_DISABLED
					10, 10, 500, 80,
					hwnd, (HMENU)200, NULL, NULL);


			//	EndPaint(hwnd,&ps);
				
					}
				else
					{
					cur_time(buf_showtime);
					DrawText(hdc,buf_showtime, -1, &rect_top, DT_WORDBREAK );

					}
				
				mydc=GetDC(hwnd);

				DrawDIB(mydc, 570, 15, &image_logo);
				ReleaseDC(hwnd,mydc);

				DeleteObject(SelectObject(hdcMem, hbmpOrg));  
				DeleteDC(hdcMem);  

                break;

		      case WM_TIMER:  
			  	
		
       			break;  
				
			case WM_COMMAND:

				//DEBUG("WM_COMMAND %d\n",wParam);
				switch(LOWORD(wParam))
				{
					case 101:
						
						DEBUG("101\n");
						//DEBUG("WM_COMMAND LOWORD %d\n",LOWORD(lParam));
                       if(strlen(buf_show)<14)
								{
									num_change=LOWORD(lParam)+'0';
									buf_show[strlen(buf_show)]=num_change;
									buf_show[strlen(buf_show)+1]='\0';
								}
							SetWindowText(edit, buf_show);
		
						break;
				
					case 110:
						DEBUG("110\n");
					
						break;
					case Function_set ://111:
						DEBUG("111\n");
						
						break;
						
					case Change_time ://125:
						//DEBUG("111\n");			
						cur_time(buf_showtime);
						//jimmy
						
						DrawText(hdc,buf_showtime, -1, &rect_top, DT_WORDBREAK );
						break;
					case 112:
						DEBUG("112\n");
					
						break;
						
				  case Iput_pw://121:
					
				  DEBUG("121\n");
				  for(num_time=0;num_time<9;num_time++)
						{       
						DrawText(hdc, "                                                  ", -1, &rect_log[num_time], DT_WORDBREAK );
						}
						DrawText(hdc,"请输入管理密码", -1, &rect_log[0], DT_WORDBREAK );
						laset_state=LOWORD(wParam);
						break;

						
				  case Pass_pw://122:
					
				  DEBUG("122\n");
				  
				  for(num_time=0;num_time<9;num_time++)
						{
						DrawText(hdc, "                                           ", -1, &rect_log[num_time], DT_WORDBREAK );
						}
						
						if(zhufu_num==1)
							{
								DrawText(hdc,"进入设置模式", -1, &rect_log[0], DT_WORDBREAK );
								DrawText(hdc,"1 防区类型               9 恢复出厂设置", -1, &rect_log[1], DT_WORDBREAK );
								DrawText(hdc,"2 时间设定               10管理密码修改", -1, &rect_log[2], DT_WORDBREAK );
								DrawText(hdc,"3 延时设定               11用户密码修改", -1, &rect_log[3], DT_WORDBREAK );
								DrawText(hdc,"4 自动布撤防             12家防设置", -1, &rect_log[4], DT_WORDBREAK );
								DrawText(hdc,"5 防区巡检周期设定       13家防巡检周期设定", -1, &rect_log[5], DT_WORDBREAK );
								DrawText(hdc,"6 打印设定", -1, &rect_log[6], DT_WORDBREAK );
								DrawText(hdc,"7 电子围栏手动切换", -1, &rect_log[7], DT_WORDBREAK );
								DrawText(hdc,"8 电子围栏自动切换", -1, &rect_log[8], DT_WORDBREAK );
							}
						else
							{
								DrawText(hdc,"进入设置模式", -1, &rect_log[0], DT_WORDBREAK );
								DrawText(hdc,"1 防区类型               6 恢复出厂设置", -1, &rect_log[1], DT_WORDBREAK );
								DrawText(hdc,"2 时间设定               7 管理密码修改", -1, &rect_log[2], DT_WORDBREAK );
								DrawText(hdc,"3 延时设定               8 用户密码修改", -1, &rect_log[3], DT_WORDBREAK );
								DrawText(hdc,"4 自动布撤防             9 家防设置    ", -1, &rect_log[4], DT_WORDBREAK );
								DrawText(hdc,"5 打印设定                             ", -1, &rect_log[5], DT_WORDBREAK );


							}
						laset_state=LOWORD(wParam);
						break;
					case Clen_buf://128:
				
					DEBUG("128\n");

					SetWindowText(edit, "");
					break;
				case Set_suc://126:
					
				  DEBUG("126\n");
				  for(num_time=0;num_time<9;num_time++)
						{
						DrawText(hdc, "                                           ", -1, &rect_log[num_time], DT_WORDBREAK );
						}
			 			DrawText(hdc,"设置成功", -1, &rect_log[0], DT_WORDBREAK );
		
					break;
					
				case Set_fal://127:
					
				  DEBUG("127\n");
				  for(num_time=0;num_time<9;num_time++)
						{
						DrawText(hdc, "                                           ", -1, &rect_log[num_time], DT_WORDBREAK );
						}
			 			DrawText(hdc,"设置错误", -1, &rect_log[0], DT_WORDBREAK );
		
					break;
					case Set_type://129:
					 for(num_time=0;num_time<9;num_time++)
						{
						DrawText(hdc, "                                           ", -1, &rect_log[num_time], DT_WORDBREAK );
						}
						
						
						DrawText(hdc,"请输入三位防区号和一位类型号", -1, &rect_log[0], DT_WORDBREAK );
						DrawText(hdc,"类型号 1:普通  2:紧急", -1, &rect_log[1], DT_WORDBREAK );
						DrawText(hdc,"如0011代表防区001设置为普通类型", -1, &rect_log[2], DT_WORDBREAK );
						laset_state=LOWORD(wParam);
						break;
					break;
					case Set_time://130:
					 for(num_time=0;num_time<9;num_time++)
						{
						DrawText(hdc, "                                           ", -1, &rect_log[num_time], DT_WORDBREAK );
						}
						DrawText(hdc,"请输入十二位数字代表年月日时分", -1, &rect_log[0], DT_WORDBREAK );
						DrawText(hdc,"如200501010000", -1, &rect_log[1], DT_WORDBREAK );
						laset_state=LOWORD(wParam);
					break;
					case Set_delay://131:
					for(num_time=0;num_time<9;num_time++)
						{
						DrawText(hdc, "                                           ", -1, &rect_log[num_time], DT_WORDBREAK );
						}
						DrawText(hdc,"请输入三位数代表设防延时多少秒", -1, &rect_log[0], DT_WORDBREAK );
						DrawText(hdc,"如100", -1, &rect_log[1], DT_WORDBREAK );
						laset_state=LOWORD(wParam);
					break;
					case Set_defend://132:
						for(num_time=0;num_time<9;num_time++)
						{
						DrawText(hdc, "                                           ", -1, &rect_log[num_time], DT_WORDBREAK );
						}
						DrawText(hdc,"请输入一位数  1:代表开启 2:代表关闭", -1, &rect_log[0], DT_WORDBREAK );
						DrawText(hdc,"如1", -1, &rect_log[1], DT_WORDBREAK );
						laset_state=LOWORD(wParam);
					break;
					case Set_defend_one:
						for(num_time=0;num_time<9;num_time++)
						{
						DrawText(hdc, "                                           ", -1, &rect_log[num_time], DT_WORDBREAK );
						}
						DrawText(hdc,"请输入八位数  ", -1, &rect_log[0], DT_WORDBREAK );
						DrawText(hdc,"前四位代表设防时分 后四位代表撤防时分", -1, &rect_log[1], DT_WORDBREAK );
						DrawText(hdc,"如08001800", -1, &rect_log[2], DT_WORDBREAK );
						laset_state=LOWORD(wParam);
					break;

					case Set_defend_two:
						for(num_time=0;num_time<9;num_time++)
						{
						DrawText(hdc, "                                           ", -1, &rect_log[num_time], DT_WORDBREAK );
						}
						DrawText(hdc,"请输入三位防区号", -1, &rect_log[0], DT_WORDBREAK );
						DrawText(hdc,"如001(999代表全部设防)", -1, &rect_log[1], DT_WORDBREAK );
						laset_state=LOWORD(wParam);
					break;


					case Passwd_error:// 144
						for(num_time=0;num_time<9;num_time++)
						{
						DrawText(hdc, "                                           ", -1, &rect_log[num_time], DT_WORDBREAK );
						}
						DrawText(hdc,"密码错误请重新输入", -1, &rect_log[0], DT_WORDBREAK );
					break;

					
					
					case Set_check://133:
					for(num_time=0;num_time<9;num_time++)
						{
						DrawText(hdc, "                                           ", -1, &rect_log[num_time], DT_WORDBREAK );
						}
						DrawText(hdc,"请输入三位数代表巡检周期多少秒", -1, &rect_log[0], DT_WORDBREAK );
						DrawText(hdc,"如100", -1, &rect_log[1], DT_WORDBREAK );
						laset_state=LOWORD(wParam);
					break;
					case Set_print://134:
						for(num_time=0;num_time<9;num_time++)
						{
						DrawText(hdc, "                                           ", -1, &rect_log[num_time], DT_WORDBREAK );
						}
						DrawText(hdc,"请输入一位数  1:代表开启实时打印 2:代表关闭", -1, &rect_log[0], DT_WORDBREAK );
						DrawText(hdc,"如1", -1, &rect_log[1], DT_WORDBREAK );
						laset_state=LOWORD(wParam);
					break;
					case Set_maner://135:
					for(num_time=0;num_time<9;num_time++)
						{
						DrawText(hdc, "                                           ", -1, &rect_log[num_time], DT_WORDBREAK );
						}
					
						DrawText(hdc,"请输入三位防区号和一位类型号", -1, &rect_log[0], DT_WORDBREAK );
						DrawText(hdc,"类型号 1:高压  2:低压", -1, &rect_log[1], DT_WORDBREAK );
						DrawText(hdc,"如0011代表防区001设置为高压类型", -1, &rect_log[2], DT_WORDBREAK );
						laset_state=LOWORD(wParam);
					break;

					case Set_auto://136:
						for(num_time=0;num_time<9;num_time++)
						{
						DrawText(hdc, "                                           ", -1, &rect_log[num_time], DT_WORDBREAK );
						}
						DrawText(hdc,"请输入一位数  1:代表开启 2:代表关闭", -1, &rect_log[0], DT_WORDBREAK );
						DrawText(hdc,"如1", -1, &rect_log[1], DT_WORDBREAK );
						laset_state=LOWORD(wParam);
					break;
					
					case Set_auto_one:
						for(num_time=0;num_time<9;num_time++)
						{
						DrawText(hdc, "                                           ", -1, &rect_log[num_time], DT_WORDBREAK );
						}
						DrawText(hdc,"请输入八位数  ", -1, &rect_log[0], DT_WORDBREAK );
						DrawText(hdc,"前四位代表设高压时分 后四位代表设低压时分", -1, &rect_log[1], DT_WORDBREAK );
						DrawText(hdc,"如08001800", -1, &rect_log[2], DT_WORDBREAK );
						laset_state=LOWORD(wParam);
					break;

					case Set_auto_two:
						for(num_time=0;num_time<9;num_time++)
						{
						DrawText(hdc, "                                           ", -1, &rect_log[num_time], DT_WORDBREAK );
						}
						DrawText(hdc,"请输入三位防区号", -1, &rect_log[0], DT_WORDBREAK );
						DrawText(hdc,"如001", -1, &rect_log[1], DT_WORDBREAK );
						laset_state=LOWORD(wParam);
					break;

					
					case Set_recover://137:
					for(num_time=0;num_time<9;num_time++)
						{
						DrawText(hdc, "                                           ", -1, &rect_log[num_time], DT_WORDBREAK );
						}
						DrawText(hdc,"正在还原中...", -1, &rect_log[0], DT_WORDBREAK );

						laset_state=LOWORD(wParam);
					break;
					case Set_com_pw://138:
						for(num_time=0;num_time<9;num_time++)
						{
						DrawText(hdc, "                                           ", -1, &rect_log[num_time], DT_WORDBREAK );
						}
						DrawText(hdc,"请输入六位管理密码", -1, &rect_log[0], DT_WORDBREAK );
						laset_state=LOWORD(wParam);
					break;
					case Set_use_pw://139:
					for(num_time=0;num_time<9;num_time++)
						{
						DrawText(hdc, "                                           ", -1, &rect_log[num_time], DT_WORDBREAK );
						}
						DrawText(hdc,"请输入六位用户密码", -1, &rect_log[0], DT_WORDBREAK );
						laset_state=LOWORD(wParam);

					break;
					case Set_home://140:
						for(num_time=0;num_time<9;num_time++)
						{
						DrawText(hdc, "                                           ", -1, &rect_log[num_time], DT_WORDBREAK );
						}
						DrawText(hdc,"请输入一位数代表家防状态", -1, &rect_log[0], DT_WORDBREAK );
						DrawText(hdc,"1:代表开启 2:代表关闭", -1, &rect_log[1], DT_WORDBREAK );
						laset_state=LOWORD(wParam);
					break;
					case Set_cycle://141:
						for(num_time=0;num_time<9;num_time++)
						{
						DrawText(hdc, "                                           ", -1, &rect_log[num_time], DT_WORDBREAK );
						}
						DrawText(hdc,"请输入三位数代表巡检周期多少秒", -1, &rect_log[0], DT_WORDBREAK );
						DrawText(hdc,"如100", -1, &rect_log[1], DT_WORDBREAK );
						laset_state=LOWORD(wParam);

					
					break;

					case defend_set://150:
						
					laset_state=LOWORD(wParam);

					//defend_delay();
					
						for(num_time=0;num_time<9;num_time++)
					{
					DrawText(hdc, "                                                  ", -1, &rect_log[num_time], DT_WORDBREAK );
					}
				printf("delay_func1\n");
					DrawText(hdc,"全部布防中，请稍后...", -1, &rect_log[0], DT_WORDBREAK );
					buzzer_run(1);
					usleep(50000);
					buzzer_run(0);
					sleep(1);



					read_file("/mnt/nand1-1/config/delay_time",buf_num);
					delay_time=(buf_num[0]-'0')*100+(buf_num[1]-'0')*10+(buf_num[2]-'0');
					DEBUG("delay_time is %d",delay_time);

					if(not_delay_flag==0)
						{
							for(i=delay_time;i>0;i--)
								{
								DrawText(hdc, "                                           ", -1, &rect_log[0], DT_WORDBREAK );
								sprintf(buf_num,"布防延时中，%d...",i);
								DrawText(hdc,buf_num, -1, &rect_log[0], DT_WORDBREAK );
								sleep(1);
			

								}
						}
					else
						{
						not_delay_flag=0;

						}
					
					buzzer_run(1);
					usleep(100000);
					buzzer_run(0);

					DrawText(hdc, "                                           ", -1, &rect_log[0], DT_WORDBREAK );
					DrawText(hdc,"系统全部布防中", -1, &rect_log[0], DT_WORDBREAK );

					state=State_Dfend;

					buzzer_run(1);
					usleep(500000);
					buzzer_run(0);

					buzzer_run(1);
					usleep(500000);
					buzzer_run(0);

					write_zj_alarm(0,Dfend,1);
					


					break;
					
					case defend_part://151:
					laset_state=LOWORD(wParam);
					
						buzzer_run(1);
						usleep(500000);
						buzzer_run(0);
						
					 for(num_time=0;num_time<9;num_time++)
						{
						DrawText(hdc, "                                           ", -1, &rect_log[num_time], DT_WORDBREAK );
						}
						
						DrawText(hdc,"请输入三位防区号和一位状态号", -1, &rect_log[0], DT_WORDBREAK );
						DrawText(hdc,"状态号 1:设防  2:撤防", -1, &rect_log[1], DT_WORDBREAK );
						DrawText(hdc,"如0011代表防区001设置为设防状态", -1, &rect_log[2], DT_WORDBREAK );
						
					break;

					case Iput_usewd://152:
						laset_state=LOWORD(wParam);


						for(num_time=0;num_time<9;num_time++)
						{
						DrawText(hdc, "                                                  ", -1, &rect_log[num_time], DT_WORDBREAK );
						}
						DrawText(hdc,"请输用户密码", -1, &rect_log[0], DT_WORDBREAK );

					break;

					case ret_defend://153:
					laset_state=LOWORD(wParam);

					for(num_time=0;num_time<9;num_time++)
						{
						DrawText(hdc, "                                           ", -1, &rect_log[num_time], DT_WORDBREAK );
						}
					DrawText(hdc,"系统全部布防中", -1, &rect_log[0], DT_WORDBREAK );


					buzzer_run(1);
					usleep(500000);
					buzzer_run(0);

					buzzer_run(1);
					usleep(500000);
					buzzer_run(0);


					break;

					case ret_defend_part://154:
					laset_state=LOWORD(wParam);
					
							for(num_time=0;num_time<9;num_time++)
						{
						DrawText(hdc, "                                           ", -1, &rect_log[num_time], DT_WORDBREAK );
						}
					DrawText(hdc,"系统局部布防中", -1, &rect_log[0], DT_WORDBREAK );


					buzzer_run(1);
					usleep(500000);
					buzzer_run(0);

					buzzer_run(1);
					usleep(500000);
					buzzer_run(0);

					write_zj_alarm(0,Part_Dfend,1);
						
					break;
					case Check_Choice_Type://155
					laset_state=LOWORD(wParam);
					
						 for(num_time=0;num_time<9;num_time++)
						{
						DrawText(hdc, "                                           ", -1, &rect_log[num_time], DT_WORDBREAK );
						}
						
						DrawText(hdc,"请输入一位查询号", -1, &rect_log[0], DT_WORDBREAK );
						DrawText(hdc,"查询号 1:家防查询  2:周界查询", -1, &rect_log[1], DT_WORDBREAK );
					//	DrawText(hdc,"如0011代表防区001设置为设防状态", -1, &rect_log[2], DT_WORDBREAK );

					break;

					case Check_Set_Time://156
					laset_state=LOWORD(wParam);
					
						 for(num_time=0;num_time<9;num_time++)
						{
						DrawText(hdc, "                                           ", -1, &rect_log[num_time], DT_WORDBREAK );
						}
						
						DrawText(hdc,"请输入四位数字代表查询的日期", -1, &rect_log[0], DT_WORDBREAK );
						DrawText(hdc,"如0101 代表一月一日", -1, &rect_log[1], DT_WORDBREAK );
					//	DrawText(hdc,"如0011代表防区001设置为设防状态", -1, &rect_log[2], DT_WORDBREAK );

					break;
					case Check_Show_Date://157
					laset_state=LOWORD(wParam);
						if(buf_show[0]!=0 || buf_show[1]!=0 || buf_show[2]!=0 || buf_show[3]!=0)
							{
						sprintf(check_time,"%c%c月%c%c日",buf_show[0],buf_show[1],buf_show[2],buf_show[3]);
							}
						printf("check_time is %s\n",check_time);
						if(check_type==1)
						{
							if((fp_check=fopen("/mnt/nand1-1/config/jiafang_record","r"))==NULL)
							{
								printf("can not open the file.\n");
								break;
							}
						}
						else if(check_type==2)
						{
							if((fp_check=fopen("/mnt/nand1-1/config/zhoujie_record","r"))==NULL)
							{
								printf("can not open the file.\n");
								break;
							}

						}

						check_point=0;
						show_num=0;
						
						while(!feof(fp_check))
						{
							memset(check_buf,0,sizeof(check_buf));
							fgets(check_buf,sizeof(check_buf),fp_check);

									if(strlen(check_buf)>0)
										{
											if((strstr(check_buf, check_time)) != NULL)
												{	
													strcpy(check_getdate[check_point],check_buf);
													check_point++;
													//printf("check_point is %d\n",check_point);
														
												}
										}
								
							
						}
						fclose(fp_check);

						 for(num_time=0;num_time<9;num_time++)
						{
						DrawText(hdc, "                                           ", -1, &rect_log[num_time], DT_WORDBREAK );
						}

						
						if(check_point==0)
							{
								DrawText(hdc, "查询无记录", -1, &rect_log[0], DT_WORDBREAK );
							}

						else if(check_point<=9)
							{
								for(num_time=0;num_time<check_point;num_time++)
							   {
							  	 DrawText(hdc, check_getdate[num_time], -1, &rect_log[num_time], DT_WORDBREAK );
						
							   }

							}
						else
							{
								 for(num_time=0;num_time<9;num_time++)
								{
									 DrawText(hdc, check_getdate[num_time], -1, &rect_log[num_time], DT_WORDBREAK );
								}

							}


					break;
					case  Check_Show_up:
						laset_state=LOWORD(wParam);
							printf("Check_Show_up\n");
							i=0;
							show_num++;
							if(show_num+9>check_point)
									{
									show_num=check_point-9;
									}
							
							for(num_time=show_num;num_time<show_num+9;num_time++)
							   {
								 DrawText(hdc, check_getdate[num_time], -1, &rect_log[i], DT_WORDBREAK );
								 i++;
							   }
					
						break;
						
					case  Check_Show_down:
						laset_state=LOWORD(wParam);
						printf("Check_Show_down\n");
						i=0;
								show_num--;
								if(show_num<=0)
									{
									show_num=0;
									}

							for(num_time=show_num;num_time<show_num+9;num_time++)
							   {
								 DrawText(hdc, check_getdate[num_time], -1, &rect_log[i], DT_WORDBREAK );
								 i++;
							   }
					

						
						break;

						case back_part_defend://160
						laset_state=LOWORD(wParam);
					
							for(num_time=0;num_time<9;num_time++)
						{
						DrawText(hdc, "                                           ", -1, &rect_log[num_time], DT_WORDBREAK );
						}
					DrawText(hdc,"系统局部布防中", -1, &rect_log[0], DT_WORDBREAK );


					buzzer_run(1);
					usleep(500000);
					buzzer_run(0);

					buzzer_run(1);
					usleep(500000);
					buzzer_run(0);
	

						
					break;

					
					case Print_now://170
					laset_state=LOWORD(wParam);

						for(num_time=0;num_time<9;num_time++)
						{
						DrawText(hdc, "                                                  ", -1, &rect_log[num_time], DT_WORDBREAK );
						}
						DrawText(hdc,"打印中请稍后...", -1, &rect_log[0], DT_WORDBREAK );


						 if(check_point<=9)
							{
								for(num_time=0;num_time<check_point;num_time++)
							   {
							   	    if(check_type==1)
									{
							  		print_punch(check_getdate[num_time],1,1)  ;
							   	 	}
								     else if(check_type==2)
								  	{
									print_punch(check_getdate[num_time],0,1)	;

								  	}
							   }

							}
						else
							{
								 for(num_time=0;num_time<9;num_time++)
								{
									if(check_type==1)
									{
							  		print_punch(check_getdate[num_time],1,1)  ;
							   	 	}
								    else if(check_type==2)
								  	{
									print_punch(check_getdate[num_time],0,1)	;

								  	}
								}

							}
						
						break;
						
							case alarm_come:
								SetBkColor(hdc, RGB(255,00,00));  
								for(num_time=0;num_time<9;num_time++)
								{
								DrawText(hdc, "                                 ", -1, &rect_log[num_time], DT_WORDBREAK );
								}

							    DrawText(hdc,alarm_date, -1, &rect_log[4], DT_WORDBREAK );
							//	sleep(1);
						 		SetBkColor(hdc, RGB(100,149,237));    
								break;

					
					case ID_NEW:
						//jimmy +++ set icon place
						//flag_connect=0;
						laset_state=LOWORD(wParam);
						flag_connect=1;
						//usleep(100000);

						//InvalidateRect (hwnd, NULL, TRUE);
						InvalidateRect (NULL, NULL, TRUE);
				

					break;

				    case ID_CONNECT:
						//jimmy +++ set icon place
						flag_connect=1;
					//	usleep(1200000);
						      //usleep(500000);
						//InvalidateRect (hwnd, NULL, TRUE);
						InvalidateRect (NULL, NULL, TRUE);
						
					break;
					default:
					break;
				}
				
				
				break;
		case WM_LBUTTONDOWN:
		
                break;

		case WM_DESTROY:
                PostQuitMessage(0);
				KillTimer(hwnd, ID_TIMER);  
                break;
        default:
                return DefWindowProc(hwnd,iMsg,wParam,lParam);
        }      
        return 0;
}
		
