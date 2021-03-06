/**
  ******************************************************************************
  * @file    main.c
  * @author  Auto-generated by STM32CubeIDE
  * @version V1.0
  * @brief   Default main function.
  ******************************************************************************
*/

#include <string.h>
#include "stm32f407xx.h"


void Delay(uint32_t counter)
{
	for(uint32_t i=0;i<counter;i++);
}

void OutputTest_PP(GPIO_Handle_t GPIO_Handle,GPIO_TypeDef *pGPIOx,uint8_t GPIO_PinNumber)
{
	GPIO_Handle.pGPIOx = pGPIOx;
	GPIO_Handle.GPIO_PinConfig.GPIO_PinNumber = GPIO_PinNumber;
	GPIO_Handle.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIO_Handle.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIO_Handle.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OP_SPEED_LOW;
	GPIO_Handle.GPIO_PinConfig.GPIO_PuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&GPIO_Handle);
}

void OutputTest_OD(GPIO_Handle_t GPIO_Handle,GPIO_TypeDef *pGPIOx,uint8_t GPIO_PinNumber)
{
	GPIO_Handle.pGPIOx = pGPIOx;
	GPIO_Handle.GPIO_PinConfig.GPIO_PinNumber = GPIO_PinNumber;
	GPIO_Handle.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIO_Handle.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
	GPIO_Handle.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OP_SPEED_LOW;
	GPIO_Handle.GPIO_PinConfig.GPIO_PuPdControl = GPIO_PIN_PU;

	GPIO_Init(&GPIO_Handle);
}

void InputTestIT(GPIO_Handle_t GPIO_Handle,GPIO_TypeDef *pGPIOx,uint8_t GPIO_PinNumber)
{
	GPIO_Handle.pGPIOx = pGPIOx;
	GPIO_Handle.GPIO_PinConfig.GPIO_PinNumber = GPIO_PinNumber;
	GPIO_Handle.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	GPIO_Handle.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OP_SPEED_LOW;
	GPIO_Handle.GPIO_PinConfig.GPIO_PuPdControl = GPIO_NO_PUPD; //On discovery board there is a external pull_down resistor on PA0
																//So there is no need to internal PD resistor

	GPIO_Init(&GPIO_Handle);

}
int main(void)
{
	//On STM32F4 DISCOVERY PD12->Green_LED PD13->Orange_LED PD14->Red_LED PD15->Blue_LED
	//On STM32F4 DISCOVERY PA0->User_Button

	GPIO_Handle_t GPIO_OUT_PP;

	//Reset all elements in GPIO_OUT_PP
	memset(&GPIO_OUT_PP,0,sizeof(GPIO_OUT_PP));

	//Configure GPIO PORT D PIN 12 OUTPUT TYPE PUSH_PULL
	OutputTest_PP(GPIO_OUT_PP, GPIOD, GPIO_PIN_NO_12);

	GPIO_Handle_t GPIO_OUT_OD;

	//Reset all elements in GPIO_OUT_PP
	memset(&GPIO_OUT_OD,0,sizeof(GPIO_OUT_OD));

	//Configure GPIO PORT D PIN 12 OUTPUT TYPE OPEN_DRAIN
	OutputTest_OD(GPIO_OUT_OD, GPIOD, GPIO_PIN_NO_13);


	GPIO_Handle_t GPIO_IN_IT;

	//Reset all elements in GPIO_OUT_PP
	memset(&GPIO_IN_IT,0,sizeof(GPIO_IN_IT));

	//Configure GPIO PORT A PIN 0 INPUT
	//PA0 Triggers the EXTI0 Interrupt
	InputTestIT(GPIO_IN_IT, GPIOA, GPIO_PIN_NO_0);

	GPIO_Handle_t GPIO_OUT_IT;

	//Reset all elements in GPIO_OUT_PP
	memset(&GPIO_OUT_IT,0,sizeof(GPIO_OUT_IT));

	//Configure GPIO PORT D PIN 14 OUTPUT TYPE PUSH_PULL
	OutputTest_PP(GPIO_OUT_IT, GPIOD, GPIO_PIN_NO_14);		//This led will toggle with GPIO Interrupt


	GPIO_IRQPriorityConfig(EXTI0_IRQn, NVIC_IRQ_PRI5);
	GPIO_IRQITConfig(EXTI0_IRQn, ENABLE);

	for(;;)
	{
		GPIO_Toggle_Pin(GPIOD, GPIO_PIN_NO_12);
		GPIO_Toggle_Pin(GPIOD, GPIO_PIN_NO_13);
		Delay(500000);
	}
}

void EXTI0_IRQHandler(void)
{

	Delay(50000/2);		//Delay avoids debouncing
	GPIO_IRQ_Handling(GPIO_PIN_NO_0);
	GPIO_Toggle_Pin(GPIOD, GPIO_PIN_NO_14);


}
