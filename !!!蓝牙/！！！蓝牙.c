#include<reg52.h>
#include<intrins.h>

typedef unsigned int uint;
typedef unsigned char uchar ;
uchar R_data;
bit R_flag=0;

void Uart_Init(void)
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
void Uart_SendByte(uchar Byte)
{
	SBUF =	Byte;
	while(!TI)                   //���������ϣ�Ӳ������λTI
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
//	static uchar i = 7;    //����Ϊ��̬�����������½�������Ӻ���ʱ i ��ֵ���ᷢ���ı�
	EA = 0;
	if(RI == 1)   //��Ӳ�����յ�һ������ʱ��RI����λ
	{
		R_data= SBUF; //�����ȥ48����Ϊ�ӵ����з��͹�����������ASCII�롣
		RI = 0;  
		R_flag=1; 
	}
	EA = 1;
}




