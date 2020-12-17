/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : SM1.c
**     Project     : fucking_teste
**     Processor   : MCF52259CAG80
**     Component   : SynchroMaster
**     Version     : Component 02.347, Driver 01.01, CPU db: 3.00.000
**     Compiler    : CodeWarrior MCF C Compiler
**     Date/Time   : 2017-06-06, 18:15, # CodeGen: 30
**     Abstract    :
**         This component "SynchroMaster" implements MASTER part of synchronous
**         serial master-slave communication.
**     Settings    :
**         Synchro type                : MASTER
**
**         Serial channel              : QSPI
**
**         Protocol
**             Init baud rate          : 5us
**             Clock edge              : falling
**             Width                   : 16 bits
**             Empty character         : 0
**             Empty char. on input    : RECEIVED
**
**         Registers
**             Input buffer            : QDR       [0x0354]
**             Output buffer           : QDR       [0x0354]
**             Control register        : QMR       [0x0340]
**             Mode register           : QMR       [0x0340]
**             Baud setting reg.       : QMR       [0x0340]
**
**
**
**         Used pins                   :
**         ----------------------------------------------------------
**              Function    | On package |    Name
**         ----------------------------------------------------------
**               Output     |     25     |  QSPI_DOUT_I2C_SCL1_UTXD1_PQS0
**               Clock      |     26     |  QSPI_CLK_I2C_SCL0_URTS1_PQS2
**         ----------------------------------------------------------
**
**     Contents    :
**         RecvChar        - byte SM1_RecvChar(SM1_TComData *Chr);
**         SendChar        - byte SM1_SendChar(SM1_TComData Chr);
**         GetCharsInRxBuf - word SM1_GetCharsInRxBuf(void);
**         GetCharsInTxBuf - word SM1_GetCharsInTxBuf(void);
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
** @file SM1.c
** @version 01.01
** @brief
**         This component "SynchroMaster" implements MASTER part of synchronous
**         serial master-slave communication.
*/         
/*!
**  @addtogroup SM1_module SM1 module documentation
**  @{
*/         

/* MODULE SM1. */

#include "SM1.h"

#define OVERRUN_ERR      0x01          /* Overrun error flag bit   */
#define CHAR_IN_RX       0x08          /* Char is in RX buffer     */
#define FULL_TX          0x10          /* Full transmit buffer     */
#define RUNINT_FROM_TX   0x20          /* Interrupt is in progress */
#define FULL_RX          0x40          /* Full receive buffer      */

static byte SerFlag;                   /* Flags for serial communication */
                                       /* Bits: 0 - OverRun error */
                                       /*       1 - Unused */
                                       /*       2 - Unused */
                                       /*       3 - Char in RX buffer */
                                       /*       4 - Full TX buffer */
                                       /*       5 - Running int from TX */
                                       /*       6 - Full RX buffer */
                                       /*       7 - Unused */

/*
** ===================================================================
**     Method      :  SM1_RecvChar (component SynchroMaster)
**     Description :
**         If any data is received, this method returns one character,
**         otherwise it returns an error code (it does not wait for
**         data). 
**         For information about SW overrun behavior please see
**         <General info page>.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Chr             - A pointer to the received character
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK - The valid data is received.
**                           ERR_SPEED - This device does not work in
**                           the active speed mode.
**                           ERR_RXEMPTY - No data in receiver.
**                           ERR_OVERRUN - Overrun error was detected
**                           from the last char or block received. In
**                           polling mode, this error code is returned
**                           only when the hardware supports detection
**                           of the overrun error. If interrupt service
**                           is enabled, and input buffer allocated by
**                           the component is full, the component
**                           behaviour depends on <Input buffer size>
**                           property : if property is 0, last received
**                           data-word is preserved (and previous is
**                           overwritten), if property is greater than 0,
**                           new received data-word are ignored.
**                           ERR_FAULT - Fault error was detected from
**                           the last char or block received. In the
**                           polling mode the ERR_FAULT is return until
**                           the user clear the fault flag bit, but in
**                           the interrupt mode ERR_FAULT is returned
**                           only once after the fault error occured.
**                           This error is supported only on the CPUs
**                           supports the faul mode function - where
**                           <Fault mode> property is available.
** ===================================================================
*/
byte SM1_RecvChar(SM1_TComData *Chr)
{
  if (!testReg16Bit(QIR,SPIF)) {       /* Is finished flag set? */
    return ERR_RXEMPTY;                /* If no then error is returned */
  }
  setReg16(QAR,16);                    /* Set receive RAM */
  *Chr = (SM1_TComData)getReg16(QDR);  /* Read data from receiver */
  setReg16Bit(QIR,SPIF);               /* Clear finished flag */
  if (SerFlag & OVERRUN_ERR) {         /* Is the overrun error flag set? */
    SerFlag &= ~OVERRUN_ERR;           /* Clear flags */
    return ERR_OVERRUN;                /* If yes then error is returned  */
  }
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  SM1_SendChar (component SynchroMaster)
**     Description :
**         Sends one character to the channel.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Chr             - Character to send
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - Device is disabled (only if
**                           output DMA is supported and enabled)
**                           ERR_TXFULL - Transmitter is full
** ===================================================================
*/
byte SM1_SendChar(SM1_TComData Chr)
{
  if (testReg16Bit(QDLYR,SPE)) {       /* Is last character send? */
    return ERR_TXFULL;                 /* If no then return error */
  }
  setReg16(QAR,0);                     /* Set transmit RAM */
  setReg16(QDR,Chr);                   /* Store char to transmitter */
  if (testReg16Bit(QIR,SPIF)) {        /* Is finished flag set? */
    SerFlag |= OVERRUN_ERR;            /* Set overrun flag */
    setReg16Bit(QIR,SPIF);             /* Clear finished flag */
  }
  setReg16Bit(QDLYR,SPE);              /* Launch transfer */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  SM1_GetCharsInRxBuf (component SynchroMaster)
**     Description :
**         Returns the number of characters in the input buffer.
**         Note: If the Interrupt service is disabled, and the Ignore
**         empty character is set to yes, and a character has been
**         received, then this method returns 1 although it was an
**         empty character.
**     Parameters  : None
**     Returns     :
**         ---             - Number of characters in the input buffer.
** ===================================================================
*/
/*
word SM1_GetCharsInRxBuf(void)

**      This method is implemented as a macro. See header module. **
*/

/*
** ===================================================================
**     Method      :  SM1_GetCharsInTxBuf (component SynchroMaster)
**     Description :
**         Returns the number of characters in the output buffer.
**     Parameters  : None
**     Returns     :
**         ---             - Number of characters in the output buffer.
** ===================================================================
*/
/*
word SM1_GetCharsInTxBuf(void)

**      This method is implemented as a macro. See header module. **
*/

/*
** ===================================================================
**     Method      :  SM1_Init (component SynchroMaster)
**
**     Description :
**         Initializes the associated peripheral(s) and the components 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void SM1_Init(void)
{
  /* QDLYR: SPE=0,QCD=0,DTL=0xFA */
  setReg16(QDLYR, 0xFAU);              /* Set Delay register */ 
  /* QMR: MSTR=1,DOHIE=0,BITS=0,CPOL=0,CPHA=0,BAUD=0xC8 */
  setReg16(QMR, 0x80C8U);              /* Set Mode register */ 
  /* QWR: HALT=0,WREN=0,WRTO=0,CSIV=0,ENDQP=0,CPTQP=0,NEWQP=0 */
  setReg16(QWR, 0x00U);                /* Set Wrap register */ 
  /* QIR: WCEFB=0,ABRTB=0,??=0,ABRTL=1,WCEFE=0,ABRTE=0,??=0,SPIFE=0,??=0,??=0,??=0,??=0,WCEF=1,ABRT=1,??=0,SPIF=1 */
  setReg16(QIR, 0x100DU);              /* Set Interrupt register */ 
  /* QAR: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,ADDR=0x20 */
  setReg16(QAR, 0x20U);                /* Select Command 0 register in QSPI RAM */ 
  /* QDR: DATA=0x6000 */
  setReg16(QDR, 0x6000U);              /* Set Command 0 register */ 
  SerFlag = 0;                         /* Reset all flags */
}

/* END SM1. */

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
