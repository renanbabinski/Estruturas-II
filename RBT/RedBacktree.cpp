#include <stdio.h>
#include <stdlib.h>
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
				}else if(z == z->p->right){
					z = z->p;
					left_rotate(T,z);
					z->p->c = BLACK;
					z->p->p->c = RED;
					right_rotate(T,z->p->p);
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
	if(x->p == NULL)
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
	insert(root,8);
	insert(root,10);
	insert(root,23);
	insert(root,6);
	insert(root,9);
	insert(root,0);
	insert(root,12);
	insert(root,35);
	insert(root,24);
	insert(root,15);
	insert(root,3);

	//printf("%d",root->root->key);
	preorder(root->root,root->nil);

	printf("\n\n\n");

	posorder(root->root,root->nil);

	printf("\n\n\n");

	inorder(root->root,root->nil);
	




	return 0;
}


