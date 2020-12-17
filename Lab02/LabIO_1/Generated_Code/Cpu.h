/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : Cpu.h
**     Project     : LabIO_1
**     Processor   : MCF52259CAG80
**     Component   : MCF52259_144_LQFP
**     Version     : Component 01.000, Driver 01.06, CPU db: 3.00.000
**     Datasheet   : MCF52259RM Rev.0 Draft B, MCF52259DS Rev.0 Draft C, Kirin3 System on a Chip GuideV0.2
**     Compiler    : CodeWarrior MCF C Compiler
**     Date/Time   : 2017-05-09, 10:51, # CodeGen: 0
**     Abstract    :
**
**     Settings    :
**
**     Contents    :
**         EnableInt   - void Cpu_EnableInt(void);
**         DisableInt  - void Cpu_DisableInt(void);
**         SetIntLevel - void Cpu_SetIntLevel(byte Level);
**
**     (c) Freescale Semiconductor, Inc.
**     2004 All Rights Reserved
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
** @file Cpu.h
** @version 01.06
** @brief
**
*/         
/*!
**  @addtogroup Cpu_module Cpu module documentation
**  @{
*/         

#ifndef __Cpu_H
#define __Cpu_H

/* MODULE Cpu. */

/* Active configuration define symbol */
#define PEcfg_INTERNAL_RAM          1U

/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"


#define CPU_BUS_CLK_HZ              0x04C4B400UL /* Initial value of the bus clock frequency in Hz */

#define CPU_INSTR_CLK_HZ            0x04C4B400UL /* Initial value of the instruction clock frequency in Hz */

#define CPU_EXT_CLK_HZ              0x02DC6C00UL /* Value of the main clock frequency (crystal or external clock) in Hz */
#define CPU_INT_CLK_HZ              0x007A1200UL /* Value of the internal oscillator clock frequency in Hz */

#define CPU_TICK_NS                 0x15U /* CPU tick is a unit derived from the frequency of external clock source. If no external clock is enabled or available it is derived from the value of internal clock source. The value of this constant represents period of the clock source in ns. */

#define CPU_FAMILY_MCF                 /* Specification of the core type of the selected cpu */
#define CPU_DERIVATIVE_MCF52259_144_LQFP /* Name of the selected cpu derivative */
#define CPU_PARTNUM_MCF52259CAG80      /* Part number of the selected cpu */

/*lint -esym(765,SR_reg,SR_lock,__initialize_hardware) Disable MISRA rule (23) checking for symbols (SR_reg,SR_lock,__initialize_hardware). */
/* Global variables */
extern volatile word SR_reg;           /* Current CCR reegister */
extern volatile byte SR_lock;



#define Cpu_DisableInt()  __DI()       /* Disable interrupts all maskable interrupt */
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

#define Cpu_EnableInt()  __EI(0x00)    /* Enable all maskable interrupts */
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

#define Cpu_SetIntLevel(Level) __EI(Level)
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

void PE_low_level_init(void);
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

PE_ISR(Cpu_INT_SCM_SWTIInterrupt);
/*
** ===================================================================
**     Method      :  Cpu_INT_SCM_SWTIInterrupt (component MCF52259_144_LQFP)
**
**     Description :
**         This ISR services the 'Core watchdog' interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/



PE_ISR(Cpu_Interrupt);
/*
** ===================================================================
**     Method      :  Cpu_Interrupt (component MCF52259_144_LQFP)
**
**     Description :
**         The method services unhandled interrupt vectors.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/


void __initialize_hardware(void);
/*
** ===================================================================
**     Method      :  __initialize_hardware (component MCF52259_144_LQFP)
**
**     Description :
**         Initializes the whole system like timing, external bus, etc.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

/* END Cpu. */

#endif
/* __Cpu_H */

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
