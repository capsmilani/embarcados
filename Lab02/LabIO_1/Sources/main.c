/* ###################################################################
**     Autor       : Matheus Milani de Assun��o
**     Project     : LabIO_1
**     Processor   : MCF52259CAG80
**     Version     : Driver 01.00
**     Compiler    : CodeWarrior MCF C Compiler
**     Date/Time   : 2017-05-09, 10:51, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.00
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Term1.h"
#include "Inhr1.h"
#include "AD1.h"
#include "Bits1.h"
#include "TI1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
	byte flag;					//variavel que controla a frequencia que os valores ser�o impressos na tela do terminal
void main(void){
  /* Write your local variable definition here */
	unsigned short data;		//variavel que receber� os dados do ADC 
	float aux;					//variavel para a transforma��o do valor lido no ADC para ponto flutuante
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  while(1){										//loop infinito do programa
	  if(flag == 1){							//s� executar� em intervalos de 200 ms(melhor visualiza��o na tela do terminal)
		  
		//**********************************************************************************************************************************
		// Bloco de leitura do acelerometro
		//**********************************************************************************************************************************
		while(AD1_Measure(1) != ERR_OK){}		//Espera a leitura do ADC
	  	AD1_GetValue(&data);					//Coloca o valor lido no ADC na variavel data
	  	data = (data & 0x7FF8) >> 3;			//faz a mascara com o maximo valor possivel lido no ADC (111111111111000), sendo que 
												//o ADC possui apenas 12 bits de resolu��o.
												//Ent�o descarta-se os 3 primeiros bits fazendo a rota��o de bits.
		//**********************************************************************************************************************************										
	  	
		//**********************************************************************************************************************************
		// Bloco de acendimento dos LED's
		//**********************************************************************************************************************************
		// Como o valor maximo lido no ADC � 4096 e dividindo o valor em 5 possibilidades(apagado, 1 LED acesso, 2 LED's acessos, 3 LED's 
		// acessos, todos os LED's acessos), sendo a varia��o lida no ADC de 0 � 3.3V, um LED ir� ser acesso a cada 0.8V adicionados no
		// potenciometro.
		if((data/1000) == 0){					//at� 0.8V lidos no ADC
			Bits1_PutVal(0b00000000);			//nenhum LED acesso
	  	}
	  	if((data/1000) == 1){					//at� 1.6V lidos no ADC
			Bits1_PutVal(0b00000001);			//um LED acesso
	  	}
	  	if((data/1000) == 2){					//at� 2.4V lidos no ADC
			Bits1_PutVal(0b00000011);			//dois LED's acessos
	  	}
	  	if((data/1000) == 3){					//at� 3.2V lidos no ADC
			Bits1_PutVal(0b00000111);			//tr�s LED's acessos
	  	}
	  	if((data/1000) == 4){					//mais que 3.2V lidos no ADC
			Bits1_PutVal(0b00001111);			//todos os LED's acessos
	  	}
		//**********************************************************************************************************************************
	  	
		//**********************************************************************************************************************************
		// Bloco de transmiss�o para o terminal
		//**********************************************************************************************************************************
		aux = data*3.3/4095;					//transforma o valor lido no ADC para float e converte para a janela de tens�o que � 
												// realmente medida (de 0V � 3.3V), utilizando uma regra de tr�s simples.
												//3.3V          - 4095
												//valorDesejado - valorLidoADC
												//valorDesejado*4095 = 3.3*valorLidoADC;
												//valorDesejado = 3.3*valorLidoADC/4095;
			
	  	Term1_SendFloatNum(aux);				//valor � mandado para o terminal do computador
	  	Term1_SendStr("\r");					//� mandado tambem uma nova linha para melhor leitura
		//**********************************************************************************************************************************
	  	flag = 0;								//s� entrar� neste la�o novamente depois de 200ms
	  }
  }

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/* Matheus Milani */
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
