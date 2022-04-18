#include <list>
#include "vector.hpp"
#include <vector>
#define TESTED_TYPE int
int		main(void)
{
	std::list<TESTED_TYPE> lst;
	std::list<TESTED_TYPE>::iterator lst_it;
	for (int i = 1; i < 5; ++i)
		lst.push_back(i * 3);

	ft::vector<TESTED_TYPE> vct(lst.begin(), lst.end());
	// printSize(vct);

	lst_it = lst.begin();
	for (int i = 1; lst_it != lst.end(); ++i)
		*lst_it++ = i * 5;
	vct.assign(lst.begin(), lst.end());
	// printSize(vct);

	vct.insert(vct.end(), lst.rbegin(), lst.rend());
	// printSize(vct);
	return (0);
}
