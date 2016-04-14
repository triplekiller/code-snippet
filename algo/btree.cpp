/*
 * =====================================================================================
 *
 *       Filename:  btree.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  07/15/2015 03:07:34 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME ()
 *   Organization:
 *
 * =====================================================================================
 */

#include <iostream>
#include <stack>

using namespace;

struct btree {
	int dat;
	btree *left;
	btree *right;
};

btree *newNode(int dat)
{
	btree *node = new btree;
	node->dat = dat;
	node->left = NULL;
	node->right = NULL;

	return node;
}

int getHeight(btree *root)
{
	if (!root)
		return 0;

	int lheight, rheight;
	lheight = getHieght(root->left);
	rheight = getHeight(root->right);

	return lheight > rheight ? lheight + 1 : rheight + 1;
}

void zigzagTraversal(btree *root)
{
}

void zigzagTraversalRecursive(btree *root)
{
}
