#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	int i,j,valor,status;
	int vet[40];

	srand((unsigned)time(NULL));

	for(i=0;i<40;i++){
		do{
			valor = 1+rand()%40;
			status = 1;
			for(j=0;j<=i;j++){
				if(vet[j]==valor){
					status = 0;
				}
			}
		}while(status == 0);
		vet[i] = valor;
	}
	for(i=0;i<40;i++)
		printf("%d -> %d\n",i,vet[i]);
}