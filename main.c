

#include "stm32f10x.h"

#define LED_PIN 13

int main(void)
{
	  long int i = 0;
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; // Enable GPIOC clock

    GPIOC->CRH &= ~(GPIO_CRH_CNF13 | GPIO_CRH_MODE13); // Clear CNF13 and MODE13 bits
    GPIOC->CRH |= GPIO_CRH_MODE13_0; // Set pin PC13 as output mode (max speed 10 MHz)

    while (1)
    {
			  if (i > 5000000 )
				{
					GPIOC->ODR ^= (1 << LED_PIN); // Toggle the LED on pin PC13
					i=0;
				}
				else
				{
					i++;
				}
				

    }
}