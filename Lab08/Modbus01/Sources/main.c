/* ###################################################################
**     Filename    : main.c
**     Project     : Modbus01
**     Processor   : MCF52259CAG80
**     Version     : Driver 01.00
**     Compiler    : CodeWarrior MCF C Compiler
**     Date/Time   : 2017-06-27, 19:37, # CodeGen: 0
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
#include "Bits1.h"
#include "Term1.h"
#include "Inhr1.h"
#include "Bits2.h"
#include "Bits3.h"
#include "AD1.h"
#include "TI1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
// Compute the MODBUS RTU CRC
static const unsigned char aucCRCHi[] = {
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0,
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1,
0x81, 0x40, 0x01,
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80,
0x41, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x01,
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00,
0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81,
0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0,
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1,
0x81, 0x40, 0x01,
0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01,
0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x01,
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81,
0x40
};
static const unsigned char aucCRCLo[] = {
0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7,
0x05, 0xC5, 0xC4,
0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB,
0x0B, 0xC9, 0x09,
0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE,
0xDF, 0x1F, 0xDD,
0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2,
0x12, 0x13, 0xD3,
0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32,
0x36, 0xF6, 0xF7,
0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E,
0xFE, 0xFA, 0x3A,
0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B,
0x2A, 0xEA, 0xEE,
0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27,
0xE7, 0xE6, 0x26,
0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1,
0x63, 0xA3, 0xA2,
0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD,
0x6D, 0xAF, 0x6F,
0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8,
0xB9, 0x79, 0xBB,
0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4,
0x74, 0x75, 0xB5,
0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0,
0x50, 0x90, 0x91,
0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94,
0x54, 0x9C, 0x5C,
0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59,
0x58, 0x98, 0x88,
0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D,
0x4D, 0x4C, 0x8C,
0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83,
0x41, 0x81, 0x80,
0x40
};

char abc = 0;																//Variavel para controle do vetor de recepção de dados
char flag_recepcao = 0;														//Flag para indicar que a transição de dados foi completa
unsigned char data_rx[16];													//Vetor principal de recepção de dados
unsigned char hour = 23, min = 59, sec = 45, a = 0;							//Variaveis que indica as horas, minutos e segundos
unsigned char timeout = 1;													//Variavel que indica erro de time out
unsigned short usMBCRC16(unsigned char * pucFrame, unsigned short usLen);	//Prototipo da função que retorna o CRC


unsigned short usMBCRC16(unsigned char * pucFrame, unsigned short usLen){
	unsigned char ucCRCHi = 0xFF;
	unsigned char ucCRCLo = 0xFF;
	int iIndex;
	while(usLen--){
		iIndex = ucCRCHi ^ *( pucFrame++ );
		ucCRCHi = ucCRCLo ^ aucCRCHi[iIndex];
		ucCRCLo = aucCRCLo[iIndex];
	}
	return (unsigned short)((ucCRCHi << 8) | ucCRCLo);
}

void main(void){
  /* Write your local variable definition here */
	unsigned short auxy, auxx, i, cont, x;									//Declaração de variaveis auxiliares
	unsigned char jooj;														//Variavel para controle de contador
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  while(1){
	  
	  if(flag_recepcao == 1){													//Se terminou a recepção de dados
		  flag_recepcao = 0;													//Zera a flag de recepção 
		  if((data_rx[0] == 0x0E) || (data_rx[0] == 0x00)){						//Se o endereço for o correto ou o broadcast
			  switch(data_rx[1]){												//Para cada caso de "comandos"
				  case 0x05:													//Se for write single coil
					  auxy = usMBCRC16(data_rx, (8-2));							//Faz o calculo de CRC para a função recebida
					  auxx = (unsigned short)((data_rx[6] << 8) + data_rx[7]);	//Concatena-se os valores recebidos de erro
					  if(auxy == auxx){											//Se o valor calculado for igual ao recebido
						  switch(data_rx[4]){									//Verifica o MSB de dados
							case 0x00:											//Se foi 0x00, desliga-se o LED
								Bits1_PutBit(data_rx[3], 0);					//Desliga o LED na posição recebida 
							break;
							case 0xFF:											//Se foi 0xFF, liga-se o LED
								Bits1_PutBit(data_rx[3], 1);					//Liga o LED na posição recebida 
							break;
						  } 
						  for(i = 0; i < 8; i++){								//Para todo o tamanho do vetor de recebimento
							  Term1_SendChar(data_rx[i]);						//Envia cada posição do vetor via UART
						  }
					  }
				  break;														//Fim do Write Single Coil
				  case 0x02:													//Se for Read Discrete Inputs		
					  auxy = usMBCRC16(data_rx, (8-2));							//Faz o calculo de CRC para a função recebida	
					  auxx = (unsigned short)((data_rx[6]<<8) + data_rx[7]);	//Concatena-se os valores recebidos de erro
					  cont = 0;													//Variavel para concatenação dos resultados lidos
					  jooj = 0;													//Variavel auxiliar para contagem 
					  if((auxx == auxy) && (data_rx[3] <= 0x0D)){				//Se o valor calculado for igual ao recebido do CRC e o valor posição não for maior que o possivel "0x0D"	
						  while((data_rx[3] <= 0x0D) && (data_rx[5] != jooj)){	//Enquanto o valor não extrapolou o valor maximo "0x0D" ou o contador não está igual ao numero de pontos
							switch(data_rx[3]){									//Para o endereço inicial	
							case 0x00:											//Se for 0
								cont = (unsigned short)(cont + (!Bits2_GetBit(0) << jooj));	//Concatena-se o valor recebido no botão 1
							break;	
							case 0x01:											//Se for 1
								cont = (unsigned short)(cont + (!Bits2_GetBit(1) << jooj));	//Concatena-se o valor recebido no botão 2
							break;
							case 0x02:											//Se for 2
								cont = (unsigned short)(cont + (!Bits3_GetBit(0) << jooj));	//Concatena-se o valor recebido no dip switch 1
							break;
							case 0x03:											//Se for 3
								cont = (unsigned short)(cont + (!Bits3_GetBit(1) << jooj));	//Concatena-se o valor recebido no dip switch 2
							break;
							case 0x04:											//Se for 4
								cont = (unsigned short)(cont + (!Bits3_GetBit(2) << jooj));	//Concatena-se o valor recebido no dip switch 3
							break;
							case 0x05:											//Se for 5
								cont = (unsigned short)(cont + (!Bits3_GetBit(3) << jooj));	//Concatena-se o valor recebido no dip switch 4
							break;
							case 0x0A:											//Se for 10
								cont = (unsigned short)(cont + (Bits1_GetBit(0) << jooj));	//Concatena-se o valor recebido no LED 1
							break;
							case 0x0B:											//Se for 11
								cont = (unsigned short)(cont + (Bits1_GetBit(1) << jooj));	//Concatena-se o valor recebido no LED 2
							break;
							case 0x0C:											//Se for 12
								cont = (unsigned short)(cont + (Bits1_GetBit(2) << jooj));	//Concatena-se o valor recebido no LED 3
							break;
							case 0x0D:											//Se for 13
								cont = (unsigned short)(cont + (Bits1_GetBit(3) << jooj));	//Concatena-se o valor recebido no LED 4
							break;
							}
							jooj++;												//Incrementa o contador 
							data_rx[3]++;										//Incrementa a posição inicial
							if(data_rx[3] == 0x06){								//Se a posição incrementada for 6 que não existe 
								data_rx[3] = 0x0A;								//Vai para a proxima posição 0x0A
							}
						  }
						 
						 Term1_SendChar(data_rx[0]);							//Envia o endereço do Slave "0x0E"
						 Term1_SendChar(data_rx[1]);							//Envia o comando "0x02"
						 if(jooj > 8){											//Se concatenou mais valores que um byte, ou seja, dois bytes
							 data_rx[2] = 2;									//Ordena no vetor o byte tamanho que será 0x02
							 data_rx[3] = (unsigned char) (cont);				//Ordena no vetor a primeira parte do short(que possui 2 bytes)
							 data_rx[4] = (unsigned char) (cont >> 8);			//Ordena no vetor a segunda parte do byte
							 auxy = usMBCRC16(data_rx, 5);						//Faz o novo calculo de CRC 
							 data_rx[5] = (unsigned char)(auxy >> 8);			//Desconcatena o valor recebido no CRC que é um short(2 bytes)
							 data_rx[6] = (unsigned char)(auxy);				//Desconcatena o valor recebido no CRC que é um short(2 bytes)
							 Term1_SendChar(data_rx[2]);						//Envia o valor do numero de bytes
							 Term1_SendChar(data_rx[3]);						//Envia a primeira parte da resposta
							 Term1_SendChar(data_rx[4]);						//Envia a segunda parte da resposta
							 Term1_SendChar(data_rx[5]);						//Envia o novo CRC calculado
							 Term1_SendChar(data_rx[6]);						//Envia o novo CRC calculado
						 }else{													//Se concatenou um byte ou menos
							 data_rx[2] = 1;									//Ordena no vetor o byte tamanho que será 0x01
							 data_rx[3] = (unsigned char) (cont);				//Ordena no vetor o byte de resposta obtida
							 auxy = usMBCRC16(data_rx, 4);						//Faz o novo calculo de CRC 
							 data_rx[4] = (unsigned char)(auxy >> 8);			//Desconcatena o valor recebido no CRC que é um short(2 bytes)
							 data_rx[5] = (unsigned char)(auxy);				//Desconcatena o valor recebido no CRC que é um short(2 bytes)
							 Term1_SendChar(data_rx[2]);						//Envia o valor do numero de bytes
							 Term1_SendChar(data_rx[3]);						//Envia a resposta
							 Term1_SendChar(data_rx[4]);						//Envia o novo CRC calculado
							 Term1_SendChar(data_rx[5]);						//Envia o novo CRC calculado
						 }
					  }
				  break;  														//Fim do Read Discrete Inputs										
				  case 0x03:													//Se for Read Holding Registers
					 auxy = usMBCRC16(data_rx, (8-2));							//Faz o calculo de CRC para a função recebida
					 auxx = (unsigned short)((data_rx[6]<<8) + data_rx[7]);		//Concatena-se os valores recebidos de erro
					 cont = data_rx[5];											//Variavel para armazenar o numero de pontos
					 jooj = 0;													//Variavel auxiliar para contagem
					 if((auxx == auxy) && (data_rx[3] <= 0x06)){				//Se o valor calculado for igual ao recebido do CRC e o valor posição não for maior que o possivel "0x06"			
						 while((jooj != cont) && (data_rx[3] <= 6)){			//Enquanto o valor não extrapolou o valor maximo "0x06" ou o contador não está igual ao numero de pontos
							switch(data_rx[3]){									//Para o endereço inicial	
					 		case 0x00:											//Se for 0
					 			data_rx[4+(2*jooj)] = 0x00;						//O MSB recebe zero
					 			data_rx[4+(2*jooj)+1] = hour;					//O Proximo valor vai o LSB de horas
					 		break;	
					 		case 0x01:											//Se for 1
					 			data_rx[4+(2*jooj)] = 0x00;						//O MSB recebe zero
					 			data_rx[4+(2*jooj)+1] = min;					//O Proximo valor vai o LSB de minutos
					 		break;
					 		case 0x02:											//Se for 2
					 			data_rx[4+(2*jooj)] = 0x00;						//O MSB recebe zero
					 			data_rx[4+(2*jooj)+1] = sec;					//O Proximo valor vai o LSB de segundos
					 		break;
					 		case 0x03:											//Se for 3
								while(AD1_MeasureChan(1, 0) != ERR_OK){}		//Espera a leitura do acelerometro do eixo x
								AD1_GetChanValue(0, &x);						//Coloca o valor lido no ADC na variavel x
								x = (x & 0x7FF8) >> 3;							//Desloca o valor recebido de 12bits
																				//Como o valor do AD é de 12 bits
					 			data_rx[4+(2*jooj)]   = (unsigned char)(x >> 8);//O primeiro valor será de 4 bits
					 			data_rx[4+(2*jooj)+1] = (unsigned char)(x);		//O segundo valor será de 8 bits							
					 		break;
					 		case 0x04:											//Se for 4
								while(AD1_MeasureChan(1, 1) != ERR_OK){}		//Espera a leitura do acelerometro do eixo y
								AD1_GetChanValue(1, &x);						//Coloca o valor lido no ADC na variavel x
								x = (x & 0x7FF8) >> 3;							//Desloca o valor recebido de 12bits
																				//Como o valor do AD é de 12 bits
					 			data_rx[4+(2*jooj)]   = (unsigned char)(x >> 8);//O primeiro valor será de 4 bits
					 			data_rx[4+(2*jooj)+1] = (unsigned char)(x);		//O segundo valor será de 8 bits
					 		break;
					 		case 0x05:											//Se for 5
								while(AD1_MeasureChan(1, 2) != ERR_OK){}		//Espera a leitura do acelerometro do eixo z
								AD1_GetChanValue(2, &x);						//Coloca o valor lido no ADC na variavel x
								x = (x & 0x7FF8) >> 3;							//Desloca o valor recebido de 12bits
																				//Como o valor do AD é de 12 bits
					 			data_rx[4+(2*jooj)]   = (unsigned char)(x >> 8);//O primeiro valor será de 4 bits
					 			data_rx[4+(2*jooj)+1] = (unsigned char)(x);		//O segundo valor será de 8 bits
					 		break;
					 		case 0x06:											//Se for 6
								while(AD1_MeasureChan(1, 3) != ERR_OK){}		//Espera a leitura do potenciometro
								AD1_GetChanValue(3, &x);						//Coloca o valor lido no ADC na variavel x
								x = (x & 0x7FF8) >> 3;							//Desloca o valor recebido de 12bits
																				//Como o valor do AD é de 12 bits
					 			data_rx[4+(2*jooj)]   = (unsigned char)(x >> 8);//O primeiro valor será de 4 bits
					 			data_rx[4+(2*jooj)+1] = (unsigned char)(x);		//O segundo valor será de 8 bits
					 		break;
					 		}
					 		jooj++;												//Incrementa o contador
					 		data_rx[3]++;										//Incrementa a posição inicial
						}
						data_rx[2] = (unsigned char)(2*jooj);					//Define o o byte de tamanho (Bytes)
						for(i = 0; i < (2*jooj); i++){							//Para todo os valores armazenados
						 	data_rx[3+i] = data_rx[4+i];						//Desloca o valor em uma posição do vetor
						}		
						auxy = usMBCRC16(data_rx, ((2*jooj)+3));				//Faz o novo calculo de CRC 	
						data_rx[(2*jooj)+3] = (unsigned char)(auxy >> 8);		//Desconcatena o valor recebido no CRC que é um short(2 bytes)	
						data_rx[(2*jooj)+4] = (unsigned char)(auxy);			//Desconcatena o valor recebido no CRC que é um short(2 bytes)				 		
					 	for(i = 0; i < ((2*jooj)+5); i++){						//Para todo o tamanho do vetor de recepção
					 		Term1_SendChar(data_rx[i]);							//Envia os valores armazenados
					 	}
					 }
				  break;														//Fim de Read Holding Registers
				  case 0x10:													//Se for Write Registers
					  auxy = usMBCRC16(data_rx, (7 + data_rx[6]));				//Faz o calculo de CRC para a função recebida
					  auxx = (unsigned short)((data_rx[7 + data_rx[6]]<<8) + data_rx[8 + data_rx[6]]);//Concatena-se os valores recebidos de erro
					  cont = data_rx[5];										//Variavel para armazenar o numero de pontos
					  jooj = 0;													//Variavel auxiliar para contagem
					  if((auxx == auxy) && (data_rx[3] <= 0x06) && (data_rx[0] != 0x00)){//Se o valor calculado for igual ao recebido do CRC e o valor posição não for maior que o possivel "0x06" e não for o broadcast
						  while((jooj != cont) && (data_rx[3] <= 3)){			//Enquanto o valor não extrapolou o valor maximo "0x06" ou o contador não está igual ao numero de pontos
							  switch(data_rx[3]){								//Para o endereço inicial
							  case 0x00:										//Se for 0
								  hour = data_rx[8+2*jooj];						//Hora recebe o valor recebido
							  break;	
							  case 0x01:										//Se for 1
								  min = data_rx[8+2*jooj];						//Minutos recebe o valor recebido
							  break;
							  case 0x02:										//Se for 2
								  sec = data_rx[8+2*jooj];						//Segundos recebe o valor recebido
							  break;
						 	  }
						 	  jooj++;											//Incrementa o contador
						 	  data_rx[3]++;										//Incrementa a posição
						  }
						  auxy = usMBCRC16(data_rx, 6);							//Faz o novo calculo de CRC 
						  data_rx[6] = (unsigned char)(auxy >> 8);				//Desconcatena o valor recebido no CRC que é um short(2 bytes)
						  data_rx[7] = (unsigned char)(auxy);					//Desconcatena o valor recebido no CRC que é um short(2 bytes)						  	  
						  for(i = 0; i < 8; i++){								//Para todas as posições do vetor
							  Term1_SendChar(data_rx[i]);						//Envia os valores armazenados
						  }
					  }
				  break;														//Fim de Write Registers
			  }
		  }
	  }
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
