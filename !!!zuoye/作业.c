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
//	while(!TI)                   //���������ϣ�Ӳ������λTI
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


void print(uchar ch) // ���ֽڴ�ӡ����
{
	SBUF = ch;
	while(TI == 0);
	TI = 0;
}

void UartInit(void)		//115200bps@11.0592MHz

{

	PCON = 0x80;		//ʹ�ܲ����ʱ���λSMOD

	SCON = 0x50;		//8λ����,�ɱ䲨����

	AUXR &= 0xBF;		//��ʱ��1ʱ��ΪFosc/12,��12T

	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����

	TMOD &= 0x0F;		//�����ʱ��1ģʽλ

	TMOD = 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ

	TL1 = 0xFF;		//�趨��ʱ��ֵ

	TH1 = 0xFF;		//�趨��ʱ����װֵ

	ET1 = 0;		//��ֹ��ʱ��1�ж�

	TR1 = 1;		//������ʱ��1

}


void print_chs(uchar ch[]) // �ַ���ӡ����
{
	uchar i;
	for(i=0;i<strlen(ch);i++) //Ӧ�õ��ִ����������������
		print(ch[i]);
}

void hanzitest()
{
	print(0x1B); // ��ӡ����ʼ��
	print(0x40); 	// ��ӡ����ʼ��

Delay100ms();

		print(0x0A);// ��ӡ����ֽ
    print(0x1b);
		print(0x62);
		print(0x00);
		print(0x0a);
	print_chs("�̼�СƱ");            
	print(0x0A);Delay100ms();
print_chs("*****");     // 
	print(0x0A);Delay100ms();


	print_chs("1�ſڴ�");     // 
	print(0x0A);Delay100ms();
	print_chs("��ע:");     // 
	print(0x0A);Delay100ms();

		print(0x0A);// ��ӡ����ֽ
    print(0x1b);
		print(0x62);
		print(0x00);
		print(0x04);
			print_chs("��Ҫ��");     // 
	print(0x0A);Delay100ms();
	print_chs("ʳƷ����:");     // 
	print(0x0A);Delay100ms();
	
		print(0x0A);// ��ӡ����ֽ
    print(0x1b);
		print(0x62);
		print(0x00);
		print(0x04);
		print_chs("��������");    // 
	print(0x0A);Delay100ms();
	print_chs("��:");     // 
	print(0x0A);Delay100ms();

		print(0x0A);// ��ӡ����ֽ
    print(0x1b);
		print(0x62);
		print(0x00);
		print(0x04);
			print_chs("2");     // 
	print(0x0A);Delay100ms();
	print_chs("�ܼ�:");     // 
	print(0x0A);Delay100ms();

		print(0x0A);// ��ӡ����ֽ
    print(0x1b);
		print(0x62);
		print(0x00);
		print(0x04);
			print_chs("20");     // 
	print(0x0A);Delay100ms();
	print_chs("*****");     // 
	print(0x0A);Delay100ms();

	print_chs("�ͺз�:2");     // 
	print(0x0A);Delay100ms();

	print_chs("���ͷ�:2");     // 
	print(0x0A);Delay100ms();

	print_chs("*****");     // 
	print(0x0A);Delay100ms();
	
	print_chs("֧�����:");  // 
	print(0x0A);Delay100ms();
			print(0x0A);// ��ӡ����ֽ
    print(0x1b);
		print(0x62);
		print(0x00);
		print(0x04);
			print_chs("24");     // 
	print(0x0A);Delay100ms();

	print_chs("������ַ:");// 
	print(0x0A);Delay100ms();
			print(0x0A);// ��ӡ����ֽ
    print(0x1b);
		print(0x62);
		print(0x00);
		print(0x04);
			print_chs("��Ԣ���¥");     // 
	print(0x0A);Delay100ms();
}


void main(void)
{
  int a=0;
   UartInit();
	while(1)
	{


if(P35==0)	//��ӡ
		{
			delay(5);
			if(P35==0)
			{
				a++;
				if(a>9999)
					a=0;
				hanzitest();
				while(!P35); //���ּ��
			}		
		}
		display(a);

	}
}

		

	
	



