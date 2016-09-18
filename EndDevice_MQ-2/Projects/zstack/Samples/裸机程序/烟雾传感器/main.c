/**************************************/
/*           WeBee团队                  */
/*         Zigbee学习例程               */
/*例程名称：烟雾传感器                   */
/*建立时间：2012/10                     */
/*描述：通过烟雾传感器，通过LED1指示
**************************************/
#include <ioCC2530.h>

#define uint unsigned int
#define uchar unsigned char

//定义控制LED灯的端口
#define LED1 P1_0	//LED1为P1.0口控制
#define AIR P2_0      //光敏为P2.0口控制

//函数声明
void Delayms(uint);		//延时函数
void InitLed(void);		//初始化LED1
void AirInit();                 //光敏初始化
uchar AirScan();                //烟雾扫描程序

/****************************
延时函数
*****************************/
void Delayms(uint xms)   //i=xms 即延时i毫秒
{
 uint i,j;
 for(i=xms;i>0;i--)
   for(j=587;j>0;j--);
}

/****************************
      LED初始化函数
*****************************/
void InitLed(void)
{
	P1DIR |= 0x01;  //P1_0定义为输出
        LED1 = 1;       //LED1灯熄灭     
}

/****************************
     按键初始化函数
*****************************/
void AirInit()
{
  P2SEL &= ~0X01;     //设置P20为普通IO口  
  P2DIR &= ~0X01;    // 在P20口，设置为输入模式 
  P2INP &=  ~0x01;   //打开P20上拉电阻,不影响
}

/****************************
     烟雾检测函数
*****************************/
uchar AirScan(void)
{
  if(AIR==0)
  {Delayms(10);
      if(AIR==0)
      {
      
        return 1;   // 无烟雾
      }
  }
  return 0;           //有烟雾
}

/***************************
      主函数
***************************/
void main(void)
{
	InitLed();		//调用初始化函数
	AirInit();
        while(1)
	{
         if(AirScan())       //按键改变LED状态
           LED1=1;    //无烟雾，LED1灭掉
         else
           LED1=0;   //有烟雾，LED1点亮
        }
}
