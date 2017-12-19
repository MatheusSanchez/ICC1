#include <stdio.h>
#include <math.h>

int main(){

	int alunos,byte,f=0,m=0;
	char aux;

	scanf("%d",&byte);
	scanf("%d",&alunos);
	
	if(byte>=0 && byte <= 3 && alunos>=0 && alunos<=pow(10,9)){

		alunos = alunos >> (byte)*8;
		
		aux = alunos;
		
		if(aux&1){
			m++;
			printf("1");
		}else{
			printf("0");
		}if(aux&(1<<1)){
			m++;
			printf("1");
		}else{
			printf("0");
		}if(aux&(1<<2)){
			m++;
			printf("1");
		}else{
			printf("0");
		}if(aux&(1<<3)){
			m++;
			printf("1");
		}else{
			printf("0");
		}if(aux&(1<<4)){
			m++;
			printf("1");
		}else{
			printf("0");
		}if(aux&(1<<5)){
			m++;
			printf("1");
		}else{
			printf("0");
		}if(aux&(1<<6)){	
			m++;
			printf("1");
		}else{
			printf("0");
		}if(aux&(1<<7)){	
			m++;
			printf("1\n");
		}else{
			printf("0\n");
		}

		f = 8 - m;
		printf("%d\n", f);
		printf("%d\n", m);

	}else{
		printf("Invalid input\n");
	}	
}