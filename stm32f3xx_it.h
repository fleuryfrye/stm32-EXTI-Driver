
#ifndef __STM32F3xx_IT_H
#define __STM32F3xx_IT_H

#ifdef __cplusplus
 extern "C" {
#endif

void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_TSC_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler(void);


#ifdef __cplusplus
}
#endif

#endif /* __STM32F3xx_IT_H */
