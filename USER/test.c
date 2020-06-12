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
	
	Stm32_Clock_Init(432,25,2,9);//����ʱ��,216Mhz
    delay_init(216);			//��ʱ��ʼ��  
	uart_init(108,115200);		//��ʼ�����ڲ�����Ϊ115200
	usmart_dev.init(108); 		//��ʼ��USMART	
	LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();					//��ʼ��LED
	Driver_Init();				//��������ʼ��
	TIM8_OPM_RCR_Init(999,216-1); //1MHz����Ƶ��  ������+�ظ�����ģʽ
	
	printf("���⴫����\r\n");
  while(1) 
	{		 	  
		keyval=KEY_Scan(0);
		
		if(keyval==WKUP_PRES)
		{
			Locate_Abs(0,500);//����WKUP�������
		}
		
		else if(keyval==KEY0_PRES)
		{
			Locate_Rle(500,500,CW);//����KEY0����500Hz��Ƶ�� ˳ʱ�뷢200����			
		}
		
		else if(keyval==KEY1_PRES)
		{
			Locate_Rle(400,500,CCW);//����KEY1����500Hz��Ƶ�� ��ʱ�뷢400����
		}	

		sen_new = GPIO_Read(GPIOI);
		if(sen_new != sen_old)
		{
			sen_old = sen_new;
			printf("��ǰ������״̬Ϊ:%x\r\n",sen_old);
		}
		delay_ms(10);
		i++;
		if(i==50)	
		{	
			i=0;
			LED1(led0sta^=1);		//LED1��˸
		}
	} 
	
	
	
	
}



