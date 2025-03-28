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
#ifndef __MCU_TYPE_H
#define __MCU_TYPE_H

#include "eg32m0xx.h"
#include "eg32m0xx_ll_gpio.h"
#include "config/mcu_config.h"
#include "eg32m0xx_ll_spi_iic.h"
#include "eg32m0xx_ll_timer.h"
#include "eg32m0xx_ll_uart.h"


#define __EG32__
#define __EG32M0x__
// #define F_CPU                       system_core_clock
// #define F_CPU  80000000L
#define CYCLES_PER_MICROSECOND      (F_CPU / 1000000U)

typedef GPIO_TypeDef gpio_type;
typedef SPI_IIC_TypeDef                 SPI_TypeDef;
typedef SPI_IIC_TypeDef                 spi_type;
typedef TIMER_TypeDef                   TIM_TypeDef;
typedef TIMER_TypeDef                   tmr_type;
typedef ADC_TypeDef                     adc_type;
typedef UART_TypeDef                    usart_type;

#define GPIO_Pin_0                  LL_GPIO_PIN_0
#define GPIO_Pin_1                  LL_GPIO_PIN_1
#define GPIO_Pin_2                  LL_GPIO_PIN_2
#define GPIO_Pin_3                  LL_GPIO_PIN_3
#define GPIO_Pin_4                  LL_GPIO_PIN_4
#define GPIO_Pin_5                  LL_GPIO_PIN_5
#define GPIO_Pin_6                  LL_GPIO_PIN_6
#define GPIO_Pin_7                  LL_GPIO_PIN_7
#define GPIO_Pin_8                  LL_GPIO_PIN_8
#define GPIO_Pin_9                  LL_GPIO_PIN_9
#define GPIO_Pin_10                 LL_GPIO_PIN_10
#define GPIO_Pin_11                 LL_GPIO_PIN_11
#define GPIO_Pin_12                 LL_GPIO_PIN_12
#define GPIO_Pin_13                 LL_GPIO_PIN_13
#define GPIO_Pin_14                 LL_GPIO_PIN_14
#define GPIO_Pin_15                 LL_GPIO_PIN_15
#define GPIO_Pin_All                LL_GPIO_PIN_All

#define TIM1                        TIMER1
#define TIM2                        TIMER2
#define TIM3                        TIMER3
#define TIM4                        TIMER4
#define TIM5                        TIMER5
#define TIM6                        TIMER6
#define TIM7                        TIMER7


/**
  * @brief adc channel select type
  */
typedef enum
{
  ADC_CHANNEL_0                          = 0x00, /*!< adc channel 0 */
  ADC_CHANNEL_1                          = 0x01, /*!< adc channel 1 */
  ADC_CHANNEL_2                          = 0x02, /*!< adc channel 2 */
  ADC_CHANNEL_3                          = 0x03, /*!< adc channel 3 */
  ADC_CHANNEL_4                          = 0x04, /*!< adc channel 4 */
  ADC_CHANNEL_5                          = 0x05, /*!< adc channel 5 */
  ADC_CHANNEL_6                          = 0x06, /*!< adc channel 6 */
  ADC_CHANNEL_7                          = 0x07, /*!< adc channel 7 */
  ADC_CHANNEL_8                          = 0x08, /*!< adc channel 8 */
  ADC_CHANNEL_9                          = 0x09, /*!< adc channel 9 */
  ADC_CHANNEL_10                         = 0x0A, /*!< adc channel 10 */
  ADC_CHANNEL_11                         = 0x0B, /*!< adc channel 11 */
  ADC_CHANNEL_12                         = 0x0C, /*!< adc channel 12 */
  ADC_CHANNEL_13                         = 0x0D, /*!< adc channel 13 */
} adc_channel_select_type;

#define ADC_CHANNEL_X ((uint8_t)0xFF)

#endif
