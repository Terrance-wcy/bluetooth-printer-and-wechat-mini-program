#include <reg52.h>
#include <string.h>
#include <math.h>
#include <intrins.h>

#define uchar unsigned char
typedef unsigned int uint;



uchar R_data;
bit R_flag=0;
void delay(int i)
{
  int j,k; 
  for(j=i;j>0;j--)
    for(k=125;k>0;k--);
}

//void Uart_SendByte(uchar Byte)
//{
//	SBUF =	Byte;
//	while(!TI)                   //如果发送完毕，硬件会置位TI
//	{
//		_nop_();	
//	}	
//}
uchar code table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,
                        0xf8,0x80,0x90};

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



void Delay100ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 180;
	j = 73;
	do
	{
		while (--j);
	} while (--i);
}


void print(uchar ch) // 单字节打印函数
{
	SBUF = ch;
	while(TI == 0);
	TI = 0;
}

void UartInit(void)		//115200bps@11.0592MHz

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


void print_chs(uchar ch[]) // 字符打印函数
{
	uchar i;
	for(i=0;i<strlen(ch);i++) //应用到字串处理函数，故须调用
		print(ch[i]);
}

void hanzitest()
{
	print(0x1B); // 打印机初始化
	print(0x40); 	// 打印机初始化

Delay100ms();

		print(0x0A);// 打印并走纸
    print(0x1b);
		print(0x62);
		print(0x00);
		print(0x0a);
	print_chs("商家小票");            
	print(0x0A);Delay100ms();
print_chs("*****");     // 
	print(0x0A);Delay100ms();


	print_chs("1号口袋");     // 
	print(0x0A);Delay100ms();
	print_chs("备注:");     // 
	print(0x0A);Delay100ms();

		print(0x0A);// 打印并走纸
    print(0x1b);
		print(0x62);
		print(0x00);
		print(0x04);
			print_chs("不要辣");     // 
	print(0x0A);Delay100ms();
	print_chs("食品名称:");     // 
	print(0x0A);Delay100ms();
	
		print(0x0A);// 打印并走纸
    print(0x1b);
		print(0x62);
		print(0x00);
		print(0x04);
		print_chs("麻辣豆腐");    // 
	print(0x0A);Delay100ms();
	print_chs("份:");     // 
	print(0x0A);Delay100ms();

		print(0x0A);// 打印并走纸
    print(0x1b);
		print(0x62);
		print(0x00);
		print(0x04);
			print_chs("2");     // 
	print(0x0A);Delay100ms();
	print_chs("总价:");     // 
	print(0x0A);Delay100ms();

		print(0x0A);// 打印并走纸
    print(0x1b);
		print(0x62);
		print(0x00);
		print(0x04);
			print_chs("20");     // 
	print(0x0A);Delay100ms();
	print_chs("*****");     // 
	print(0x0A);Delay100ms();

	print_chs("餐盒费:2");     // 
	print(0x0A);Delay100ms();

	print_chs("配送费:2");     // 
	print(0x0A);Delay100ms();

	print_chs("*****");     // 
	print(0x0A);Delay100ms();
	
	print_chs("支付金额:");  // 
	print(0x0A);Delay100ms();
			print(0x0A);// 打印并走纸
    print(0x1b);
		print(0x62);
		print(0x00);
		print(0x04);
			print_chs("24");     // 
	print(0x0A);Delay100ms();

	print_chs("外卖地址:");// 
	print(0x0A);Delay100ms();
			print(0x0A);// 打印并走纸
    print(0x1b);
		print(0x62);
		print(0x00);
		print(0x04);
			print_chs("公寓五号楼");     // 
	print(0x0A);Delay100ms();
}


void main(void)
{
  int a=0;
   UartInit();
	while(1)
	{


if(P35==0)	//打印
		{
			delay(5);
			if(P35==0)
			{
				a++;
				if(a>9999)
					a=0;
				hanzitest();
				while(!P35); //松手检测
			}		
		}
		display(a);

	}
}

		

	
	



