#include <stdio.h>
#include <stdlib.h>


#define T 2


typedef struct Node{
	int n;			//número de elementos no nodo	
	int * key;		//a chave que o nodo armazena	
	long * c;		//um vetor de longs para armazenar o offset dos filhos
	int leaf;		//uma variável que indica se o Nodo é um filho
} Node;


typedef struct Tree{
	Node * r;		//o nodo raiz
	long pos;		//a posição do nodo no arquivo
} Tree;



//essa função inicia a árvore
Tree * init ( FILE * f ){
	Tree * t = malloc(sizeof(Tree));
	t->r = malloc(sizeof(Node));

	t->r->n = 0;
	t->r->leaf= 1;
	t->r->c = malloc(2*T*(sizeof(long)));
	t->r->key = malloc((2*T - 1)* sizeof(long));
	
	t->pos = ftell(f);	

	fwrite(t, sizeof(Tree), 1, f);

	return t;	
}


//essa função busca uma chave
Node * btree_search ( FILE * f, Node * x, int key ){
	int i;

	for ( i = 0; i < x->n && x->key[i] < key; i++ );
	
	if ( i < x->n && x->key[i] == key )
		return x;
	
	if (x->leaf){
		return NULL;

	} else {

		fseek(f, x->c[i], SEEK_SET);
		fread (x, sizeof(Node), 1, f);
		return btree_search(f, x, key);
	}		
} 

int main ( int argc, char ** argv ){
	
	return 0;		
}
