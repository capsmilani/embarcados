/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Bits1.h"
#include "TI1.h"
#include "Bits2.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#define t1 1
#define t2 2
enum estados{q0, q1, q2, q3, q4};
struct maquina{
	unsigned char saida;
	unsigned char tempo;
	unsigned char transicao[2];
};
const struct maquina m[5] = {{0, t1, {q1, q0}},
							 {0, t2, {q2, q0}},
							 {0, t1, {q2, q3}},
							 {0, t2, {q2, q4}},
							 {1, t1, {q1, q0}}};
unsigned char temporizador = t1;
void main(void){
  /* Write your local variable definition here */

	unsigned char chaveok = 0;
	unsigned char estado_atual = q0;
	
	
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  for(;;){ 
	  if(temporizador == 0){
		  estado_atual = m[estado_atual].transicao[Bits2_GetVal() == 1];
		  chaveok = m[estado_atual].saida;
		  temporizador = m[estado_atual].tempo;
	  }
	  if(chaveok == 1){
		  Bits1_PutVal(Bits1_GetVal()^0x01); 
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
