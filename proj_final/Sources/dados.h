/*
 * dados.h
 *
 *  Created on: May 23, 2017
 *      Author: Caps
 */

//-----------------------------------------------------------------------------
//								ASSINATURAS									//
//-----------------------------------------------------------------------------
void imprime();
void imprimeLab(char lab);
void imprimeParabens();
void imprimeNum(char lab);
void inicializaMatriz();
void limpa();
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//							VARIAVEIS IMPORTADAS							//
//-----------------------------------------------------------------------------
extern char campo[8][8];//matriz de controle para os leds
extern char x, y;
extern char Sx, Sy;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//					FUNÇÃO DE IMPRESSÃO NA MATRIZ DE LED             		//
//-----------------------------------------------------------------------------
void imprime(){
	char m, l;
	unsigned short valor;
	char campo_mandar[8];
	for(m = 1; m < 9; m++){
		campo_mandar[m - 1] = 0;
		for(l = 0; l < 8; l++){	
			campo_mandar[m - 1] = (campo[m - 1][l] << l) + campo_mandar[m - 1];
		}
		Bit1_PutVal(0);
		Cpu_Delay100US(100);
		valor = (unsigned short)((m << 8)|(campo_mandar[m - 1]));
		SM1_SendChar(valor); //
		Cpu_Delay100US(100);
		Bit1_PutVal(1);
	}	
	
}	
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//					FUNÇÃO DE IMPRESSÃO NA MATRIZ DE LED             		//
//-----------------------------------------------------------------------------
void limpa(){
	char l, m;
  for(m = 0; m < 8; m++){
	  for(l = 0; l < 8; l++){
		  campo[m][l] = 0;
	  }
  }
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//					INICIALIZAÇÃO IMPRESSÃO NA MATRIZ DE LED           		//
//-----------------------------------------------------------------------------
void inicializaMatriz(){
	char m;
	
	Bit1_PutVal(0);
	Cpu_Delay100US(10);
	SM1_SendChar(0x0F01);
	Cpu_Delay100US(100);
	Bit1_PutVal(1);
	Cpu_Delay100US(4000);
	  
	Bit1_PutVal(0);
	Cpu_Delay100US(10);
	SM1_SendChar(0x0F00);
	Cpu_Delay100US(100);
	Bit1_PutVal(1);

	Bit1_PutVal(0);
	Cpu_Delay100US(10);
	SM1_SendChar(0x0A00);
	Cpu_Delay100US(100);
	Bit1_PutVal(1);
	  
	Bit1_PutVal(0);
	Cpu_Delay100US(10);
	SM1_SendChar(0x0B0F);
	Cpu_Delay100US(100);
	Bit1_PutVal(1);
	  
	Bit1_PutVal(0);
	Cpu_Delay100US(10);
	SM1_SendChar(0x0C01);
	Cpu_Delay100US(10);
	Bit1_PutVal(1);

	Bit1_PutVal(0);
	Cpu_Delay100US(10);
	SM1_SendChar(0x0900);
	Cpu_Delay100US(100);
	Bit1_PutVal(1);
  
	//Zerar a matriz de LED
	for(m = 1; m <= 8; m++){
		unsigned short aux = 0x100;
		aux = (unsigned short)m*aux;
  		  
  		Bit1_PutVal(0);
  		Cpu_Delay100US(10);
  		SM1_SendChar(aux);
  		Cpu_Delay100US(100);
  		Bit1_PutVal(1);
	}
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//						ARMAZENAMENTO DOS LABIRINTOS	  	        		//
//-----------------------------------------------------------------------------
void imprimeLab(char lab){
	char a;
	limpa();
	if(lab == 0){
		for(a = 1; a <= 5; a++){
			campo[0][a] = 1;
		}
		for(a = 2; a <= 6; a++){
			campo[2][a] = 1;
		}
		for(a = 1; a <= 5; a++){
			campo[4][a] = 1;
		}
		campo[5][5] = 1;
		campo[6][2] = 1;
		campo[6][3] = 1;
		for(a = 2; a <= 6; a++){
			campo[7][a] = 1;
		}
		for(a = 0; a <= 7; a++){
			campo[a][0] = 1;
		}
		for(a = 0; a <= 7; a++){
			campo[a][7] = 1;
		}
		Sx = 7;
		Sy = 1;
		
		x = 0;
		y = 6;
	}
	if(lab == 1){
		for(a = 0; a <= 7; a++){
			campo[a][0] = 1;
		}
		for(a = 0; a <= 7; a++){
			campo[a][7] = 1;
		}
		for(a = 1; a <= 6; a++){
			campo[7][a] = 1;
		}
		for(a = 1; a <= 3; a++){
			campo[0][a] = 1;
		}
		for(a = 0; a <= 2; a++){
			campo[a][5] = 1;
		}
		for(a = 2; a <= 5; a++){
			campo[a][3] = 1;
		}
		campo[2][2] = 1;
		campo[2][4] = 1;
		campo[4][1] = 1;
		campo[5][1] = 1;
		campo[4][5] = 1;
		campo[5][5] = 1;
		campo[4][6] = 1;
		
		Sx = 0;
		Sy = 4;
		
		x = 0;
		y = 6;
	}
	if(lab == 2){
		for(a = 0; a <= 7; a++){
			campo[a][0] = 1;
		}
		for(a = 0; a <= 7; a++){
			campo[a][7] = 1;
		}
		for(a = 2; a <= 7; a++){
			campo[a][5] = 1;
		}
		for(a = 2; a <= 5; a++){
			campo[a][2] = 1;
		}
		for(a = 1; a <= 6; a++){
			campo[0][a] = 1;
		}
		for(a = 1; a <= 4; a++){
			campo[7][a] = 1;
		}
		campo[2][3] = 1;
		campo[2][4] = 1;
		campo[5][3] = 1;
		campo[4][3] = 1;
		Sx = 3;
		Sy = 3;
		
		x = 7;
		y = 6;
	}
	if(lab == 3){
		for(a = 0; a <= 3; a++){
			campo[a][0] = 1;
		}
		for(a = 5; a <= 7; a++){
			campo[a][0] = 1;
		}
		for(a = 0; a <= 2; a++){
			campo[a][7] = 1;
		}
		for(a = 4; a <= 7; a++){
			campo[a][7] = 1;
		}
		for(a = 2; a <= 5; a++){
			campo[a][5] = 1;
		}
		for(a = 1; a <= 6; a++){
			campo[0][a] = 1;
		}
		for(a = 1; a <= 6; a++){
			campo[7][a] = 1;
		}
		campo[3][1] = 1;
		campo[5][1] = 1;
		campo[2][2] = 1;
		campo[4][3] = 1;
		campo[5][3] = 1;
		campo[2][4] = 1;
		Sx = 4;
		Sy = 0;
		
		x = 3;
		y = 7;
	}
}	
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//					ARMAZENAMENTO DOS VALORES DE "LEVEL"	          		//
//-----------------------------------------------------------------------------
  
	//-------------------------- Imprimir "L"
void imprimeNum(char lab){
	char a;
	limpa();
	for(a = 0; a < 8; a++){	
		campo[0][a] = 1;
		campo[a%4][7] = 1;
	}
	campo[0][0] = 0;
	//--------------------------
	
	//-------------------------- Imprimir "1"	
	if(lab == 0){
		for(a = 1; a < 8; a++){	
			campo[7][a] = 1;
		}
		campo[5][3] = 1;
		campo[6][2] = 1;	
	}
	//--------------------------
	
	//-------------------------- Imprimir "2"
	if(lab == 1){
		campo[5][1] = 1;	
		campo[6][1] = 1;
		campo[7][1] = 1;
		campo[7][1] = 1;
		campo[7][2] = 1;
		campo[7][3] = 1;
		campo[7][4] = 1;
		campo[6][4] = 1;
		campo[5][4] = 1;
		campo[5][5] = 1;
		campo[5][6] = 1;
		campo[5][7] = 1;
		campo[6][7] = 1;
		campo[7][7] = 1;
	}
	//-------------------------- 
	
	//-------------------------- Imprimir "3"
	if(lab == 2){
		campo[5][1] = 1;	
		campo[6][1] = 1;
		campo[7][1] = 1;
		campo[7][2] = 1;
		campo[7][3] = 1;
		campo[7][4] = 1;
		campo[6][4] = 1;
		campo[5][4] = 1;
		campo[7][5] = 1;
		campo[7][6] = 1;
		campo[5][7] = 1;
		campo[6][7] = 1;
		campo[7][7] = 1;
	}
	//-------------------------- 
	
	//-------------------------- Imprimir "4"
	if(lab == 3){
		for(a = 1; a < 8; a++){	
			campo[7][a] = 1;
		}
		campo[0][0] = 0;
		campo[6][3] = 1;
		campo[5][3] = 1;
		campo[5][2] = 1;
		campo[5][1] = 1;
	}
	//-------------------------- 
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//					ARMAZENAMENTO DOS VALORES DE "PARABENS"	          		//
//-----------------------------------------------------------------------------
void imprimeParabens(){
	char i, j, k;
	char campo_aux[53][8];
	//--------------------------"Zerar a matriz auxiliar"
	for(i = 0; i < 53; i++){
	  	for(j = 0; j < 8; j++){
			campo_aux[i][j] = 0;
		}
	}
	//--------------------------
	
	//---------------------------"P"
	for(i = 0; i < 8; i++){	
		campo_aux[8][i] = 1;
	}
	campo_aux[9][0] = 1;
	campo_aux[9][3] = 1;
	campo_aux[10][0] = 1;
	campo_aux[10][3] = 1;
	campo_aux[11][0] = 1;
	campo_aux[11][1] = 1;
	campo_aux[11][2] = 1;
	campo_aux[11][3] = 1;
	//---------------------------
	
	//---------------------------"A"
	for(i = 0; i < 8; i++){	
		  campo_aux[13][i] = 1;
	}
	campo_aux[14][0] = 1;
	campo_aux[14][3] = 1;
	campo_aux[15][0] = 1;
	campo_aux[15][3] = 1;
	for(i = 0; i < 8; i++){	
		  campo_aux[16][i] = 1;
	} 
	//---------------------------
	
	//---------------------------"R"
	for(i = 0; i < 8; i++){	
	  	  campo_aux[18][i] = 1;
	}
	campo_aux[19][0] = 1;
	campo_aux[19][4] = 1;
	campo_aux[19][5] = 1;
	campo_aux[20][0] = 1;
	campo_aux[20][4] = 1;
	campo_aux[20][6] = 1; 
	for(i = 0; i < 4; i++){	
	 	  campo_aux[21][i] = 1;
	}	  
	campo_aux[21][0] = 1;
	campo_aux[21][4] = 1;
	campo_aux[21][7] = 1;
	//---------------------------

	//---------------------------"A"
	for(i = 0; i < 8; i++){	
		  campo_aux[23][i] = 1;
	}
	campo_aux[24][0] = 1;
	campo_aux[24][3] = 1;
	campo_aux[25][0] = 1;
	campo_aux[25][3] = 1;
	for(i = 0; i < 8; i++){	
		  campo_aux[26][i] = 1;
	} 
	//---------------------------
	
	//---------------------------"b"
	for(i = 0; i < 8; i++){	
		  campo_aux[28][i] = 1;
	}
	campo_aux[29][4] = 1;
	campo_aux[29][7] = 1;
	campo_aux[30][4] = 1;
	campo_aux[30][7] = 1;
	for(i = 4; i < 8; i++){	
		  campo_aux[31][i] = 1;
	} 
	//---------------------------

	//---------------------------"E"
	for(i = 0; i < 8; i++){	
	  	  campo_aux[33][i] = 1;
	}
	campo_aux[34][0] = 1;
	campo_aux[34][4] = 1;
	campo_aux[34][7] = 1;
	campo_aux[35][0] = 1;
	campo_aux[35][4] = 1;
	campo_aux[35][7] = 1;
	campo_aux[36][0] = 1;
	campo_aux[36][4] = 1;
	campo_aux[36][7] = 1;
	//---------------------------

	//---------------------------"N"
	for(i = 4; i < 8; i++){	
	 	  campo_aux[38][i] = 1;
	}
	campo_aux[39][5] = 1;
	campo_aux[40][6] = 1;
	for(i = 4; i < 8; i++){	
		campo_aux[41][i] = 1;
	}  
	//---------------------------  
	
	//---------------------------"S"
	for(i = 0; i < 4; i++){	
		campo_aux[43][i] = 1;
	}
	campo_aux[43][7] = 1;
	campo_aux[44][0] = 1;
	campo_aux[44][3] = 1;
	campo_aux[44][7] = 1;
	campo_aux[45][0] = 1;
	campo_aux[45][3] = 1;
	campo_aux[45][7] = 1;
	for(i = 3; i < 8; i++){	
		campo_aux[46][i] = 1;
	}  
	campo_aux[46][0] = 1;
	//---------------------------
	
	//--------------------------- Faz com que a matriz principal "corra" na matriz de impressão
	limpa();
	for(k = 0; k < 46; k++){
		for(i = 0; i < 8; i++){
			for(j = 0; j < 8; j++){
				campo[i][j] = campo_aux[k+i][j];
			}
		}
	    for(i = 0; i < 400/4; i++){}
		imprime();
	}
	//---------------------------
}	
//-----------------------------------------------------------------------------
