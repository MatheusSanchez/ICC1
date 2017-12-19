#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct _imagem{
	char tipo;								// tipo da imagem
	int xdm; 								// dimensões no eixo x
	int ydm;								// dimensões no eixo y	
	unsigned char **mat;					// matriz da imagem
	int max_val;							// valor máximo do cabeçalho
	int min_val;							// valor mínimo do cabeçalho		
}imagem;

void allocaImagem(imagem* img_aux, FILE* fpr){

	fgetc(fpr);								// Char P do cabeçalho
	img_aux->tipo = fgetc(fpr);				// Tipo da Imagem 2 ou 5
	fgetc(fpr);								// quebra de linha da primeira linha

	char header[100];						// Variável temporária
	fgets(header, 100, fpr);				//Comentario qualquer presente no cabeçalho


	fscanf(fpr, "%d%d%d\n", &img_aux->xdm,&img_aux->ydm,&img_aux->max_val);	//leitura das dimensões e do valor máximo do pixel

	img_aux->mat = malloc(sizeof(unsigned char *)*img_aux->ydm);	

	for (int i = 0; i < img_aux->ydm; ++i){									// alocando matriz para receber a imagem
		img_aux->mat[i] = malloc(sizeof(unsigned char) * img_aux->xdm);
	}

	if(img_aux->tipo == '2'){

		for (int i = 0; i < img_aux->ydm; i++){
			for (int k = 0; k < img_aux->xdm; ++k){	
				fscanf(fpr, "%hhu", &img_aux->mat[i][k]);				// leitura da imagem				
			}
		}

	}else{		

		for (int i = 0; i < img_aux->ydm; i++){
			for (int k = 0; k < img_aux->xdm; ++k){		
				fread(&img_aux->mat[i][k],sizeof(char), 1,fpr);			// leitura da imagem	
			}
		}
			
	}
	return;
}

int calcula_max(imagem *img_aux){						// retorna o pixel de maior valor presente na imagem; 

	int aux = 0;	// menor pixel possível					

	for (int i = 0; i < img_aux->ydm; i++){
		for (int k = 0; k < img_aux->xdm; ++k){

			if(aux != 255){								// caso o maior pixel ja encontrado for igual a 255
				if(img_aux->mat[i][k] > aux){			// não precisamos mais percorrer a imagem
					aux = img_aux->mat[i][k];
				}

			}else{
				return aux;
			}
		}
	}
	return aux;
}
	
int calcula_min(imagem *img_aux){					// retorna o pixel de menor valor presente na imagem; 

	int aux = 255;		// maior pixel possível

	for (int i = 0; i < img_aux->ydm; i++){

		for (int k = 0; k < img_aux->xdm; ++k){

			if(aux != 0){							// caso o maior pixel ja encontrado for igual a 0
				if(img_aux->mat[i][k] < aux){		// não precisamos mais percorrer a imagem	
					aux = img_aux->mat[i][k];
				}

			}else{
				img_aux->min_val = aux;				// o pixel de menor valor é guardado para mais eficiência
				return aux;							// na função "con_stret"	 	
			}
		}
	}

	img_aux->min_val = aux;
	return aux;
}




void op_log(imagem* img_aux){				//operação de log

	float aux = (255/(log(1+(calcula_max(img_aux)))));		// variável temporária para mais eficiência	da função

	for (int i = 0; i < img_aux->ydm; i++){
		for (int k = 0; k < img_aux->xdm; ++k){
			img_aux->mat[i][k] = aux * (log(1+(img_aux->mat[i][k])));
			
		}
	}
}

void con_stret(imagem* img_aux){			// operação de Contrast Stretching

	float aux = ((calcula_max(img_aux) - calcula_min(img_aux)));// variável temporária para mais eficiência	da função

	for (int i = 0; i < img_aux->ydm; i++){
		for (int k = 0; k < img_aux->xdm; ++k){
			img_aux->mat[i][k] = ((img_aux->mat[i][k]- img_aux->min_val)/aux)*255;

		}
	}		
}


void floodFill(imagem *img_aux, int x, int y){	// operação de Flood Fill -> ja recebe o pixel central na primeira chamada.

	if(img_aux->mat[x][y] == 255){
		return;
	}
	if(img_aux->mat[x][y] == 100){
		return;
	}

	img_aux->mat[x][y] = 100;

	floodFill(img_aux,x+1,y);			// chama a pintura o pixel a direita em relação ao pixel atual
	floodFill(img_aux,x,y+1);			// chama a pintura o pixel de baixo	em relação ao pixel atual
	floodFill(img_aux,x-1,y);			// chama a pintura o pixel a esquerda em relação ao pixel atual
	floodFill(img_aux,x,y-1);			// chama a pintura o pixel de cima em relação ao pixel atual

}


void saidaArquivo(imagem* img_aux){					// salva a imagem em um arquivo com nome "saida.pgm"

	img_aux->tipo = '2';
	
	FILE* fpw;

	if ((fpw = fopen("saida.pgm", "w")) == NULL){
		printf("Nao foi possivel abrir o arquivo");
		exit(0);
	}

	fprintf(fpw, "P%c\n", img_aux->tipo);
	fprintf(fpw, "%s\n", "# CREATOR: Image Generator SCC-221 - ICC I");
	fprintf(fpw, "%d ", img_aux->xdm);
	fprintf(fpw, "%d\n", img_aux->ydm);
	fprintf(fpw, "%d\n", img_aux->max_val);

	for (int i = 0; i < img_aux->ydm; i++){		
		for (int k = 0; k < img_aux->xdm; ++k){	
			fprintf(fpw, "%d\n", img_aux->mat[i][k]);
		}

	}

	fclose(fpw);
}

void saida(imagem* img_aux){					// imprime na tela a imagem

	img_aux->tipo = '2';
	printf("P%c\n", img_aux->tipo);
	printf("%s\n", "# CREATOR: Image Generator SCC-221 - ICC I");
	printf("%d ", img_aux->xdm);
	printf("%d\n", img_aux->ydm);
	printf("%d\n", img_aux->max_val);

	for (int i = 0; i < img_aux->ydm; i++){
		for (int k = 0; k < img_aux->xdm; ++k){
			printf("%d\n", img_aux->mat[i][k]);
		}
	}
	
}
void desalocImagem(imagem* img_aux){		//função que desaloca a matriz da imagem

	for (int i = 0; i < img_aux->ydm; ++i){
		free(img_aux->mat[i]);					// desalocando os vetores que representam as linhas da imagem
	}

	free(img_aux->mat);						// desalocando o vetor de ponteiro para a imagem
}

void selectOperacao(int operacao, imagem* img){			// seleciona a operação para fazer na imagem

	if(operacao == 1){
		op_log(img);
	}else if(operacao == 2){
		con_stret(img);
	}else if(operacao == 3){
		floodFill(img,img->xdm/2,img->ydm/2);
	}
}

imagem* start(){			//função que faz os tratamentos iniciais do problema

	int operacao;			
	char arquivo[20];
	FILE* fpr;

	scanf("%d\n",&operacao);		// lê operação que o usuário deseja fazer

	fgets(arquivo,sizeof(arquivo),stdin);			// nome do arquivo onde se encontra a imagem

	arquivo[strlen(arquivo)] = '\0';


	if ((fpr = fopen(arquivo, "rb")) == NULL){
		printf("Nao foi possivel abrir o arquivo %s",arquivo);		//tratamento da abertura da imagem
		exit(0);
	}

	imagem *img = (imagem *)malloc(sizeof(imagem));		// alocando a estrutura _imagem

	allocaImagem(img, fpr);								// alocando a imagem e preenchendo as informações				
														//	na estrutura alocada acima
	
	fclose(fpr);										// não precisamos mais do arquivo	

	selectOperacao(operacao,img); 

	return img;
}



int main(int argc, char const *argv[]){

	imagem *img = start();				//começa o programa
	saida(img);					// chama a impressão da nova imagem
	desalocImagem(img);			// desalocando a imagem
	free(img);					// desalocando a estrutura _imagem
	return 0;
}