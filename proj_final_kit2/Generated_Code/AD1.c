/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : AD1.c
**     Project     : kit2_comandos
**     Processor   : MCF52259CAG80
**     Component   : ADC
**     Version     : Component 01.690, Driver 01.05, CPU db: 3.00.000
**     Compiler    : CodeWarrior MCF C Compiler
**     Date/Time   : 2017-06-06, 09:21, # CodeGen: 40
**     Abstract    :
**         This device "ADC" implements an A/D converter,
**         its control methods and interrupt/event handling procedure.
**     Settings    :
**          Component name                                 : AD1
**          A/D converter                                  : ADC
**          Sharing                                        : Disabled
**          Interrupt service/event                        : Enabled
**            A/D interrupt                                : INT_ADC_ADCA
**            A/D interrupt priority                       : level 7, priority within level 4
**            Interrupt                                    : INT_ADC_ADCINT
**            Interrupt priority                           : level 7, priority within level 5
**          A/D channels                                   : 5
**            Channel0                                     : 
**              A/D channel (pin)                          : AN0_PAN0
**              A/D channel (pin) signal                   : 
**              Mode select                                : Single Ended
**            Channel1                                     : 
**              A/D channel (pin)                          : AN1_PAN1
**              A/D channel (pin) signal                   : 
**              Mode select                                : Single Ended
**            Channel2                                     : 
**              A/D channel (pin)                          : AN2_PAN2
**              A/D channel (pin) signal                   : 
**              Mode select                                : Single Ended
**            Channel3                                     : 
**              A/D channel (pin)                          : AN4_PAN4
**              A/D channel (pin) signal                   : 
**              Mode select                                : Single Ended
**            Channel4                                     : 
**              A/D channel (pin)                          : AN5_PAN5
**              A/D channel (pin) signal                   : 
**              Mode select                                : Single Ended
**          Queue                                          : Enabled
**            Mode                                         : Sequential
**            A/D samples                                  : 8
**              Sample0                                    : Enabled
**                Channel                                  : 0
**                High limit                               : 32760
**                Low limit                                : 0
**                Offset                                   : 0
**                Zero crossing                            : Disabled
**              Sample1                                    : Enabled
**                Channel                                  : 1
**                High limit                               : 32760
**                Low limit                                : 0
**                Offset                                   : 0
**                Zero crossing                            : Disabled
**              Sample2                                    : Enabled
**                Channel                                  : 2
**                High limit                               : 32760
**                Low limit                                : 0
**                Offset                                   : 0
**                Zero crossing                            : Disabled
**              Sample3                                    : Enabled
**                Channel                                  : 3
**                High limit                               : 32760
**                Low limit                                : 0
**                Offset                                   : 0
**                Zero crossing                            : Disabled
**              Sample4                                    : Enabled
**                Channel                                  : 4
**                High limit                               : 32760
**                Low limit                                : 0
**                Offset                                   : 0
**                Zero crossing                            : Disabled
**              Sample5                                    : Disabled
**              Sample6                                    : Disabled
**              Sample7                                    : Disabled
**          A/D resolution                                 : Autoselect
**          Conversion time                                : 10.2 �s
**          External trigger                               : Disabled
**          Internal trigger                               : Disabled
**          Volt. ref. recovery time                       : 100
**          Power up delay                                 : 13
**          Power savings mode                             : Disabled
**          Auto standby                                   : Disabled
**          Volt. ref. source                              : controlled by this component for both converter
**            High volt. ref. source                       : internal
**            Low volt. ref. source                        : internal
**          Number of conversions                          : 1
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**            Events enabled in init.                      : yes
**          CPU clock/speed selection                      : 
**            High speed mode                              : This component enabled
**            Low speed mode                               : This component disabled
**            Slow speed mode                              : This component disabled
**          High input limit                               : 1
**          Low input limit                                : 0
**          Get value directly                             : yes
**          Wait for result                                : yes
**     Contents    :
**         Measure        - byte AD1_Measure(bool WaitForResult);
**         MeasureChan    - byte AD1_MeasureChan(bool WaitForResult, byte Channel);
**         GetValue16     - byte AD1_GetValue16(word *Values);
**         GetChanValue16 - byte AD1_GetChanValue16(byte Channel, word *Value);
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
** @file AD1.c
** @version 01.05
** @brief
**         This device "ADC" implements an A/D converter,
**         its control methods and interrupt/event handling procedure.
*/         
/*!
**  @addtogroup AD1_module AD1 module documentation
**  @{
*/         

/* MODULE AD1. */

#include "Events.h"
#include "AD1.h"

#define IDLE            0              /* IDLE state           */
#define MEASURE         1              /* MESURE state         */
#define CONTINUOUS      2              /* CONTINUOUS state     */
#define SINGLE          3              /* SINGLE state         */

static const byte Table[] = {          /* Table of mask constants */
0x01,0x02,0x04,0x08,0x10};
static const byte Channels[] = {       /* Number of the channel for each used sample */
0x00,0x01,0x02,0x04,0x05};
static byte OutFlg;                    /* Measurement finish flags */
static byte SumChan;                   /* Number of the measured channels */
/*lint -esym(765,AD1_ModeFlg) Disable MISRA rule (23) checking for symbols (AD1_ModeFlg). */
volatile byte AD1_ModeFlg;             /* Current state of device */
static word AD1_OutV[5];               /* Sum of measured values */

/*
** ===================================================================
**     Method      :  AD1_InterruptCC (component ADC)
**
**     Description :
**         The method services the conversion complete interrupt of the 
**         selected peripheral(s) and eventually invokes the components 
**         event(s).
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
__declspec(interrupt) void AD1_InterruptCC(void)
{
  setReg16Bits(ADSTAT,0x0800);         /* Clear EOSI flag */
  if (AD1_ModeFlg != SINGLE) {
    AD1_OutV[0] = getReg16(ADRSLT0);   /* Save measured values to the output buffer */
    AD1_OutV[1] = getReg16(ADRSLT1);   /* Save measured values to the output buffer */
    AD1_OutV[2] = getReg16(ADRSLT2);   /* Save measured values to the output buffer */
    AD1_OutV[3] = getReg16(ADRSLT3);   /* Save measured values to the output buffer */
    AD1_OutV[4] = getReg16(ADRSLT4);   /* Save measured values to the output buffer */
    OutFlg = 0x1F;                     /* Measured values are available */
    AD1_ModeFlg = IDLE;                /* Set the component to the idle mode */
    AD1_OnEnd();                       /* If yes then invoke user event */
  }
  else {
    AD1_OutV[SumChan] = getReg16(ADRSLT0); /* Save measured values to the output buffer */
    OutFlg |= Table[SumChan];          /* Measured values are available */
    AD1_ModeFlg = IDLE;                /* Set the component to the idle mode */
    AD1_OnEnd();                       /* If yes then invoke user event */
  }
}

/*
** ===================================================================
**     Method      :  HWEnDi (component ADC)
**
**     Description :
**         Enables or disables the peripheral(s) associated with the 
**         component. The method is called automatically as a part of 
**         Enable, Disable and Init methods and several internal methods.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void HWEnDi(void)
{
  if (AD1_ModeFlg) {                   /* Launch measurement? */
    if (AD1_ModeFlg != SINGLE) {
      OutFlg = 0x00;                   /* Measured values are available */
    }
    else {
      OutFlg &= ~Table[SumChan];       /* Output value isn't available */
    }
    clrReg16Bit(CTRL1,STOP0);          /* Normal operation mode */
    setReg16Bit(CTRL1,START0);         /* Launching of conversion */
  }
  else {
    setReg16Bit(CTRL1,STOP0);          /* Stop command issued */
  }
}

/*
** ===================================================================
**     Method      :  AD1_Measure (component ADC)
*/
/*!
**     @brief
**         This method performs one measurement on all channels that
**         are set in the component inspector. (Note: If the [number of
**         conversions] is more than one the conversion of A/D channels
**         is performed specified number of times.)
**     @param
**         WaitForResult   - Wait for a result of a
**                           conversion. If [interrupt service] is
**                           disabled, A/D peripheral doesn't support
**                           measuring all channels at once or Autoscan
**                           mode property isn't enabled and at the same
**                           time the [number of channels] is greater
**                           than 1, then the WaitForResult parameter is
**                           ignored and the method waits for each
**                           result every time. If the [interrupt
**                           service] is disabled and a [number of
**                           conversions] is greater than 1, the
**                           parameter is ignored and the method also
**                           waits for each result every time.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - Device is disabled
**                           ERR_BUSY - A conversion is already running
*/
/* ===================================================================*/
byte AD1_Measure(bool WaitForResult)
{
  if (AD1_ModeFlg != IDLE) {           /* Is the device in running mode? */
    return ERR_BUSY;                   /* If yes then error */
  }
  /* ADLST1: ??=0,SAMPLE3=4,??=0,SAMPLE2=2,??=0,SAMPLE1=1,??=0,SAMPLE0=0 */
  setReg16(ADLST1,0x4210);             /* Set ADC channel list reg. */
  /* ADSDIS: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,DS7=1,DS6=1,DS5=1,DS4=0,DS3=0,DS2=0,DS1=0,DS0=0 */
  setReg16(ADSDIS,0xE0);               /* Enable/disable of samples */
  AD1_ModeFlg = MEASURE;               /* Set state of device to the measure mode */
  HWEnDi();                            /* Enable the device */
  if (WaitForResult)                   /* Is WaitForResult TRUE? */
    while (AD1_ModeFlg == MEASURE) {}  /* If yes then wait for end of measurement */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  AD1_MeasureChan (component ADC)
*/
/*!
**     @brief
**         This method performs measurement on one channel. (Note: If
**         the [number of conversions] is more than one the conversion
**         of the A/D channel is performed specified number of times.)
**     @param
**         WaitForResult   - Wait for a result of
**                           conversion. If the [interrupt service] is
**                           disabled and at the same time a [number of
**                           conversions] is greater than 1, the
**                           WaitForResult parameter is ignored and the
**                           method waits for each result every time.
**     @param
**         Channel         - Channel number. If only one
**                           channel in the component is set this
**                           parameter is ignored, because the parameter
**                           is set inside this method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - Device is disabled
**                           ERR_BUSY - A conversion is already running
**                           ERR_RANGE - Parameter "Channel" out of range
*/
/* ===================================================================*/
byte AD1_MeasureChan(bool WaitForResult,byte Channel)
{
  if (Channel >= 5) {                  /* Is channel number out of range? */
    return ERR_RANGE;                  /* If yes then error */
  }
  if (AD1_ModeFlg != IDLE) {           /* Is the device in running mode? */
    return ERR_BUSY;                   /* If yes then error */
  }
  setReg16(ADLST1,Channels[Channel]);  /* Set ADC channel list reg. */
  /* ADSDIS: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,DS7=1,DS6=1,DS5=1,DS4=1,DS3=1,DS2=1,DS1=1,DS0=0 */
  setReg16(ADSDIS,0xFE);               /* Enable/disable of sample 0 */
  AD1_ModeFlg = SINGLE;                /* Set state of device to the measure mode */
  SumChan = Channel;                   /* Set required channel */
  HWEnDi();                            /* Enable the device */
  if (WaitForResult)                   /* Is WaitForResult TRUE? */
    while (AD1_ModeFlg == SINGLE) {}   /* If yes then wait for end of measurement */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  AD1_GetValue16 (component ADC)
*/
/*!
**     @brief
**         This method returns the last measured values of all channels.
**         Compared with [GetValue] method this method returns more
**         accurate result if the [number of conversions] is greater
**         than 1 and [AD resolution] is less than 16 bits. In addition,
**         the user code dependency on [AD resolution] is eliminated.
**     @param
**         Values          - Pointer to the array that contains
**                           the measured data.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_NOTAVAIL - Requested value not
**                           available
**                           ERR_OVERRUN - External trigger overrun flag
**                           was detected after the last value(s) was
**                           obtained (for example by GetValue). This
**                           error may not be supported on some CPUs
**                           (see generated code).
*/
/* ===================================================================*/
byte AD1_GetValue16(word *Values)
{
  if (OutFlg != 0x1F) {                /* Is measured value(s) available? */
    return ERR_NOTAVAIL;               /* If no then error */
  }
  *Values++ = (word)((AD1_OutV[0] + 0x00) << 1); /* Store value from output to user buffer */
  *Values++ = (word)((AD1_OutV[1] + 0x00) << 1); /* Store value from output to user buffer */
  *Values++ = (word)((AD1_OutV[2] + 0x00) << 1); /* Store value from output to user buffer */
  *Values++ = (word)((AD1_OutV[3] + 0x00) << 1); /* Store value from output to user buffer */
  *Values = (word)((AD1_OutV[4] + 0x00) << 1); /* Store value from output to user buffer */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  AD1_GetChanValue16 (component ADC)
*/
/*!
**     @brief
**         This method returns the last measured value of the required
**         channel. Compared with [GetChanValue] method this method
**         returns more accurate result if the [number of conversions]
**         is greater than 1 and [AD resolution] is less than 16 bits.
**         In addition, the user code dependency on [AD resolution] is
**         eliminated.
**     @param
**         Channel         - Channel number. If only one
**                           channel in the component is set then this
**                           parameter is ignored.
**     @param
**         Value           - Pointer to the measured value.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_NOTAVAIL - Requested value not
**                           available
**                           ERR_RANGE - Parameter "Channel" out of
**                           range
**                           ERR_OVERRUN - External trigger overrun flag
**                           was detected after the last value(s) was
**                           obtained (for example by GetValue). This
**                           error may not be supported on some CPUs
**                           (see generated code).
*/
/* ===================================================================*/
byte AD1_GetChanValue16(byte Channel,word *Value)
{
  if (Channel >= 5) {                  /* Is channel number out of range? */
    return ERR_RANGE;                  /* If yes then error */
  }
  if (!(OutFlg & Table[Channel])) {    /* Is measured value(s) available? */
    return ERR_NOTAVAIL;               /* If no then error */
  }
  *Value = (word)((AD1_OutV[Channel] + 0x00) << 1); /* Store value from output to user buffer */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  AD1_Init (component ADC)
**
**     Description :
**         Initializes the associated peripheral(s) and the components 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void AD1_Init(void)
{
  volatile word i;

  OutFlg = 0;                          /* No measured value */
  AD1_ModeFlg = IDLE;                  /* Device isn't running */
  /* CTRL1: ??=0,STOP0=1,START0=0,SYNC0=0,EOSIE0=1,ZCIE=0,LLMTIE=0,HLMTIE=0,CHNCFG=0,??=0,SMODE=0 */
  setReg16(CTRL1,0x4800);              /* Set control register 1 */
  /* CAL: SEL_VREFH=0,SEL_VREFL=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
  setReg16(CAL,0x00);                  /* Set calibration register */
  /* POWER: ASB=0,??=0,??=0,PSTS2=0,PSTS1=0,PSTS0=0,PUDELAY=0x0D,APD=0,PD2=0,PD1=0,PD0=0 */
  setReg16(POWER,0xD0);                /* Enable device */
  /* ADOFS0: ??=0,OFFSET=0,??=0,??=0,??=0 */
  setReg16(ADOFS0,0x00);               /* Set offset reg. 0 */
  /* ADOFS1: ??=0,OFFSET=0,??=0,??=0,??=0 */
  setReg16(ADOFS1,0x00);               /* Set offset reg. 1 */
  /* ADOFS2: ??=0,OFFSET=0,??=0,??=0,??=0 */
  setReg16(ADOFS2,0x00);               /* Set offset reg. 2 */
  /* ADOFS3: ??=0,OFFSET=0,??=0,??=0,??=0 */
  setReg16(ADOFS3,0x00);               /* Set offset reg. 3 */
  /* ADOFS4: ??=0,OFFSET=0,??=0,??=0,??=0 */
  setReg16(ADOFS4,0x00);               /* Set offset reg. 4 */
  /* ADHLMT0: ??=0,HLMT=0x0FFF,??=0,??=0,??=0 */
  setReg16(ADHLMT0,0x7FF8);            /* Set high limit reg. 0 */
  /* ADHLMT1: ??=0,HLMT=0x0FFF,??=0,??=0,??=0 */
  setReg16(ADHLMT1,0x7FF8);            /* Set high limit reg. 1 */
  /* ADHLMT2: ??=0,HLMT=0x0FFF,??=0,??=0,??=0 */
  setReg16(ADHLMT2,0x7FF8);            /* Set high limit reg. 2 */
  /* ADHLMT3: ??=0,HLMT=0x0FFF,??=0,??=0,??=0 */
  setReg16(ADHLMT3,0x7FF8);            /* Set high limit reg. 3 */
  /* ADHLMT4: ??=0,HLMT=0x0FFF,??=0,??=0,??=0 */
  setReg16(ADHLMT4,0x7FF8);            /* Set high limit reg. 4 */
  /* ADLLMT0: ??=0,LLMT=0,??=0,??=0,??=0 */
  setReg16(ADLLMT0,0x00);              /* Set low limit reg. 0 */
  /* ADLLMT1: ??=0,LLMT=0,??=0,??=0,??=0 */
  setReg16(ADLLMT1,0x00);              /* Set low limit reg. 1 */
  /* ADLLMT2: ??=0,LLMT=0,??=0,??=0,??=0 */
  setReg16(ADLLMT2,0x00);              /* Set low limit reg. 2 */
  /* ADLLMT3: ??=0,LLMT=0,??=0,??=0,??=0 */
  setReg16(ADLLMT3,0x00);              /* Set low limit reg. 3 */
  /* ADLLMT4: ??=0,LLMT=0,??=0,??=0,??=0 */
  setReg16(ADLLMT4,0x00);              /* Set low limit reg. 4 */
  /* ADZCSTAT: ??=1,??=1,??=1,??=1,??=1,??=1,??=1,??=1,ZCS7=1,ZCS6=1,ZCS5=1,ZCS4=1,ZCS3=1,ZCS2=1,ZCS1=1,ZCS0=1 */
  setReg16(ADZCSTAT,0xFFFF);           /* Clear zero crossing status flags */
  /* ADLSTAT: HLS7=1,HLS6=1,HLS5=1,HLS4=1,HLS3=1,HLS2=1,HLS1=1,HLS0=1,LLS7=1,LLS6=1,LLS5=1,LLS4=1,LLS3=1,LLS2=1,LLS1=1,LLS0=1 */
  setReg16(ADLSTAT,0xFFFF);            /* Clear high and low limit status */
  /* ADSTAT: CIP0=0,CIP1=0,??=0,EOSI1=0,EOSI0=1,ZCI=0,LLMTI=0,HLMTI=0,RDY7=0,RDY6=0,RDY5=0,RDY4=0,RDY3=0,RDY2=0,RDY1=0,RDY0=0 */
  setReg16(ADSTAT,0x0800);             /* Clear EOSI flag */
  /* ADLST2: ??=0,SAMPLE7=0,??=0,SAMPLE6=0,??=0,SAMPLE5=0,??=0,SAMPLE4=5 */
  setReg16(ADLST2,0x05);               /* Set ADC channel list reg. */
  /* ADZCC: ZCE7=0,ZCE6=0,ZCE5=0,ZCE4=0,ZCE3=0,ZCE2=0,ZCE1=0,ZCE0=0 */
  setReg16(ADZCC,0x00);                /* Set zero crossing control reg. */
  /* CTRL2: ??=0,STOP1=0,START1=0,SYNC1=0,EOSIE1=0,??=0,??=0,??=0,??=0,??=0,SIMULT=1,DIV=0x16 */
  setReg16(CTRL2,0x36);                /* Set prescaler */
  for (i=0;i<0x64;i++) {}              /* Recovery time of voltage reference */
  while (POWER&((POWER_PSTS0_BITMASK|POWER_PSTS1_BITMASK|POWER_PSTS2_BITMASK))) {} /* Wait for device powered up */
}



/* END AD1. */

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