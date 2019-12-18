/**
  ******************************************************************************
  * @file    main.c
  * @author  Auto-generated by STM32CubeIDE
  * @version V1.0
  * @brief   Default main function.
  ******************************************************************************
*/

#include "stm32f407xx.h"
#include <stdio.h>
#include <string.h>


void Delay(void)
{
	for(uint32_t i=0;i<500000;i++);
}



int main(void)
{
	GPIO_Handle_t GPIOLED;

	memset(&GPIOLED,0,sizeof(GPIOLED));

	GPIOLED.pGPIOx = GPIOD;
	GPIOLED.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GPIOLED.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIOLED.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOLED.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OP_SPEED_LOW;
	GPIOLED.GPIO_PinConfig.GPIO_PuPdControl = GPIO_NO_PUPD;

	GPIO_PCLK_Control(GPIOD, ENABLE);

	GPIO_Init(&GPIOLED);

	GPIO_Handle_t Button;

	memset(&Button,0,sizeof(Button));

	Button.pGPIOx = GPIOA;
	Button.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	Button.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	Button.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OP_SPEED_LOW;
	Button.GPIO_PinConfig.GPIO_PuPdControl = GPIO_NO_PUPD;

	GPIO_PCLK_Control(GPIOA, ENABLE);

	GPIO_Init(&Button);

	GPIO_IRQPriorityConfig(EXTI0_IRQn, NVIC_IRQ_PRI5);
	GPIO_IRQITConfig(EXTI0_IRQn, ENABLE);

	for(;;)
	{

	}
}


void EXTI0_IRQHandler(void)
{
	Delay();

	GPIO_IRQ_Handling(GPIO_PIN_NO_0);

	GPIO_Toggle_Pin(GPIOD, GPIO_PIN_NO_12);

}