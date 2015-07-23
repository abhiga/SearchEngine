
// Implementation of a dictionary using an AVL tree
// AVL Trees are balanced binary trees 

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "avl-dictionary.h"

bool debug = false;

// Constructor
AVLDictionary::AVLDictionary()
{
	root = NULL;
	nElements = 0;
}

// Add a record to the dictionary. Returns false if key already exists
bool
AVLDictionary::addRecord( KeyType key, DataType record)
{
	if ( debug) {
		printf("------------------------------------\n");
		printf("addRecord(\"%s\",%ld)\n",  key, (long) record);
		printf("---------- Before -----------------\n");
		printNode("", root, 0);
	}
	
	// Add your implementation here

	//Find node to insert into 
	//Node does not exist. Create it.
	//Height might not be valid anymore.
	//We need to restructure .
	
	AVLNode *e = new AVLNode();
    e -> key = key;
    e -> data = record;
    e -> height = 1;
    e -> left = NULL;
    e -> right = NULL;
    e -> parent = NULL;

    if(root == NULL) {
        root = e;
		nElements++;
		return true;
    }
	AVLNode *curr = root;
	
    AVLNode *prev = NULL;
	
    while(curr != NULL)
	{
        prev = curr;
        if (strcmp(key, curr->key) < 0) {
            curr = curr -> left;
        }
        else if (strcmp(key, curr->key) > 0) {
            curr = curr -> right;
        }
        else {
            curr -> data = record;
            return false;
        }
    }
	if (strcmp(key, prev->key) > 0) 
        prev -> right = e;
    else
        prev -> left = e;
    e -> parent = prev;
	int maxh;
    AVLNode *p = e-> parent;
	while(p != NULL)
	{
        maxh = 0;
        if(p -> left != NULL)
            maxh = p -> left -> height;
        if(p -> right != NULL && maxh < p ->right -> height)
            maxh = p -> right -> height;
        p -> height = 1 + maxh;
        p = p -> parent;
    }


	if ( debug) {
		printf("---------- Before Restructure -----------------\n");
		printNode("", root, 0);
	}
	
	// Call restructure
	restructure(e);

	if (debug) {
		checkRecursive(root);
		
		printf("---------- After Restructure -----------------\n");
		printNode("", root, 0);
	}
	nElements++;	
	return true;
}

void
AVLDictionary::restructure(AVLNode * n) {
	//Balance the tree starting at n 

	//Go upwards until root is found

        // See class notes

	// Add your implementation here
	AVLNode *z = n;
	int hleft;

	while (z != NULL) {
		hleft = 0;
		
		if (z->left != NULL) {
			hleft = z->left->height;
		}

		int hright = 0;

		if (z->right != NULL) {
			hright = z->right->height;
		}

		int hdiff = hleft - hright;

		if (hdiff < 0) { 
			hdiff = -hdiff;
		}

		if (hleft > hright)	{
			z->height = 1 + hleft;
		} else {
			z->height = 1 + hright;
		}
		if (hdiff <= 1)	{
			z = z->parent;
			continue;
		}

		AVLNode *y = NULL;
		int maxHeight = 0;

		if (z->left != NULL) {
			y = z->left;
			maxHeight = y->height;
		}

		if (z->right != NULL && z->right->height > maxHeight) {
			y = z->right;
			maxHeight = y->height;
		}

		assert(y != NULL);

		AVLNode *x = NULL;

		maxHeight = 0;

		if (y->left != NULL) {
			x = y->left;
			maxHeight = x->height;
		}

		if (y->right != NULL && y->right->height > maxHeight) {
			x = y->right;
			maxHeight = x->height;
		}

		assert(x != NULL);

		AVLNode *t0, *t1, *t2, *t3;
		AVLNode *a, *b, *c;

		if (z->right == y) {
			if (y->right == x) {
				a = z;
				b = y;
				c = x;
				t0 = a->left;
				t1 = b->left;
				t2 = c->left;
				t3 = c->right;
			} else {
				a = z;
				b = x;
				c = y;
				t0 = a->left;
				t1 = b->left;
				t2 = b->right;
				t3 = c->right;
			}
		} else { 
			if (y->left == x) { 
				a = x;
				b = y;
				c = z;
				t0 = a->left;
				t1 = a->right;
				t2 = b->right;
				t3 = c->right;
			} else {
				a = y;
				b = x;
				c = z;
				t0 = a->left;
				t1 = b->left;
				t2 = b->right;
				t3 = c->right;
			}
		}
			
		AVLNode *p = z->parent;
		if (p == NULL) {
			root = b;
		} else {	
			if (p->left == z) {
				p->left = b;
			} else {
				p->right = b;
			}
		}

		b->parent = p;
		b->left = a;
		b->right = c;
		
		a->parent = b;
		a->left = t0;
		a->right = t1;
		
		c->parent = b;
		c->left = t2;
		c->right = t3;

		if (t0 != NULL)	{
			t0->parent = a;
		}
		
		if (t1 != NULL)	{
			t1->parent = a;
		}
		
		if (t2 != NULL)	{
			t2->parent = c;
		}

		if (t3 != NULL) {
			t3->parent = c;
		}

		maxHeight = 0;

		if (a->left != NULL) {
			maxHeight = a->left->height;
		}

		if (a->right != NULL && maxHeight < a->right->height) {
			maxHeight = a->right->height;
		}

		a->height = maxHeight + 1;

		maxHeight = 0;

		if (c->left != NULL) {
			maxHeight = c->left->height;
		}

		if (c->right != NULL && maxHeight < c->right->height) {
			maxHeight = c->right->height;
		}

		c->height = maxHeight + 1;

		maxHeight = 0;

		if (b->left != NULL) {
			maxHeight = b->left->height;
		}

		if (b->right != NULL && maxHeight < b->right->height) {
			maxHeight = b->right->height;
		}

		b->height = maxHeight + 1;
		z = p;
	}
}

// Find a key in the dictionary and return corresponding record or NULL
DataType
AVLDictionary::findRecord( KeyType key)
{
        // Add your implementation here
	  AVLNode *e = root;
	
	while (e != NULL) {
		if (strcmp(e -> key, key) == 0)
			return e -> data;
		else if (strcmp(e -> key, key) < 0)
			e = e -> right;
		else
			e = e -> left;
	}
	return NULL;
}

// Removes one element from the dictionary
bool
AVLDictionary::removeElement(KeyType key)
{
	if (debug) {
		printf("------------------------------------\n");
		printf("removeElement(\"%s\")\n",  key);
		printf("---------- Before -----------------\n");
		printNode("", root, 0);
	}


	// Add your implementation here
	AVLNode *current = root;
	while (current != NULL)	{
		if (strcmp(current->key, key) == 0) 
			break;
		else if (strcmp(current->key, key) > 0) 
			current = current->left;
		else 
			current = current->right;
		
	}
	
	if (current == NULL) {
		return false;
	}

	AVLNode *parent = NULL;
	if (current != root)
		parent = current->parent;
	else
		current->left = current->right->parent;

	if (current->left == NULL && current->right == NULL) {
		if (current == parent->right) 
			parent->right = NULL;
		else 
			parent->left = NULL;
		
		delete current;
		restructure(parent);
	} else if (current->left == NULL) {
		if (current == parent->right) {
			parent->right = NULL;
			parent->right = current->right;
			parent->right->height = current->right->height;
			delete current;
			current = NULL;
			restructure(parent);
		} else {
			parent->left = NULL;
			parent->left = current->right;
			parent->left->height = current->right->height;
			restructure(parent);
			delete current;
			current = NULL;
		}

	} else if (current->right == NULL) {
		if (current == parent->right) {
			parent->right = NULL;
			parent->right = current->left;
			parent->right->height = current->left->height;
			restructure(parent);
			delete current;
			current = NULL;
			
		} else {
			parent->left = NULL;
			parent->left = current->left;
			parent->left->height = current->left->height;
			restructure(parent);
			delete current;
			current = NULL;
			
		}
	} else {
		AVLNode *preorder = current->left;

		while (preorder->right != NULL) {
			preorder = preorder->right;
		}

		current->key = preorder->key;
		current->data = preorder->data;
		
		current = preorder;

		if (current->left == NULL) {
			if (current->parent->right == current) {
				current->parent->right = current->right;
			} else {
				current->parent->left = current->right;
			}
		} else {
			if (current->parent->right == current) {
				current->parent->right = current->left;
			} else {
				current->parent->left = current->left;
			}
		}

		restructure(current->parent);
		delete current;
	}
	
	
	if (debug) {
		printf("---------- After -----------------\n");
		printNode("", root, 0);

		checkRecursive(root);
	}
	
	return true;
}

// Returns all the elements in the table as an array of strings.
// *n is the size of the table and it is returned by reference
KeyType *
AVLDictionary::keys(int * n)
{
	KeyType * a = (KeyType *) malloc(nElements * sizeof(KeyType));
	*n = 0;
	addKeysRecursive(root, a, n);

	return a;
}

// Add keys recursively
void
AVLDictionary::addKeysRecursive(AVLNode * node, KeyType * a, int * n) {
	if (node==NULL) {
		return;
	}
	
	a[*n] = node->key;
	(*n)++;
	addKeysRecursive(node->left, a, n);
	addKeysRecursive(node->right, a, n);
}

