
// ͨ�ö�ʱ��TIMx,x[2,3,4,5]��ʱӦ��
#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_TiMbase.h"
#include "bsp_exti.h"
#include "bsp_lcd.h"
#include "hcsr.h"
#include <stdio.h>

#define CLI() __set_PRIMASK(1)				/* �����ж� */  
#define SEI() __set_PRIMASK(0)				/* �����ж� */ 

volatile u32 triger_time = 0; // us triger��ʱ����,>10us
volatile u32 echo_time = 0;   // us echo��ʱ����, =����*2/����

uint8_t echo_flag = 0;				// echo_flag=1 ->���յ��ز��ź�


/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main(void)
{
	float height = 0;
	char cStr[10];
	
	/* led �˿����� */ 
	LED_GPIO_Config();
	
	//CLI();
	//SEI();
	
	/* exti line config */
	EXTI_Pxy_Config(); 		//����PB9Ϊ�������жϣ�PB9->Echo

	/* ͨ�ö�ʱ�� TIMx,x[2,3,4,5] ��ʱ���� */	
  TIMx_Configuration();
	
	/* ����ͨ�ö�ʱ�� TIMx,x[2,3,4,5]���ж����ȼ� */
	TIMx_NVIC_Configuration();
	
	LCD_Init ();         //LCD ???
	
  ILI9341_GramScan ( 1 );
  ILI9341_Clear ( 0, 0, 240, 320, macBACKGROUND);
	ILI9341_DispChar_EN ( 60, 60, 'A', macBACKGROUND, macRED );
	
	LED3_ON;
  while(1)
  {
		Triger();
		LED1_ON;
		
		echo_time = 0;
		
		echo_flag = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9);
		while(echo_flag == 0)				//�ȴ��յ��ز��ź�
		{
			LED1_OFF;LED2_ON;
			echo_flag = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9);
		}
		echo_time = 0;
		while(echo_flag)						//�ȴ��ز��źŽ������
		{
			LED2_OFF;LED3_ON;
			echo_flag = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9);
		}
		macTIM_APBxClock_FUN (macTIM_CLK, DISABLE);
		height = Calculation();
		sprintf(cStr,"%0.2f",height);
		ILI9341_DispString_EN ( 60, 60, cStr, macBACKGROUND, macRED );
		
  }
}
/*********************************************END OF FILE**********************/

