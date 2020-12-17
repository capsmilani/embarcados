/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : Vectors.c
**     Project     : fucking_teste
**     Processor   : MCF52259CAG80
**     Version     : Component 01.000, Driver 01.06, CPU db: 3.00.000
**     Compiler    : CodeWarrior MCF C Compiler
**     Date/Time   : 2017-06-09, 23:29, # CodeGen: 54
**     Abstract    :
**
**     Settings    :
**
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file Vectors.c                                                  
** @version 01.06
** @brief
**
*/         
/*!
**  @addtogroup Vectors_module Vectors module documentation
**  @{
*/         

#include "startcf.h"
#include "Cpu.h"
#include "Bit1.h"
#include "SM1.h"
#include "TI1.h"
#include "Bits1.h"
#include "AD1.h"
#include "Bits2.h"
#include "Term1.h"
#include "Inhr1.h"
#include "Events.h"


  /* ISR prototype */
  typedef void (*const tIsrFunc)(void);
  
  #pragma define_section vectortable ".vectortable" far_absolute R
  
  static __declspec(vectortable) tIsrFunc _InterruptVectorTable[0xC0] = { /* Interrupt vector table */
    /* ISR name                             No. Address      Lvl Pri Name                       Description */
    (tIsrFunc)__SP_AFTER_RESET,        /* 0x00  0x20000000   -   -   ivINT_INIT_SP              used by PE */
    _startup,                          /* 0x01  0x20000004   -   -   ivINT_INIT_PC              used by PE */
    Cpu_Interrupt,                     /* 0x02  0x20000008   -   -   ivINT_ACC_ERR              unused by PE */
    Cpu_Interrupt,                     /* 0x03  0x2000000C   -   -   ivINT_ADDR_ERR             unused by PE */
    Cpu_Interrupt,                     /* 0x04  0x20000010   -   -   ivINT_ILLEGAL_INSTR        unused by PE */
    Cpu_Interrupt,                     /* 0x05  0x20000014   -   -   ivINT_DIV_ZERO             unused by PE */
    Cpu_Interrupt,                     /* 0x06  0x20000018   -   -   ivReserved6                unused by PE */
    Cpu_Interrupt,                     /* 0x07  0x2000001C   -   -   ivReserved7                unused by PE */
    Cpu_Interrupt,                     /* 0x08  0x20000020   -   -   ivINT_PRIVILEGE_VIOL       unused by PE */
    Cpu_Interrupt,                     /* 0x09  0x20000024   -   -   ivINT_TRACE                unused by PE */
    Cpu_Interrupt,                     /* 0x0A  0x20000028   -   -   ivINT_UNIMPLEMENTED_A_LINE unused by PE */
    Cpu_Interrupt,                     /* 0x0B  0x2000002C   -   -   ivINT_UNIMPLEMENTED_F_LINE unused by PE */
    Cpu_Interrupt,                     /* 0x0C  0x20000030   -   -   ivINT_DEBUG                unused by PE */
    Cpu_Interrupt,                     /* 0x0D  0x20000034   -   -   ivReserved13               unused by PE */
    Cpu_Interrupt,                     /* 0x0E  0x20000038   -   -   ivINT_FORMAT_ERR           unused by PE */
    Cpu_Interrupt,                     /* 0x0F  0x2000003C   -   -   ivReserved15               unused by PE */
    Cpu_Interrupt,                     /* 0x10  0x20000040   -   -   ivReserved16               unused by PE */
    Cpu_Interrupt,                     /* 0x11  0x20000044   -   -   ivReserved17               unused by PE */
    Cpu_Interrupt,                     /* 0x12  0x20000048   -   -   ivReserved18               unused by PE */
    Cpu_Interrupt,                     /* 0x13  0x2000004C   -   -   ivReserved19               unused by PE */
    Cpu_Interrupt,                     /* 0x14  0x20000050   -   -   ivReserved20               unused by PE */
    Cpu_Interrupt,                     /* 0x15  0x20000054   -   -   ivReserved21               unused by PE */
    Cpu_Interrupt,                     /* 0x16  0x20000058   -   -   ivReserved22               unused by PE */
    Cpu_Interrupt,                     /* 0x17  0x2000005C   -   -   ivReserved23               unused by PE */
    Cpu_Interrupt,                     /* 0x18  0x20000060   -   -   ivINT_SPURIOUS_INT         unused by PE */
    Cpu_Interrupt,                     /* 0x19  0x20000064   -   -   ivReserved25               unused by PE */
    Cpu_Interrupt,                     /* 0x1A  0x20000068   -   -   ivReserved26               unused by PE */
    Cpu_Interrupt,                     /* 0x1B  0x2000006C   -   -   ivReserved27               unused by PE */
    Cpu_Interrupt,                     /* 0x1C  0x20000070   -   -   ivReserved28               unused by PE */
    Cpu_Interrupt,                     /* 0x1D  0x20000074   -   -   ivReserved29               unused by PE */
    Cpu_Interrupt,                     /* 0x1E  0x20000078   -   -   ivReserved30               unused by PE */
    Cpu_Interrupt,                     /* 0x1F  0x2000007C   -   -   ivReserved31               unused by PE */
    Cpu_Interrupt,                     /* 0x20  0x20000080   -   -   ivINT_TRAP0                unused by PE */
    Cpu_Interrupt,                     /* 0x21  0x20000084   -   -   ivINT_TRAP1                unused by PE */
    Cpu_Interrupt,                     /* 0x22  0x20000088   -   -   ivINT_TRAP2                unused by PE */
    Cpu_Interrupt,                     /* 0x23  0x2000008C   -   -   ivINT_TRAP3                unused by PE */
    Cpu_Interrupt,                     /* 0x24  0x20000090   -   -   ivINT_TRAP4                unused by PE */
    Cpu_Interrupt,                     /* 0x25  0x20000094   -   -   ivINT_TRAP5                unused by PE */
    Cpu_Interrupt,                     /* 0x26  0x20000098   -   -   ivINT_TRAP6                unused by PE */
    Cpu_Interrupt,                     /* 0x27  0x2000009C   -   -   ivINT_TRAP7                unused by PE */
    Cpu_Interrupt,                     /* 0x28  0x200000A0   -   -   ivINT_TRAP8                unused by PE */
    Cpu_Interrupt,                     /* 0x29  0x200000A4   -   -   ivINT_TRAP9                unused by PE */
    Cpu_Interrupt,                     /* 0x2A  0x200000A8   -   -   ivINT_TRAP10               unused by PE */
    Cpu_Interrupt,                     /* 0x2B  0x200000AC   -   -   ivINT_TRAP11               unused by PE */
    Cpu_Interrupt,                     /* 0x2C  0x200000B0   -   -   ivINT_TRAP12               unused by PE */
    Cpu_Interrupt,                     /* 0x2D  0x200000B4   -   -   ivINT_TRAP13               unused by PE */
    Cpu_Interrupt,                     /* 0x2E  0x200000B8   -   -   ivINT_TRAP14               unused by PE */
    Cpu_Interrupt,                     /* 0x2F  0x200000BC   -   -   ivINT_TRAP15               unused by PE */
    Cpu_Interrupt,                     /* 0x30  0x200000C0   -   -   ivReserved48               unused by PE */
    Cpu_Interrupt,                     /* 0x31  0x200000C4   -   -   ivReserved49               unused by PE */
    Cpu_Interrupt,                     /* 0x32  0x200000C8   -   -   ivReserved50               unused by PE */
    Cpu_Interrupt,                     /* 0x33  0x200000CC   -   -   ivReserved51               unused by PE */
    Cpu_Interrupt,                     /* 0x34  0x200000D0   -   -   ivReserved52               unused by PE */
    Cpu_Interrupt,                     /* 0x35  0x200000D4   -   -   ivReserved53               unused by PE */
    Cpu_Interrupt,                     /* 0x36  0x200000D8   -   -   ivReserved54               unused by PE */
    Cpu_Interrupt,                     /* 0x37  0x200000DC   -   -   ivReserved55               unused by PE */
    Cpu_Interrupt,                     /* 0x38  0x200000E0   -   -   ivReserved56               unused by PE */
    Cpu_Interrupt,                     /* 0x39  0x200000E4   -   -   ivReserved57               unused by PE */
    Cpu_Interrupt,                     /* 0x3A  0x200000E8   -   -   ivReserved58               unused by PE */
    Cpu_Interrupt,                     /* 0x3B  0x200000EC   -   -   ivReserved59               unused by PE */
    Cpu_Interrupt,                     /* 0x3C  0x200000F0   -   -   ivReserved60               unused by PE */
    Cpu_Interrupt,                     /* 0x3D  0x200000F4   -   -   ivReserved61               unused by PE */
    Cpu_Interrupt,                     /* 0x3E  0x200000F8   -   -   ivReserved62               unused by PE */
    Cpu_Interrupt,                     /* 0x3F  0x200000FC   -   -   ivReserved63               unused by PE */
    Cpu_Interrupt,                     /* 0x40  0x20000100   -   -   ivReserved64               unused by PE */
    Cpu_Interrupt,                     /* 0x41  0x20000104   -   -   ivINT_EPORT_EPF1           unused by PE */
    Cpu_Interrupt,                     /* 0x42  0x20000108   -   -   ivINT_EPORT_EPF2           unused by PE */
    Cpu_Interrupt,                     /* 0x43  0x2000010C   -   -   ivINT_EPORT_EPF3           unused by PE */
    Cpu_Interrupt,                     /* 0x44  0x20000110   -   -   ivINT_EPORT_EPF4           unused by PE */
    Cpu_Interrupt,                     /* 0x45  0x20000114   -   -   ivINT_EPORT_EPF5           unused by PE */
    Cpu_Interrupt,                     /* 0x46  0x20000118   -   -   ivINT_EPORT_EPF6           unused by PE */
    Cpu_Interrupt,                     /* 0x47  0x2000011C   -   -   ivINT_EPORT_EPF7           unused by PE */
    Cpu_INT_SCM_SWTIInterrupt,         /* 0x48  0x20000120   0   0   ivINT_SCM_SWTI             used by PE */
    Cpu_Interrupt,                     /* 0x49  0x20000124   -   -   ivINT_DMA0_DONE            unused by PE */
    Cpu_Interrupt,                     /* 0x4A  0x20000128   -   -   ivINT_DMA1_DONE            unused by PE */
    Cpu_Interrupt,                     /* 0x4B  0x2000012C   -   -   ivINT_DMA2_DONE            unused by PE */
    Cpu_Interrupt,                     /* 0x4C  0x20000130   -   -   ivINT_DMA3_DONE            unused by PE */
    Cpu_Interrupt,                     /* 0x4D  0x20000134   -   -   ivINT_UART0                unused by PE */
    Inhr1_Interrupt,                   /* 0x4E  0x20000138   1   0   ivINT_UART1                used by PE */
    Cpu_Interrupt,                     /* 0x4F  0x2000013C   -   -   ivINT_UART2                unused by PE */
    Cpu_Interrupt,                     /* 0x50  0x20000140   -   -   ivReserved80               unused by PE */
    Cpu_Interrupt,                     /* 0x51  0x20000144   -   -   ivINT_I2C0_IIF             unused by PE */
    Cpu_Interrupt,                     /* 0x52  0x20000148   -   -   ivINT_QSPI                 unused by PE */
    Cpu_Interrupt,                     /* 0x53  0x2000014C   -   -   ivINT_DTIM0                unused by PE */
    Cpu_Interrupt,                     /* 0x54  0x20000150   -   -   ivINT_DTIM1                unused by PE */
    Cpu_Interrupt,                     /* 0x55  0x20000154   -   -   ivINT_DTIM2                unused by PE */
    Cpu_Interrupt,                     /* 0x56  0x20000158   -   -   ivINT_DTIM3                unused by PE */
    Cpu_Interrupt,                     /* 0x57  0x2000015C   -   -   ivINT_FEC_X_INTF           unused by PE */
    Cpu_Interrupt,                     /* 0x58  0x20000160   -   -   ivINT_FEC_X_INTB           unused by PE */
    Cpu_Interrupt,                     /* 0x59  0x20000164   -   -   ivINT_FEC_UN               unused by PE */
    Cpu_Interrupt,                     /* 0x5A  0x20000168   -   -   ivINT_FEC_RL               unused by PE */
    Cpu_Interrupt,                     /* 0x5B  0x2000016C   -   -   ivINT_FEC_R_INTF           unused by PE */
    Cpu_Interrupt,                     /* 0x5C  0x20000170   -   -   ivINT_FEC_R_INTB           unused by PE */
    Cpu_Interrupt,                     /* 0x5D  0x20000174   -   -   ivINT_FEC_MII              unused by PE */
    Cpu_Interrupt,                     /* 0x5E  0x20000178   -   -   ivINT_FEC_LC               unused by PE */
    Cpu_Interrupt,                     /* 0x5F  0x2000017C   -   -   ivINT_FEC_HBERR            unused by PE */
    Cpu_Interrupt,                     /* 0x60  0x20000180   -   -   ivINT_FEC_GRA              unused by PE */
    Cpu_Interrupt,                     /* 0x61  0x20000184   -   -   ivINT_FEC_EBERR            unused by PE */
    Cpu_Interrupt,                     /* 0x62  0x20000188   -   -   ivINT_FEC_BABT             unused by PE */
    Cpu_Interrupt,                     /* 0x63  0x2000018C   -   -   ivINT_FEC_BABR             unused by PE */
    Cpu_Interrupt,                     /* 0x64  0x20000190   -   -   ivReserved100              unused by PE */
    Cpu_Interrupt,                     /* 0x65  0x20000194   -   -   ivReserved101              unused by PE */
    Cpu_Interrupt,                     /* 0x66  0x20000198   -   -   ivReserved102              unused by PE */
    Cpu_Interrupt,                     /* 0x67  0x2000019C   -   -   ivReserved103              unused by PE */
    Cpu_Interrupt,                     /* 0x68  0x200001A0   -   -   ivINT_RNGA                 unused by PE */
    Cpu_Interrupt,                     /* 0x69  0x200001A4   -   -   ivINT_GPT_TOF              unused by PE */
    Cpu_Interrupt,                     /* 0x6A  0x200001A8   -   -   ivINT_GPT_PAIF             unused by PE */
    Cpu_Interrupt,                     /* 0x6B  0x200001AC   -   -   ivINT_GPT_PAOVF            unused by PE */
    TI1_Interrupt,                     /* 0x6C  0x200001B0   7   7   ivINT_GPT_C0F              used by PE */
    Cpu_Interrupt,                     /* 0x6D  0x200001B4   -   -   ivINT_GPT_C1F              unused by PE */
    Cpu_Interrupt,                     /* 0x6E  0x200001B8   -   -   ivINT_GPT_C2F              unused by PE */
    Cpu_Interrupt,                     /* 0x6F  0x200001BC   -   -   ivINT_GPT_C3F              unused by PE */
    Cpu_Interrupt,                     /* 0x70  0x200001C0   -   -   ivINT_PMM_LVDF             unused by PE */
    Cpu_Interrupt,                     /* 0x71  0x200001C4   -   -   ivINT_ADC_ADCA             unused by PE */
    Cpu_Interrupt,                     /* 0x72  0x200001C8   -   -   ivINT_ADC_ADCB             unused by PE */
    Cpu_Interrupt,                     /* 0x73  0x200001CC   -   -   ivINT_ADC_ADCINT           unused by PE */
    Cpu_Interrupt,                     /* 0x74  0x200001D0   -   -   ivINT_PWM                  unused by PE */
    Cpu_Interrupt,                     /* 0x75  0x200001D4   -   -   ivINT_USB                  unused by PE */
    Cpu_Interrupt,                     /* 0x76  0x200001D8   -   -   ivReserved118              unused by PE */
    Cpu_Interrupt,                     /* 0x77  0x200001DC   -   -   ivINT_PIT0_PIF             unused by PE */
    Cpu_Interrupt,                     /* 0x78  0x200001E0   -   -   ivINT_PIT1_PIF             unused by PE */
    Cpu_Interrupt,                     /* 0x79  0x200001E4   -   -   ivReserved121              unused by PE */
    Cpu_Interrupt,                     /* 0x7A  0x200001E8   -   -   ivINT_CFM_CBEIF            unused by PE */
    Cpu_Interrupt,                     /* 0x7B  0x200001EC   -   -   ivINT_CFM_CCIF             unused by PE */
    Cpu_Interrupt,                     /* 0x7C  0x200001F0   -   -   ivINT_CFM_PVIF             unused by PE */
    Cpu_Interrupt,                     /* 0x7D  0x200001F4   -   -   ivINT_CFM_AEIF             unused by PE */
    Cpu_Interrupt,                     /* 0x7E  0x200001F8   -   -   ivINT_I2C1_IIF             unused by PE */
    Cpu_Interrupt,                     /* 0x7F  0x200001FC   -   -   ivINT_RTC                  unused by PE */
    Cpu_Interrupt,                     /* 0x80  0x20000200   -   -   ivReserved128              unused by PE */
    Cpu_Interrupt,                     /* 0x81  0x20000204   -   -   ivReserved129              unused by PE */
    Cpu_Interrupt,                     /* 0x82  0x20000208   -   -   ivReserved130              unused by PE */
    Cpu_Interrupt,                     /* 0x83  0x2000020C   -   -   ivReserved131              unused by PE */
    Cpu_Interrupt,                     /* 0x84  0x20000210   -   -   ivReserved132              unused by PE */
    Cpu_Interrupt,                     /* 0x85  0x20000214   -   -   ivReserved133              unused by PE */
    Cpu_Interrupt,                     /* 0x86  0x20000218   -   -   ivReserved134              unused by PE */
    Cpu_Interrupt,                     /* 0x87  0x2000021C   -   -   ivReserved135              unused by PE */
    Cpu_Interrupt,                     /* 0x88  0x20000220   -   -   ivINT_FLEXCAN_BUF0I        unused by PE */
    Cpu_Interrupt,                     /* 0x89  0x20000224   -   -   ivINT_FLEXCAN_BUF1I        unused by PE */
    Cpu_Interrupt,                     /* 0x8A  0x20000228   -   -   ivINT_FLEXCAN_BUF2I        unused by PE */
    Cpu_Interrupt,                     /* 0x8B  0x2000022C   -   -   ivINT_FLEXCAN_BUF3I        unused by PE */
    Cpu_Interrupt,                     /* 0x8C  0x20000230   -   -   ivINT_FLEXCAN_BUF4I        unused by PE */
    Cpu_Interrupt,                     /* 0x8D  0x20000234   -   -   ivINT_FLEXCAN_BUF5I        unused by PE */
    Cpu_Interrupt,                     /* 0x8E  0x20000238   -   -   ivINT_FLEXCAN_BUF6I        unused by PE */
    Cpu_Interrupt,                     /* 0x8F  0x2000023C   -   -   ivINT_FLEXCAN_BUF7I        unused by PE */
    Cpu_Interrupt,                     /* 0x90  0x20000240   -   -   ivINT_FLEXCAN_BUF8I        unused by PE */
    Cpu_Interrupt,                     /* 0x91  0x20000244   -   -   ivINT_FLEXCAN_BUF9I        unused by PE */
    Cpu_Interrupt,                     /* 0x92  0x20000248   -   -   ivINT_FLEXCAN_BUF10I       unused by PE */
    Cpu_Interrupt,                     /* 0x93  0x2000024C   -   -   ivINT_FLEXCAN_BUF11I       unused by PE */
    Cpu_Interrupt,                     /* 0x94  0x20000250   -   -   ivINT_FLEXCAN_BUF12I       unused by PE */
    Cpu_Interrupt,                     /* 0x95  0x20000254   -   -   ivINT_FLEXCAN_BUF13I       unused by PE */
    Cpu_Interrupt,                     /* 0x96  0x20000258   -   -   ivINT_FLEXCAN_BUF14I       unused by PE */
    Cpu_Interrupt,                     /* 0x97  0x2000025C   -   -   ivINT_FLEXCAN_BUF15I       unused by PE */
    Cpu_Interrupt,                     /* 0x98  0x20000260   -   -   ivINT_FLEXCAN_ERR_INT      unused by PE */
    Cpu_Interrupt,                     /* 0x99  0x20000264   -   -   ivINT_FLEXCAN_BOFF_INT     unused by PE */
    Cpu_Interrupt,                     /* 0x9A  0x20000268   -   -   ivReserved154              unused by PE */
    Cpu_Interrupt,                     /* 0x9B  0x2000026C   -   -   ivReserved155              unused by PE */
    Cpu_Interrupt,                     /* 0x9C  0x20000270   -   -   ivReserved156              unused by PE */
    Cpu_Interrupt,                     /* 0x9D  0x20000274   -   -   ivReserved157              unused by PE */
    Cpu_Interrupt,                     /* 0x9E  0x20000278   -   -   ivReserved158              unused by PE */
    Cpu_Interrupt,                     /* 0x9F  0x2000027C   -   -   ivReserved159              unused by PE */
    Cpu_Interrupt,                     /* 0xA0  0x20000280   -   -   ivReserved160              unused by PE */
    Cpu_Interrupt,                     /* 0xA1  0x20000284   -   -   ivReserved161              unused by PE */
    Cpu_Interrupt,                     /* 0xA2  0x20000288   -   -   ivReserved162              unused by PE */
    Cpu_Interrupt,                     /* 0xA3  0x2000028C   -   -   ivReserved163              unused by PE */
    Cpu_Interrupt,                     /* 0xA4  0x20000290   -   -   ivReserved164              unused by PE */
    Cpu_Interrupt,                     /* 0xA5  0x20000294   -   -   ivReserved165              unused by PE */
    Cpu_Interrupt,                     /* 0xA6  0x20000298   -   -   ivReserved166              unused by PE */
    Cpu_Interrupt,                     /* 0xA7  0x2000029C   -   -   ivReserved167              unused by PE */
    Cpu_Interrupt,                     /* 0xA8  0x200002A0   -   -   ivReserved168              unused by PE */
    Cpu_Interrupt,                     /* 0xA9  0x200002A4   -   -   ivReserved169              unused by PE */
    Cpu_Interrupt,                     /* 0xAA  0x200002A8   -   -   ivReserved170              unused by PE */
    Cpu_Interrupt,                     /* 0xAB  0x200002AC   -   -   ivReserved171              unused by PE */
    Cpu_Interrupt,                     /* 0xAC  0x200002B0   -   -   ivReserved172              unused by PE */
    Cpu_Interrupt,                     /* 0xAD  0x200002B4   -   -   ivReserved173              unused by PE */
    Cpu_Interrupt,                     /* 0xAE  0x200002B8   -   -   ivReserved174              unused by PE */
    Cpu_Interrupt,                     /* 0xAF  0x200002BC   -   -   ivReserved175              unused by PE */
    Cpu_Interrupt,                     /* 0xB0  0x200002C0   -   -   ivReserved176              unused by PE */
    Cpu_Interrupt,                     /* 0xB1  0x200002C4   -   -   ivReserved177              unused by PE */
    Cpu_Interrupt,                     /* 0xB2  0x200002C8   -   -   ivReserved178              unused by PE */
    Cpu_Interrupt,                     /* 0xB3  0x200002CC   -   -   ivReserved179              unused by PE */
    Cpu_Interrupt,                     /* 0xB4  0x200002D0   -   -   ivReserved180              unused by PE */
    Cpu_Interrupt,                     /* 0xB5  0x200002D4   -   -   ivReserved181              unused by PE */
    Cpu_Interrupt,                     /* 0xB6  0x200002D8   -   -   ivReserved182              unused by PE */
    Cpu_Interrupt,                     /* 0xB7  0x200002DC   -   -   ivReserved183              unused by PE */
    Cpu_Interrupt,                     /* 0xB8  0x200002E0   -   -   ivReserved184              unused by PE */
    Cpu_Interrupt,                     /* 0xB9  0x200002E4   -   -   ivReserved185              unused by PE */
    Cpu_Interrupt,                     /* 0xBA  0x200002E8   -   -   ivReserved186              unused by PE */
    Cpu_Interrupt,                     /* 0xBB  0x200002EC   -   -   ivReserved187              unused by PE */
    Cpu_Interrupt,                     /* 0xBC  0x200002F0   -   -   ivReserved188              unused by PE */
    Cpu_Interrupt,                     /* 0xBD  0x200002F4   -   -   ivReserved189              unused by PE */
    Cpu_Interrupt,                     /* 0xBE  0x200002F8   -   -   ivReserved190              unused by PE */
    Cpu_Interrupt                      /* 0xBF  0x200002FC   -   -   ivReserved191              unused by PE */
  };
  
  /* CFM init */
  
  #define CFM_KEY_UPPER   0x00
  #define CFM_KEY_LOWER   0x00
  #define CFM_CFMPROT     0x00
  #define CFM_CFMSACC     0x00
  #define CFM_CFMDACC     0x00
  #define CFM_CFMSEC      0x00
  
  #pragma define_section cfmconfig ".cfmconfig"  far_absolute R
  #pragma explicit_zero_data on
  
  __declspec(cfmconfig)  unsigned long _cfm[0x06] = {
    CFM_KEY_UPPER,    /* 0x00000400 */
    CFM_KEY_LOWER,    /* 0x00000404 */
    CFM_CFMPROT,      /* 0x00000408 */
    CFM_CFMSACC,      /* 0x0000040C */
    CFM_CFMDACC,      /* 0x00000410 */
    CFM_CFMSEC        /* 0x00000414 */
  };
  

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale MCF series of microcontrollers.
**
** ###################################################################
*/
