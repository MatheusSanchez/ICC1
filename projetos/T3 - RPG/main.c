#include <stdio.h>
#include <stdlib.h>


#define CA_DRITZ 10  
#define CA_ARTEMIS 7 
#define ND_DRITZ 1			// aqui declaramos as constantes do jogo para fácil manutenção;
#define ND_ARTEMIS 2
#define FACE_DRITZ 9
#define FACE_ARTEMIS 7


typedef struct{

	int COD_JOGADOR;		// parâmetro usado para a função de ataque
	int vida;
	int CA;					// struct padrão que os dois personagens possuem;
	int n_dados;
	int n_faces;

}personagens;


void ataque(personagens *dritz, personagens *artemis, int oponente, int *dda){ // função de ataque dos personagens
	int porrada = 0;

	//ARTEMIS ATACANDO
	if(oponente == dritz->COD_JOGADOR){  //verifica oponente

		if(random()%*dda+1 > dritz->CA){ // autorização do ataque

			for (int i = 0; i < artemis->n_dados; ++i){
				porrada += 	random()%artemis->n_faces + 1; // rodando os dados
			}

			if(porrada == artemis->n_dados*artemis->n_faces){ // crítico
				porrada += porrada/2;
			}else if(porrada == artemis->n_dados){ //miss
				ataque(dritz,artemis,artemis->COD_JOGADOR,dda); // errou o ataque, próximo ataque
				return;
			}

			printf("Artemis %d\n", porrada); 

			dritz->vida -= porrada;    // tira vida

			//printf("vida dritz %d\n", dritz->vida);

			if(dritz->vida>0){ //dritz esta vivo 
				ataque(dritz,artemis,artemis->COD_JOGADOR,dda); // se dritz esta vivo ele ataca
			}

		}else{			// ataque não autorizado
			ataque(dritz,artemis,artemis->COD_JOGADOR,dda);
		}

	//dritz atacando
	}else{

		if(random()%*dda+1 > artemis->CA){ // autorização do ataque

			for (int i = 0; i < dritz->n_dados; ++i){ //rodando os dados -- para o trabalho não precisamos deste for pois 
				porrada += 	random()%dritz->n_faces + 1;	//o numero de dados do dritz é igual a um 
			}

			if(porrada == dritz->n_dados*dritz->n_faces){ // crítico
				porrada += porrada/2;
			}else if(porrada == dritz->n_dados){ //miss
				ataque(dritz,artemis,dritz->COD_JOGADOR,dda); // errou o ataque, próximo ataque
				return;
			}

			printf("Drizzt %d\n", porrada);
			
			artemis->vida -= porrada; // tira vida
			//printf("vida artemis %d\n", artemis->vida );

			if(artemis->vida > 0){// artemis esta vivo ?
				ataque(dritz,artemis,dritz->COD_JOGADOR,dda); // se artemis esta vivo ele ataca
			}

		}else{	// ataque não autorizado
				ataque(dritz,artemis,dritz->COD_JOGADOR,dda);
		}

	}

}

void start(personagens *dritz, personagens *artemis,int vida_dritz, int vida_artemis){	//função que seta as vidas dos jogadores;
	dritz->vida = vida_dritz;
	artemis->vida = vida_artemis;		
}

int main(){

	personagens dritz,artemis;	// inicialização dos personagens

	int lutas,vida_dritz,vida_artemis,artemis_ganhou=0,dritz_ganhou=0,i=0,dda; //contadores 

	scanf("%d",&lutas);			// numero lutas
	scanf("%d",&vida_dritz);	// vida dritz
	scanf("%d",&vida_artemis);	// vida artemis
	scanf("%d",&dda);			// dado dda
	
	//inicialização dritz;
	dritz.COD_JOGADOR = 1;		
	dritz.vida = vida_dritz;
	dritz.CA = CA_DRITZ;		// inicialização dos personagens
	dritz.n_dados = ND_DRITZ;
	dritz.n_faces = FACE_DRITZ;


	//inicialização artemis;
	artemis.COD_JOGADOR = 2;
	artemis.vida = vida_artemis;
	artemis.CA = CA_ARTEMIS;
	artemis.n_dados = ND_ARTEMIS;
	artemis.n_faces = FACE_ARTEMIS;

	//inicialização dado
	srand(dda*dda); 

	for (i = 0; i < lutas; ++i){

		printf("Luta %d\n",i+1);
		if(random()%dda+1 < random()%dda+1){ // dritz e artemis jogam o dado

			ataque(&dritz,&artemis,dritz.COD_JOGADOR,&dda);	// artemis atacando
		}else{
			ataque(&dritz,&artemis,artemis.COD_JOGADOR,&dda);	// dritz atacando
		}	
		

		if(dritz.vida>0){ // dritz esta vivo ?
			printf("Fim da luta. Vencedor: Drizzt\n");
			dritz_ganhou++;
		}else{			// se não artemis ganhou
			printf("Fim da luta. Vencedor: Artemis\n");
			artemis_ganhou++;
		}

		if((artemis_ganhou > lutas/2) || (dritz_ganhou>lutas/2)){
			break;  	// verifica vitória
		}

		start(&dritz,&artemis,vida_dritz,vida_artemis); // recupera as vidas dos personagens
	}

	if (artemis_ganhou>dritz_ganhou){ 						//compara do contadores
		printf("Fim da batalha. Vencedor: ARTEMIS\n"); 
	}else if(artemis_ganhou<dritz_ganhou){
		printf("Fim da batalha. Vencedor: DRIZZT\n");

	}else{ // tratamento caso de empate -- caso não executado no trabalho

		if(random()%dda+1 < random()%dda+1){ 
			printf("Luta %d\n", i);
			ataque(&dritz,&artemis,dritz.COD_JOGADOR,&dda);
		}else{
			printf("Luta %d\n", i);
			ataque(&dritz,&artemis,artemis.COD_JOGADOR,&dda);
		}

		if(dritz.vida>0){
			printf("Fim da luta. Vencedor: Drizzt\n");
			printf("Fim da batalha. Vencedor: DRIZZT\n");
			
		}else{
			printf("Fim da luta. Vencedor: Artemis\n");
			printf("Fim da batalha. Vencedor: ARTEMIS\n");
		}
	}

	return 0;

}