/***************************************************************
* File     : rf_stm32f1_delay.h
***************************************************************/

/***************************************************************
// Header Files Includes
***************************************************************/
#include "stm32f10x.h"
#include "core_cm3.h"


#define SysTick_CLKSource_HCLK_Div8    ((uint32_t)0xFFFFFFFB)
#define SysTick_CLKSource_HCLK         ((uint32_t)0x00000004)
#define IS_SYSTICK_CLK_SOURCE(SOURCE) (((SOURCE) == SysTick_CLKSource_HCLK) || \
                                       ((SOURCE) == SysTick_CLKSource_HCLK_Div8))
/***************************************************************
* Global Function
***************************************************************/
void FM_delay_init(void);
void delay_ms(u16 nms);
void delay_us(u32 nus);

/***************************************************************/
