/**********************************************************
* AVL Tree Implementation file
*
*  ** riffed and modified heavily by Aaron Crandall - 2016
*  ** All implementation in header because of templating
*
**********************************************************/

#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <queue>
#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>  // rand
#include <time.h>    // time for srand
#include <math.h>

using namespace std;

template<class T>
class AVLNode {
public:
	// Default blank AVLNode constructor
	AVLNode() {
		left = right = NULL;
		height = 0;
	}

	// Constructor with provided element (data) and children
	AVLNode(const T& el, AVLNode *l = NULL, AVLNode *r = NULL) {
		key = el;
		left = l;
		right = r;
		height = 0;
	}

	T key;                  // Key to compare/insert on of type <T>
	AVLNode *left, *right;  // Children of this node
	int height;             // Height of this node in the tree
};

/*
* Main AVLTree class that stores AVLNode objects
*  -- REQUIRES: implementation of rotation functions
*  -- REQUIRES: implementation of node heights
*  -- REQUIRES: implementation of contains function
*  -- REQUIRES: implementation of remove function
*/
template<class T>
class AVLTree {
public:
	AVLTree() { root = NULL; }

	void insert(const T& key) { insert(root, key); }
	void printTree() { printTree(root); }
	bool contains(const T& key) { return(contains(root, key)); }
	void remove(const T& key) { remove(root, key); }
	void run();
private:
	AVLNode<T>* root;
	/************************************************
	* Function: void rightRotation(AVLNode<T>* & k2)
	* Created Data: 10/20/2016
	* Last Data: 10/25/2016
	************************************************/
	void rightRotation(AVLNode<T>* & k2)//totateWithLeftChild
	{
		AVLNode<T>* k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;
		k2->height = max(height(k2->left), height(k2->right)) + 1;
		k1->height = max(height(k1->left), k2->height) + 1;
		k2 = k1;
	}
	/************************************************
	* Function: void leftRotation(AVLNode<T>* & k1)
	* Created Data: 10/20/2016
	* Last Data: 10/25/2016
	************************************************/
	void leftRotation(AVLNode<T>* & k1)//totateWithRightChild
	{
		AVLNode<T>* k2 = k1->right;
		k1->right = k2->left;
		k2->left = k1;
		k1->height = max(height(k1->right), height(k1->left)) + 1;
		k2->height = max(height(k2->right), k1->height) + 1;
		k1 = k2;
	}
	/************************************************
	* Function: void DoubleWithLeftChild(AVLNode<T>* &k3)
	* Created Data: 10/20/2016
	* Last Data: 10/25/2016
	************************************************/
	void DoubleWithLeftChild(AVLNode<T>* &k3)
	{
		leftRotation(k3->left);
		rightRotation(k3);
	}
	/************************************************
	* Function: void DoubleWithRightChild(AVLNode<T>* &k1)
	* Created Data: 10/20/2016
	* Last Data: 10/25/2016
	************************************************/
	void DoubleWithRightChild(AVLNode<T>* &k1)
	{
		rightRotation(k1->right);
		leftRotation(k1);
	}
	/************************************************
	* Function: int height(AVLNode<T>* node) const
	* Created Data: 10/20/2016
	* Last Data: 10/25/2016
	************************************************/
	int height(AVLNode<T>* node) const
	{
		return node == NULL ? -1 : node->height;
	}

	/*
	*  Insert function needs updating!
	*  This function needs to update heights as it returns from recursive insert.
	*  If the heights of a node are more than 2 different, rotate to fix
	*  After fixing, repair the heights of all nodes in the rotated tree
	*/
	/************************************************
	* Function: void insert(AVLNode<T>* &node, const T& key)
	* Created Data: 10/20/2016
	* Last Data: 10/25/2016
	************************************************/
	void insert(AVLNode<T>* &node, const T& key) {
		if (node == NULL) {
			node = new AVLNode<T>(key, NULL, NULL);
		}
		else if (key > node->key) {
			insert(node->right, key);
		}
		else {
			insert(node->left, key);
		}
		balance(node);
	}
	/************************************************
	* Function: void balance(AVLNode<T>* &t)
	* Created Data: 10/20/2016
	* Last Data: 10/25/2016
	************************************************/
	void balance(AVLNode<T>* &t)
	{
		if (t == NULL) return;
		if (height(t->left) - height(t->right) > 1)
			if (height(t->left->left) >= height(t->left->right))
				rightRotation(t);
			else
				DoubleWithLeftChild(t);
		else
			if (height(t->right) - height(t->left) > 1)
				if(height(t->right->right) >= height(t->right->left))
					leftRotation(t);
				else
					DoubleWithRightChild(t);
		t->height = max(height(t->left), height(t->right)) + 1;
	}
	/************************************************
	* Function: bool contains(AVLNode<T>* root, const T& key)
	* Created Data: 10/20/2016
	* Last Data: 10/25/2016
	************************************************/
	bool contains(AVLNode<T>* root, const T& key) {
		if (root == NULL)
			return false;
		if (root->key > key)
			return contains(root->left, key);
		else if (root->key < key)
			return contains(root->right, key);
		else
			return true;
	}
	/************************************************
	* Function: 	void remove(AVLNode<T>* &root, const T& key)
	* Created Data: 10/20/2016
	* Last Data: 10/25/2016
	************************************************/
	void remove(AVLNode<T>* &root, const T& key) {
		if (root == NULL) return;
		if (key < root->key)
			remove(root->left, key);
		else if (key > root->key)
			remove(root->right, key);
		else if(root->left&&root->right)
		{
			root->key = findMin(root->right)->key;
			remove(root->right, root->key);
		}
		else
		{
			AVLNode<T> *oldNode = root;
			root = (root->left != NULL) ? root->left : root->right;
			delete oldNode;
		}
		balance(root);
	}
	/************************************************
	* Function: AVLNode<T> * findMin(AVLNode<T>* t) const
	* Created Data: 10/20/2016
	* Last Data: 10/25/2016
	************************************************/
	AVLNode<T> * findMin(AVLNode<T>* t) const
	{
		if (t == NULL)
			return NULL;
		if (t->left == NULL)
			return t;
		return findMin(t->left);
	}

	// Should do a level order printout with actual depth (no alignment)
	/************************************************
	* Function: void printTree(AVLNode<T>* node)
	* Created Data: 10/20/2016
	* Last Data: 10/25/2016
	************************************************/
	void printTree(AVLNode<T>* node) {
		queue<AVLNode<T>*> bufQueue;
		int curr_height = node->height;
		int i = 1, j = 1;
		bufQueue.push(node);
		while (!bufQueue.empty()) {
			AVLNode<T>* curr = bufQueue.front();
			if (curr->left != NULL) { bufQueue.push(curr->left); }
			if (curr->right != NULL) { bufQueue.push(curr->right); }
			/****************************************************************************************************/
			//Use 2s'power to print endl; hwoever, There is a bug, when the end of the tree is not increase by 2s'power.
			if (i == pow(2, j)) {
				cout << endl;
				j++;
			}
			i++;
			/****************************************************************************************************/
			//original code
			/*if (curr->height < curr_height) {
				cout << endl;
				curr_height = curr->height;
			}*/
			cout << curr->key << " ";
			bufQueue.pop();
		}
		cout << endl;
	}
	// end private
};
template<class T>
inline void AVLTree<T>::run()
{
	AVLTree<int> myTree;
	cout << "Sample series of inserts. Will do all 4 cases of rotates." << endl
		<< "printTree has been changed and commented" << endl << endl << "===myTree===" << endl;
	myTree.insert(20);
	myTree.insert(10);
	myTree.insert(5);
	myTree.insert(30);
	myTree.insert(40);
	myTree.insert(15);
	myTree.insert(18);
	myTree.insert(13);
	myTree.insert(4);
	myTree.insert(19);
	myTree.printTree();

	if (myTree.contains(15)) {
		cout << "Tree contains 15" << endl;
	}

	else {
		cout << "Tree does not contain 15" << endl;
	}

	myTree.remove(15);

	if (myTree.contains(15)) {
		cout << "Tree contains 15" << endl;
	}
	else {
		cout << "Tree does not contain 15" << endl;
	}
	cout << endl << "===Big tree===" <<endl;
	/* BIGGER test of your AVL tree! */
	vector<int> incVals;
	AVLTree<int> bigTree;
	srand(time(NULL));
	for (int i = 0; i < 300; i++) {
		int newVal = rand() % 900;        // Generate new integer to insert into tree
		bool skip = false;
		for (unsigned int j = 0; j < incVals.size(); j++) { // Very dumb search!
			if (incVals[j] == newVal) {
				skip = true;
				j = incVals.size();
			}
		}

		if (!skip) {
			bigTree.insert(newVal);
			incVals.push_back(newVal);
		}

		if (i % 3 == 0) {   // Delete a random element every 3 inserts
			int remIndex = rand() % incVals.size();
			bigTree.remove(incVals[remIndex]);
			incVals.erase(incVals.begin() + remIndex);
		}

	}

	bigTree.printTree();

}

#endif

