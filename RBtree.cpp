// #include "Rb_tree_iterator.hpp"
#include "RBtree.hpp"

int main()
{
	ft::RBtree<int, ft::pair<int, int>> T;

	for (int i = 0; i < 10; ++i)
		T.RBinsert(ft::pair<int, int>(i, i));
	// T.RBdelete(2);
	T.printTree();
	ft::_Rb_tree_iterator<ft::pair<int, int>> it = T._M_begin();
	std::cout << it->first << std::endl;
	while (it != T._M_end())
	{
		std::cout << "YES >> ";
		std::cout << it->first << std::endl;
		it++;
	}
	T.RBclear();
}
