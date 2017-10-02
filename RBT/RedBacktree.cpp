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
rbtree * dinossauro_inicia ();
void insert ( rbtree * T, int k );
void insert_fix_up(rbtree* T,node* z);
void left_rotate(rbtree* T, node* x);
void right_rotate(rbtree* T, node* x);
void preorder(node* r, node* nil);




rbtree * dinossauro_inicia (){
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
				}else if(z == z->p->left){
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
			}else if(z == z->p->right){
				z = z->p;
				left_rotate(T,z);
				z->p->c = BLACK;
				z->p->p->c = RED;
				right_rotate(T,z->p->p);
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

int main(){

	rbtree* root = dinossauro_inicia();
	insert(root,8);
	insert(root,10);
	insert(root,23);
	//insert(root,6);
	//insert(root,9);
	//insert(root,0);
	//insert(root,12);
	//insert(root,35);
	//insert(root,24);
	//insert(root,15);
	//insert(root,3);

	//printf("%d",root->root->key);
	preorder(root->root,root->nil);
	









	printf("\n\n\nHELLO\n\n\n");



	return 0;
}


