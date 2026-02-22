# STM32F3 EXTI Driver

Lightweight EXTI (external interrupt) helper for STM32F3 devices. It configures the EXTI line source, edge selection, and callback dispatch, with ISR handlers that fan out by pin.

## Files
- `EXTI.c` / `EXTI.h`: Driver API and EXTI configuration.
- `stm32f3xx_it.c` / `stm32f3xx_it.h`: EXTI ISR implementations that call your callbacks.
- `STM32F3xx/Include/`: Device headers used by the driver.

## Requirements
- STM32F3 device headers (`stm32f3xx.h`) available in your include path.
- CMSIS definition for `NVIC_EnableIRQ()`.
- EXTI line source mapping supports GPIOA, GPIOB, GPIOF.

## Quick Start
1. Add `EXTI.c` and `stm32f3xx_it.c` to your build.
2. Add `EXTI.h` and `stm32f3xx_it.h` to your include path.
3. Ensure your vector table references the EXTI ISRs from `stm32f3xx_it.c`.
4. Configure your GPIO pin as input with the desired pull and speed.
5. Register a callback with `EXTISetSource()`.

## API
```c
void initEXTI(GPIO_TypeDef *port, uint8_t pin);
void deinitEXTI(GPIO_TypeDef *port, uint8_t pin);
void EXTISetSource(GPIO_TypeDef *port, uint8_t pin, EXTI_INT_SOURCE_t source, EXTI_Callback_t callback);
EXTI_Callback_t EXTIGetCallback(uint8_t pin);
```

## Example
```c
#include "EXTI.h"

static void on_button(void)
{
    // Handle button press
}

void app_init(void)
{
    // Configure GPIOA pin 0 as input elsewhere
    EXTISetSource(GPIOA, 0, EXTI_FALLING_EDGE, on_button);
}
```

## Notes
- The driver enables the corresponding IRQ based on the pin number.
- EXTI callbacks are dispatched from the ISR handlers in `stm32f3xx_it.c`.
- Supported ports for EXTI source selection: `GPIOA`, `GPIOB`, `GPIOF`.
- `deinitEXTI()` masks the EXTI line and clears the SYSCFG EXTI source selection for that pin.
