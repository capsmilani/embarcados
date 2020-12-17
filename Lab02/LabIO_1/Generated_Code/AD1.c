/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : AD1.c
**     Project     : LabIO_1
**     Processor   : MCF52259CAG80
**     Component   : ADC
**     Version     : Component 01.699, Driver 01.05, CPU db: 3.00.000
**     Compiler    : CodeWarrior MCF C Compiler
**     Date/Time   : 2017-05-12, 02:51, # CodeGen: 7
**     Abstract    :
**         This device "ADC" implements an A/D converter,
**         its control methods and interrupt/event handling procedure.
**     Settings    :
**          Component name                                 : AD1
**          A/D converter                                  : ADC
**          Sharing                                        : Disabled
**          Interrupt service/event                        : Disabled
**          A/D channels                                   : 1
**            Channel0                                     : 
**              A/D channel (pin)                          : AN3_PAN3
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
**              Sample1                                    : Disabled
**              Sample2                                    : Disabled
**              Sample3                                    : Disabled
**              Sample4                                    : Disabled
**              Sample5                                    : Disabled
**              Sample6                                    : Disabled
**              Sample7                                    : Disabled
**          A/D resolution                                 : Autoselect
**          Conversion time                                : 10 �s
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
**         Measure    - byte AD1_Measure(bool WaitForResult);
**         GetValue   - byte AD1_GetValue(void* Values);
**         GetValue16 - byte AD1_GetValue16(word *Values);
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

#include "AD1.h"

#define IDLE            0              /* IDLE state           */
#define MEASURE         1              /* MESURE state         */
#define CONTINUOUS      2              /* CONTINUOUS state     */
#define SINGLE          3              /* SINGLE state         */

static bool OutFlg;                    /* Measurement finish flag */
/*lint -esym(765,AD1_ModeFlg) Disable MISRA rule (23) checking for symbols (AD1_ModeFlg). */
volatile byte AD1_ModeFlg;             /* Current state of device */

/*
** ===================================================================
**     Method      :  MainMeasure (component ADC)
**
**     Description :
**         The method performs A/D conversion(s). The method is called 
**         automatically as a part of measure methods or the HWEnDi 
**         method.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void MainMeasure(void)
{
  if (testReg16Bit(ADSTAT,EOSI0)) {    /* Is a scan cycle completed? */
    setReg16Bits(ADSTAT,0x0800);       /* Clear EOSI flag */
    OutFlg = TRUE;                     /* Measured values are available */
    AD1_ModeFlg = IDLE;                /* Set the component to the idle mode */
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
    OutFlg = FALSE;                    /* Measured values are available */
    setReg16Bits(ADSTAT,0x0800);       /* Clear flag */
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
  AD1_ModeFlg = MEASURE;               /* Set state of device to the measure mode */
  HWEnDi();                            /* Enable the device */
  if (WaitForResult)                   /* Is WaitForResult TRUE? */
    while (AD1_ModeFlg == MEASURE)     /* Calling MainMeasure while IDLE state occured */
      MainMeasure();                   /* A/D converter handler */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  AD1_GetValue (component ADC)
*/
/*!
**     @brief
**         Returns the last measured values for all channels. Format
**         and width of the value is a native format of the A/D
**         converter.
**     @param
**         Values          - Pointer to the array that contains
**                           the measured data. Data type is a byte, a
**                           word or an int. It depends on the supported
**                           modes, resolution, etc. of the AD converter.
**                           See the Version specific information for
**                           the current CPU in [General Info].
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
byte AD1_GetValue(void* Values)
{
  register word *pValue=(word*)Values; /* Temporary pointer to the user buffer */

  if (AD1_ModeFlg != IDLE) {           /* Is the device in any measure mode? */
    MainMeasure();                     /* Call A/D converter handler */
  }
  if (!OutFlg) {                       /* Is measured value(s) available? */
    return ERR_NOTAVAIL;               /* If no then error */
  }
  *pValue = getReg16(ADRSLT0);         /* Store value from result register of device to user buffer */
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
  if (AD1_ModeFlg != IDLE) {           /* Is the device in any measure mode? */
    MainMeasure();                     /* Call A/D converter handler */
  }
  if (!OutFlg) {                       /* Is measured value(s) available? */
    return ERR_NOTAVAIL;               /* If no then error */
  }
  *Values = (word)((getReg16(ADRSLT0) + 0x00) << 1); /* Store value from result register of device to user buffer */
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

  OutFlg = FALSE;                      /* No measured value */
  AD1_ModeFlg = IDLE;                  /* Device isn't running */
  /* CTRL1: ??=0,STOP0=1,START0=0,SYNC0=0,EOSIE0=0,ZCIE=0,LLMTIE=0,HLMTIE=0,CHNCFG=0,??=0,SMODE=0 */
  setReg16(CTRL1,0x4000);              /* Set control register 1 */
  /* CAL: SEL_VREFH=0,SEL_VREFL=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
  setReg16(CAL,0x00);                  /* Set calibration register */
  /* POWER: ASB=0,??=0,??=0,PSTS2=0,PSTS1=0,PSTS0=0,PUDELAY=0x0D,APD=0,PD2=0,PD1=1,PD0=0 */
  setReg16(POWER,0xD2);                /* Enable device */
  /* ADOFS0: ??=0,OFFSET=0,??=0,??=0,??=0 */
  setReg16(ADOFS0,0x00);               /* Set offset reg. 0 */
  /* ADHLMT0: ??=0,HLMT=0x0FFF,??=0,??=0,??=0 */
  setReg16(ADHLMT0,0x7FF8);            /* Set high limit reg. 0 */
  /* ADLLMT0: ??=0,LLMT=0,??=0,??=0,??=0 */
  setReg16(ADLLMT0,0x00);              /* Set low limit reg. 0 */
  /* ADZCSTAT: ??=1,??=1,??=1,??=1,??=1,??=1,??=1,??=1,ZCS7=1,ZCS6=1,ZCS5=1,ZCS4=1,ZCS3=1,ZCS2=1,ZCS1=1,ZCS0=1 */
  setReg16(ADZCSTAT,0xFFFF);           /* Clear zero crossing status flags */
  /* ADLSTAT: HLS7=1,HLS6=1,HLS5=1,HLS4=1,HLS3=1,HLS2=1,HLS1=1,HLS0=1,LLS7=1,LLS6=1,LLS5=1,LLS4=1,LLS3=1,LLS2=1,LLS1=1,LLS0=1 */
  setReg16(ADLSTAT,0xFFFF);            /* Clear high and low limit status */
  /* ADSTAT: CIP0=0,CIP1=0,??=0,EOSI1=0,EOSI0=1,ZCI=0,LLMTI=0,HLMTI=0,RDY7=0,RDY6=0,RDY5=0,RDY4=0,RDY3=0,RDY2=0,RDY1=0,RDY0=0 */
  setReg16(ADSTAT,0x0800);             /* Clear EOSI flag */
  /* ADSDIS: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,DS7=1,DS6=1,DS5=1,DS4=1,DS3=1,DS2=1,DS1=1,DS0=0 */
  setReg16(ADSDIS,0xFE);               /* Enable/disable of samples */
  /* ADLST1: ??=0,SAMPLE3=0,??=0,SAMPLE2=0,??=0,SAMPLE1=0,??=0,SAMPLE0=3 */
  setReg16(ADLST1,0x03);               /* Set ADC channel list reg. */
  /* ADZCC: ZCE7=0,ZCE6=0,ZCE5=0,ZCE4=0,ZCE3=0,ZCE2=0,ZCE1=0,ZCE0=0 */
  setReg16(ADZCC,0x00);                /* Set zero crossing control reg. */
  /* CTRL2: ??=0,STOP1=0,START1=0,SYNC1=0,EOSIE1=0,??=0,??=0,??=0,??=0,??=0,SIMULT=1,DIV=0x16 */
  setReg16(CTRL2,0x36);                /* Set prescaler */
  for (i=0;i<0x64;i++) {}              /* Recovery time of voltage reference */
  while (POWER&((POWER_PSTS0_BITMASK|POWER_PSTS2_BITMASK))) {} /* Wait for device powered up */
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