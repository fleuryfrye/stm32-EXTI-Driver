
/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_it.h"
#include "EXTI.h"

static void EXTI_HandleLines(uint8_t firstPin, uint8_t lastPin)
{
  for (uint8_t pin = firstPin; pin <= lastPin; ++pin)
  {
    if ((EXTI->PR & (1U << pin)))
    {
      /* Clear interrupt by writing 1 to the pending bit. */
      EXTI->PR |= (1U << pin);
      
      EXTI_Callback_t callback = EXTIGetCallback(pin);
      if (callback != NULL)
      {
        callback();
      }
    }
  }
}

/**
  * @brief This function handles EXTI line 0 interrupt.
  */
void EXTI0_IRQHandler(void)
{
  EXTI_HandleLines(0U, 0U);
}

/**
  * @brief This function handles EXTI line 1 interrupt.
  */
void EXTI1_IRQHandler(void)
{
  EXTI_HandleLines(1U, 1U);
}

/**
  * @brief This function handles EXTI line 2 interrupt.
  */
void EXTI2_TSC_IRQHandler(void)
{
  EXTI_HandleLines(2U, 2U);
}

/**
  * @brief This function handles EXTI line 3 interrupt.
  */
void EXTI3_IRQHandler(void)
{
  EXTI_HandleLines(3U, 3U);
}

/**
  * @brief This function handles EXTI line 4 interrupt.
  */
void EXTI4_IRQHandler(void)
{
  EXTI_HandleLines(4U, 4U);
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles EXTI line 9 to 5 interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
  EXTI_HandleLines(5U, 9U);
}

/**
  * @brief This function handles EXTI line 15 to 10 interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
  EXTI_HandleLines(10U, 15U);
}

