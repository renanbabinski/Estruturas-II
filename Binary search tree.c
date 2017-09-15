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
node* MenorNodo(node* node);
node* delete(node* root, int key);

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

void *inorder (node * r){
	if(r != NULL){
		inorder(r->left);
		printf("%d\n",r->key);
		inorder(r->right);
	}
}

void *preorder(node * r){
	if(r != NULL){
		printf("%d\n",r->key);
		preorder(r->left);
		preorder(r->right);
	}
}

void posorder(node * r){
	if(r != NULL){
		posorder(r->left);
		posorder(r->right);
		printf("%d\n",r->key);
	}
}

node * insert (node * r, int key){
	node * n = (node *)malloc(sizeof(node));		
	n->left = n->right = NULL;
	n->key = key;
			
	if(!r) return n;			

	node * it = r;	

	while(1){
		if(key < it->key){
			if(!it->left){
				it->left = n; 		
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

/* Essa função é chamada no caso da deleção de um Nodo com dois filhos,
ela encontra o menor valor da sub-árvore a direita do Nodo a ser deletado,
então, retorna o menor Nodo para substituição*/
node* MenorNodo(node* no){
	node* aux = no;
	while(aux->left != NULL)
		aux = aux->left;
	return aux;
}

/*Recebe uma árvore binária de busca e uma chave,
essa função deleta a chave e retorna uma nova raiz*/
node* delete(node* root, int key){
	if(root == NULL)    //árvore vazia
		return root;
	if(key < root->key)  //Se a chave for menor que a chave da raiz
		root->left = delete(root->left, key);
	else if(key > root->key)  //Se a chave for maior que a chave da raiz
		root->right = delete(root->right, key);
	//Se a chave é igual a chave da raiz, então esse é o Nodo a ser deletado
	else{
		//Se o nodo tiver um ou nenhum filho
		if(root->left == NULL){
			node* temp = root->right;
			free(root);
			return temp;
		}
		else if(root->right == NULL){
			node* temp = root->left;
			free(root);
			return temp;
		}
		//Se o nodo tiver dois filhos, achar o menor valor da sub-árvore a direita
		node* temp = MenorNodo(root->right);
		//Substituir o nodo raiz pelo menor nodo
		root->key = temp->key;
		//Deletar o menor nodo da árvore
		root->right = delete(root->right,temp->key);
	}
	return root;
}

/////////////////////////////////////

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
				printf("\nDigite o número que deseja excluir da árvore:\n");
				scanf("%d",&n);
				getchar();
				if(delete(root,n) == NULL)
					printf("O número não existe na árvore!!!\n");
				else
					printf("***Deletado com sucesso***\n");
					printf("Pressione ENTER para continuar...\n");
					getchar();
				break;
			case 4:
				printf("\nElementos da árvore (IN ORDER) : \n");
				inorder(root);
				printf("\nPressione ENTER para continuar...");
				getchar();
				break;
			case 5:
				printf("\nElementos da árvore (PRE ORDER) : \n");
				preorder(root);
				printf("\nPressione ENTER para continuar...");
				getchar();
				break;
			case 6:
				printf("\nElementos da árvore (POS ORDER) : \n");
				posorder(root);
				printf("\nPressione ENTER para continuar...");
				getchar();
				break;
			case 0:
				break;
			default:
				break;
		}
	}

	return 0;
		}




