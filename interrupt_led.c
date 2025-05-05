#include<stm32f10x.h>
void delay(unsigned int cnt)
{
	while(cnt--);
}
void EXTI0_IRQHandler()
{
	if(EXTI->PR&1<<0)
	{
		GPIOB->BRR=1<<0;
		GPIOB->ODR=1<<1;
		delay(500000);
		GPIOB->BRR=1<<1;
		delay(500000);
	}
	EXTI->PR=1<<0;
}
int main()
{
	RCC->CR=0X00000083;
	RCC->CFGR=0X00000000;
	RCC->APB2ENR=1<<0|1<<2|1<<3;
	GPIOA->CRL=0X00000008;
	GPIOB->CRL=0X00000022;
	AFIO->EXTICR[0]=0X00000000;
	EXTI->IMR=1<<0;
	EXTI->RTSR=1<<0;
	EXTI->FTSR=0;
	NVIC_EnableIRQ(EXTI0_IRQn);//ENABLING THE INTERRUPT
	
	while(1)
	{
		GPIOB->ODR=1<<0;
	}
}