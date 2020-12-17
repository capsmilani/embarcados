/* ###################################################################
**     Filename    : Events.c
**     Project     : Modbus01
**     Processor   : MCF52259CAG80
**     Component   : Events
**     Compiler    : CodeWarrior MCF C Compiler
**     Date/Time   : 2017-06-27, 19:37, # CodeGen: 0
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

/* User includes (#include below this line is not maintained by Processor Expert) */
extern char data_rx[];							//Vetor principal de recepção de dados
extern char abc;								//Variavel para controle do vetor de recepção de dados
extern char flag_recepcao;						//Flag para indicar que a transição de dados foi completa
extern unsigned char hour;						//Variavel que indica as horas 
extern unsigned char min;						//Variavel que indica os minutos
extern unsigned char sec;						//Variavel que indica os segundos 
extern unsigned char a;							//Variavel que indica os 100 milisegundos
extern unsigned char timeout;					//Variavel que indica erro de time out
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
void Cpu_OnCoreWatchdogINT(void){
  /* Write your code here ... */
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
void Inhr1_OnRxChar(void){
  /* Write your code here ... */
	char jajaja;					//variavel auxiliar para recepção de dados
	Term1_ReadChar(&jajaja);		//lê o que foi mandado
	data_rx[abc] = jajaja;			//transfere o valor lido para o vetor de recepção
	abc++;							//vai para a proxima posição do vetor de recepção
	if(data_rx[1] == 0x10){			//se o comando for 0x10 o tamanho do vetor de recepção é variavel
		jajaja = 8 + data_rx[6];	//o vetor é dependente do tamanho fixo de dados + a variavel tamanho 
		
	}else{							//se não for o comando 0x10
		jajaja = 7;					//tamanho do vetor de recepção fixo em 7
	}
	if(abc > jajaja){				//faz com que não extrapole o tamanho do vetor
		flag_recepcao = 1;			//fala que todos o valores foram recebidos na transmissão
		abc = 0;					//volta para a posição 1 do vetor de recepção
	}
	timeout = 1;					//retorna para 1 em time out
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
void TI1_OnInterrupt(void){
  /* Write your code here ... */
	a++;							//a cada 100ms é incrementada a variavel
	if(a >= 10){					//se a chegou em 1s
		sec++;						//incrementa a variavel segundo
		a = 0;						//reinicia a variavel auxiliar para contar milisegundos
	}
	if(sec >= 60){					//se chegou em 60 segundos 
		min++;						//incrementa a variavel minuto
		sec = 0;					//reinicia a variavel auxiliar para contar segundos
	}
	if(min >= 60){					//se chegou em 60 minutos
		hour++;						//incrementa a variavel hora
		min = 0;					//reinicia a variavel auxiliar para contar minutos
	}
	if(hour >= 24){					//se chegou em 24 horas
		hour = 0;					//reinicia a variavel auxiliar para contar horas
	}
	if(timeout > 0){				//se passou 100ms 
		timeout--;					//a flag de timeout fica em zero
	}else{							//se ficou em zero
		abc = 0;					//reinicia a posição do vetor de recepção
	}
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
