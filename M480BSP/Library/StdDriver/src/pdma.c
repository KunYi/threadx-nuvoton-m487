/**************************************************************************//**
 * @file     pdma.c
 * @version  V1.00
 * @brief    M480 series PDMA driver source file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "NuMicro.h"


static uint8_t u32ChSelect[PDMA_CH_MAX];

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup PDMA_Driver PDMA Driver
  @{
*/


/** @addtogroup PDMA_EXPORTED_FUNCTIONS PDMA Exported Functions
  @{
*/

/**
 * @brief       PDMA Open
 *
 * @param[in]   pdma            The pointer of the specified PDMA module
 *
 * @param[in]   u32Mask     Channel enable bits.
 *
 * @return      None
 *
 * @details     This function enable the PDMA channels.
 */
void PDMA_Open(PDMA_T * pdma,uint32_t u32Mask)
{
    uint32_t i;

    for (i=0UL; i<PDMA_CH_MAX; i++)
    {
        if((1 << i) & u32Mask)
        {
            pdma->DSCT[i].CTL = 0UL;
            u32ChSelect[i] = PDMA_MEM;
        }
    }

    pdma->CHCTL |= u32Mask;
}

/**
 * @brief       PDMA Close
 *
 * @param[in]   pdma            The pointer of the specified PDMA module
 *
 * @return      None
 *
 * @details     This function disable all PDMA channels.
 */
void PDMA_Close(PDMA_T * pdma)
{
    pdma->CHCTL = 0UL;
}

/**
 * @brief       Set PDMA Transfer Count
 *
 * @param[in]   pdma            The pointer of the specified PDMA module
 * @param[in]   u32Ch           The selected channel
 * @param[in]   u32Width        Data width. Valid values are
 *                - \ref PDMA_WIDTH_8
 *                - \ref PDMA_WIDTH_16
 *                - \ref PDMA_WIDTH_32
 * @param[in]   u32TransCount   Transfer count
 *
 * @return      None
 *
 * @details     This function set the selected channel data width and transfer count.
 */
void PDMA_SetTransferCnt(PDMA_T * pdma,uint32_t u32Ch, uint32_t u32Width, uint32_t u32TransCount)
{
    pdma->DSCT[u32Ch].CTL &= ~(PDMA_DSCT_CTL_TXCNT_Msk | PDMA_DSCT_CTL_TXWIDTH_Msk);
    pdma->DSCT[u32Ch].CTL |= (u32Width | ((u32TransCount - 1UL) << PDMA_DSCT_CTL_TXCNT_Pos));
}

/**
 * @brief       Set PDMA Stride Mode
  *
 * @param[in]   pdma            The pointer of the specified PDMA module
 * @param[in]   u32Ch           The selected channel
 * @param[in]   u32DestLen      Destination stride count
 * @param[in]   u32SrcLen       Source stride count
 * @param[in]   u32TransCount   Transfer count
 *
 * @return      None
 *
 * @details     This function set the selected stride mode.
 */
void PDMA_SetStride(PDMA_T * pdma,uint32_t u32Ch, uint32_t u32DestLen, uint32_t u32SrcLen, uint32_t u32TransCount)
{
    pdma->DSCT[u32Ch].CTL |= PDMA_DSCT_CTL_STRIDEEN_Msk;
    pdma->STRIDE[u32Ch].ASOCR =((u32DestLen-1)<<16) | (u32SrcLen-1);
    pdma->STRIDE[u32Ch].STCR = u32TransCount-1;
}

/**
 * @brief       Set PDMA Repeat
  *
 * @param[in]   pdma                The pointer of the specified PDMA module
 * @param[in]   u32Ch               The selected channel
 * @param[in]   u32DestInterval     Destination address interval count
 * @param[in]   u32SrcInterval      Source address interval count
 * @param[in]   u32RepeatCount      Repeat count
 *
 * @return      None
 *
 * @details     This function set the selected repeat.
 */
void PDMA_SetRepeat(PDMA_T * pdma,uint32_t u32Ch, uint32_t u32DestInterval, uint32_t u32SrcInterval, uint32_t u32RepeatCount)
{
    pdma->DSCT[u32Ch].CTL |= PDMA_DSCT_CTL_STRIDEEN_Msk;
    pdma->REPEAT[u32Ch].AICTL =((u32DestInterval)<<16) | (u32SrcInterval);
    pdma->REPEAT[u32Ch].RCNT = u32RepeatCount;
}

/**
 * @brief       Set PDMA Transfer Address
  *
 * @param[in]   pdma            The pointer of the specified PDMA module
 * @param[in]   u32Ch           The selected channel
 * @param[in]   u32SrcAddr      Source address
 * @param[in]   u32SrcCtrl      Source control attribute. Valid values are
 *                - \ref PDMA_SAR_INC
 *                - \ref PDMA_SAR_FIX
 * @param[in]   u32DstAddr      destination address
 * @param[in]   u32DstCtrl      destination control attribute. Valid values are
 *                - \ref PDMA_DAR_INC
 *                - \ref PDMA_DAR_FIX
 *
 * @return      None
 *
 * @details     This function set the selected channel source/destination address and attribute.
 */
void PDMA_SetTransferAddr(PDMA_T * pdma,uint32_t u32Ch, uint32_t u32SrcAddr, uint32_t u32SrcCtrl, uint32_t u32DstAddr, uint32_t u32DstCtrl)
{
    pdma->DSCT[u32Ch].SA = u32SrcAddr;
    pdma->DSCT[u32Ch].DA = u32DstAddr;
    pdma->DSCT[u32Ch].CTL &= ~(PDMA_DSCT_CTL_SAINC_Msk | PDMA_DSCT_CTL_DAINC_Msk);
    pdma->DSCT[u32Ch].CTL |= (u32SrcCtrl | u32DstCtrl);
}

/**
 * @brief       Set PDMA Transfer Mode
  *
 * @param[in]   pdma            The pointer of the specified PDMA module
 * @param[in]   u32Ch           The selected channel
 * @param[in]   u32Peripheral   The selected peripheral. Valid values are
 *                - \ref PDMA_MEM
 *                - \ref PDMA_USB_TX
 *                - \ref PDMA_USB_RX
 *                - \ref PDMA_UART0_TX
 *                - \ref PDMA_UART0_RX
 *                - \ref PDMA_UART1_TX
 *                - \ref PDMA_UART1_RX
 *                - \ref PDMA_UART2_TX
 *                - \ref PDMA_UART2_RX
 *                - \ref PDMA_UART3_TX
 *                - \ref PDMA_UART3_RX
 *                - \ref PDMA_UART4_TX
 *                - \ref PDMA_UART4_RX
 *                - \ref PDMA_UART5_TX
 *                - \ref PDMA_UART5_RX
 *                - \ref PDMA_USCI0_TX
 *                - \ref PDMA_USCI0_RX
 *                - \ref PDMA_USCI1_TX
 *                - \ref PDMA_USCI1_RX
 *                - \ref PDMA_QSPI0_TX
 *                - \ref PDMA_QSPI0_RX
 *                - \ref PDMA_SPI0_TX
 *                - \ref PDMA_SPI0_RX
 *                - \ref PDMA_SPI1_TX
 *                - \ref PDMA_SPI1_RX
 *                - \ref PDMA_SPI2_TX
 *                - \ref PDMA_SPI2_RX
 *                - \ref PDMA_SPI3_TX
 *                - \ref PDMA_SPI3_RX
 *                - \ref PDMA_EPWM0_P1_RX
 *                - \ref PDMA_EPWM0_P2_RX
 *                - \ref PDMA_EPWM0_P3_RX
 *                - \ref PDMA_EPWM1_P1_RX
 *                - \ref PDMA_EPWM1_P2_RX
 *                - \ref PDMA_EPWM1_P3_RX
 *                - \ref PDMA_I2C0_TX
 *                - \ref PDMA_I2C0_RX
 *                - \ref PDMA_I2C1_TX
 *                - \ref PDMA_I2C1_RX
 *                - \ref PDMA_I2C2_TX
 *                - \ref PDMA_I2C2_RX
 *                - \ref PDMA_I2S0_TX
 *                - \ref PDMA_I2S0_RX
 *                - \ref PDMA_TMR0
 *                - \ref PDMA_TMR1
 *                - \ref PDMA_TMR2
 *                - \ref PDMA_TMR3
 *                - \ref PDMA_EADC0_RX
 *                - \ref PDMA_DAC0_TX
 *                - \ref PDMA_DAC1_TX
 *                - \ref PDMA_EPWM0_CH0_TX
 *                - \ref PDMA_EPWM0_CH1_TX
 *                - \ref PDMA_EPWM0_CH2_TX
 *                - \ref PDMA_EPWM0_CH3_TX
 *                - \ref PDMA_EPWM0_CH4_TX
 *                - \ref PDMA_EPWM0_CH5_TX
 *                - \ref PDMA_EPWM1_CH0_TX
 *                - \ref PDMA_EPWM1_CH1_TX
 *                - \ref PDMA_EPWM1_CH2_TX
 *                - \ref PDMA_EPWM1_CH3_TX
 *                - \ref PDMA_EPWM1_CH4_TX
 *                - \ref PDMA_EPWM1_CH5_TX
 *                - \ref PDMA_UART6_TX
 *                - \ref PDMA_UART6_RX
 *                - \ref PDMA_UART7_TX
 *                - \ref PDMA_UART7_RX
 *                - \ref PDMA_EADC1_RX
 * @param[in]   u32ScatterEn    Scatter-gather mode enable
 * @param[in]   u32DescAddr     Scatter-gather descriptor address
 *
 * @return      None
 *
 * @details     This function set the selected channel transfer mode. Include peripheral setting.
 */
void PDMA_SetTransferMode(PDMA_T * pdma,uint32_t u32Ch, uint32_t u32Peripheral, uint32_t u32ScatterEn, uint32_t u32DescAddr)
{
    u32ChSelect[u32Ch] = u32Peripheral;
    switch(u32Ch)
    {
    case 0ul:
        pdma->REQSEL0_3 = (pdma->REQSEL0_3 & ~PDMA_REQSEL0_3_REQSRC0_Msk) | u32Peripheral;
        break;
    case 1ul:
        pdma->REQSEL0_3 = (pdma->REQSEL0_3 & ~PDMA_REQSEL0_3_REQSRC1_Msk) | (u32Peripheral << PDMA_REQSEL0_3_REQSRC1_Pos);
        break;
    case 2ul:
        pdma->REQSEL0_3 = (pdma->REQSEL0_3 & ~PDMA_REQSEL0_3_REQSRC2_Msk) | (u32Peripheral << PDMA_REQSEL0_3_REQSRC2_Pos);
        break;
    case 3ul:
        pdma->REQSEL0_3 = (pdma->REQSEL0_3 & ~PDMA_REQSEL0_3_REQSRC3_Msk) | (u32Peripheral << PDMA_REQSEL0_3_REQSRC3_Pos);
        break;
    case 4ul:
        pdma->REQSEL4_7 = (pdma->REQSEL4_7 & ~PDMA_REQSEL4_7_REQSRC4_Msk) | u32Peripheral;
        break;
    case 5ul:
        pdma->REQSEL4_7 = (pdma->REQSEL4_7 & ~PDMA_REQSEL4_7_REQSRC5_Msk) | (u32Peripheral << PDMA_REQSEL4_7_REQSRC5_Pos);
        break;
    case 6ul:
        pdma->REQSEL4_7 = (pdma->REQSEL4_7 & ~PDMA_REQSEL4_7_REQSRC6_Msk) | (u32Peripheral << PDMA_REQSEL4_7_REQSRC6_Pos);
        break;
    case 7ul:
        pdma->REQSEL4_7 = (pdma->REQSEL4_7 & ~PDMA_REQSEL4_7_REQSRC7_Msk) | (u32Peripheral << PDMA_REQSEL4_7_REQSRC7_Pos);
        break;
    case 8ul:
        pdma->REQSEL8_11 = (pdma->REQSEL8_11 & ~PDMA_REQSEL8_11_REQSRC8_Msk) | u32Peripheral;
        break;
    case 9ul:
        pdma->REQSEL8_11 = (pdma->REQSEL8_11 & ~PDMA_REQSEL8_11_REQSRC9_Msk) | (u32Peripheral << PDMA_REQSEL8_11_REQSRC9_Pos);
        break;
    case 10ul:
        pdma->REQSEL8_11 = (pdma->REQSEL8_11 & ~PDMA_REQSEL8_11_REQSRC10_Msk) | (u32Peripheral << PDMA_REQSEL8_11_REQSRC10_Pos);
        break;
    case 11ul:
        pdma->REQSEL8_11 = (pdma->REQSEL8_11 & ~PDMA_REQSEL8_11_REQSRC11_Msk) | (u32Peripheral << PDMA_REQSEL8_11_REQSRC11_Pos);
        break;
    case 12ul:
        pdma->REQSEL12_15 = (pdma->REQSEL12_15 & ~PDMA_REQSEL12_15_REQSRC12_Msk) | u32Peripheral;
        break;
    case 13ul:
        pdma->REQSEL12_15 = (pdma->REQSEL12_15 & ~PDMA_REQSEL12_15_REQSRC13_Msk) | (u32Peripheral << PDMA_REQSEL12_15_REQSRC13_Pos);
        break;
    case 14ul:
        pdma->REQSEL12_15 = (pdma->REQSEL12_15 & ~PDMA_REQSEL12_15_REQSRC14_Msk) | (u32Peripheral << PDMA_REQSEL12_15_REQSRC14_Pos);
        break;
    case 15ul:
        pdma->REQSEL12_15 = (pdma->REQSEL12_15 & ~PDMA_REQSEL12_15_REQSRC15_Msk) | (u32Peripheral << PDMA_REQSEL12_15_REQSRC15_Pos);
        break;
    default:
        break;
    }

    if(u32ScatterEn)
    {
        pdma->DSCT[u32Ch].NEXT = u32DescAddr - (PDMA->SCATBA);
        pdma->DSCT[u32Ch].CTL = (pdma->DSCT[u32Ch].CTL & ~PDMA_DSCT_CTL_OPMODE_Msk) | PDMA_OP_SCATTER;
    }
    else
    {
        pdma->DSCT[u32Ch].CTL = (pdma->DSCT[u32Ch].CTL & ~PDMA_DSCT_CTL_OPMODE_Msk) | PDMA_OP_BASIC;
    }
}

/**
 * @brief       Set PDMA Burst Type and Size
 *
 * @param[in]   pdma            The pointer of the specified PDMA module
 * @param[in]   u32Ch           The selected channel
 * @param[in]   u32BurstType    Burst mode or single mode. Valid values are
 *                - \ref PDMA_REQ_SINGLE
 *                - \ref PDMA_REQ_BURST
 * @param[in]   u32BurstSize    Set the size of burst mode. Valid values are
 *                - \ref PDMA_BURST_128
 *                - \ref PDMA_BURST_64
 *                - \ref PDMA_BURST_32
 *                - \ref PDMA_BURST_16
 *                - \ref PDMA_BURST_8
 *                - \ref PDMA_BURST_4
 *                - \ref PDMA_BURST_2
 *                - \ref PDMA_BURST_1
 *
 * @return      None
 *
 * @details     This function set the selected channel burst type and size.
 */
void PDMA_SetBurstType(PDMA_T * pdma,uint32_t u32Ch, uint32_t u32BurstType, uint32_t u32BurstSize)
{
    pdma->DSCT[u32Ch].CTL &= ~(PDMA_DSCT_CTL_TXTYPE_Msk | PDMA_DSCT_CTL_BURSIZE_Msk);
    pdma->DSCT[u32Ch].CTL |= (u32BurstType | u32BurstSize);
}

/**
 * @brief       Enable timeout function
 *
 * @param[in]   pdma            The pointer of the specified PDMA module
 *
 * @param[in]   u32Mask         Channel enable bits.
 *
 * @return      None
 *
 * @details     This function enable timeout function of the selected channel(s).
 */
void PDMA_EnableTimeout(PDMA_T * pdma,uint32_t u32Mask)
{
    pdma->TOUTEN |= u32Mask;
}

/**
 * @brief       Disable timeout function
 *
 * @param[in]   pdma            The pointer of the specified PDMA module
 *
 * @param[in]   u32Mask         Channel enable bits.
 *
 * @return      None
 *
 * @details     This function disable timeout function of the selected channel(s).
 */
void PDMA_DisableTimeout(PDMA_T * pdma,uint32_t u32Mask)
{
    pdma->TOUTEN &= ~u32Mask;
}

/**
 * @brief       Set PDMA Timeout Count
 *
 * @param[in]   pdma            The pointer of the specified PDMA module
 * @param[in]   u32Ch           The selected channel,
 * @param[in]   u32OnOff        Enable/disable time out function
 * @param[in]   u32TimeOutCnt   Timeout count
 *
 * @return      None
 *
 * @details     This function set the timeout count.
 * @note        M480 only supported channel 0/1.
 */
void PDMA_SetTimeOut(PDMA_T * pdma,uint32_t u32Ch, uint32_t u32OnOff, uint32_t u32TimeOutCnt)
{
    switch(u32Ch)
    {
    case 0ul:
        pdma->TOC0_1 = (pdma->TOC0_1 & ~PDMA_TOC0_1_TOC0_Msk) | u32TimeOutCnt;
        break;
    case 1ul:
        pdma->TOC0_1 = (pdma->TOC0_1 & ~PDMA_TOC0_1_TOC1_Msk) | (u32TimeOutCnt << PDMA_TOC0_1_TOC1_Pos);
        break;
    default:
        break;
    }

    if (u32OnOff)
        pdma->TOUTEN |= (1 << u32Ch);
    else
        pdma->TOUTEN &= ~(1 << u32Ch);
}

/**
 * @brief       Trigger PDMA
 *
 * @param[in]   pdma            The pointer of the specified PDMA module
 * @param[in]   u32Ch           The selected channel
 *
 * @return      None
 *
 * @details     This function trigger the selected channel.
 */
void PDMA_Trigger(PDMA_T * pdma,uint32_t u32Ch)
{
    if(u32ChSelect[u32Ch] == PDMA_MEM)
    {
        pdma->SWREQ = (1ul << u32Ch);
    }
    else {}
}

/**
 * @brief       Enable Interrupt
 *
 * @param[in]   pdma            The pointer of the specified PDMA module
 * @param[in]   u32Ch           The selected channel
 * @param[in]   u32Mask         The Interrupt Type. Valid values are
 *                - \ref PDMA_INT_TRANS_DONE
 *                - \ref PDMA_INT_TEMPTY
 *                - \ref PDMA_INT_TIMEOUT
 *
 * @return      None
 *
 * @details     This function enable the selected channel interrupt.
 */
void PDMA_EnableInt(PDMA_T * pdma,uint32_t u32Ch, uint32_t u32Mask)
{
    switch(u32Mask)
    {
    case PDMA_INT_TRANS_DONE:
        pdma->INTEN |= (1ul << u32Ch);
        break;
    case PDMA_INT_TEMPTY:
        pdma->DSCT[u32Ch].CTL &= ~PDMA_DSCT_CTL_TBINTDIS_Msk;
        break;
    case PDMA_INT_TIMEOUT:
        pdma->TOUTIEN |= (1ul << u32Ch);
        break;

    default:
        break;
    }
}

/**
 * @brief       Disable Interrupt
 *
 * @param[in]   pdma            The pointer of the specified PDMA module
 * @param[in]   u32Ch           The selected channel
 * @param[in]   u32Mask         The Interrupt Type. Valid values are
 *                - \ref PDMA_INT_TRANS_DONE
 *                - \ref PDMA_INT_TEMPTY
 *                - \ref PDMA_INT_TIMEOUT
 *
 * @return      None
 *
 * @details     This function disable the selected channel interrupt.
 */
void PDMA_DisableInt(PDMA_T * pdma,uint32_t u32Ch, uint32_t u32Mask)
{
    switch(u32Mask)
    {
    case PDMA_INT_TRANS_DONE:
        pdma->INTEN &= ~(1ul << u32Ch);
        break;
    case PDMA_INT_TEMPTY:
        pdma->DSCT[u32Ch].CTL |= PDMA_DSCT_CTL_TBINTDIS_Msk;
        break;
    case PDMA_INT_TIMEOUT:
        pdma->TOUTIEN &= ~(1ul << u32Ch);
        break;

    default:
        break;
    }
}

/*@}*/ /* end of group PDMA_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group PDMA_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2014~2016 Nuvoton Technology Corp. ***/
