#include "includes\stm32f10x.h"
#include "includes\rf_stm32f1_led.h"
#include "Includes\rf_stm32f1_delay.h"
#include "Includes\stm32f10x_gpio.h"
#include "Includes\stm32f10x_usart.h"
#include "Includes\stm32f10x_rcc.h"


const char MyStr[8]={'M','a','h','m','o','u','d'};



/**********************************************************
 * Setup a User Push Button on Port B15
 *********************************************************/
static void button_setup(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

	// Clock Enable
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // Configure as digital input
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/*****************************************************
 * Initialize USART1: enable interrupt on reception
 * of a character
 *****************************************************/
void USART1_Init(void)
{
    /* USART configuration structure for USART1 */
    USART_InitTypeDef usart1_init_struct;
    /* Bit configuration structure for GPIOA PIN9 and PIN10 */
    GPIO_InitTypeDef gpioa_init_struct;

    /* Enable clock for USART1, AFIO and GPIOA */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO |
                           RCC_APB2Periph_GPIOA, ENABLE);

    /* GPIOA PIN9 alternative function Tx */
    gpioa_init_struct.GPIO_Pin = GPIO_Pin_9;
    gpioa_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
    gpioa_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &gpioa_init_struct);
    /* GPIOA PIN10 alternative function Rx */
    gpioa_init_struct.GPIO_Pin = GPIO_Pin_10;
    gpioa_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
    gpioa_init_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &gpioa_init_struct);

    /* Enable USART1 */
    USART_Cmd(USART1, ENABLE);
    /* Baud rate 9600, 8-bit data, One stop bit
     * No parity, Do both Rx and Tx, No HW flow control
     */
    usart1_init_struct.USART_BaudRate = 9600;
    usart1_init_struct.USART_WordLength = USART_WordLength_8b;
    usart1_init_struct.USART_StopBits = USART_StopBits_1;
    usart1_init_struct.USART_Parity = USART_Parity_No ;
    usart1_init_struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    usart1_init_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    /* Configure USART1 */
    USART_Init(USART1, &usart1_init_struct);
    /* Enable RXNE interrupt */
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    /* Enable USART1 global interrupt */
    NVIC_EnableIRQ(USART1_IRQn);
}

/**********************************************************
 * USART Send a character
 *********************************************************/
void UU_PutChar(USART_TypeDef* USARTx, uint8_t ch)
{
  while(!(USARTx->SR & USART_SR_TXE));
  USARTx->DR = ch;
}

/**********************************************************
 * USART Send a string of data
 *********************************************************/
void UU_PutString(USART_TypeDef* USARTx, uint8_t * str)
{
  while(*str != 0)
  {
    UU_PutChar(USARTx, *str);
    str++;
  }
}

/**********************************************************
 * USART1 interrupt request handler: on reception of a
 * character 't', transmit a string
 *********************************************************/
void USART1_IRQHandler(void)
{
    /* RXNE handler */
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        /* If received 't', toggle LED and transmit 'T' */
        if((char)USART_ReceiveData(USART1) == 't')
        {
            /* Other actions like toggle LED can also be performed here */
            UU_PutString(USART1, "Hello\r\n");
            /* Wait until Tx data register is empty, not really
             * required for this example but put in here anyway.
             */
            /*
            while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
            {
            }*/
        }
    }

    /* ------------------------------------------------------------ */
    /* Other USART1 interrupts handler can go here ...             */
}



int main(void)
{
    // initialize the system frequency @ 56Mhz
    SystemInit();
    // Delay initialize
    delay_init();
    // all LED initialize
    FM_Led_Init();
	/* Initialize USART1 */
    USART1_Init();


    while (1)
    {
        
            delay_ms(500);
			FM_Led_Toggle(LED_1);
			UU_PutString(USART1, "Button Pushed\r\n");
				
    }
}