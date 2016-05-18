
// ͨ�ö�ʱ��TIMx,x[2,3,4,5]��ʱӦ��
#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_TiMbase.h"

volatile u32 time = 0; // ms ��ʱ���� 


/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main(void)
{
	/* led �˿����� */ 
	LED_GPIO_Config();

	/* ͨ�ö�ʱ�� TIMx,x[2,3,4,5] ��ʱ���� */	
  TIMx_Configuration();
	
	/* ����ͨ�ö�ʱ�� TIMx,x[2,3,4,5]���ж����ȼ� */
	TIMx_NVIC_Configuration();

	/* ͨ�ö�ʱ�� TIMx,x[2,3,4,5] ���¿�ʱ�ӣ���ʼ��ʱ */
	macTIM_APBxClock_FUN (macTIM_CLK, ENABLE);
	
  while(1)
  {
    if ( time == 1000 ) /* 1000 * 1 ms = 1s ʱ�䵽 */
    {
      time = 0;
			/* LED1 ȡ�� */      
			LED1_TOGGLE; 
    }        
  }
}
/*********************************************END OF FILE**********************/

