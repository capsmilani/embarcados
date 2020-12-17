/* ###################################################################
**     Filename    : main.c
**     Project     : kit2_comandos
**     Processor   : MCF52259CAG80
**     Version     : Driver 01.00
**     Compiler    : CodeWarrior MCF C Compiler
**     Date/Time   : 2017-05-23, 09:25, # CodeGen: 0
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
#include "AD1.h"
#include "Term1.h"
#include "Inhr1.h"
#include "PWM1.h"
#include "Bits1.h"
#include "TI1.h"
#include "Bits2.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/*------------------------------------------------------------
 * Nomes:	Rodrigo A S Kraemer
 * 			Matheus M Assunção
 * 				ATIVIDADE PRATICA SUPERVISIONADA
 * 					SISTEMAS EMBARCADOS
 *------------------------------------------------------------*/

/*---------------------DESCRIÇÃO DO CÓDIGO---------------------
 * Este código é responsável pela leitura do acelerômetro e do
 * joystick para comandar o led do labirinto.
 * Após a leitura do acelerômetro ou do joystick, o valor obtido
 * pelo conversor AD é convertido para o valor tabelado do roteiro
 * do projeto e enviado via RS-232 para o kit1.
 * A cada mudança de labirinto, término da fase, ou locomoção do led
 * o buzzer é acionado (Sons diferentes para cada ocasião).
 * ------------------------------------------------------------*/
/*------------------DESCRIÇÃO DOS COMPONENTES------------------
 * ---> Conversor AD
 * Canal 0 - 2: Acelerômetro
 * Canal 4 - 5: Joystick
 * 
 * --->Bit1
 * SW do joystick
 * 
 * --->Bits1
 * LEDS - indicam o labirinto que está sendo exibido na matriz
 * 
 * --->PWM1
 * Acionamento do Buzzer
 * ------------------------------------------------------------*/

/*------------------TABELA DE DIREÇÕES------------------
 * ESQUERDA	- 0xEE
 * DIREITA	- 0xDD
 * FRENTE	- 0xFF
 * P/ TRAS	- 0xBB
 * LABIRINTO 1	- 0x01
 * LABIRINTO 2	- 0x02
 * LABIRINTO 3	- 0x03
 * LABIRINTO 4	- 0x04
 * ------------------------------------------------------------*/

byte flag; //flag para indicar que passaram-se 100ms e uma nova leitura no AD deve ser realizada
byte flag_rx; //flag que indica recebimento de dados via RS232
byte flag_tx; //flag para delay de envio de comandos - a cada 500ms
byte flag_buzzer; //flag para indicar que o buzzer pode ser acionado. Occorre quando um dado é enviado
byte buzzer;
char dado_recebido; //variavel para salvar dado recebido via RS232
char vetor_rx[3]; //buffer de recebimento de dados
byte i; //flag de incremento do vetor de recebimento
byte aux;


/* User includes (#include below this line is not maintained by Processor Expert) */

void main(void)
{
  /* Write your local variable definition here */
	unsigned short x, y, z, Rx, Ry, Rz; //coordenadas x, y, z do acelerometro. E RX, Ry do joystick
	unsigned short comando; //comando enviado ao kit1
	byte prot_com; // variavel para controle do protocolo de comunicação
	byte j;
	byte aux_x;
	
	byte cont; //numero de labirintos a serem carregados
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  
  //--------------------------------------------------
  //INICIALIZACAO DOS VALORES INICIAIS DAS VARIAVEIS
  flag = 0;
  flag_rx = 0;
  flag_buzzer = 0;
  comando = 0x00;
  cont = 1;
  i = 0;
  j = 1;
  PWM1_Disable();
  aux_x=0;
  //--------------------------------------------------
  
  
  for(;;){
	  if(flag == 1){//se passou 100 ms, realiza leitura do AD
		  flag = 0; //reinicia flag para ler após 100 ms NOVAMENTE
		  
		  //----------------------- LEITURA DOS CANAIS AD -----------------------
		  while(AD1_MeasureChan(1,0) != ERR_OK); //Realiza a leitura do canal 1 - eixo x
		  AD1_GetChanValue16(0, &x);	//Salva o valor lido na variavel x
		  		  
		  while(AD1_MeasureChan(1,1) != ERR_OK); //Realiza a leitura do canal 2 - eixo y
		  AD1_GetChanValue16(1, &y);	//Salva o valor lido na variavel y
		  		  
		  while(AD1_MeasureChan(1,2) != ERR_OK); //Realiza a leitura do canal 3 - eixo z
		  AD1_GetChanValue16(2, &z);	//Salva o valor lido na variavel z
		  
		  while(AD1_MeasureChan(1,3) != ERR_OK); //Realiza a leitura do canal 4 - eixo Rx
		  AD1_GetChanValue16(3, &Ry);	//Salva o valor lido na variavel Rx - joystick
		  
		  while(AD1_MeasureChan(1,4) != ERR_OK); //Realiza a leitura do canal 5 - eixo Ry
		  AD1_GetChanValue16(4, &Rx);	//Salva o valor lido na variavel Ry - joystick
		  
		  
		  //----------------------- COMANDOS DO ACELERÔMETRO -----------------------
		  if(x<34000 && x>28000) //eixo y sera comandado
		  {
			  if(y>34400)
				  comando = 0xEE; //comando enviado correspondente a diraeção esquerda
			  if(y<28000) 
				  comando = 0xDD; //inclinando para direita
		  }
		  if(y<34400 && y>28000) //eixo x sera comandado
		  {
			  if(x>34400) //inclinando para tras
				  comando = 0xBB;
			  if(x<28000) //inclinando para frente
				  comando = 0xFF;
		  }
		  			  
		  //como o eixo z do acelerometro nao funciona nao sera implementado
		  //ele seria responsavel, assim como o eixo z do joystick de troca de labirinto
		  
		  //----------------------- COMANDOS DO JOYSTICK -----------------------
		  if(Ry>30000 && Ry<50000) //eixo x sera comandado
		  {
		  	  if(Rx > 55000) //vai para esquerda
		  		  comando = 0xEE;
		  	  else if(Rx < 30000)
		  		  comando = 0xDD; //DIREITA
		  }
		  if(Rx>30000 && Rx<50000) //eixo y sera comandado
		  {
		  	  if(Ry > 55000)
		  		  comando = 0xBB; //para tras
		  	  else if(Ry < 30000)
		  		  comando = 0xFF; //para frente
		  }
		  
		  Rz = Bits2_GetVal();
		  if(Rz == 0){//Realiza a leitura do eixo z do joystick
		  	  j ++; //acrescenta o labirinto a ser carregado
		  	  if(j > 4) //se esta no labirinto 4
		  	   	  j = 1; //retorna a carregar o 1	
		  	  comando = (char_t)j;
		  }
	  
	  }
	  
	  
	  
	  //--------------------- ENVIO DE COMANDO VIA RS232 ---------------------
	  if(flag_tx == 5){ //envia a cada 500ms
	  	if(comando != 0x00){ //caso a variavel comando for diferente de zero, significa que ha comando valido a ser enviado
	  		Term1_SendChar(0xAA); //indica o inicio de envio de dados de deslocamento ou troca de labirinto
	  		Term1_SendChar(comando); //envia o comando lido pelo AD
	  		Term1_SendChar(0x55); //indica o inicio de envio de dados de deslocamento ou troca de labirinto
	  		comando = 0x00;
	  	}
		flag_tx=0;
	  		
	  }
	  	  
		  
	  //--------------------- TRATAMENTO DE DADOS RECEBIDOS VIA RS232 ---------------------
	  if(flag_rx == 1){ //se recebeu algo via rs232
		  if(vetor_rx[1] == 0xAA){
			  flag_rx = vetor_rx[0];
			  vetor_rx[0] = vetor_rx[1];
			  vetor_rx[1] = vetor_rx[2];
			  vetor_rx[2] = flag_rx;
			  flag_rx = 1;
		  }
		  if(vetor_rx[2] == 0xAA){
			  flag_rx = vetor_rx[0];
			  vetor_rx[0] = vetor_rx[2];
			  vetor_rx[2] = vetor_rx[1];
			  vetor_rx[1] = flag_rx;
			  flag_rx = 1;
		  }
		  
		  if(vetor_rx[0] == 0xAA){
			  buzzer = 1;
			  switch(vetor_rx[1]){
			  
			  case 0x69: //deslocamento valido
				  PWM1_SetDutyUS(0x55); //som de deslocamento
				  flag_buzzer = 3; //300ms o buzzer fica acionado
				  break;

				  
			  case 0x01: //labirinto 1
				  PWM1_SetDutyUS(0xA1); //som de troca de labirinto
				  cont = 1;
				  flag_buzzer = 2; //200ms o buzzer fica acionado
				  break;
				  
			  case 0x02: // labirinto 2
				  PWM1_SetDutyUS(0xA1); //som de troca de labirinto
				  cont = 2;
				  flag_buzzer = 2; //200ms o buzzer fica acionado
				  break;
				  
			  case 0x03: // labirinto 3
				  PWM1_SetDutyUS(0xA1); //som de troca de labirinto
				  cont = 3;
				  flag_buzzer = 2; //200ms o buzzer fica acionado
				  break;
				  
			  case 0x04: //labirinto 4
				  PWM1_SetDutyUS(0xA1); //som de troca de labirinto
				  cont = 4;
				  flag_buzzer = 2; //200ms o buzzer fica acionado
				  break;
				  
			  case 0x11: //fim de fase
				  PWM1_SetDutyUS(0xBB); //som de fim de fase
				  flag_buzzer = 10; //1s o buzzer fica acionado
				  break;
				  
			  case 0x13: //fim de jogo - parabens
				  PWM1_SetDutyUS(0xBB);
				  PWM1_SetRatio8(0x50);
				  flag_buzzer = 55; //1s o buzzer fica acionado
				  /*for(aux=0;aux<10;aux++){
					  PWM1_Enable();
					  PWM1_SetDutyUS(0x88);
					  Cpu_Delay100US(0xFF);
					  PWM1_Disable();
				  }
				  aux_x=13;*/
				  break;
				  
			  }
			  if(vetor_rx[2] == 0x55){
				  flag_rx--; // decrementa a flag de recebimento para um novo tratamento futuro
			  }
			  
		  }
	  }
	  
	  j = cont;		//recebe o labirinto que esta sendo exibido na matriz
	  Bits1_PutVal((1<<cont)-1); //liga os leds correspondentes ao labirinto que e exibido na matriz
  
  }

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
