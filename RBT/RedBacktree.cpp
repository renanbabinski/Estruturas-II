#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RED false
#define BLACK true

struct node{
	int key;
	node * left, * right, *p;
	bool c;
};

struct rbtree{
	node * root;
	node * nil;
};

///////////////////////////////////////////////
rbtree * root_init ();
void insert ( rbtree * T, int k );
void insert_fix_up(rbtree* T,node* z);
void left_rotate(rbtree* T, node* x);
void right_rotate(rbtree* T, node* x);
void preorder(node* r, node* nil);
int menuprincipal(int menu);
node * search (rbtree* T, node * r, int key);
node* MenorNodo(rbtree* T, node* no);
node* tree_sucessor(rbtree* T,node* n);
void delete_fix_up(rbtree* T,node* x);
void deleta(rbtree* T, int key);
int* gera_vetor();
//////////////////////////////////////////////

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

rbtree * root_init(){
	rbtree * nova = (rbtree *)malloc(sizeof(rbtree));
	nova->nil = (node *)malloc(sizeof(node));

	nova->nil->p = NULL;
	nova->nil->left = NULL;
	nova->nil->right = NULL;
	nova->nil->c = BLACK;
	
	nova->root = nova->nil;
	return nova;
} 

void insert ( rbtree * T, int k ){
	node * n = (node *)malloc(sizeof(node));
	n->p = n->left = n->right = T->nil;
	n->key = k;
	n->c = RED;

	node * y;
	node * x;
	
	y = T->nil;
	x = T->root;


	while ( x != T->nil ){
		y = x;
		if ( k < x->key )
			x = x->left;
		else x = x->right;
	}

	n->p = y;

	if(y == T->nil)
		T->root = n;
	else if (k < y->key)
		y->left = n;
	else y->right = n;

	insert_fix_up(T,n);	
	
}

void insert_fix_up(rbtree* T,node* z){
	node* y;

	while(z->p->c == RED){
		if(z->p == z->p->p->left){
			y = z->p->p->right;
			if(y->c == RED){
				z->p->c = BLACK;
				y->c = BLACK;
				z->p->p->c = RED;
				z = z->p->p;
				}else{
					 if(z == z->p->right){
						z = z->p;
						left_rotate(T,z);
						z->p->c = BLACK;
						z->p->p->c = RED;
						right_rotate(T,z->p->p);
					}else{
						z = z->p;
						right_rotate(T,z);
					}
				}
		}else{
			y = z->p->p->left;
			if(y->c == RED){
				z->p->c = BLACK;
				y->c = BLACK;
				z->p->p->c = RED;
				z = z->p->p;
			}else{ 
				if(z == z->p->left){
					z = z->p;
					right_rotate(T,z);
					z->p->c = BLACK;
					z->p->p->c = RED;
					left_rotate(T,z->p->p);
				}else{
					z = z->p;
					left_rotate(T,z);
				}

			}
		}
	}
	T->root->c = BLACK;
}

void left_rotate(rbtree* T, node* x){
	node* y;

	y = x->right;
	x->right = y->left;
	if(y->left != T->nil)
		y->left->p = x;
	y->p = x->p;
	if(x->p == T->nil)
		T->root = y;
	else if(x == x->p->left)
		x->p->left = y;
	else
		x->p->right = y;
	y->left = x;
	x->p = y;
}

void right_rotate(rbtree* T, node* x){
	node* y;

	y = x->left;
	x->left = y->right;
	if(y->right != T->nil)
		y->right->p = x;
	y->p = x->p;
	if(x->p == T->nil)
		T->root = y;
	else if(x == x->p->right)
		x->p->right = y;
	else
		x->p->left = y;
	y->right = x;
	x->p = y;
}

void preorder(node* r, node* nil){
	if(r != nil){
		if(r->c == RED)
			printf("RED\n");
		else 
			printf("BLACK\n");
		printf("%d\n\n",r->key);
		preorder(r->left,nil);
		preorder(r->right,nil);
	}
}

void inorder(node* r, node* nil){
	if(r != nil){
		inorder(r->left,nil);
		if(r->c == RED)
			printf("RED\n");
		else 
			printf("BLACK\n");
		printf("%d\n\n",r->key);
		inorder(r->right,nil);
	}
}

void posorder(node* r, node* nil){
	if(r != nil){
		posorder(r->left,nil);
		posorder(r->right,nil);
		if(r->c == RED)
			printf("RED\n");
		else 
			printf("BLACK\n");
		printf("%d\n\n",r->key);
	}
}

int* gera_vetor(){
	int i,j,valor,status;
	int *vet;
	vet = (int*)malloc(40*sizeof(int));

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
	return vet;
}

void deleta(rbtree* T, int key){
	node* z = search(T, T->root, key);
	node* y ,* x;
	if(z == T->nil){
		printf("Numero não encontrado na árvore!");
		getchar();
		return ;
	}
	if(z->left == T->nil || z->right == T->nil)
		y = z;
		else
			y = tree_sucessor(T,z);
	if(y->left != T->nil)
		x = y->left;
		else
			x = y->right;
	x->p = y->p;
	if(y->p == T->nil)
		T->root = x;
		else if(y == y->p->left)
			y->p->left = x;
		else
			y->p->right = x;
	if(y != z)
		z->key = y->key;
	if(y->c == BLACK)
		delete_fix_up(T,x);
	
}

void delete_fix_up(rbtree* T,node* x){
	node* w;

	while(x != T->root && x->c == BLACK){
		if(x == x->p->left){
			w = x->p->right;
			if(w->c == RED){
				w->c = BLACK;
				x->p->c = RED;
				left_rotate(T,x->p);
				w = x->p->right;
			}
			if(w->left->c == BLACK && w->right->c == BLACK){
				w->c = RED;
				x = x->p;
				}else if(w->right->c == BLACK){
					w->left->c = BLACK;
					w->c = RED;
					right_rotate(T,w);
					w = x->p->right;
			
				w->c = w->p->c;
				x->p->c = BLACK;
				w->right->c = BLACK;
				left_rotate(T,x->p);
				x = T->root;
			}
		}else{
			w = x->p->left;
			if(w->c == RED){
				w->c = BLACK;
				x->p->c = RED;
				right_rotate(T,x->p);
				w = x->p->left;
			}
			if(w->right->c == BLACK && w->left->c == BLACK){
				w->c = RED;
				x = x->p;
				}else if(w->left->c == BLACK){
					w->right->c = BLACK;
					w->c = RED;
					left_rotate(T,w);
					w = x->p->left;
			
				w->c = w->p->c;
				x->p->c = BLACK;
				w->left->c = BLACK;
				right_rotate(T,x->p);
				x = T->root;
			}
		}
	}
	x->c = BLACK;
}

node* tree_sucessor(rbtree* T,node* n){
	if(n->right != T->nil)
		return MenorNodo(T,n->right);
	node* parent = n->p;
	while(parent != T->nil && n == parent->right){
		n = parent;
		parent = parent->p;
	}
	return parent;
}

node* MenorNodo(rbtree* T, node* no){
	node* aux = no;
	while(aux->left != T->nil)
		aux = aux->left;
	return aux;
}

node * search (rbtree* T, node * r, int key){
	if(r == T->nil || r->key == key ) return r;				

	if(key <= r->key) return search (T,r->left, key);
	
	return search (T,r->right, key);

}

int main(){

	/*int menu = 10;

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
	}*/
	rbtree* root = root_init();

	/*int *vet;
	int i;

	vet = gera_vetor();
	for(i=0;i<40;i++){
		printf("Número que será inserido na árvore:\n");
		printf("%d -> %d\n",i,*vet);
		getchar();
		system("clear");
		insert(root,*vet);
		preorder(root->root,root->nil);
		vet++;
	}*/


	
	insert(root,40);
	insert(root,24);
	insert(root,32);
	insert(root,9);
	insert(root,19);
	insert(root,17);
	insert(root,39);
	insert(root,4);
	insert(root,18);


	preorder(root->root,root->nil);
	printf("\n\n\n");


	deleta(root,24);
	//deleta(root,18);
	//deleta(root,19);
	//deleta(root,40);
	//deleta(root,39);
	//eleta(root,4);
	





	/*insert(root,15);
	insert(root,11);
	insert(root,32);
	insert(root,34);
	insert(root,50);
	insert(root,10);
	insert(root,2);
	insert(root,1);
	insert(root,64);
	insert(root,17);*/

	//printf("%d",root->root->key);
	preorder(root->root,root->nil);

	/*printf("\n\n\n");

	posorder(root->root,root->nil);

	printf("\n\n\n");

	inorder(root->root,root->nil);*/
	




	return 0;
}


