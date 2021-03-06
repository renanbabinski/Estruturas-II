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
node* deleta(rbtree* T, int key);
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

node* deleta(rbtree* T, int key){
	node* z = search(T, T->root, key);
	node* y ,* x;
	if(z == T->nil){
		return z;
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
	return z;
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
				}else{
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
				}else{
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

	rbtree* root = root_init();

	int n;
	int menu = 10;

	while(menu != 0){
		menu = menuprincipal(menu);
		switch(menu){
			case 1:
				printf("\nInsira os numeros com ENTER até que uma letra seja digitada:\n");
				while(scanf("%d", &n)){
					insert(root, n);
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
				if(search(root,root->root,n) != root->nil)
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
				if(deleta(root,n) == root->nil)
					printf("O número não existe na árvore!!!\n");
				else
					printf("***Deletado com sucesso***\n");
					printf("Pressione ENTER para continuar...\n");
					getchar();
				break;
			case 4:
				printf("\nElementos da árvore (IN ORDER) : \n");
				inorder(root->root,root->nil);
				printf("\nPressione ENTER para continuar...");
				getchar();
				break;
			case 5:
				printf("\nElementos da árvore (PRE ORDER) : \n");
				preorder(root->root,root->nil);
				printf("\nPressione ENTER para continuar...");
				getchar();
				break;
			case 6:
				printf("\nElementos da árvore (POS ORDER) : \n");
				posorder(root->root,root->nil);
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


