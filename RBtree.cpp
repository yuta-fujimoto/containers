#include "RBtree.hpp"

void printNode(RBnode *N, int level)
{
	for (int i = 0; i < level; ++i)
		std::cout << '\t';
	if (N->color == RED)
		std::cout << "\033[31m" << N->key << "\033[0m" << std::endl;
	else
		std::cout << N->key << std::endl;
}

void printTree(RBnode *N, int level)
{
	if (!N)
		return ;
	printTree(N->left, level + 1);
	printNode(N, level);
	printTree(N->right, level + 1);
}

int main()
{
	RBtree T;

	for (int i = 0; i < 10; ++i)
		RBinsert(&T, newRBnode(i));
	RBdelete(&T, 8);
	printTree(T.root, 0);
	RBclear(T.root);
}
