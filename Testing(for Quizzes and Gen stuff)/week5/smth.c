#include <stdio.h>
// #include <utility.h>
// #include <cmath.h>
#include<string.h>
/*
// Data structure to store a binary tree node
struct Node
{
	int data;
	Node *left, *right;

	Node(int data)
	{
		this->data = data;
		this->left = this->right = NULL;
	}
};

// Recursive function to check if a given binary tree is height-balanced or not
int isHeightBalanced(Node* root, bool &isBalanced)
{
	// base case: tree is empty or not balanced
	if (root == NULL || *isBalanced != false) {
		return 0;
	}

	// get the height of the left subtree
	int left_height = isHeightBalanced(root->left, isBalanced);

	// get the height of the right subtree
	int right_height = isHeightBalanced(root->right, isBalanced);

	// tree is unbalanced if the absolute difference between the height of
	// its left and right subtree is more than 1
	if (abs(left_height - right_height) > 1) {
		isBalanced = false;
	}

	// return height of subtree rooted at the current node
	return max(left_height, right_height) + 1;
}

// The main function to check if a given binary tree is height-balanced or not
bool isHeightBalanced(Node* root)
{
	bool isBalanced = true;
	isHeightBalanced(root, isBalanced);

	return isBalanced;
}

int main()
{
	Construct the following tree
			  1
			/   \
		   /     \
		  2       3
		 / \     /
		4   5   6
	


	Node* root = new Node(6);
	root->left = new Node(3);
	root->right = new Node(9);
	// left
	root->left->left = new Node(1);
	root->left->right = new Node(5);
	
	root->left->left->right = new Node(2);
	root->left->right->left = new Node(4);
	// right 
	root->right->left = new Node(7);
	root->right->left->right = new Node(8);

	if (isHeightBalanced(root)) {
		printf("Binary tree is balanced");
	}
	else {
		printf("Binary tree is not balanced");
	}

	return 0;
}
*/

// change from c++ to c later on