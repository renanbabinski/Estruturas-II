#include <stdio.h>
#include <stdlib.h>

#define DEBUG

typedef struct Exemplo{
	int id;
} Exemplo;


int main ( int argc, char ** argv ){

	FILE * f;
	Exemplo bolinho;
	
	#ifdef DEBUG
	// quantidade de arquivos de entrada
	printf("%d ", argc); 
	#endif

	f = fopen("teste", "w+");
		
	while(scanf("%d", &bolinho.id)){
		//escreve bolinho, de tamanho sizeof(exemplo) no arquivo f
		fwrite(&bolinho, sizeof(Exemplo), 1, f);
	}  
	
	fseek(f, 0, SEEK_SET);

	while(!feof(f)){
		fread(&bolinho, sizeof(Exemplo), 1, f);
		printf("%d ", bolinho.id);
	}


    fclose(f);

	return 0;
}