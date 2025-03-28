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
#include "libcore/adc.h"
#include "eg32m0xx.h"
#include "eg32m0xx_ll_dma.h"
#include "eg32m0xx_ll_adc.h"
#include <stdbool.h>

#define ADC_DMA_REGMAX 14

#define IS_ADC_CHANNEL(channel) (channel <= ADC_CHANNEL_13)

/*引脚注册个数*/
static uint8_t ADC_DMA_RegCnt = 0;

/*ADC通道注册列表*/
static uint8_t ADC_DMA_RegChannelList[ADC_DMA_REGMAX] = {0};

/*ADC DMA缓存数组*/
static uint16_t ADC_DMA_ConvertedValue[ADC_DMA_REGMAX] = {0};

/**
  * @brief  搜索注册列表，找出ADC通道对应的索引号
  * @param  ADC_Channel:ADC通道号
  * @retval ADC通道注册列表对应索引号，-1:未找到对应通道号
  */
static int16_t ADC_DMA_SearchChannel(uint16_t ADC_Channel)
{
    uint8_t index;

    for(index = 0; index < ADC_DMA_RegCnt; index++)
    {
        if(ADC_Channel == ADC_DMA_RegChannelList[index])
        {
            return index;
        }
    }
    return -1;
}


/**
  * @brief  注册需要DMA搬运的ADC通道
  * @param  ADC_Channel:ADC通道号
  * @retval 见ADC_DMA_Res_Type
  */
ADC_DMA_Res_Type ADC_DMA_Register(uint8_t ADC_Channel)
{
    /*初始化ADC通道列表*/
    static bool isInit = false;
    if(!isInit)
    {
        uint8_t i;
        for(i = 0; i < ADC_DMA_REGMAX; i++)
        {
            ADC_DMA_RegChannelList[i] = 0xFF;
        }
        isInit = true;
    }

    /*是否是合法ADC通道*/
    if(!IS_ADC_CHANNEL(ADC_Channel))
        return ADC_DMA_RES_NOT_ADC_CHANNEL;

    /*是否已在引脚列表重复注册*/
    if(ADC_DMA_SearchChannel(ADC_Channel) != -1)
        return ADC_DMA_RES_DUPLICATE_REGISTRATION;

    /*是否超出最大注册个数*/
    if(ADC_DMA_RegCnt >= ADC_DMA_REGMAX)
        return ADC_DMA_RES_MAX_NUM_OF_REGISTRATIONS_EXCEEDED;

    /*写入注册列表*/
    ADC_DMA_RegChannelList[ADC_DMA_RegCnt] = ADC_Channel;

    /*注册个数+1*/
    ADC_DMA_RegCnt++;

    return ADC_DMA_RES_OK;
}

/**
  * @brief  获取已注册的ADC DMA通道数量
  * @param  无
  * @retval ADC DMA通道数量
  */
uint8_t ADC_DMA_GetRegisterCount(void)
{
    return ADC_DMA_RegCnt;
}

/**
  * @brief  ADC DMA 配置
  * @param  无
  * @retval 无
  */
void ADC_DMA_Init(void)
{
	TYPE_LL_DMA_INIT dma_init = {
        .priority = LL_DMA_PRIORITY_LOW,
        .trg_src = LL_DMA_TRG_ADC_RDMA_REQ,
        .data_width = LL_DMA_DATA_WIDTH_16BIT,
        .block_len = 1,
        .block_cnt = ADC_DMA_RegCnt,
        .source_mode = LL_DMA_ADDR_MODE_FIX,
        .destin_mode = LL_DMA_ADDR_MODE_LINE_INC,
        .dst_addr = (u32) &(ADC_DMA_ConvertedValue[0]),
        .src_addr = (u32) &(ADC->DATA),
    };

    TYPE_LL_ADC_INIT adc_init = {
        .ref_voltage = LL_ADC_VSEL_3_0V,        	// 选择参考电压3.0V
        .data_align = LL_ADC_DATA_RIGHT_ALIGN,  	// 数据右对齐
        .prescaler = 0x3,                       	// ADC预分频器值
        .interval_period = 0x10,                    // 两次ADC转换间隔时间
    };

	TYPE_LL_ADC_EXT_TRG_CONFIG adc_trgger = {
        .ext_trg_source = LL_ADC_TRG_SW,
        .ext_trg_delay = LL_ADC_DELAY_64_clock,
    };

    ll_adc_init(ADC, &adc_init);

	// 连续转换模式
	ll_adc_single_conversion();	
    ll_adc_set_rseq_multi_ch(ADC_DMA_RegChannelList, ADC_DMA_RegCnt );	
	adc_trgger.ext_trg_delay = LL_ADC_DELAY_64_clock;
	adc_trgger.ext_trg_source = LL_ADC_TRG_SW;
	ll_adc_external_trigger_rseq_config(ADC, &adc_trgger);
	ll_adc_rdma_enable();		// 使能DMA

	ll_adc_ldo_enable();		// 开启LDO

	ll_dma_init(DMA, DMA_CHANNEL_0, &dma_init);
	ll_dma_auto_reload_enable(DMA, DMA_CHANNEL_0);
	
	ll_dma_enable(DMA, DMA_CHANNEL_0);

    ll_adc_enable();

    // ll_adc_enable();
	// ll_adc_hardword_calibrate_enable();
	// while(ADC->STA & LL_ADC_STA_BUSY);
}

/**
  * @brief  获取DMA搬运的ADC值
  * @param  ADC_Channel:ADC通道号
  * @retval ADC值
  */
uint16_t ADC_DMA_GetValue(uint8_t ADC_Channel)
{
    int16_t index;

    if(!IS_ADC_CHANNEL(ADC_Channel))
        return 0;

    index = ADC_DMA_SearchChannel(ADC_Channel);
    if(index == -1)
        return 0;

    return ADC_DMA_ConvertedValue[index];
}
