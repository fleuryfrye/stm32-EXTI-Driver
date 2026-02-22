#include "EXTI.h"

#define SYSCFG_EXTI_BITMASK 0xF
#define SYSCFG_SET_EXTI_SOURCE(select, pin) ((select) << (4 * (pin % 4)))

volatile uint8_t extTriggered = 0;
static EXTI_Callback_t extiCallbacks[16] = {0};

static inline void EXTI_MaskPin(uint8_t pin);
static inline void EXTI_UnmaskPin(uint8_t pin);
static EXTI_Callback_t EXTIGetCallback(uint8_t pin);


void initEXTI(GPIO_TypeDef *port, uint8_t pin)
{
    __HAL_RCC_SYSCFG_CLK_ENABLE();

    switch (pin)
    {
        case 0:
            NVIC_EnableIRQ(EXTI0_IRQn);
            break;
        case 1:
            NVIC_EnableIRQ(EXTI1_IRQn);
            break;
        case 2:
            NVIC_EnableIRQ(EXTI2_TSC_IRQn);
            break;
        case 3:
            NVIC_EnableIRQ(EXTI3_IRQn);
            break;
        case 4:
            NVIC_EnableIRQ(EXTI4_IRQn);
            break;
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            NVIC_EnableIRQ(EXTI9_5_IRQn);
            break;
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            NVIC_EnableIRQ(EXTI15_10_IRQn);
            break;
        default:
            return;
    }

    uint32_t *syscfg_exticr_start = (uint32_t *)SYSCFG->EXTICR;
    uint32_t *syscfg_exticr = syscfg_exticr_start + (pin / 4);

    *syscfg_exticr &= ~(SYSCFG_SET_EXTI_SOURCE(SYSCFG_EXTI_BITMASK, pin));
    uint16_t syscfg_select_port = 0;
    if (port == GPIOA) {
        syscfg_select_port = 0x0;
    } else if (port == GPIOB) {
        syscfg_select_port = 0x1;
    } else if (port == GPIOF) {
        syscfg_select_port = 0x5;
    } else {
        return;
    }

    /* Select pin source for EXTI multiplexor */
    *syscfg_exticr |= SYSCFG_SET_EXTI_SOURCE(syscfg_select_port, pin);
}

void deinitEXTI(GPIO_TypeDef *port, uint8_t pin)
{
    EXTI_MaskPin(pin);
    uint32_t *syscfg_exticr_start = (uint32_t *)SYSCFG->EXTICR;
    uint32_t *syscfg_exticr = syscfg_exticr_start + (pin / 4);
    *syscfg_exticr &= ~(SYSCFG_SET_EXTI_SOURCE(SYSCFG_EXTI_BITMASK, pin));
}


void EXTISetSource(GPIO_TypeDef *port, uint8_t pin, EXTI_INT_SOURCE_t source, EXTI_Callback_t callback)
{
    if (pin > 15U)
    {
        return;
    }

    initEXTI(port, pin);
    extiCallbacks[pin] = callback;

    EXTI->RTSR &= ~(1U << pin);
    EXTI->FTSR &= ~(1U << pin);

    if (source == EXTI_RISING_EDGE || source == EXTI_ANY_EDGE)
    {
        EXTI->RTSR |= (1U << pin);
    }

    if (source == EXTI_FALLING_EDGE || source == EXTI_ANY_EDGE)
    {
        EXTI->FTSR |= (1U << pin);
    }

    EXTI_UnmaskPin(pin);
}

EXTI_Callback_t EXTIGetCallback(uint8_t pin)
{
    if (pin > 15U)
    {
        return NULL;
    }

    return extiCallbacks[pin];
}

static inline void EXTI_MaskPin(uint8_t pin)
{
    EXTI->IMR &= ~(1U << pin);
}

static inline void EXTI_UnmaskPin(uint8_t pin)
{
    EXTI->IMR |= (1U << pin);
}

