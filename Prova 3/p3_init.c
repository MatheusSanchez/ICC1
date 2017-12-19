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

			// se vc quiser testar se a leitura está correta, 
			//basta escrever apos esta linha, a estrofe que acabou de ser criada!


			p->qtd++; // incrementa a quantidade de estrofes do Poema!
		}
	} while (controle != '*');
}

int main(int argc, char const *argv[])
{
	/* code */
	int opcao;
	Poema p;

	initPoema(&p);

	do {
		scanf("%d", &opcao);
		getchar();  // consome '\n' do final da linha

		switch(opcao){
			case 1:
				// le o poema inteiro, armazenando as 
				//estrofes e os respectivos versos...
				lePoema(&p);
				// Implemente aqui sua questao 1
			break;
			case 2:
				lePoema(&p);
				// escreva aqui sua questao 2
			break;
			case 3:
				lePoema(&p);
				// escreva aqui sua questao 3
			break;
			case 4:
				lePoema(&p);
				// escreva aqui sua questao 4
			break;

		}

	} while (opcao != 0);



	return 0;
}