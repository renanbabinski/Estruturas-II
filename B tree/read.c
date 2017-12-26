#include <stdio.h>
#include <stdlib.h>

#define DEBUG

typedef struct Exemplo{
	int id;
} Exemplo;


int main ( int argc, char ** argv ){

	FILE * f;
	long offset;
	Exemplo bolinho;

	// abre o arquivo <argv[1]> para leitura
	f = fopen(argv[1], "a+");

	/*if(!f){
		printf("could not open file!!!");
		return -1;
	}*/	

	#ifdef DEBUG	
	printf("%s", argv[1]);
	#endif	

	// posição do offset do arquivo f
	fseek(f, 0, SEEK_SET);

	//enquanto o offset do arquivo não estiver no fim
	while(!feof(f)){
		//lê <1> conteúdo de tamanho <sizeof(exemplo)> do arquivo <f> 
		//apartir da posição do offset e escreve no endereço do <bolinho>
		fread( &bolinho, sizeof(Exemplo), 1, f);
		printf("%d\n", bolinho.id);
	}
	
	//fecha o arquivo
	fclose(f);
	
	return 0;
}
