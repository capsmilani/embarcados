/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : Cpu.c
**     Project     : fucking_teste
**     Processor   : MCF52259CAG80
**     Component   : MCF52259_144_LQFP
**     Version     : Component 01.000, Driver 01.06, CPU db: 3.00.000
**     Datasheet   : MCF52259RM Rev.0 Draft B, MCF52259DS Rev.0 Draft C, Kirin3 System on a Chip GuideV0.2
**     Compiler    : CodeWarrior MCF C Compiler
**     Date/Time   : 2017-06-09, 23:32, # CodeGen: 55
**     Abstract    :
**
**     Settings    :
**
**     Contents    :
**         EnableInt   - void Cpu_EnableInt(void);
**         DisableInt  - void Cpu_DisableInt(void);
**         SetIntLevel - void Cpu_SetIntLevel(byte Level);
**         Delay100US  - void Cpu_Delay100US(word us100);
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
** @file Cpu.c
** @version 01.06
** @brief
**
*/         
/*!
**  @addtogroup Cpu_module Cpu module documentation
**  @{
*/         

/* MODULE Cpu. */

#include "Bit1.h"
#include "SM1.h"
#include "TI1.h"
#include "Bits1.h"
#include "AD1.h"
#include "Bits2.h"
#include "Term1.h"
#include "Inhr1.h"
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Events.h"
#include "Cpu.h"
#include "IO_Map.h"


/* Global variables */
volatile word SR_reg;                  /* Current value of the SR register */
volatile byte SR_lock = 0x00;          /* Lock */
/*
** ===================================================================
**     Method      :  Cpu_Interrupt (component MCF52259_144_LQFP)
**
**     Description :
**         The method services unhandled interrupt vectors.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_Interrupt)
{
  /* This code can be changed using the CPU bean property "Build Options / Unhandled int code" */
  /*lint -save  -e950 Disable MISRA rule (1.1) checking. */
  asm (HALT);
  /*lint -restore Enable MISRA rule (1.1) checking. */
}

/*
** ===================================================================
**     Method      :  Cpu_INT_SCM_SWTIInterrupt (component MCF52259_144_LQFP)
**
**     Description :
**         This ISR services the 'Core watchdog' interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_INT_SCM_SWTIInterrupt)
{
  Cpu_OnCoreWatchdogINT();
}

/*
** ===================================================================
**     Method      :  Cpu_DisableInt (component MCF52259_144_LQFP)
**     Description :
**         Disables all maskable interrupts. This method sets the
**         interrupt level mask group in the SR register by value = 7.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void Cpu_DisableInt(void)

**      This method is implemented as macro in the header module. **
*/

/*
** ===================================================================
**     Method      :  Cpu_EnableInt (component MCF52259_144_LQFP)
**     Description :
**         Enables all maskable interrupts. This method sets the
**         interrupt level mask group in the SR register by value = 0.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void Cpu_EnableInt(void)

**      This method is implemented as macro in the header module. **
*/

/*
** ===================================================================
**     Method      :  Cpu_SetIntLevel (component MCF52259_144_LQFP)
**     Description :
**         Sets the interrupt level mask in the SR register. Interrupt
**         requests are inhibited for all priority levels less than or
**         equal to current level, except edge-sensitive level 7
**         request, which cannot be masked.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Level           - New interrupt priority level value.
**     Returns     : Nothing
** ===================================================================
*/
/*
void Cpu_SetIntLevel(byte Level)

**      This method is implemented as macro in the header module. **
*/

/*
** ===================================================================
**     Method      :  Cpu_Delay100US (component MCF52259_144_LQFP)
**     Description :
**         This method realizes software delay. The length of delay is
**         at least 100 microsecond multiply input parameter [us100].
**         As the delay implementation is not based on real clock, the
**         delay time may be increased by interrupt service routines
**         processed during the delay. The method is independent on
**         selected speed mode.
**     Parameters  :
**         NAME            - DESCRIPTION
**         us100           - Number of 100 us delay repetitions.
**     Returns     : Nothing
** ===================================================================
*/
__declspec(register_abi) void Cpu_Delay100US(word us100:__D0)
{
  /* irremovable one time overhead (ignored): 11 cycles */
  /* move: 1 cycle overhead (load parameter into register) */
  /* jsr:  3 cycles overhead (jump to subroutine) */
  /* andi: 1 cycle overhead (clear upper word of d0) */
  /* tpf: 1 cycle overhead (alignment) */
  /* rts:  5 cycles overhead (return from subroutine) */

  /* aproximate irremovable overhead for each 100us cycle (counted) : 3 cycles */
  /* subq.l 1 cycles overhead  */
  /* bne.b  2 cycles overhead  */

  /* Disable MISRA rule 55 checking - Non-case label used */
  /*lint -esym( 961, 55)   */
#pragma unused(us100)
  asm {
    naked
    andi.l #0xFFFF,d0                  /* parameter is word - clear the rest of d0 register */
    tpf                                /* alignment */
loop:
    /* 100 us delay block begin */
    /*
     * Delay
     *   - requested                  : 100 us @ 80MHz,
     *   - possible                   : 8000 c, 100000 ns
     *   - without removable overhead : 7997 c, 99962.5 ns
     */
    move.l #0x0A69,d1                  /* (1 c: 12.5 ns) number of iterations */
label0:
    subq.l #1,d1                       /* (1 c: 12.5 ns) decrement d1 */
    bne.b label0                       /* (2 c: 25 ns) repeat 2665x */
    tpf                                /* (1 c: 12.5 ns) wait for 1 c */
    /* 100 us delay block end */
    subq.l #1,d0                       /* parameter is passed via d0 register */
    bne.w loop                         /* next loop */
    rts                                /* return from subroutine */
  }
  /* Restore MISRA rule 55 checking - Non-case label used */
  /*lint +esym( 961, 55)   */
}

/*
** ===================================================================
**     Method      :  __initialize_hardware (component MCF52259_144_LQFP)
**
**     Description :
**         Initializes the whole system like timing, external bus, etc.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

/*** !!! Here you can place your own code using property "User data declarations" on the build options tab. !!! ***/

void __initialize_hardware(void)
{
  extern uint32 __VECTOR_RAM[];


  /*** !!! Here you can place your own code before PE initialization using property "User code before PE initialization" on the build options tab. !!! ***/


  /* Initialize IPSBAR and validate it */
  asm {
    move.l  #0x40000001,d0
    move.l  d0,0x40000000
  }
  /* Initialize FLASHBAR */
  asm {
    move.l  #0x00000021,d0
    movec   d0,FLASHBAR
  }
  /* Initialize RAMBAR */
  asm {
    move.l  #0x20000221,d0
    movec   d0,RAMBAR
  }
  /* Initialize Vector Base Register (VBR) */
  asm {
    lea   __VECTOR_RAM,A0
    movec A0,VBR
    nop
  }


  /*** ### MCF52259CAG80 "Cpu" init code ... ***/
  /*** PE initialization code after reset ***/
  /* System clock initialization */
  /* OCLR: OSCEN=1,REFS=1,LPEN=0,RANGE=0,??=0,??=0,??=0,??=0 */
  setReg8(OCLR, 0xC0U);                /* Enable external oscillator */ 
  /* CCLR: ??=0,??=0,??=0,??=0,??=0,??=0,OSCSEL1=0,OSCSEL0=0 */
  setReg8(CCLR, 0x00U);                /* Swith to the external clock */ 
  /* OCHR: OCOEN=0,STBY=0,??=0,??=0,??=0,??=0,??=0,??=0 */
  setReg8(OCHR, 0x00U);                /* Turn off the on-chip relaxation oscillator */ 
  /* CCHR: ??=0,??=0,??=0,??=0,??=0,CCHR=5 */
  setReg8(CCHR, 0x05U);                /* Set the predivider */ 
  /* SYNCR: LOLRE=0,MFD=3,LOCRE=0,RFD=0,LOCEN=0,DISCLK=0,FWKUP=0,??=0,??=0,CLKSRC=1,PLLMODE=1,PLLEN=1 */
  setReg16(SYNCR, 0x3007U);            /* Set the SYNCR register */ 
  while (!(SYNSR & SYNSR_LOCK_BITMASK)){} /* Wait until the PLL is locked. */
  /* LPDR: ??=0,??=0,??=0,??=0,LPD=0 */
  setReg8(LPDR, 0x00U);                /* Set the low power divider */ 
  /* RTCCR: ??=0,EXTALEN=0,??=0,OSCEN=0,KHZEN=0,REFS=0,LPEN=0,RTCSEL=1 */
  setReg8(RTCCR, 0x01U);               /* Set the RTC oscillator and RTC clock select */ 
  /* BWCR: ??=0,??=0,??=0,??=0,??=0,??=0,BWDSTOP=0,BWDSEL=1 */
  setReg32(BWCR, 0x01UL);              /* Set the BWCR register */ 
  /* Initialization of the ExternalBus module */
  /* CSMR0: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,V=0 */
  clrReg32Bits(CSMR0, 0xFEFFUL);        
  /* CSMR1: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,V=0 */
  clrReg32Bits(CSMR1, 0xFEFFUL);        
  /*** End of PE initialization code after reset ***/

  /*** !!! Here you can place your own code after PE initialization using property "User code after PE initialization" on the build options tab. !!! ***/

}

/*
** ===================================================================
**     Method      :  PE_low_level_init (component MCF52259_144_LQFP)
**
**     Description :
**         Initializes beans and provides common register initialization. 
**         The method is called automatically as a part of the 
**         application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void PE_low_level_init(void)
{
  /* Initialization of the SCM module */
  /* CWCR: CWE=0,CWRI=0,CWT=0,CWTA=0,CWTAVAL=1,CWTIF=1 */
  setReg8(CWCR, 0x03U);                 
  /* CWSR: CWSR=0x55 */
  setReg8(CWSR, 0x55U);                 
  /* CWSR: CWSR=0xAA */
  setReg8(CWSR, 0xAAU);                 
  /* CWCR: CWE=0,CWRI=0,CWT=0,CWTA=0,CWTAVAL=0,CWTIF=0 */
  setReg8(CWCR, 0x00U);                 
  /* MPARK: BCR24BIT=0 */
  clrReg32Bits(MPARK, 0x01000000UL);    
  /* DMAREQC: DMAC3=0,DMAC2=0,DMAC1=0,DMAC0=0 */
  clrReg32Bits(DMAREQC, 0xFFFFUL);      
  /* MPARK: M2_P_EN=0,M3_PRTY=3,M2_PRTY=2,M0_PRTY=0,M1_PRTY=1,FIXED=0,TIMEOUT=0,PRKLAST=0,LCKOUT_TIME=0 */
  clrSetReg32Bits(MPARK, 0x021E7F00UL, 0x00E10000UL); 
  /* MPR: MPR=3 */
  clrSetReg8Bits(MPR, 0x0CU, 0x03U);    
  /* PACR0: LOCK1=0,ACCESS_CTRL1=0 */
  clrReg8Bits(PACR0, 0xF0U);            
  /* PACR1: LOCK0=0,ACCESS_CTRL0=0 */
  clrReg8Bits(PACR1, 0x0FU);            
  /* PACR2: LOCK1=0,ACCESS_CTRL1=0,LOCK0=0,ACCESS_CTRL0=0 */
  setReg8(PACR2, 0x00U);                
  /* PACR3: LOCK1=0,ACCESS_CTRL1=0 */
  clrReg8Bits(PACR3, 0xF0U);            
  /* PACR4: LOCK1=0,ACCESS_CTRL1=0,LOCK0=0,ACCESS_CTRL0=0 */
  setReg8(PACR4, 0x00U);                
  /* PACR5: LOCK1=0,ACCESS_CTRL1=0 */
  clrReg8Bits(PACR5, 0xF0U);            
  /* PACR6: LOCK1=0,ACCESS_CTRL1=0,LOCK0=0,ACCESS_CTRL0=0 */
  setReg8(PACR6, 0x00U);                
  /* PACR7: LOCK1=0,ACCESS_CTRL1=0,LOCK0=0,ACCESS_CTRL0=0 */
  setReg8(PACR7, 0x00U);                
  /* PACR8: LOCK1=0,ACCESS_CTRL1=0,LOCK0=0,ACCESS_CTRL0=0 */
  setReg8(PACR8, 0x00U);                
  /* PACR10: LOCK1=0,ACCESS_CTRL1=0 */
  clrReg8Bits(PACR10, 0xF0U);           
  /* GPACR0: LOCK=0,ACCESS_CTRL=0 */
  clrReg8Bits(GPACR0, 0x8FU);           
  /* GPACR1: LOCK=0,ACCESS_CTRL=0 */
  clrReg8Bits(GPACR1, 0x8FU);           
  /* Initialization of the PowerManagement module */
  /* LPCR: LPMD=0 */
  clrReg8Bits(LPCR, 0xC0U);             
  /* LPICR: ENBSTOP=0,XLPM_IPL=0 */
  clrReg8Bits(LPICR, 0xF0U);            
  /* PPMRH: CDRTC=0,CDCFM=0,CDFCAN=0,CDPWM=0,CDGPT=0,CDADC=0,CDPIT1=0,CDPIT0=0,CDEPORT=0,CDGPIO=0 */
  clrReg32Bits(PPMRH, 0x4F9BUL);        
  /* PPMRL: CDFEC=0,CDINTC1=0,CDINTC0=0,CDDTIM3=0,CDDTIM2=0,CDDTIM1=0,CDDTIM0=0,CDI2C1=0,CDQSPI=0,CDI2C0=0,CDUART2=0,CDUART1=0,CDUART0=0,CDDMA=0,CDMINIBUS=0,CDG=0 */
  clrReg32Bits(PPMRL, 0x0027EEFAUL);    
  /* IPSBMT: BME=1,BMT=0 */
  clrSetReg8Bits(IPSBMT, 0x07U, 0x08U); 
  /* Initialization of the ResetController module */
  /* ResetController_RCR: SOFTRST=0,FRCRSTOUT=0,??=0,LVDF=1,LVDIE=0,LVDRE=1,??=0,LVDE=1 */
  setReg8(ResetController_RCR, 0x15U);  
  /* Initialization of the CCM module */
  /* CCR: LOAD=0 */
  clrReg16Bits(CCR, 0x8000U);           
  /* IMRL0: MASKALL=0 */
  clrReg32Bits(IMRL0, 0x01UL);         /* Disable masking of all interrupts of the INTC0 device */ 
  /* IMRL1: MASKALL=0 */
  clrReg32Bits(IMRL1, 0x01UL);         /* Disable masking of all interrupts of the INTC1 device */ 
  /* SCM_RAMBAR: BA=0x2000,??=0,??=0,??=0,??=0,??=0,??=0,BDE=1,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
  setReg32(SCM_RAMBAR, 0x20000200UL);   
  /* Common initialization of the CPU registers */
  /* PORTQS: PORTQS3=0 */
  clrReg8Bits(PORTQS, 0x08U);           
  /* DDRQS: DDRQS3=1 */
  setReg8Bits(DDRQS, 0x08U);            
  /* ICR044: IL=7,IP=7 */
  setReg8Bits(ICR044, 0x3FU);           
  /* DDRTA: DDRTA0=0 */
  clrReg8Bits(DDRTA, 0x01U);            
  /* PTAPAR: PTAPAR0=0 */
  clrReg8Bits(PTAPAR, 0x03U);           
  /* PANPAR: PANPAR1=1,PANPAR0=1 */
  setReg8Bits(PANPAR, 0x03U);           
  /* PORTTC: PORTTC3=0,PORTTC2=0,PORTTC1=0,PORTTC0=0 */
  clrReg8Bits(PORTTC, 0x0FU);           
  /* DDRTC: DDRTC3=1,DDRTC2=1,DDRTC1=1,DDRTC0=1 */
  setReg8Bits(DDRTC, 0x0FU);            
  /* PTCPAR: PTCPAR3=0,PTCPAR2=0,PTCPAR1=0,PTCPAR0=0 */
  setReg8(PTCPAR, 0x00U);               
  /* PUBPAR: PUBPAR1=1,PUBPAR0=1 */
  clrSetReg8Bits(PUBPAR, 0x0AU, 0x05U); 
  /* ICR014: IL=3,IP=0 */
  clrSetReg8Bits(ICR014, 0x27U, 0x18U); 
  /* PTEPAR: PTEPAR7=1,PTEPAR6=1,PTEPAR5=1,PTEPAR4=1,PTEPAR3=1,PTEPAR2=1,PTEPAR1=1,PTEPAR0=1 */
  setReg8(PTEPAR, 0xFFU);               
  /* PTFPAR: PTFPAR7=1,PTFPAR6=1,PTFPAR5=1,PTFPAR4=1,PTFPAR3=1,PTFPAR2=1,PTFPAR1=1,PTFPAR0=1 */
  setReg8(PTFPAR, 0xFFU);               
  /* PTGPAR: PTGPAR7=1,PTGPAR6=1,PTGPAR3=1,PTGPAR2=1,PTGPAR1=1,PTGPAR0=1 */
  setReg8Bits(PTGPAR, 0xCFU);           
  /* ICR008: IL=0,IP=0 */
  clrReg8Bits(ICR008, 0x3FU);           
  /* ICR048: IL=0,IP=0 */
  clrReg8Bits(ICR048, 0x3FU);           
  /* PQSPAR: PQSPAR3=0,PQSPAR2=1,PQSPAR0=1 */
  clrSetReg16Bits(PQSPAR, 0xE2U, 0x11U); 
  /* PTHPAR: PTHPAR7=1,PTHPAR6=1,PTHPAR5=1,PTHPAR4=1,PTHPAR3=1,PTHPAR2=1,PTHPAR1=1,PTHPAR0=1 */
  setReg16(PTHPAR, 0x5555U);            
  /* IMRH0: INT_MASK48=1,INT_MASK44=0 */
  clrSetReg32Bits(IMRH0, 0x1000UL, 0x00010000UL); 
  /* IMRL0: INT_MASK14=0,INT_MASK8=1 */
  clrSetReg32Bits(IMRL0, 0x4000UL, 0x0100UL); 
  /* ### BitIO "Bit1" init code ... */
  /* ### SynchroMaster "SM1" init code ... */
  SM1_Init();
  /* ### TimerInt "TI1" init code ... */
  TI1_Init();
  /* ### BitsIO "Bits1" init code ... */
  /* ### ADC "AD1" init code ... */
  AD1_Init();
  /* ### BitsIO "Bits2" init code ... */
  /* ### Asynchro serial "Inhr1" init code ... */
  Inhr1_Init();
  /* ###  "Term1" init code ... */
  __EI(0);                             /* Enable interrupts of the given priority level */
}


/* END Cpu. */

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
