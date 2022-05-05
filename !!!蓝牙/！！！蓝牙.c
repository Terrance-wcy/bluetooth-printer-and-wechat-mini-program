#include<reg52.h>
#include<intrins.h>

typedef unsigned int uint;
typedef unsigned char uchar ;
uchar R_data;
bit R_flag=0;

void Uart_Init(void)
{

	PCON = 0x80;		//使能波特率倍速位SMOD

	SCON = 0x50;		//8位数据,可变波特率

	AUXR &= 0xBF;		//定时器1时钟为Fosc/12,即12T

	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器

	TMOD &= 0x0F;		//清除定时器1模式位

	TMOD = 0x20;		//设定定时器1为8位自动重装方式

	TL1 = 0xFF;		//设定定时初值

	TH1 = 0xFF;		//设定定时器重装值

	ET1 = 0;		//禁止定时器1中断

	TR1 = 1;		//启动定时器1

}
void Uart_SendByte(uchar Byte)
{
	SBUF =	Byte;
	while(!TI)                   //如果发送完毕，硬件会置位TI
	{
		_nop_();	
	}	
}

void main()
{
	Uart_Init();
	while(1)
	{
		if(R_flag==1)
		{
			Uart_SendByte(R_data );
			R_flag=0;
		}	
	}		
}

void Uart_Int(void) interrupt 4
{
//	static uchar i = 7;    //定义为静态变量，当重新进入这个子函数时 i 的值不会发生改变
	EA = 0;
	if(RI == 1)   //当硬件接收到一个数据时，RI会置位
	{
		R_data= SBUF; //这里减去48是因为从电脑中发送过来的数据是ASCII码。
		RI = 0;  
		R_flag=1; 
	}
	EA = 1;
}




