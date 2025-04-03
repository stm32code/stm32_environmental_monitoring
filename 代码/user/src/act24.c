#include "act24.h"
void Act24_Init(void)
{
	IIC_Port_Init();
}
/*
函数名：At24cxx_WriteByte
函数功能：字节写
形参：
u8 data 写入数据
u8 addr 写入地址（写入位置）  0 - 255
返回值：u8   0：通信正常   非0：通信不正常
函数说明：
字节写代码步骤：
1、	发送起始信号
2、	MCU发送写方向地址，接收并判断正常应答
3、	发送字地址，接收并判断正常应答
4、	发送8bit数据，接收并判断正常应答
5、	发送停止信号
6、	写周期（延时5ms）

*/
u8 At24cxx_WriteByte(u8 addr ,u8 date,u8 us)
{
	IIC_Start(us);//发送起始条件
	if(IIC_SendData(0xA0,us))//发送写地址条件
	{
		IIC_Stop(us);//发送失败，停止条件
		return 1 ;
	}
	if(IIC_SendData(addr,us))//发送字地址
	{
		IIC_Stop(us);//发送失败，停止条件
		return 2;
	}
		if(IIC_SendData(date,us))//发送数据
	{
		IIC_Stop(us);//发送失败，停止条件
		return 3;
	}
	IIC_Stop(us);//发送完成，停止发送
	delay_ms(5);//写周期，数据存入内部
	printf("发送一个字节成功\r\n");
	return 0;
	
}
/*
函数名：Act24_Ran_Read
函数功能：随机读
形参：
u8 *data 读取数据
u8 addr 读取地址（写入位置）  0 - 255
返回值：u8   0：通信正常   非0：通信不正常
函数说明：
读操作初始化步骤：
1、	发送起始信号
2、	MCU发送写方向地址，接收并判断正常应答
3、	发送字地址，接收并判断正常应答
4、	发送起始信号
5、	MCU发送读方向地址，接收并判断正常应答
6、	读取8bit数据并非应答
7、	停止信号


*/


u8 Act24_Ran_Read (u8 addr,u8 *date,u8 us)
{
	IIC_Start(us);//发送起始条件
	if(IIC_SendData(0xA0,us))//发送写地址条件
	{
		IIC_Stop(us);//发送失败，停止条件
		return 1 ;
	}
	if(IIC_SendData(addr,us))//发送字地址
	{
		IIC_Stop(us);//发送失败，停止条件
		return 2;
	}
	IIC_Start(us);//重复发送起始条件
	if(IIC_SendData(0xA1,us))//发送读地址条件
	{
		IIC_Stop(us);//发送失败，停止条件
		return 3;
	}
	*date=IIC_RecData(1,us);//接收数据
	IIC_Stop(us);//结束通信
	return 0;
}
/*
函数名：Act24_PageWrite
函数功能：页写
形参：
u8 *data 读取数据
u8 addr 读取地址（写入位置）  0 - 255
u16 len 字节长度
u8 us 延迟时间
返回值：u8   0：通信正常   非0：通信不正常
函数说明：
读操作初始化步骤：

*/

u8 Act24_PageWrite(u8*data,u8 addr,u16 len,u8 us)
{
	
	IIC_Start(us);//发送起始条件
	if(IIC_SendData(0xA0,us))//发送写地址条件
	{
		IIC_Stop(us);//发送失败，停止条件
		return 1 ;
	}
	if(IIC_SendData(addr,us))//发送字地址
	{
		IIC_Stop(us);//发送失败，停止条件
		return 2;
	}
	for(int i=0;i<len;i++)
	{
		if(IIC_SendData(*(data+i),us))//发送数据
	{
		IIC_Stop(us);//发送失败，停止条件
		return 3;
	}
	}
	IIC_Stop(us);//发送完成，停止发送
	delay_ms(5);//写周期，数据存入内部
	printf("页写成功\r\n");
	return 0;
}

/*
函数名：Act24_ContinueRead
函数功能：连续读
形参：
u8 *data 读取数据
u8 addr 读取地址（写入位置）  0 - 255
u16 len 字节长度
u8 us 延迟时间
返回值：u8   0：通信正常   非0：通信不正常
函数说明：
读操作初始化步骤：

*/
u8 Act24_ContinueRead(u8*data,u8 addr,u16 len,u8 us)
{
	IIC_Start(us);//发送起始条件
	if(IIC_SendData(0xA0,us))//发送写地址条件
	{
		IIC_Stop(us);//发送失败，停止条件
		return 1 ;
	}
	if(IIC_SendData(addr,us))//发送字地址
	{
		IIC_Stop(us);//发送失败，停止条件
		return 2;
	}
	IIC_Start(us);//重复发送起始条件
	if(IIC_SendData(0xA1,us))//发送读地址条件
	{
		IIC_Stop(us);//发送失败，停止条件
		return 3;
	}
	for(int i=0;i<len ;i++)
	{
		if(i<len-1)
		{
			*(data+i)=IIC_RecData(0,us);//接收数据
		}
		if(i==len-1)
		{
			*(data+i)=IIC_RecData(1,us);//接收数据
		}
	}
	IIC_Stop(us);//结束通信
	return 0;
}
/*
函数名：Act24_AutoWrite
函数功能：跨页写
形参：
u8 *data 读取数据
u8 addr 读取地址（写入位置）  0 - 255
u16 len 字节长度
u8 us 延迟时间
返回值：u8   0：通信正常   非0：通信不正常
函数说明：
读操作初始化步骤：
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


//存放温度原始值
void Pass_lock(void)//存放密码
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

	printf("存放密码成功\r\n");
}


