/* ###################################################################
**     Filename    : main.c
**     Project     : Projeto
**     Processor   : MCF52259CAG80
**     Version     : Driver 01.00
**     Compiler    : CodeWarrior MCF C Compiler
**     Date/Time   : 2017-05-23, 08:33, # CodeGen: 0
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
#include "Bit1.h"
#include "SM1.h"
#include "TI1.h"
#include "Bits1.h"
#include "AD1.h"
#include "Bits2.h"
#include "Term1.h"
#include "Inhr1.h"
#include "dados.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
//-----------------------------------------------------------------------------
//								PROJETO   									//
//							SISTEMAS EMBARCADOS								//
//-----------------------------------------------------------------------------
//Autores:	Matheus Milani													//
//			Rodrigo Kraemer													//
//Data: Maio de 2017														//
//																			//
//Descrição: Codigo destinado ao microcontrolador conectado com a placa de  //
//matriz de leds.															// 
//-----------------------------------------------------------------------------

char cont_tempo = 0;							//contador de tempo para a maquina de estados
char campo[8][8];								//matriz de controle para os leds
char lab = 0;									//variavel de controle do labirinto
char x,y;										//posição do cursor
char Sy = 9;									//posição de fim de coluna
char Sx = 9;									//posição de fim de linha
char estado = 1;								//variavel que controla a maquina de estados
char flag_imprime = 0;							//variavel para temporização de impressão do labirinto na matriz de LED
char flag_ponto = 0;							//variavel para o ponto piscar
char flag_recepcao = 0;							//variavel para verificar se foi recebido algum dado
char teste;

void main(void){
  /* Write your local variable definition here */
	char rx;									//variavel que pega o valor da comunicação RS-232
	char flag_rx = 0;							//variavel auxiliar para controle
	char cont_lab = 0;							//conta quantos lab. foram completos
	char capeta;
	char f = 0, l = 0, g = 0;
	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/
	
	/* Write your code here */
	inicializaMatriz();
	teste = 0;
	while(1){
		
//-----------------------------------------------------------------------------
//						BLOCO DE RECEPÇÃO									//
//-----------------------------------------------------------------------------
//Estado 3 da maquina de estados onde trata o valor recebido via RS-232 e 
//até que a fase seja terminada.
		
		if(flag_recepcao >= 1){									//se o contador não esta zerado (se recebeu alguma coisa)
			capeta = rx;
			Term1_ReadChar(&rx);							//le a comunicação serial
			Cpu_Delay100US(20);

			if(rx == 0xAA){
				f = 1;
			}
			if(rx == 0xDD){
				g = 1;
			}
			if(rx == 0x55){
				l = 1;
			}
			if(!flag_rx && rx == 0xAA){						//se recebeu o primeiro valor do protocolo
				flag_rx = 1;								//indica que a comunicação esta ativa
			}
			else if(flag_rx >= 1){							//se a comunição esta ativa
				switch(rx){									//executa o comando
					case 0x01:								//trocar para labirinto 1
						lab = 0;							//atualiza a variavel do labirinto
						flag_rx = 2;						//indica troca de labirinto
					break;
					case 0x02:								//trocar para labirinto 2
						lab = 1;							//atualiza  a variavel do labirinto
						flag_rx = 2;						//indica troca de labirinto
					break;
					case 0x03:								//trocar para labirinto 3
						lab = 2;							//atualiza  a variavel do labirinto
						flag_rx = 2;						//indica troca de labirinto
					break;
					case 0x04:								//trocar para labirinto 4
						lab = 3;							//atualiza  a variavel do labirinto
						flag_rx = 2;						//indica troca de labirinto
					break;		
					case 0xFF: 								//andar para cima
						if(campo[x][y-1] != 1 && y > 0){ 	//testa se a proxima posição não é parede ou fora do labirinto
							campo[x][y] = 0;
							y--;							//decrementa a posição em y
						}	
					break;
					case 0xBB: 								//andar para baixo
						if(campo[x][y+1] != 1 && y < 7){	//testa se a proxima posição não é parede ou fora do labirinto
							campo[x][y] = 0;
							y++;							//incrementa a posição em y
						}
					break;
					case 0xDD: 								//andar para a direita
						if(campo[x+1][y] != 1 && x < 7){	//testa se a proxima posição não é parede ou fora do labirinto
							campo[x][y] = 0;
							x++;							//incrementa a posição em x
						}
					break;
					case 0xEE:								//andar ao oeste
						if(campo[x-1][y] != 1 && x > 0){	//testa se a proxima posição não é parede ou fora do labirinto
							campo[x][y] = 0;
							x--;							//decrementa a posição em x
						}
					break;	
					case 0x55:								//fim da comunicação
						l = 0;
						g = 0;
						f = 0;
						if(flag_rx == 2){					//se recebeu comando de troca de labirinto, confirma o labirinto
							Term1_SendChar(0xAA);			//inicio do protocolo
							Term1_SendChar((char_t)(lab+1));//numero do labirinto
							Term1_SendChar(0x55);			//fim do protocolo
							estado = 1;						//comando na maquina de estados para atualizar a matriz
						}
						if((x == Sy) && (y == Sx)){
							estado = 4;
							cont_lab++;
						}
						flag_rx = 0;						//indica fim da comunicação
					break;
				}
			}
			flag_recepcao = 0;
		}
//-----------------------------------------------------------------------------	

		
//-----------------------------------------------------------------------------
//						BLOCO DE CONTROLE									//
//-----------------------------------------------------------------------------
// Maquina de estados que controla o que esta na matriz de leds.

		if(cont_tempo == 0){					//se o contador de tempo de estado zerou
			if(estado == 1){					//se deve começar uma nova fase
				imprimeNum(lab);				//imprime o nome do novo labirinto
				estado++;						//vai para o proximo estado
				cont_tempo = 10;				//configura para o timer contar 1s
			}
			else if(estado == 2){				//se deve carregar o labirinto
				imprimeLab(lab);				//altera para o labirinto
				estado = 3;						//fica em estado de espera
			}
			else if(estado > 3 && estado < 9){	//se chegou ao fim da fase
												//pisca o labirinto
				if(estado%2){					//se é par desliga os leds
					limpa();					//função que limpa a matriz
				}
				else{							//se é impar imprime o labirirnto
					imprimeLab(lab);			//carrega novamente o labirinto
				}								
				cont_tempo = 4;					//configura para o timer contar 400ms
				estado++;						//avança para a proxima etapa
				if(estado == 9){				//se chegou a ultima etapa de piscar
					if(cont_lab < 3){			//se ainda não completou 4 fases
												//volta ao começo sem dar parabens
						estado = 10;	     		//pula para a atualização de labirindo
					}
					else{						//senão
						imprimeParabens();
						cont_lab = 0;
						estado = 10;
						
					}
				}
			}
			
			else if(estado == 10){				//estado de atualização de labirinto
				estado = 1;						//começa o processo novamente
				//envia para a outra tower o aviso de troca de fase
				lab = (lab+1)%4;				//proximo lab;
				Term1_SendChar(0xAA);			//inicio comunicação
				Term1_SendChar((char_t)(lab+1));//numero do labirinto
				Term1_SendChar(0x55);			//fim comunicação
			}
			if(Bits1_GetVal() == 0){
				estado = 4;
				cont_tempo = 5;				
			}
		}
		if(flag_imprime == 1){
			imprime();
			flag_imprime = 0;
		}
		if((flag_ponto == 0) && (estado == 3)){
			campo[x][y] = campo[x][y] ^ 0x01;
			flag_ponto = 2;
		}	
//-----------------------------------------------------------------------------
	  		

	}//fim do laço infinito
	//linha em branco
	/*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
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


