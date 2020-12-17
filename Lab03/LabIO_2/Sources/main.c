/* ###################################################################
**     Autor       : Matheus Milani de Assunção
**     Project     : LabIO_2
**     Processor   : MCF52259CAG80
**     Version     : Driver 01.00
**     Compiler    : CodeWarrior MCF C Compiler
**     Date/Time   : 2017-05-09, 13:09, # CodeGen: 0
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
#include "Bits1.h"
#include "TI1.h"
#include "AD1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
byte flag;						//variavel que controla a frequencia que os valores serão impressos na tela do terminal
void main(void){
  /* Write your local variable definition here */
	unsigned short x, y, z;		//variaveis para o armazenamento dos valores lidos no acelerometro
	float fx, fy, fz;			//variaveis para a transformação do valor lido no acelerometro para ponto flutuante
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  while(1){												//Loop infinito do programa
	  if(flag == 1){									//Só executará em intervalos de 200 ms(melhor visualização na tela do terminal)
	  
		//**********************************************************************************************************************************
		// Bloco de leitura do acelerometro
		//**********************************************************************************************************************************  
			while(AD1_MeasureChan(1, 0) != ERR_OK){}	//Espera a leitura do acelerometro do eixo x
			AD1_GetChanValue(0, &x);					//Coloca o valor lido no ADC na variavel x
			while(AD1_MeasureChan(1, 1) != ERR_OK){}	//Espera a leitura do acelerometro do eixo y
			AD1_GetChanValue(1, &y);					//Coloca o valor lido no ADC na variavel y
			while(AD1_MeasureChan(1, 2) != ERR_OK){}	//Espera a leitura do acelerometro do eixo z
			AD1_GetChanValue(2, &z);					//Coloca o valor lido no ADC na variavel z
			
			//Faz a mascara com o maximo valor possivel lido no ADC (111111111111000), sendo que o ADC possui apenas 12 bits de resolução.
			//Então descarta-se os 3 primeiros bits fazendo a rotação de bits.
			x = (x & 0x7FF8) >> 3;		//Para a variavel lida no ADC (x)				
			y = (y & 0x7FF8) >> 3;		//Para a variavel lida no ADC (y)
			z = (z & 0x7FF8) >> 3;		//Para a variavel lida no ADC (z)
		//**********************************************************************************************************************************
		
		//**********************************************************************************************************************************
		// Bloco de transformação para angulo(graus)
		//**********************************************************************************************************************************
			//Valores retirados de forma empirica mostraram que o valor maximo obtido do acelerometro foi de 2400
			//Valores retirados de forma empirica mostraram que o valor minimo obtido do acelerometro foi de 1650
			//Portanto a diferença do maximo e minimo é de 750.
			//Como a variação máxima do angulo da TOWER é 180º e a variação maxima obtida com as medições é 750, realiza-se a regra de três.
			//180           - 750
			//valorDesejado - valorLidoADC
			//valorDesejado*750 = 180*valorLidoADC;
			//valorDesejado = 180*valorLidoADC/750;
			//Porem houve um erro em regime de aproximadamente 480, retirando o valor mencionado é obtido o valor desejado com precisão de
			//proximadamente 3º;
			fx = 180*x/750 - 475;		//Conversão do valor lido no ADC do eixo x para graus
			fy = 180*y/750 - 485;		//Conversão do valor lido no ADC do eixo y para graus
			fz = 180*z/750 - 480;		//Conversão do valor lido no ADC do eixo z para graus
		//**********************************************************************************************************************************  

		//**********************************************************************************************************************************
		// Bloco de transmissão para o terminal
		//**********************************************************************************************************************************		  
			Term1_SendFloatNum(fx);		//Valor é mandado para o terminal do computador em graus
			Term1_SendChar(' ');		//É mandado tambem um espaço para melhor leitura
			Term1_SendFloatNum(fy);		//Valor é mandado para o terminal do computador em graus
			Term1_SendChar(' ');		//É mandado tambem um espaço para melhor leitura
			Term1_SendFloatNum(fz);		//Valor é mandado para o terminal do computador em graus
			Term1_SendStr("\r");		//É mandado tambem uma nova linha para melhor leitura
		//**********************************************************************************************************************************
		
		//**********************************************************************************************************************************
		// Bloco de acendimento dos LED's
		//**********************************************************************************************************************************		  
			if(fy <= -45){					//Se a inclinação da placa está para a esquerda(maior que 45º)
				Bits1_PutVal(0x01);			//Liga o primeiro LED
			}
			if((fy > -45) && (fy < -5)){	//Se a inclinação da placa está para a esquerda(menor que 45º)
				Bits1_PutVal(0x02);			//Liga o segundo LED
			}
			if((fy > -5) && (fy < 5)){		//Se não ha inclinação na placa 
				Bits1_PutVal(0x06);			//Liga os dois LED's do meio (segundo e terceiro)
			}
			if((fy > 5) && (fy < 45)){		//Se a inclinação da placa está para a direita(menor que 45º)
				Bits1_PutVal(0x04);			//Liga o terceiro LED
			}
			if((fy >= 45)){					//Se a inclinação da placa está para a direita(maior que 45º)
				Bits1_PutVal(0x08);			//Liga o ultimo LED
			}
		//**********************************************************************************************************************************
		
		flag = 0;						//só entrará neste laço novamente depois de 200ms
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
