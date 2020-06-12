#include "sys.h"
#include "delay.h"  
#include "usart.h"  
#include "led.h"
#include "usmart.h"
#include "key.h"
#include "driver.h"



int main(void)
{   
 	u8 i;
	u8 keyval;
	u8 led0sta=1;
	
	u8 sen_old = 0x0f;
	u8 sen_new;
	
	Stm32_Clock_Init(432,25,2,9);//设置时钟,216Mhz
    delay_init(216);			//延时初始化  
	uart_init(108,115200);		//初始化串口波特率为115200
	usmart_dev.init(108); 		//初始化USMART	
	LED_Init();		  			//初始化与LED连接的硬件接口
	KEY_Init();					//初始化LED
	Driver_Init();				//驱动器初始化
	TIM8_OPM_RCR_Init(999,216-1); //1MHz计数频率  单脉冲+重复计数模式
	
	printf("红外传感器\r\n");
  while(1) 
	{		 	  
		keyval=KEY_Scan(0);
		
		if(keyval==WKUP_PRES)
		{
			Locate_Abs(0,500);//按下WKUP，回零点
		}
		
		else if(keyval==KEY0_PRES)
		{
			Locate_Rle(500,500,CW);//按下KEY0，以500Hz的频率 顺时针发200脉冲			
		}
		
		else if(keyval==KEY1_PRES)
		{
			Locate_Rle(400,500,CCW);//按下KEY1，以500Hz的频率 逆时针发400脉冲
		}	

		sen_new = GPIO_Read(GPIOI);
		if(sen_new != sen_old)
		{
			sen_old = sen_new;
			printf("当前传感器状态为:%x\r\n",sen_old);
		}
		delay_ms(10);
		i++;
		if(i==50)	
		{	
			i=0;
			LED1(led0sta^=1);		//LED1闪烁
		}
	} 
	
	
	
	
}



