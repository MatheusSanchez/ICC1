#include <stdio.h>


int main (){

	//int N;
	//scanf("%d",N)
	int pont = 0,N;
	char tipo;
	scanf("%c",&tipo);

	if(tipo == 'A'){
		int reps;
		scanf("%d",&reps);
		scanf("%d",&N);

		while(reps>0){

			for(int i = 0; i<N; i++){
				pont = i;
				for (int k = 0; k < N; k++){
					if (k==pont){
						printf("O ");
					}else{
						printf("X ");
					}
				}

				printf("\n");

			}

			for (int k = 0; k < N; k++) printf("X ");

			printf("\n");
			printf("\n");

			reps --;
		}
		


	}else{
		scanf("%d",&N);

		for (int j = 0; j < N; j++){
			pont = j;

			for(int i = pont; i<N; i++){

				for (int k = 0; k < N; k++){
					if (k==pont){
						printf("O ");
					}else{
						printf("X ");
					}
				}

				pont ++;
				printf("\n");

			}
			for (int k = 0; k < N; k++) printf("X ");
				printf("\n");
			printf("\n");

		}

	}
	

	return 0;
}