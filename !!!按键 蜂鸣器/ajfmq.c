#include <reg52.h>
#include <string.h>
#include <math.h>
#include <intrins.h>

#define uchar unsigned char


sbit  BEEP= P2^5;
sbit  P33=P3^3;
uchar  H_count,L_count;

uchar code table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,
                        0xf8,0x80,0x90};

void delay(int i)
{
  int j,k; 
  for(j=i;j>0;j--)
    for(k=125;k>0;k--);
}

void display(int Dis_data)
{
  
   P0=table[Dis_data/1000];
   P20 = 0;
   delay(2);
   P20 = 1;

   P0=table[Dis_data%1000/100];
   P21 = 0;
   delay(2);
   P21 = 1;

   P0=table[Dis_data%1000%100/10];
   P22 = 0;
   delay(2);
   P22 = 1;

   P0=table[Dis_data%10];
   P23 = 0;
   delay(2);
   P23 = 1;
   
}

void main(void)
{
int a =0;
	while(1)
	{
if(P33==0)	//∑‰√˘∆˜
		{
			delay(5);
			if(P33==0)
		{	BEEP=1;
    TMOD=0x01; 
    TH0=0xff; 
    TL0=0xa0;
    H_count=0xff;
    L_count=0xa0;      
    EA=1;
    ET0=1; 
       TR0=1;
			a++;
				if(a>9999)
					a=0;

    }
				while(!P33); //À… ÷ºÏ≤‚
			}		
	display(a);	 //œ‘ æ
	}
}

void Time0(void) interrupt 1 using 0
{
	BEEP=~BEEP;
	if( L_count!=0x00 )
	{
	   L_count--;
	   TH0=H_count; 
       TL0=L_count;
       return;
     }else  H_count--;
		
	if( H_count!=0xfc )
	{
	   L_count--;
	   TH0=H_count; 
       TL0=L_count;
       return;
	}
	else
     {
        H_count=0xff;
        L_count=0xa0;
        TH0=H_count;
        TL0=L_count;
        BEEP=1;
        TR0=0;
     }   
}
   
/*********************************************************/