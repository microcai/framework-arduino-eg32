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
#include "Arduino.h"
#include "eg32m0xx_ll_gpio.h"

/**
  * @brief  配置引脚输入输出模式
  * @param  pin: 引脚编号
  * @param  PinMode_x: 模式
  * @retval 无
  */
void pinMode(uint8_t pin, PinMode_TypeDef mode)
{
    if(!IS_PIN(pin))
    {
        return;
    }

    if((mode == INPUT_ANALOG_DMA))
    {
        if(!IS_ADC_PIN(pin))
        {
            return;
        }

        TYPE_LL_GPIO_INIT gpio_init = {
            .gpio_pin = PIN_MAP[pin].GPIO_Pin_x,
            .gpio_mode = LL_GPIO_MODE_AN,
            .gpio_type = LL_GPIO_TYPE_OUT_PP,
            .gpio_speed_level = LL_GPIO_SPEED_LEVEL_HIGHEST,
            .gpio_pupd = LL_GPIO_PUPD_NOPULL,
            .gpio_edge = LL_GPIO_EDGE_NONE,
        };

        ll_gpio_init(PIN_MAP[pin].GPIOx, &gpio_init);
        if (mode == INPUT_ANALOG_DMA)
            ADC_DMA_Register(PIN_MAP[pin].ADC_Channel);
    }
    else if(mode == PWM)
    {
        // PWM_Init(pin, PWM_RESOLUTION_DEFAULT, PWM_FREQUENCY_DEFAULT);
    }
    else
    {
        GPIOx_Init(
            PIN_MAP[pin].GPIOx,
            PIN_MAP[pin].GPIO_Pin_x,
            mode
        );
    }
}

/**
  * @brief  将数字HIGH(1)或LOW(0)值写入数字引脚
  * @param  pin:引脚编号
  * @param  value: 写入值
  * @retval 无
  */
void digitalWrite(uint8_t pin, uint8_t value)
{
    if(!IS_PIN(pin))
    {
        return;
    }

    value ? digitalWrite_HIGH(pin) : digitalWrite_LOW(pin);
}

/**
  * @brief  读取引脚电平
  * @param  pin: 引脚编号
  * @retval 引脚电平
  */
uint8_t digitalRead(uint8_t pin)
{
    if(!IS_PIN(pin))
    {
        return 0;
    }

    return digitalRead_FAST(pin);
}

/**
  * @brief  将模拟值(PWM占空比)写入引脚
  * @param  pin: 引脚编号
  * @param  value: PWM占空比
  * @retval 无
  */
void analogWrite(uint8_t pin, uint16_t value)
{
    if(!IS_PWM_PIN(pin))
    {
        return;
    }

    PWM_Write(pin, value);
}

/**
  * @brief  从指定的模拟引脚读取值
  * @param  pin: 引脚编号
  * @retval ADC值：0~4095
  */
uint16_t analogRead(uint8_t pin)
{
    if(!IS_ADC_PIN(pin))
    {
        return 0;
    }

    return ADC_DMA_GetValue(PIN_MAP[pin].ADC_Channel);
}

/**
  * @brief  从指定的引脚读取值(DMA方式)
  * @param  pin: 引脚编号
  * @retval ADC值：0~4095
  */
uint16_t analogRead_DMA(uint8_t pin)
{
    if(!IS_ADC_PIN(pin))
    {
        return 0;
    }

    return ADC_DMA_GetValue(PIN_MAP[pin].ADC_Channel);
}

/**
  * @brief  一次移出一个字节的数据，从最左端或最小(最右边)开始
  * @param  dataPin: 输出每个位的 pin
  * @param  clockPin: 将 dataPin 设置为正确值后要切换的 pin (int)
  * @param  bitOrder: MSBFIRST / LSBFIRST
  * @param  value: 要移出的数据(字节)
  * @retval 无
  */
void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t value)
{
    uint8_t i;
    if(!(IS_PIN(dataPin) && IS_PIN(clockPin)))
    {
        return;
    }

    digitalWrite_LOW(clockPin);
    for (i = 0; i < 8; i++)
    {
        int bit = bitOrder == LSBFIRST ? i : (7 - i);
        digitalWrite(dataPin, (value >> bit) & 0x1);
        togglePin(clockPin);
        togglePin(clockPin);
    }
}

/**
  * @brief  一次将一个字节的数据移位，从最左端或最小 (最右边) 开始
  * @param  dataPin:  输入每个位的 pin
  * @param  clockPin: 要切换到的 pin 信号从dataPin读取
  * @param  bitOrder: MSBFIRST/LSBFIRST
  * @retval 读取的值 (字节)
  */
uint32_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint32_t bitOrder)
{
    uint8_t value = 0;
    uint8_t i;

    if(!(IS_PIN(dataPin) && IS_PIN(clockPin)))
    {
        return 0;
    }

    for (i = 0; i < 8; ++i)
    {
        digitalWrite_HIGH(clockPin);
        if (bitOrder == LSBFIRST )
        {
            value |= digitalRead(dataPin) << i;
        }
        else
        {
            value |= digitalRead(dataPin) << (7 - i);
        }
        digitalWrite_LOW(clockPin);
    }

    return value;
}

/**
  * @brief  将一个数字(整形)从一个范围重新映射到另一个区域
  * @param  x: 要映射的数字
  * @param  in_min: 值的当前范围的下界
  * @param  in_max: 值的当前范围的上界
  * @param  out_min: 值的目标范围的下界
  * @param  out_max: 值目标范围的上界
  * @retval 映射的值(long)
  */
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**
  * @brief  将一个数字(浮点型)从一个范围重新映射到另一个区域
  * @param  x: 要映射的数字
  * @param  in_min: 值的当前范围的下界
  * @param  in_max: 值的当前范围的上界
  * @param  out_min: 值的目标范围的下界
  * @param  out_max: 值目标范围的上界
  * @retval 映射的值(double)
  */
float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void yield(void)
{
}
