/*
 * MIT License
 * Copyright (c) 2017 - 2022 _VIFEXTech
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "eg32m0xx.h"
#include "libcore/exti.h"
#include "libcore/gpio.h"

#define EXTI_GetPortSourceGPIOx(Pin) GPIO_GetPortNum(Pin)
#define EXTI_GetPinSourcex(Pin)      GPIO_GetPinNum(Pin)

static EXTI_CallbackFunction_t EXTIA_Function[16] = {0};
static EXTI_CallbackFunction_t EXTIB_Function[16] = {0};
static EXTI_CallbackFunction_t EXTIC_Function[16] = {0};

/**
  * @brief  获取外部中断的中断通道
  * @param  Pin: 引脚编号
  * @retval 通道编号
  */
static IRQn_Type EXTI_GetIRQn(uint8_t Pin)
{
    IRQn_Type EXINTx_IRQn = GPIOA_IRQn;
    uint8_t PortNum = GPIO_GetPortNum(Pin);


    switch(PortNum)
    {
    case 0:
        EXINTx_IRQn = GPIOA_IRQn;
        break;
    case 1:
        EXINTx_IRQn = GPIOB_IRQn;
        break;
    case 2:
        EXINTx_IRQn = GPIOC_IRQn;
        break;
    }

    return EXINTx_IRQn;
}

/**
  * @brief  外部中断初始化
  * @param  Pin: 引脚编号
  * @param  Function: 回调函数
  * @param  Trigger_Mode: 触发方式
  * @param  PreemptionPriority: 抢占优先级
  * @param  SubPriority: 子优先级
  * @retval 无
  */
void EXTIx_Init(
    uint8_t Pin,
    EXTI_CallbackFunction_t Function,
    TPYE_ENUM_LL_GPIO_TG_EDGE line_polarity,
    uint8_t PreemptionPriority,
    uint8_t SubPriority
)
{
    if(!IS_PIN(Pin))
        return;

    if (PIN_MAP[Pin].GPIOx == GPIOA)
    {
        EXTIA_Function[Pin % 16] = Function;
    }else if (PIN_MAP[Pin].GPIOx == GPIOB)
    {
        EXTIB_Function[Pin % 16] = Function;
    }else if (PIN_MAP[Pin].GPIOx == GPIOC)
    {
        EXTIC_Function[Pin % 16] = Function;
    }

    ll_gpio_set_pin(PIN_MAP[Pin].GPIOx, PIN_MAP[Pin].GPIO_Pin_x, LL_GPIO_MODE_IN, LL_GPIO_TYPE_OUT_OD, LL_GPIO_PUPD_UP);

    ll_gpio_irq_config(PIN_MAP[Pin].GPIOx, PIN_MAP[Pin].GPIO_Pin_x, line_polarity);
    ll_gpio_irq_enable(PIN_MAP[Pin].GPIOx, PIN_MAP[Pin].GPIO_Pin_x);

    NVIC_EnableIRQ(EXTI_GetIRQn(Pin));
}

/**
  * @brief  外部中断初始化 (Arduino)
  * @param  Pin: 引脚编号
  * @param  function: 回调函数
  * @param  Trigger_Mode: 触发方式
  * @retval 无
  */
void attachInterrupt(uint8_t Pin, EXTI_CallbackFunction_t Function, TPYE_ENUM_LL_GPIO_TG_EDGE line_polarity)
{
    EXTIx_Init(
        Pin,
        Function,
        line_polarity,
        EXTI_PREEMPTIONPRIORITY_DEFAULT,
        EXTI_SUBPRIORITY_DEFAULT
    );
}

/**
  * @brief  关闭给定的中断 (Arduino)
  * @param  Pin: 引脚编号
  * @retval 无
  */
void detachInterrupt(uint8_t Pin)
{
    if(!IS_PIN(Pin))
        return;

    ll_gpio_irq_disable(PIN_MAP[Pin].GPIOx, PIN_MAP[Pin].GPIO_Pin_x);
}

/**
  * @brief  外部中断入口，通道0
  * @param  无
  * @retval 无
  */
void GPIOA_IRQHandler(void)
{
    for (int pin = 0; pin <= 15; pin ++)
    {
        if (LL_GPIO_PENDING_GET(GPIOB, 1 << pin))
        {
            if(EXTIA_Function[pin])
                EXTIA_Function[pin]();
            LL_GPIO_PENDING_CLR(GPIOB, 1 << pin);
        }
    }}

/**
  * @brief  外部中断入口，通道1
  * @param  无
  * @retval 无
  */
void GPIOB_IRQHandler(void)
{
    for (int pin = 0; pin <= 15; pin ++)
    {
        if (LL_GPIO_PENDING_GET(GPIOB, 1 << pin))
        {
            if(EXTIB_Function[pin])
                EXTIB_Function[pin]();
            LL_GPIO_PENDING_CLR(GPIOB, 1 << pin);
        }
    }
}

/**
  * @brief  外部中断入口，通道2
  * @param  无
  * @retval 无
  */
void GPIOC_IRQHandler(void)
{
    for (int pin = 0; pin < 16; pin ++)
    {
        if (LL_GPIO_PENDING_GET(GPIOC, 1 << pin))
        {
            if(EXTIC_Function[pin])
                EXTIC_Function[pin]();
            LL_GPIO_PENDING_CLR(GPIOC, 1 << pin);
        }
    }
}
