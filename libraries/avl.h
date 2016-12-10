/*
 * Ryan Symington
 * 11/28/16
*/

#ifndef __AVL_H__
#define __AVL_H__

#include "linkedlist.h"

typedef struct node
{
	Record *list;
	
	void *key;
	int freq;
	int height;
	
	struct node *left;
	struct node *right;
}Node;

typedef struct tree
{
	Node *root;
}Tree;

//initializes a tree
Tree * init();

//mallocs memmory for node
//returns the new node on added to heap
Node * createNode(void *key);

//finds spot to put node with given key
//balances tree accordingly
Node * insert(Node *root, void *key);

Tree *makeKeys(Tree *tree, char *para, char *filename);

Node * get(Node *root, char *key);

Node * removeNode(Node *root, char *key);

Node * findMin(Node *root);

Node * rotateRight(Node *root);

Node * rotateLeft(Node *root);

Node *destroyNodes(Node *root);

Node * destroyNode(Node *node);

Node *getNodeAt(Node *root, int count, int nodeNum);

Record * searchTerms(Node *root, char *term);

//frees malloced memory for tree and its components
Tree * destroyTree(Tree *tree);

//creates a tree out of given folder
Tree * createTree(Tree *tree, char *startFolder);

void printNode(Node *node);

void printTree(Node *root);

void printNodes(Node *root, int depth, int height);

//returns a pointer to the key in node casted as a char *
char * getKey(Node *node);

int getHeight(Node *root, int height);

int getBalance(Node *root);

#endif
