#include "act24.h"
void Act24_Init(void)
{
	IIC_Port_Init();
}
/*
��������At24cxx_WriteByte
�������ܣ��ֽ�д
�βΣ�
u8 data д������
u8 addr д���ַ��д��λ�ã�  0 - 255
����ֵ��u8   0��ͨ������   ��0��ͨ�Ų�����
����˵����
�ֽ�д���벽�裺
1��	������ʼ�ź�
2��	MCU����д�����ַ�����ղ��ж�����Ӧ��
3��	�����ֵ�ַ�����ղ��ж�����Ӧ��
4��	����8bit���ݣ����ղ��ж�����Ӧ��
5��	����ֹͣ�ź�
6��	д���ڣ���ʱ5ms��

*/
u8 At24cxx_WriteByte(u8 addr ,u8 date,u8 us)
{
	IIC_Start(us);//������ʼ����
	if(IIC_SendData(0xA0,us))//����д��ַ����
	{
		IIC_Stop(us);//����ʧ�ܣ�ֹͣ����
		return 1 ;
	}
	if(IIC_SendData(addr,us))//�����ֵ�ַ
	{
		IIC_Stop(us);//����ʧ�ܣ�ֹͣ����
		return 2;
	}
		if(IIC_SendData(date,us))//��������
	{
		IIC_Stop(us);//����ʧ�ܣ�ֹͣ����
		return 3;
	}
	IIC_Stop(us);//������ɣ�ֹͣ����
	delay_ms(5);//д���ڣ����ݴ����ڲ�
	printf("����һ���ֽڳɹ�\r\n");
	return 0;
	
}
/*
��������Act24_Ran_Read
�������ܣ������
�βΣ�
u8 *data ��ȡ����
u8 addr ��ȡ��ַ��д��λ�ã�  0 - 255
����ֵ��u8   0��ͨ������   ��0��ͨ�Ų�����
����˵����
��������ʼ�����裺
1��	������ʼ�ź�
2��	MCU����д�����ַ�����ղ��ж�����Ӧ��
3��	�����ֵ�ַ�����ղ��ж�����Ӧ��
4��	������ʼ�ź�
5��	MCU���Ͷ������ַ�����ղ��ж�����Ӧ��
6��	��ȡ8bit���ݲ���Ӧ��
7��	ֹͣ�ź�


*/


u8 Act24_Ran_Read (u8 addr,u8 *date,u8 us)
{
	IIC_Start(us);//������ʼ����
	if(IIC_SendData(0xA0,us))//����д��ַ����
	{
		IIC_Stop(us);//����ʧ�ܣ�ֹͣ����
		return 1 ;
	}
	if(IIC_SendData(addr,us))//�����ֵ�ַ
	{
		IIC_Stop(us);//����ʧ�ܣ�ֹͣ����
		return 2;
	}
	IIC_Start(us);//�ظ�������ʼ����
	if(IIC_SendData(0xA1,us))//���Ͷ���ַ����
	{
		IIC_Stop(us);//����ʧ�ܣ�ֹͣ����
		return 3;
	}
	*date=IIC_RecData(1,us);//��������
	IIC_Stop(us);//����ͨ��
	return 0;
}
/*
��������Act24_PageWrite
�������ܣ�ҳд
�βΣ�
u8 *data ��ȡ����
u8 addr ��ȡ��ַ��д��λ�ã�  0 - 255
u16 len �ֽڳ���
u8 us �ӳ�ʱ��
����ֵ��u8   0��ͨ������   ��0��ͨ�Ų�����
����˵����
��������ʼ�����裺

*/

u8 Act24_PageWrite(u8*data,u8 addr,u16 len,u8 us)
{
	
	IIC_Start(us);//������ʼ����
	if(IIC_SendData(0xA0,us))//����д��ַ����
	{
		IIC_Stop(us);//����ʧ�ܣ�ֹͣ����
		return 1 ;
	}
	if(IIC_SendData(addr,us))//�����ֵ�ַ
	{
		IIC_Stop(us);//����ʧ�ܣ�ֹͣ����
		return 2;
	}
	for(int i=0;i<len;i++)
	{
		if(IIC_SendData(*(data+i),us))//��������
	{
		IIC_Stop(us);//����ʧ�ܣ�ֹͣ����
		return 3;
	}
	}
	IIC_Stop(us);//������ɣ�ֹͣ����
	delay_ms(5);//д���ڣ����ݴ����ڲ�
	printf("ҳд�ɹ�\r\n");
	return 0;
}

/*
��������Act24_ContinueRead
�������ܣ�������
�βΣ�
u8 *data ��ȡ����
u8 addr ��ȡ��ַ��д��λ�ã�  0 - 255
u16 len �ֽڳ���
u8 us �ӳ�ʱ��
����ֵ��u8   0��ͨ������   ��0��ͨ�Ų�����
����˵����
��������ʼ�����裺

*/
u8 Act24_ContinueRead(u8*data,u8 addr,u16 len,u8 us)
{
	IIC_Start(us);//������ʼ����
	if(IIC_SendData(0xA0,us))//����д��ַ����
	{
		IIC_Stop(us);//����ʧ�ܣ�ֹͣ����
		return 1 ;
	}
	if(IIC_SendData(addr,us))//�����ֵ�ַ
	{
		IIC_Stop(us);//����ʧ�ܣ�ֹͣ����
		return 2;
	}
	IIC_Start(us);//�ظ�������ʼ����
	if(IIC_SendData(0xA1,us))//���Ͷ���ַ����
	{
		IIC_Stop(us);//����ʧ�ܣ�ֹͣ����
		return 3;
	}
	for(int i=0;i<len ;i++)
	{
		if(i<len-1)
		{
			*(data+i)=IIC_RecData(0,us);//��������
		}
		if(i==len-1)
		{
			*(data+i)=IIC_RecData(1,us);//��������
		}
	}
	IIC_Stop(us);//����ͨ��
	return 0;
}
/*
��������Act24_AutoWrite
�������ܣ���ҳд
�βΣ�
u8 *data ��ȡ����
u8 addr ��ȡ��ַ��д��λ�ã�  0 - 255
u16 len �ֽڳ���
u8 us �ӳ�ʱ��
����ֵ��u8   0��ͨ������   ��0��ͨ�Ų�����
����˵����
��������ʼ�����裺
*/
void Act24_AutoWrite(u8*data,u8 addr,u16 len,u8 us)
{
	u16 leng;
	leng=16-addr%16;
	if(leng>=len)
	{
		leng=len;
	}
	while(1)
	{
		Act24_PageWrite(data,addr,leng,us);
		if(leng==len)
		{
			break;
		}
		len=len-leng;
		addr=addr+leng;
		data=data+leng;
		if(len<=16)
		{
			leng=len;
		}
		else
		{
			leng=16;
		}
	}
}


//����¶�ԭʼֵ
void Pass_lock(void)//�������
{
	u8 Temp=35;
	u8 Hum=30;
	u8 Light=50;
	u8 CO2=50;
	u8 Soil=1;
	Act24_AutoWrite(&Temp,0,sizeof(Temp),6);
	Act24_AutoWrite(&Hum,2,sizeof(Hum),6);
	Act24_AutoWrite(&Light,4,sizeof(Light),6);
	Act24_AutoWrite(&CO2,6,sizeof(CO2),6);
	Act24_AutoWrite(&Soil,8,sizeof(Soil),6);

	printf("�������ɹ�\r\n");
}


