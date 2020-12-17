/*
Universidade Tecnológica Federal do Paraná
Autor: Matheus Milani de Assunção
RA: 1342878
Lab01 - Semafaro(struct)
*/



/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"					//Incluindo o headear para tratamento de interrupção
#include "Bits1.h"					//Incluindo o header para botões
#include "Bits2.h"					//Incluindo o header para os LED's 
#include "TI1.h"					//Incluindo o header para interrupção
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
unsigned char temporizador = 100;	//variavel para controle de tempo entre transições (começa com 10s para satisfazer o RESET)
struct maquina{						//definindo a struct maquina que possui parametros, como:
	unsigned char saida;			//saída
	unsigned char tempo;			//tempo
	unsigned char transicao[4];		//e transição entre estados(sendo duas entradas bínarias
};									//as possibilidades de entrada são: 00, 01, 10, 11, ou seja
									//4 entradas possiveis).


enum{									//definição dos nomes dos estados
	q0, q1, q2, q3, q4, q5, q6, q7, q8	//sendo que q0 = 0, q1 = 1,...
};

void main(void){
  /* Write your local variable definition here */
	const struct maquina m[9] = {		//instaciação da struct maquina tendo tamanho igual ao número de estados
		{2, 100, {q6, q1, q6, q1}},		//q0
		{3, 20,  {q2, q2, q2, q2}},		//q1
		{0, 85,  {q3, q3, q3, q3}},		//q2
		{1, 5,   {q4, q4, q4, q4}},		//q3
		{0, 5,   {q5, q5, q5, q5}},		//q4
		{1, 5,   {q0, q0, q0, q0}},		//q5
		{2, 10,  {q7, q7, q6, q7}},		//q6
		{2, 2,   {q8, q6, q8, q8}},		//q7
		{2, 10,  {q8, q1, q1, q1}}		//q8
	};
	unsigned char estado_atual = q2;	//estado+1 em que o RESET começa (q3)
	unsigned char saida = 0;			//começa com o semafaro no vermelho
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  while(1){															//loop infinito
	  if(temporizador == 0){										// verifica se o tempo do estado passou
		  estado_atual = m[estado_atual].transicao[Bits1_GetVal()];	//Faz a mudança de estado conforme a entrada
		  saida = m[estado_atual].saida;							//faz com que a saída tenha um valor correspondente da maquina de estados
		  temporizador = m[estado_atual].tempo;						//inicia o cronometro com o valor do estado
	  }
	  if(saida == 0){												//se a variavel saída for 0
		  Bits2_PutVal(0b00001000);									//sinal vermelho acesso
	  }
	  if(saida == 1){												//se a variavel saída for 1
		  Bits2_PutVal(0b00001001);									//sinal vermelho e pedestre acesso
	  }
	  if(saida == 2){												//se a variavel saída for 2
		  Bits2_PutVal(0b00000011);									//sinal verde e pedestre acesso
	  }
	  if(saida == 3){												//se a variavel saída for 3
		  Bits2_PutVal(0b00000101);									//sinal amarelo e pedestre acesso
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
