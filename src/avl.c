/*
 * Ryan Symington
 * 11/28/16
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "avl.h"

Tree * init()
{
	Tree *tree = malloc(sizeof(tree));
	
	if(!tree)
	{
		perror("malloc error");
		exit(1);
	}
	
	tree->root = NULL;
	
	return tree;
}

Node * createNode(void *key)
{
	Node *node = malloc(sizeof(Node));
	
	if(!node)
	{
		perror("malloc error");
		exit(1);
	}
	
	node->key = malloc(sizeof(void) * (strlen(key) + 1));
	
	if(!(node->key))
	{
		perror("malloc error");
		exit(1);
	}
	
	node->list = NULL;
	
	strcpy(node->key, key);
	node->freq = 1;
	node->height = 0;
	
	node->left = NULL;
	node->right = NULL;
	
	return node;
}

Tree *makeKeys(Tree *tree, char *para, char *filename)
{
	if(para)
	{
		int start = 0;
		for(int i = 0; i < strlen(para); i ++)
		{
			if(para[i] == ' ' || para[i] == '\n')
			{
				//printf("start:%d, i:%d\n", start, i);
				char key[i - start + 1];
				strncpy(key, para + start, i - start);
				key[i - start] = '\0';
				
				char *found = strstr(key, "\r");
				if(found)
					*found = '\0';	
				
				if(strlen(key) != 0)
				{
					tree->root = insert(tree->root, key);
					Node *node = get(tree->root, key);
					if(node)
					{
						node->list = addToBack(node->list, para, filename);
					}
				}
				
				start = i + 1;
			}
		}
	}
	
	return tree;
}

Node * insert(Node *root, void *key)
{
	if(root == NULL)
	{
		Node *root = createNode(key);
		return root;
	}
	else if(strcmp(key, getKey(root)) < 0)
	{
		root->left = insert(root->left, key);
	}
	else if(strcmp(key, getKey(root)) > 0)
	{
		root->right = insert(root->right, key);
	}
	else
	{
		root->freq ++;
		return root;
	}
	
	if(root == NULL)
	{
		return root;
	}
	
	root->height = getHeight(root, 0);
	
	int balance = getBalance(root);
	
	if(balance > 1 && strcmp(key, getKey(root->left)) < 0)
	{
		return rotateRight(root);
	}		
	else if(balance < -1 && strcmp(key, getKey(root->right)) > 0)
	{
		return rotateLeft(root);
	}
	else if(balance > 1 && strcmp(key, getKey(root->left)) > 0)
	{
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	}
	else if(balance < -1 && strcmp(key, getKey(root->right)) < 0)
	{
		root->right = rotateRight(root->right);
		return rotateLeft(root);
	}
	
	return root;
}

Node * get(Node *root, char *key)
{
	if(root == NULL)
	{
		return root;
	}
	else if(strcasecmp(key, getKey(root)) < 0)
	{
		return get(root->left, key);
	}
	else if(strcasecmp(key, getKey(root)) > 0)
	{
		return get(root->right, key);
	}
	else
	{
		return root;
	}
}

Node * removeNode(Node *root, char *key)
{
	if(root == NULL)
	{
		return root;
	}
	else if(strcmp(key, getKey(root)) < 0)
	{
		root->left = removeNode(root->left, key);
	}
	else if(strcmp(key, getKey(root)) > 0)
	{
		root->right = removeNode(root->right, key);
	}
	else
	{
		printf("FOUND\n");
		if(root->freq == 1)
		{
			if(!root->left || !root->right)
			{
				Node *temp = root->left ? root->left : root->right;
				
				if(!temp)
				{
					temp = root;
					root = NULL;
				}
				else
				{
					*root = *temp;
				}
				
				free(temp);
			}
			else
			{
				Node *temp = findMin(root->right);
				
				strcpy(root->key, temp->key);
				root->freq = temp->freq;
				temp->freq = 1;
				
				root->right = removeNode(root->right, temp->key);
			}
		}
		else
		{
			root->freq --;
		}
	}
	
	if(root == NULL)
		return root;
	
	root->height = getHeight(root, 0);
	
	int balance = getBalance(root);
	
	if(balance > 1 && strcmp(key, getKey(root->left)) < 0)
	{
		return rotateRight(root);
	}		
	else if(balance < -1 && strcmp(key, getKey(root->right)) > 0)
	{
		return rotateLeft(root);
	}
	else if(balance > 1 && strcmp(key, getKey(root->left)) > 0)
	{
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	}
	else if(balance < -1 && strcmp(key, getKey(root->right)) < 0)
	{
		root->right = rotateRight(root->right);
		return rotateLeft(root);
	}
	
	return root;
}

Node * findMin(Node *root)
{
	while(root->left)
	{
		root = root->left;
	}
	return root;
}

Node * rotateRight(Node *root)
{
	Node *leftChild = root->left;
		
	root->left = leftChild->right;
	
	leftChild->right = root;
	
	return leftChild;
}

Node * rotateLeft(Node *root)
{
	Node *rightChild = root->right;
		
	root->right = rightChild->left;
	
	rightChild->left = root;
	
	return rightChild;
}

Node *destroyNodes(Node *root)
{
	if(root == NULL)
	{
		return root;
	}
	else
	{
		root->left = destroyNodes(root->left);
		root->right = destroyNodes(root->right);
		root = destroyNode(root);
		return root;
	}
}

Node * destroyNode(Node *node)
{
	if(node)
	{
		free(node->key);
		node->key = NULL;
		
		node->list = destroyList(node->list);
		
		free(node);
		node = NULL;
	}
	return node;
}

Node *getNodeAt(Node *root, int count, int nodeNum)
{
	if (root == NULL)
	{
		return root;
	}
	else if (count == nodeNum)
	{
		return root;
	}
	else
	{
		Node *node = getNodeAt(root->left, count + 1, nodeNum);
		if (!node)
			node = getNodeAt(root->right, count + 1, nodeNum);
		return node;
	}
}

Record * searchTerms(Node *root, char *term)
{
	term = strtok(term, " ");
	
	Record *final = NULL;
	
	if(term)
	{
		Node *found = get(root, term);
		if(found)
		{
			Record *list = found->list;
			
			if(list)
			{
				
				do{
					
					final = addToBack(final, list->string, list->filename);
					
				}while((list = list->next));
				
				while((term = strtok(NULL, " ")))
				{
					found = get(root, term);
					
					if(found)
					{
						Record *toCheck = found->list;
						
						if(toCheck)
						{
							Record *finalCheck = final;
							do{
							
								if(!exists(toCheck, finalCheck->string, finalCheck->filename))
								{
									final = removeRecord(final, finalCheck->string, finalCheck->filename);
								}
								
							}while((finalCheck = finalCheck->next));
						}
					}
				}
			}
		}
		
	}
	
	return final;
}

Tree * destroyTree(Tree *tree)
{
	if(!tree)
		return tree;
	tree->root = destroyNodes(tree->root);
	
	printf("tree destroyed\n");
	return tree;
}

Tree * createTree(Tree *tree, char *startFolder)
{
	tree = destroyTree(tree);
	return tree;
}

void printNode(Node *node)
{
	printf("%s\n", getKey(node));
}

void printTree(Node *root)
{
	if(root)
		for(int i = 0; i <= root->height + 1; printNodes(root, 0, i), printf("\n"), i ++);
	else
		printf("N \n");
}

void printNodes(Node *root, int depth, int height)
{
	if(root == NULL)
	{
		if(depth == height)
			printf("N ");
		return;
	}
	else if(depth == height)
	{
		printf("%s ", getKey(root));
		return;
	}
	else
	{
		printNodes(root->left, depth+1, height);
		printNodes(root->right, depth+1, height);
		return;
	}
}

int getBalance(Node *root)
{
	if(root)
		return getHeight(root->left, 0) - getHeight(root->right, 0);
	
	return 0;
}

int getHeight(Node *root, int height)
{
	if(!root)
	{
		return height;
	}
	else if(!root->left && !root->right)
	{
		return height;
	}
	else
	{
		height = getHeight(root->left, height + 1);
		int hHolder = getHeight(root->right, height);

		if(height < hHolder)
			height = hHolder;
		return height;
	}
}

char * getKey(Node *node)
{
	return (char*)node->key;
}
