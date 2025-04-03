#include "iic.h"
/*
函数名：IIC_Port_Init
函数功能：IIC管脚初始化
形参：void
返回值：void
函数说明：
AT24CXX_SDA --- PB7 --- 通用开漏输出    当SDA = 1切换成纯输入模式
AT24CXX_SCL --- PB6 --- 通用推挽输出
*/

void IIC_Port_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//打开GPIOB时钟
	
	GPIO_InitTypeDef GPIO_InitStruct={0};//定义结构体变量名
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;//配置为推挽输出模式
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;//配置管脚
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//速度为50Mhz
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;//配置为开漏输出
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;//配置管脚
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//速度为50Mhz
	GPIO_Init(GPIOB,&GPIO_InitStruct);
}



/*
函数名：IIC_Start
函数功能：IIC起始信号
形参：u8 nus SCL线拉高和拉低所需时间
返回值：void
函数说明：

*/
void IIC_Start(u8 us)
{
	IIC_SCL_L;//拉低时钟线
	delay_us(us);
	IIC_SCL_H;//拉高时钟线
	IIC_SDA_H;//拉高数据线
	delay_us(us);
	IIC_SDA_L;//拉低数据线
	delay_us(us);

}
/*
函数名：IIC_Stop
函数功能：IIC停止信号
形参：u8 nus SCL线拉高和拉低所需时间
返回值：void
函数说明：
SCL---时钟   SDA---数据
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
函数名：IIC_SendAck
函数功能：发送1bit应答
形参：
u8 ack   0：应答，输出低电平    1：非应答,输出高电平
u8 nus  SCL线拉高和拉低所需时间  
返回值：void
函数说明：
数据有效性：SCL高电平接收数据    SCL低电平发送数据
*/

void IIC_SendAck(u8 ack ,u8 us)
{
	IIC_SCL_L;//拉低电平准备发送数据
	delay_us(us);
	if(ack)
	{
		IIC_SDA_H;//应答为1，高
	}
	else
	{
		IIC_SDA_L;//应答为0，低
	}
	//保持周期完整性
	IIC_SCL_H;//拉高电平
	delay_us(us);
	IIC_SCL_L;//拉低电平
	delay_us(us);
}

/*
函数名：IIC_RecAck
函数功能：接收1bit应答
形参：
u8 nus  SCL线拉高和拉低所需时间  
返回值：u8 在从机接收过来的应答位    0：应答    1：非应答
函数说明：
数据有效性：SCL高电平接收数据    SCL低电平发送数据
*/
u8 IIC_RecAck(u8 us)
{
	u8 ack=0;
	IIC_SDA_H;//拉高数据线，使IO口变成输入模式
	IIC_SCL_L;//拉低时钟线，属于周期一部分
	delay_us(us);
	IIC_SCL_H;
	delay_us(us);
	if(IIC_SDA_In)
	{
		ack |=1;
	}
	//保持周期完整性
	IIC_SCL_L;
	delay_us(us);
	return ack;
}	
/*
函数名：IIC_SendData
函数功能：发送8bit数据并接收1bit应答
形参：
u8 data 发送8bit数据
u8 nus  SCL线拉高和拉低所需时间  
返回值：u8 在从机接收过来的应答位    0：应答    1：非应答
函数说明：
数据有效性：SCL高电平接收数据    SCL低电平发送数据
高位先发，一次8bit
*/
u8 IIC_SendData(u8 date,u8 us)
{
	for(int i=0;i<8;i++)
	{
		IIC_SCL_L; //拉低时钟线准备发送数据
		
		if(date &(0x80>>i))
		{
			IIC_SDA_H;
		}
		else
		{
			IIC_SDA_L;
		}
		delay_us(us);
		IIC_SCL_H;//拉高时钟线完成发送周期
		delay_us(us);
	}
	return IIC_RecAck(us);//返回1bit应答

}
/*
函数名：IIC_RecData
函数功能：接收8bit数据并发送1bit应答
形参：
u8 ack 发送应答位     0：应答    1：非应答
u8 nus  SCL线拉高和拉低所需时间  
返回值：u8 接收从机的8bit数据   
函数说明：
数据有效性：SCL高电平接收数据    SCL低电平发送数据
高位先发，一次8bit
*/

u8 IIC_RecData(u8 ack,u8 us)
{
	IIC_SDA_H;
	u8 date=0;
	for(int i=0;i<8;i++)
	{
		IIC_SCL_L;
		delay_us(us);
		IIC_SCL_H;//拉高时钟线准备接收数据
		date<<=1;
		if(IIC_SDA_In)
		{
			date |=1;
		}
		delay_us(us);
	}
	IIC_SendAck(ack,us);//发送一bit应答
	return date;



}
