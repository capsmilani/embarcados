/* ###################################################################
**     Filename    : Events.c
**     Project     : kit2_comandos
**     Processor   : MCF52259CAG80
**     Component   : Events
**     Compiler    : CodeWarrior MCF C Compiler
**     Date/Time   : 2017-05-23, 09:25, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnCoreWatchdogINT - void Cpu_OnCoreWatchdogINT(void);
**
** ###################################################################*/
/*!
** @file Events.c
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

extern byte flag_tx; //flag para delay de envio de comandos - a cada 500ms
extern byte flag; //flag para indicar que passaram-se 100ms e uma nova leitura no AD deve ser realizada
extern byte flag_rx; //flag que indica recebimento de dados via RS232
extern byte i; //flag de incremento do vetor de recebimento
extern char dado_recebido; //variavel para salvar dado recev[bido via RS232
extern char vetor_rx[3]; //buffer de recebimento de dados
extern byte flag_buzzer; //flag para indicar que o buzzer pode ser acionado. Occorre quando um dado é enviado
extern byte buzzer;
extern byte aux;

/* User includes (#include below this line is not maintained by Processor Expert) */

/*
** ===================================================================
**     Event       :  Cpu_OnCoreWatchdogINT (module Events)
**
**     Component   :  Cpu [MCF52259_144_LQFP]
**     Description :
**         This event is called when the OnCoreWatchdog interrupt had
**         occurred. This event is automatically enabled when the <Mode>
**         is set to 'Interrupt'.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Cpu_OnCoreWatchdogINT(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AD1_OnEnd (module Events)
**
**     Component   :  AD1 [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AD1_OnEnd(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  TI1_OnInterrupt (module Events)
**
**     Component   :  TI1 [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void TI1_OnInterrupt(void)
{
  /* Write your code here ... */
	flag++; //seta flag para leitura do AD
	flag_tx++; //tempo de envio de comandos - 500ms
	

	if(buzzer != 0){
	
		PWM1_Enable(); //liga o buzzer - pwm
		flag_buzzer--; //incrementa flag para determinar tempo que estara ligado o buzzer
		if(flag_buzzer == 0){
			PWM1_Disable(); //desliga o pwm
			buzzer = 0;
		}
			
	}
}

/*
** ===================================================================
**     Event       :  Inhr1_OnRxChar (module Events)
**
**     Component   :  Inhr1 [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Inhr1_OnRxChar(void)
{
  /* Write your code here ... */
  //indica recebimento de dados via RS232
	Term1_ReadChar(&dado_recebido); // armazena o dado
	vetor_rx[i] = dado_recebido;
	i++;
	if(i>2){
		i = 0;
		flag_rx = 1;
	}
	
 
}

/*
** ===================================================================
**     Event       :  Inhr1_OnTxChar (module Events)
**
**     Component   :  Inhr1 [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Inhr1_OnTxChar(void)
{
  /* Write your code here ... */
}

/* END Events */

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
