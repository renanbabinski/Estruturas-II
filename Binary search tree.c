#include <stdlib.h>
#include <stdio.h>

struct no{
	int key;  						
	struct no *left;
	struct no *right;		   
};

typedef struct no node;

//////////////////////////////////////////

int menuprincipal(int menu);
node * search (node * r, int key);
void * inorder (node * r);
node * insert (node * r, int key);

//////////////////////////////////////////

int menuprincipal(int menu){
	system("clear");
	printf(" MENU PRINCIPAL:\n\n");
	printf("1--Inserir novos nodos\n");
	printf("2--Buscar um nodo na árvore\n");
	printf("3--Deletar um nodo\n");
	printf("4--Imprimir árvore IN ORDER\n");
	printf("5--Imprimir árvore PRE ORDER\n");
	printf("6--Imprimir árvore POS ORDER\n");
	printf("0--EXIT\n");
	scanf("%d",&menu);
	getchar();
	return menu;
}

node * search (node * r, int key){
	if(!r || r->key == key ) return r;				

	if(key <= r->key) return search (r->left, key);
	
	return search (r->right, key); 	
}

void * inorder (node * r){
	if(r != NULL){
		inorder(r->left);
		printf("%d\n",r->key);
		inorder(r->right);
	}
}

//insere um nodo com chave key na árvore com raiz r
//retorna um ponteiro para a raiz da árvore

node * insert (node * r, int key){
	node * n = (node *)malloc(sizeof(node));		//cria um novo nodo
	n->left = n->right = NULL;
	n->key = key;
			
	if(!r) return n;			// se a arvore estiver vazia

	node * it = r;	

	while(1){
		if(key < it->key){
			if(!it->left){
				it->left = n; 		//atualiza o filho da esquerda de r	
				break;		
			}
			it = it->left;	
		}else{
			if(!it->right){
				it->right = n;
				break;			
			}
			it = it->right;
		}		
	}

	return r;
}

//remove o nodo da árvore com raiz r que possui chave igual a key
//(lembra que tem que dar free no nodo)
//void remove (node * r, int key);

int main ( void ){

	int n,menu = 10;
	
	node * root = NULL;

	while(menu != 0){
		menu = menuprincipal(menu);
		switch(menu){
			case 1:
				printf("\nInsira os numeros com ENTER até que uma letra seja digitada:\n");
				while(scanf("%d", &n)){
					root = insert(root, n);
				}
				getchar();
				printf("\nNumeros inseridos na árvore!\nPressione ENTER para continuar...\n");
				getchar();
				getchar();
				break;
			case 2:
				printf("\nDigite um número para buscar na árvore:\n");
				scanf("%d",&n);
				getchar();
				if(search(root,n))
					printf("O numero está na árvore!!!\n");
				else
					printf("Numero não encontrado na árvore!!!\n");
				printf("\nPressione ENTER para continuar...");
				getchar();
				break;
			case 3:
				break;
			case 4:
				printf("\nElementos da árvore (IN ORDER) : \n");
				inorder(root);
				printf("\nPressione ENTER para continuar...");
				getchar();
				break;
			case 0:
				break;
		}
	}

	return 0;
		}




