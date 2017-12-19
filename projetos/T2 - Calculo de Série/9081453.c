#include <stdio.h>
#include <math.h>

#define fat1 1;
#define fat2 2;
#define fat3 6;
#define fat4 24;

int escolhe_fat(int k){
	if(k==1){
		return fat1;
	}else if((k==2)||(k==0)){
		return fat2;
	}else if(k==3){
		return fat3;
	}else if(k==4){
		return fat4;
	}else{
		return fat3;
	}

}

int main(){

	int N,sinal=-1;
	double X,cima,baixo,soma=0;
	scanf("%lf",&X);
	scanf("%d",&N);

	for (int i = 1; i <= N; ++i){

		cima = (pow(X,i+1));
		
		baixo = escolhe_fat((i%6));
		
		soma = soma + (sinal*(cima/baixo));
		sinal = -sinal;

	}

	printf("%.4lf\n", soma);
	return 0;

}