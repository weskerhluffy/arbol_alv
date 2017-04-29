/*
 ============================================================================
 Name        : arbol_alv.c
 Author      : ernesto
 Version     :
 Copyright   : a veces siento que
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

/* Node is defined as :
 * */
typedef struct node {
	int val;
	struct node* left;
	struct node* right;
	int ht;
} node;

int balance_factor(node *nodo) {
	int caca = 0;
	if (nodo->left) {
		caca = nodo->left->ht;
	} else {
		caca = -1;
	}
	if (nodo->right) {
		caca -= nodo->right->ht;
	} else {
		caca += 1;
	}
	return caca;
}

int max(int a, int b) {
	return a > b ? a : b;
}

void actualiza_altura(node *nodo) {
	int alt_izq = nodo->left ? (nodo->left->ht + 1) : 0;
	int alt_der = nodo->right ? (nodo->right->ht + 1) : 0;

	nodo->ht = max(alt_izq, alt_der);
}

node *rota_izq(node *a) {
	node *b = a->right;

	a->right = b->left;
	b->left = a;
	actualiza_altura(a);
	actualiza_altura(b);
	return b;
}

node *rota_der(node *a) {
	node *b = a->left;

	a->left = b->right;
	b->right = a;
	actualiza_altura(a);
	actualiza_altura(b);
	return b;
}

node * insert(node * root, int val) {
	node *res = NULL;
	if (!root) {
		res = (node *) calloc(1, sizeof(node));
		res->val = val;
	} else {
		if (val < root->val) {
			root->left = insert(root->left, val);
		} else {
			root->right = insert(root->right, val);
		}
		actualiza_altura(root);
		int balance_caca = balance_factor(root);
		node *nodo = root;
		if (balance_caca > 1) {
			if (val < nodo->left->val) {
				res = rota_der(nodo);
			} else {
				nodo->left = rota_izq(nodo->left);
				res = rota_der(nodo);
			}
		} else {
			if (balance_caca < -1) {
				if (val > nodo->right->val) {
					res = rota_izq(nodo);
				} else {
					nodo->right = rota_der(nodo->right);
					res = rota_izq(nodo);
				}
			} else {
				res = nodo;
			}
		}
	}
	return res;
}

int main(void) {
	puts("he corrido con algo de suerte"); /* prints he corrido con algo de suerte */
	return EXIT_SUCCESS;
}
