#include <stdio.h>			

#define LINHA 7		
#define COLUNA 7
#define true 1
#define false 0	
typedef int bool;			

void lendo_matriz(int vet[][COLUNA]){
	for (int i = 0; i < LINHA; ++i){
		for (int k = 0; k < COLUNA; ++k){		// função que lê a matriz
			//vet[i][k] = i*C+k;
			scanf("%d",&vet[i][k]);
		}
	}
}

/*void mostra_matriz(int lab[][COLUNA]){

	for (int i = 0; i < LINHA; ++i){
		for (int k = 0; k < COLUNA; ++k){
			printf("%3d",lab[i][k]);				// função para exibir a matriz para debug;
		}
		printf("\n");
	}
	printf("\n");

}*/

void imprime_resp(int lab[][COLUNA], int lin,int col){

		printf("%d ", lin*COLUNA+col);	 // imprime o número da casa
		lab[lin][col] = 1;

		if(lin-1 >= 0 && lab[lin-1][col] == 2) imprime_resp(lab,lin-1,col);

		if(col+1 < COLUNA && lab[lin][col+1] == 2) imprime_resp(lab,lin,col+1);
																					// procurando o número 2 na matriz
		if(lin+1 < LINHA && lab[lin+1][col] == 2) imprime_resp(lab,lin+1,col);		// que representa o caminho percorrido até a saída

		if(col-1 >= 0 && lab[lin][col-1] == 2) imprime_resp(lab,lin,col-1);

}

bool corre(int lab[][COLUNA], int lin,int col){ // preenche com 2 o caminho até a saída;
	bool ja_fui = true;
	lab[lin][col] = 2;
	
	if(lin-1 >= 0 && lab[lin-1][col] !=1 && ja_fui){	// posso ir para cima ?
		if(lab[lin-1][col] == 2){			// já percorri este caminho?
			ja_fui = true;
		}else{
			ja_fui = corre(lab,lin-1,col); // se não percorri, bora lá
		}
	}

	if(col+1 < COLUNA && lab[lin][col+1] != 1 && ja_fui){	// posso ir para direita ?
		if(lab[lin][col+1] == 2){
			ja_fui = true;
		}else{
			ja_fui = corre(lab,lin,col+1);
		}
	}

	if(lin+1 < LINHA && lab[lin+1][col] != 1 && ja_fui){	// posso ir para baixo ?
		if(lab[lin+1][col] == 2){
			ja_fui = true;
		}else{
			ja_fui = corre(lab,lin+1,col);
		}
	}
	
	if(col-1 >= 0 && lab[lin][col-1] != 1 && ja_fui){	// posso ir para esquerda ?
		if(lab[lin][col-1] == 2){
			ja_fui = true;
		}else{	
			ja_fui = corre(lab,lin,col-1);
		}
	}


	if(!(lin == 0 || col == 0 || lin == LINHA-1 || col == COLUNA-1) && ja_fui){ // encontrei a saída? estou em um beco sem saída ?

		lab[lin][col] = 1;
		return true;	

	}else{
		return false;	// caso achei a saída retorne falso e pare a execução das chamadas encadeadas 	
	}
}


int main(){

	int lab[LINHA][COLUNA];				// labirinto
	int pos_inicial;

	lendo_matriz(lab);
	scanf("%d",&pos_inicial);			// input da entrada no labirinto
	

	if(!corre(lab,pos_inicial/COLUNA,pos_inicial%COLUNA)){			// pos_inicial/COLUNA -> linha
		imprime_resp(lab,pos_inicial/COLUNA,pos_inicial%COLUNA);	// pos_inicial%COLUNA -> coluna
	}	

	printf("\n");
	
}