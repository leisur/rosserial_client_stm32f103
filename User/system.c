#include "system.h"
//#include "stm32f4xx.h"
#include "stm32f10x.h"


uint32_t runtime = 0;

// ϵͳ�δ�ʱ��ʹ��
void Systick_Init(void)
{
 /*   if (SysTick_Config(SystemCoreClock / 1000))
    { 
        
        while (1);
    }
*/
	
  /* Setup SysTick Timer for 10 msec interrupts  */
  /*
	�������ڳ�ʼ��ʱ�����SystemInit��������ϵͳƵ����Ϊ72Mhz��
	��SystemCoreClock=72000000��
	��ô�������Ҫ1ms�Ķ�ʱ���ڣ�ֻ��Ҫ��������Ϊ72000
	*/
  if (SysTick_Config(SystemCoreClock / 1000))                //SysTick���ú���
  {
  /* Capture error */
    while (1);
  } 
 
  
}

// ms��ʱ����
void delay_ms(uint16_t msec)
{
    uint32_t target_time = runtime + msec;
    while(runtime <= target_time);
}

// NVIC����������
void NVIC_Configuration(void)
{
	//����NVIC�ṹ��
	NVIC_InitTypeDef nvic;
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
	//����nvic�Ĵ���ǿռλ���ڼ��飩
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
//    
/*	
//    ����DMA�ж�
//    nvic.NVIC_IRQChannel = USART3_IRQn;
	  nvic.NVIC_IRQChannel = DMA1_Channel2_IRQn;
	  //ǿռ���ȼ�������ԽСԽ��
//    nvic.NVIC_IRQChannelPreemptionPriority = 0;
	  nvic.NVIC_IRQChannelPreemptionPriority = 2;
	  //��Ӧ���ȼ�
//    nvic.NVIC_IRQChannelSubPriority = 0;
	  nvic.NVIC_IRQChannelSubPriority = 1;
      nvic.NVIC_IRQChannelCmd = ENABLE;
      NVIC_Init(&nvic);
*/	
	  //    ���ô����ж�
      nvic.NVIC_IRQChannel = USART1_IRQn;	  
	  //ǿռ���ȼ�������ԽСԽ��
	  nvic.NVIC_IRQChannelPreemptionPriority = 2;	  
	  //��Ӧ���ȼ�
      nvic.NVIC_IRQChannelSubPriority = 0;	  
      nvic.NVIC_IRQChannelCmd = ENABLE;
      NVIC_Init(&nvic);
	
	
	  /* Configure the SysTick handler priority */
	  NVIC_SetPriority(SysTick_IRQn, 0x0);                       //SysTick�ж����ȼ�����

}


void System_Init(void)
{
    NVIC_Configuration();
	
    Systick_Init();
}

// systick���� 1ms�Լ�һ��
extern "C" void SysTick_Handler(void)
{
    runtime++;
}



uint32_t System_GetTime(void)
{
    return runtime;
}
