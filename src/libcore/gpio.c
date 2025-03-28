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
#include "libcore/gpio.h"
#include "eg32m0xx_ll_gpio.h"
#include "eg32m0xx_ll_adc.h"

const PinInfo_TypeDef PIN_MAP[PIN_MAX] =
{
    /*GPIO_Type* GPIOx;  //对应GPIOx地址
    TIM_Type* TIMx;      //对应TIMx地址
    ADC_Type* ADCx;      //对应ADCx地址

    uint16_t GPIO_Pin_x;    //对应GPIO_Pin位
    uint8_t TimerChannel;   //对应定时器通道
    uint8_t ADC_CHANNEL;*/  //对应ADC通道
    {GPIOA, TIM2, ADC,  GPIO_Pin_0, 3, ADC_CHANNEL_0}, /* PA0 */
    {GPIOA, TIM2, ADC,  GPIO_Pin_1, 2, ADC_CHANNEL_1}, /* PA1 */
    {GPIOA, TIM3, ADC,  GPIO_Pin_2, 1, ADC_CHANNEL_2}, /* PA2 */
    {GPIOA, TIM2, ADC,  GPIO_Pin_3, 4, ADC_CHANNEL_3}, /* PA3 */
    {GPIOA, TIM4, ADC,  GPIO_Pin_4, 1, ADC_CHANNEL_4}, /* PA4 */
    {GPIOA, TIM2, ADC,  GPIO_Pin_5, 1, ADC_CHANNEL_5}, /* PA5 */
    {GPIOA, TIM5, ADC,  GPIO_Pin_6, 1, ADC_CHANNEL_6}, /* PA6 */
    {GPIOA, TIM3, ADC,  GPIO_Pin_7, 2, ADC_CHANNEL_7}, /* PA7 */

    {GPIOA, TIM1, NULL,  GPIO_Pin_8, 1, ADC_CHANNEL_X}, /* PA8 */
    {GPIOA, TIM1, NULL,  GPIO_Pin_9, 2, ADC_CHANNEL_X}, /* PA9 */
    {GPIOA, TIM1, NULL, GPIO_Pin_10, 3, ADC_CHANNEL_X}, /* PA10 */
    {GPIOA, TIM1, NULL, GPIO_Pin_11, 4, ADC_CHANNEL_X}, /* PA11 */

    {GPIOA, NULL, NULL, GPIO_Pin_12, 0, ADC_CHANNEL_X}, /* PA12 */
    {GPIOA, NULL, NULL, GPIO_Pin_13, 0, ADC_CHANNEL_X}, /* PA13 */
    {GPIOA, NULL, NULL, GPIO_Pin_14, 0, ADC_CHANNEL_X}, /* PA14 */
    {GPIOA, TIM6, NULL, GPIO_Pin_15, 1, ADC_CHANNEL_X}, /* PA15 */

    {GPIOB, TIM3, ADC,  GPIO_Pin_0, 3, ADC_CHANNEL_8}, /* PB0 */
    {GPIOB, NULL, ADC,  GPIO_Pin_1, 0, ADC_CHANNEL_9}, /* PB1 */
    {GPIOB, TIM4, NULL,  GPIO_Pin_2, 1, ADC_CHANNEL_X}, /* PB2 */
    {GPIOB, NULL, ADC,  GPIO_Pin_3, 2, ADC_CHANNEL_10}, /* PB3 */
    {GPIOB, NULL, ADC,  GPIO_Pin_4, 0, ADC_CHANNEL_11}, /* PB4 */
    {GPIOB, NULL, NULL,  GPIO_Pin_5, 0, ADC_CHANNEL_X}, /* PB5 */
    {GPIOB, NULL, NULL,  GPIO_Pin_6, 0, ADC_CHANNEL_X}, /* PB6 */
    {GPIOB, NULL, ADC,  GPIO_Pin_7, 0, ADC_CHANNEL_12}, /* PB7 */
    {GPIOB, NULL, NULL,  GPIO_Pin_8, 0, ADC_CHANNEL_X}, /* PB8 */
    {GPIOB, NULL, NULL,  GPIO_Pin_9, 0, ADC_CHANNEL_X}, /* PB9 */
    {GPIOB, NULL, NULL, GPIO_Pin_10, 3, ADC_CHANNEL_X}, /* PB10 */
    {GPIOB, NULL, NULL, GPIO_Pin_11, 4, ADC_CHANNEL_X}, /* PB11 */
    {GPIOB, NULL, NULL, GPIO_Pin_12, 0, ADC_CHANNEL_X}, /* PB12 */
    {GPIOB, NULL, NULL, GPIO_Pin_13, 0, ADC_CHANNEL_X}, /* PB13 */
    {GPIOB, NULL, NULL, GPIO_Pin_14, 0, ADC_CHANNEL_X},/* PB14 */
    {GPIOB, NULL, NULL, GPIO_Pin_15, 0, ADC_CHANNEL_X}, /* PB15 */

    {GPIOC, NULL, NULL,  GPIO_Pin_0, 0, ADC_CHANNEL_X},/* PC0 */
    {GPIOC, NULL, NULL,  GPIO_Pin_1, 0, ADC_CHANNEL_X},/* PC1 */
    {GPIOC, NULL, NULL,  GPIO_Pin_2, 0, ADC_CHANNEL_X},/* PC2 */
    {GPIOC, TIM5, NULL,  GPIO_Pin_3, 1, ADC_CHANNEL_X},/* PC3 */
    {GPIOC, TIM5, NULL,  GPIO_Pin_4, 2, ADC_CHANNEL_X},/* PC4 */
    {GPIOC, NULL, NULL,  GPIO_Pin_5, 0, ADC_CHANNEL_X},/* PC5 */
    {GPIOC, TIM6, NULL,  GPIO_Pin_6, 2, ADC_CHANNEL_X}, /* PC6 */
    {GPIOC, NULL, NULL,  GPIO_Pin_7, 2, ADC_CHANNEL_X}, /* PC7 */
    {GPIOC, NULL, NULL,  GPIO_Pin_8, 3, ADC_CHANNEL_X}, /* PC8 */
    {GPIOC, NULL, NULL,  GPIO_Pin_9, 4, ADC_CHANNEL_X}, /* PC9 */
    {GPIOC, NULL, NULL, GPIO_Pin_10, 0, ADC_CHANNEL_X}, /* PC10 */
    {GPIOC, NULL, NULL, GPIO_Pin_11, 0, ADC_CHANNEL_X}, /* PC11 */
    {GPIOC, NULL, NULL, GPIO_Pin_12, 0, ADC_CHANNEL_X}, /* PC12 */
    {GPIOC, NULL, NULL, GPIO_Pin_13, 0, ADC_CHANNEL_X}, /* PC13 */
    {GPIOC, NULL, NULL, GPIO_Pin_14, 0, ADC_CHANNEL_X}, /* PC14 */
    {GPIOC, NULL, NULL, GPIO_Pin_15, 0, ADC_CHANNEL_X}, /* PC15 */
};

/**
  * @brief  GPIO初始化
  * @param  GPIOx: GPIO地址
  * @param  GPIO_Pin_x: GPIO对应位
  * @param  GPIO_Mode_x: GPIO模式
  * @param  GPIO_Speed_x: GPIO速度
  * @retval 无
  */
void GPIOx_Init(gpio_type* GPIOx, uint16_t GPIO_Pin_x, PinMode_TypeDef Mode)
{
    TYPE_LL_GPIO_INIT gpio_init_struct = {0};

    gpio_init_struct.gpio_pin = GPIO_Pin_x;

    if(Mode == INPUT)
    {
        gpio_init_struct.gpio_mode = LL_GPIO_MODE_IN;
        gpio_init_struct.gpio_type = LL_GPIO_TYPE_OUT_OD;
    }
    else if(Mode == INPUT_PULLUP)
    {
        gpio_init_struct.gpio_mode = LL_GPIO_MODE_IN;
        gpio_init_struct.gpio_pupd = LL_GPIO_PUPD_UP;
    }
    else if(Mode == INPUT_PULLDOWN)
    {
        gpio_init_struct.gpio_mode = LL_GPIO_MODE_IN;
        gpio_init_struct.gpio_pupd = LL_GPIO_PUPD_DOWN;
    }
    else if(Mode == INPUT_ANALOG)
    {
        gpio_init_struct.gpio_mode = LL_GPIO_MODE_AN;
        gpio_init_struct.gpio_type = LL_GPIO_TYPE_OUT_OD;
    }
    else if(Mode == OUTPUT)
    {
        gpio_init_struct.gpio_mode = LL_GPIO_MODE_OUT;
        gpio_init_struct.gpio_pupd = LL_GPIO_PUPD_DOWN;
    }
    else if(Mode == OUTPUT_OPEN_DRAIN)
    {
        gpio_init_struct.gpio_mode = LL_GPIO_MODE_OUT;
        gpio_init_struct.gpio_type = LL_GPIO_TYPE_OUT_OD;
        gpio_init_struct.gpio_pupd = LL_GPIO_PUPD_NOPULL;
    }
    else if(Mode == OUTPUT_AF_PP)
    {
        gpio_init_struct.gpio_mode = LL_GPIO_MODE_AF;
        gpio_init_struct.gpio_type = LL_GPIO_TYPE_OUT_PP;
        gpio_init_struct.gpio_pupd = LL_GPIO_PUPD_DOWN;
    }
    else if(Mode == OUTPUT_AF_OD)
    {
        gpio_init_struct.gpio_mode = LL_GPIO_MODE_AF;
        gpio_init_struct.gpio_type = LL_GPIO_TYPE_OUT_OD;
        gpio_init_struct.gpio_pupd = LL_GPIO_PUPD_NOPULL;
    }
    else
    {
        return;
    }

    ll_gpio_init(GPIOx, &gpio_init_struct);
}

/**
  * @brief  禁用JTAG引脚
  * @param  无
  * @retval 无
  */
void GPIO_JTAG_Disable(void)
{
    swd_disable();
}

/**
  * @brief  获取当前引脚对应的GPIOx编号
  * @param  Pin: 引脚编号
  * @retval 无
  */
uint8_t GPIO_GetPortNum(uint8_t Pin)
{
    uint8_t retval = 0xFF;
    uint8_t index;
    gpio_type* GPIOx = PIN_MAP[Pin].GPIOx;

    gpio_type* GPIO_Map[] =
    {
        GPIOA,
        GPIOB,
        GPIOC,
    };

    for(index = 0; index < sizeof(GPIO_Map) / sizeof(GPIO_Map[0]); index++)
    {
        if(GPIOx == GPIO_Map[index])
        {
            retval = index;
            break;
        }
    }

    return retval;
}

/**
  * @brief  获取当前引脚对应的 PinSource
  * @param  GPIO_Pin_x: GPIO对应位
  * @retval 无
  */
uint8_t GPIO_GetPinSource(uint16_t GPIO_Pin_x)
{
    uint8_t PinSource = 0;
    while(GPIO_Pin_x > 1)
    {
        GPIO_Pin_x >>= 1;
        PinSource++;
    }
    return PinSource;
}

/**
  * @brief  获取当前引脚对应的编号
  * @param  Pin: 引脚编号
  * @retval 无
  */
uint8_t GPIO_GetPinNum(uint8_t Pin)
{
    return GPIO_GetPinSource(PIN_MAP[Pin].GPIO_Pin_x);
}
