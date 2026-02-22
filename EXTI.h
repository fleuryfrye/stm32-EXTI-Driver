#ifndef EXTI_H
#define EXTI_H

#include <stdint.h>
#include "stm32f3xx.h"

typedef enum
{
    EXTI_RISING_EDGE = 0,
    EXTI_FALLING_EDGE = 1,
    EXTI_ANY_EDGE = 2
} EXTI_INT_SOURCE_t;

typedef void (*EXTI_Callback_t)(void);

void initEXTI(GPIO_TypeDef *port, uint8_t pin);
void EXTISetSource(GPIO_TypeDef *port, uint8_t pin, EXTI_INT_SOURCE_t source, EXTI_Callback_t callback);

#endif /* EXTI_H */
