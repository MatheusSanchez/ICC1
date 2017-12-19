#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct verso{
	char *str;
} Verso;



typedef struct  estrofe {
	Verso *verso;
	int qtd;     // quantidade de versos na estrofe
}Estrofe;


typedef struct poema {
	Estrofe estrofes[10];
	int qtd; // quantidade de estrofes no poema
} Poema;

// Cria um poema inicialmente vazio
void initPoema (Poema *p){
	p->qtd = 0;
}

// Desaloca toda a memoria heap usada pelo poema
void apaguePoema(Poema *p){
	for (int i = 0; i < p->qtd; ++i){
		free(p->estrofes[i].verso);		
	}
}


// Le um poema, com todas suas estrofes e respectivos versos
void lePoema(Poema *p){
	// caso um poema ja exista, apague o poema !
	if (p->qtd > 0)
		apaguePoema(p); // voce tem que implementar esta funcao. Vale um ponto extra

	//char linha[10];
	int i;
	char controle;
	p->qtd = 0;
	
	do {
		// le o caracter especial
		controle = getchar();
		if (controle == '#'){
			int temp;
			//le a quantidade de versos nesta estrofe!
			scanf("%d", &temp); getchar();
			// armazena a quantidade de versos nesta estrofe
			p->estrofes[p->qtd].qtd = temp;
			// aloca o vetor de versos desta estrofe
			p->estrofes[p->qtd].verso = (Verso *)malloc(sizeof(Verso) * p->estrofes[p->qtd].qtd);
			// agora le cada verso, armazendo no vetor alocado acima
			for (i=0; i<p->estrofes[p->qtd].qtd; i++){
				size_t tmp;
				getline(&(p->estrofes[p->qtd].verso[i].str) , &tmp, stdin);
				// retira o '\n' do final de cada verso
				int len = strlen(p->estrofes[p->qtd].verso[i].str);
				p->estrofes[p->qtd].verso[i].str[len-1] = '\0';
				
			}



			p->qtd++; // incrementa a quantidade de estrofes do Poema!
		}
	} while (controle != '*');
}

void ex1(Poema *p){

	int versos = 0;

	for (int i=0; i<p->qtd; i++){

		versos += p->estrofes[i].qtd;
		for (int j = 0; j < p->estrofes[i].qtd; ++j){
			printf("%s\n",p->estrofes[i].verso[j].str);
		}
		printf("\n");
	}

	printf("Este poema tem %d estrofes e %d versos\n", p->qtd,versos);

}


void ex2(Poema *p){
	
	unsigned char soma = 0;
	
	for (int i=0; i<p->qtd; i++){	
		for (int j = 0; j < p->estrofes[i].qtd; ++j){
			for (int k = 0; p->estrofes[i].verso[j].str[k] != '\0'; ++k){
				if(p->estrofes[i].verso[j].str[k]  != '.' 
					&& p->estrofes[i].verso[j].str[k]  != '?' 
					&& p->estrofes[i].verso[j].str[k] != '!' 
					&& p->estrofes[i].verso[j].str[k]  != ';' 
					&& p->estrofes[i].verso[j].str[k] != ','){
					soma += p->estrofes[i].verso[j].str[k];
					//printf("%c -> %d -> %d\n", p->estrofes[i].verso[j].str[k],p->estrofes[i].verso[j].str[k],soma);
				}
			}	
		}

	}	
	printf("O CheckSum deste poema eh = %d\n",soma);
	
		

}

void ex3(Poema *p){

	int *hist = malloc(sizeof(int)*27);

	for (int i = 0; i < 27; ++i){
		hist[i] = 0;
	}

	for (int i=0; i<p->qtd; i++){

		for (int j = 0; j < p->estrofes[i].qtd; ++j){
			for (int k = 0; p->estrofes[i].verso[j].str[k] != '\0'; ++k){
				if(p->estrofes[i].verso[j].str[k] >= 97 && p->estrofes[i].verso[j].str[k] <= 122){
					hist[p->estrofes[i].verso[j].str[k] - 97]++;
				}else if(p->estrofes[i].verso[j].str[k] >= 65 && p->estrofes[i].verso[j].str[k] <= 90){
					hist[p->estrofes[i].verso[j].str[k] - 65]++;
				}else if(p->estrofes[i].verso[j].str[k]  == '.' 
					|| p->estrofes[i].verso[j].str[k]  == '?' 
					|| p->estrofes[i].verso[j].str[k] == '!' 
					|| p->estrofes[i].verso[j].str[k]  == ';' 
					|| p->estrofes[i].verso[j].str[k] == ','){
					hist[26]++;
				}
			}	
		}
		
	}

	for (int i = 0; i < 26; ++i){
		printf("%-4c", i+65);
	}
	printf("\n");
	for (int i = 0; i < 27; ++i){
		printf("%-4d",hist[i]);
	}

	free(hist);

}

int ex4_aux(Verso *verso,int i,int desc){
	if(verso->str[i] != '\0'){

		if(verso->str[i] != '.' && verso->str[i] != '?' && verso->str[i] != '!' && verso->str[i] != ';' && verso->str[i] != ','){			
			return ex4_aux(verso,++i,desc);
		}else{		
			return ex4_aux(verso,++i,++desc);
		}

	}else{
		return i-desc;
	}

}

void ex4(Poema *p){
	int soma = 0;

	for (int i=0; i<p->qtd; i++){
		for (int j = 0; j < p->estrofes[i].qtd; ++j){		
			soma = ex4_aux(&(p->estrofes[i].verso[j]),0,0);	 // ponteiro para verso, função recursiva, por isso não vamos ficar passando uma copia do verso toda vez;
			printf("%s -> %d\n", p->estrofes[i].verso[j].str,soma);		
		}
		if(i != p->qtd -1){
			printf("\n");	
		}
	}	
}


int main(int argc, char const *argv[]){
	/* code */
	int opcao;
	Poema p;

	initPoema(&p);

	do {
		scanf("%d", &opcao);
		getchar();  // consome '\n' do final da linha

		switch(opcao){
			case 1:
				lePoema(&p);
				ex1(&p);
				
			break;
			case 2:
				lePoema(&p);
				ex2(&p);
				
			break;
			case 3:
				lePoema(&p);
				ex3(&p);
				
			break;
			case 4:
				lePoema(&p);
				ex4(&p);
				
			break;

		}

	} while (opcao != 0);


	apaguePoema(&p);
	return 0;
}