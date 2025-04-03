#include "iic.h"
/*
��������IIC_Port_Init
�������ܣ�IIC�ܽų�ʼ��
�βΣ�void
����ֵ��void
����˵����
AT24CXX_SDA --- PB7 --- ͨ�ÿ�©���    ��SDA = 1�л��ɴ�����ģʽ
AT24CXX_SCL --- PB6 --- ͨ���������
*/

void IIC_Port_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//��GPIOBʱ��
	
	GPIO_InitTypeDef GPIO_InitStruct={0};//����ṹ�������
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;//����Ϊ�������ģʽ
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;//���ùܽ�
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�Ϊ50Mhz
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;//����Ϊ��©���
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;//���ùܽ�
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�Ϊ50Mhz
	GPIO_Init(GPIOB,&GPIO_InitStruct);
}



/*
��������IIC_Start
�������ܣ�IIC��ʼ�ź�
�βΣ�u8 nus SCL�����ߺ���������ʱ��
����ֵ��void
����˵����

*/
void IIC_Start(u8 us)
{
	IIC_SCL_L;//����ʱ����
	delay_us(us);
	IIC_SCL_H;//����ʱ����
	IIC_SDA_H;//����������
	delay_us(us);
	IIC_SDA_L;//����������
	delay_us(us);

}
/*
��������IIC_Stop
�������ܣ�IICֹͣ�ź�
�βΣ�u8 nus SCL�����ߺ���������ʱ��
����ֵ��void
����˵����
SCL---ʱ��   SDA---����
*/

void IIC_Stop(u8 us)
{
	IIC_SCL_L;
	delay_us(us);
	IIC_SDA_L;
	IIC_SCL_H;
	delay_us(us);
	IIC_SDA_H;
	delay_us(us);
}

/*
��������IIC_SendAck
�������ܣ�����1bitӦ��
�βΣ�
u8 ack   0��Ӧ������͵�ƽ    1����Ӧ��,����ߵ�ƽ
u8 nus  SCL�����ߺ���������ʱ��  
����ֵ��void
����˵����
������Ч�ԣ�SCL�ߵ�ƽ��������    SCL�͵�ƽ��������
*/

void IIC_SendAck(u8 ack ,u8 us)
{
	IIC_SCL_L;//���͵�ƽ׼����������
	delay_us(us);
	if(ack)
	{
		IIC_SDA_H;//Ӧ��Ϊ1����
	}
	else
	{
		IIC_SDA_L;//Ӧ��Ϊ0����
	}
	//��������������
	IIC_SCL_H;//���ߵ�ƽ
	delay_us(us);
	IIC_SCL_L;//���͵�ƽ
	delay_us(us);
}

/*
��������IIC_RecAck
�������ܣ�����1bitӦ��
�βΣ�
u8 nus  SCL�����ߺ���������ʱ��  
����ֵ��u8 �ڴӻ����չ�����Ӧ��λ    0��Ӧ��    1����Ӧ��
����˵����
������Ч�ԣ�SCL�ߵ�ƽ��������    SCL�͵�ƽ��������
*/
u8 IIC_RecAck(u8 us)
{
	u8 ack=0;
	IIC_SDA_H;//���������ߣ�ʹIO�ڱ������ģʽ
	IIC_SCL_L;//����ʱ���ߣ���������һ����
	delay_us(us);
	IIC_SCL_H;
	delay_us(us);
	if(IIC_SDA_In)
	{
		ack |=1;
	}
	//��������������
	IIC_SCL_L;
	delay_us(us);
	return ack;
}	
/*
��������IIC_SendData
�������ܣ�����8bit���ݲ�����1bitӦ��
�βΣ�
u8 data ����8bit����
u8 nus  SCL�����ߺ���������ʱ��  
����ֵ��u8 �ڴӻ����չ�����Ӧ��λ    0��Ӧ��    1����Ӧ��
����˵����
������Ч�ԣ�SCL�ߵ�ƽ��������    SCL�͵�ƽ��������
��λ�ȷ���һ��8bit
*/
u8 IIC_SendData(u8 date,u8 us)
{
	for(int i=0;i<8;i++)
	{
		IIC_SCL_L; //����ʱ����׼����������
		
		if(date &(0x80>>i))
		{
			IIC_SDA_H;
		}
		else
		{
			IIC_SDA_L;
		}
		delay_us(us);
		IIC_SCL_H;//����ʱ������ɷ�������
		delay_us(us);
	}
	return IIC_RecAck(us);//����1bitӦ��

}
/*
��������IIC_RecData
�������ܣ�����8bit���ݲ�����1bitӦ��
�βΣ�
u8 ack ����Ӧ��λ     0��Ӧ��    1����Ӧ��
u8 nus  SCL�����ߺ���������ʱ��  
����ֵ��u8 ���մӻ���8bit����   
����˵����
������Ч�ԣ�SCL�ߵ�ƽ��������    SCL�͵�ƽ��������
��λ�ȷ���һ��8bit
*/

u8 IIC_RecData(u8 ack,u8 us)
{
	IIC_SDA_H;
	u8 date=0;
	for(int i=0;i<8;i++)
	{
		IIC_SCL_L;
		delay_us(us);
		IIC_SCL_H;//����ʱ����׼����������
		date<<=1;
		if(IIC_SDA_In)
		{
			date |=1;
		}
		delay_us(us);
	}
	IIC_SendAck(ack,us);//����һbitӦ��
	return date;



}
