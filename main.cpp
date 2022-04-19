#include <list>
#include <vector>
#include <iostream>
#include "containers_test/srcs/base.hpp"

#include "map.hpp"
// #define TESTED_NAMESPACE ft
#define TESTED_TYPE foo<int>
#define _pair TESTED_NAMESPACE::pair

#include "common.hpp"

#define T1 int
#define T2 foo<int>
typedef TESTED_NAMESPACE::map<T1, T2>::value_type T3;
typedef TESTED_NAMESPACE::map<T1, T2>::iterator ft_iterator;
typedef TESTED_NAMESPACE::map<T1, T2>::const_iterator ft_const_iterator;

static int iter = 0;

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

template <typename _T1, typename _T2>
void	printReverse(TESTED_NAMESPACE::map<_T1, _T2> &mp)
{
	typename TESTED_NAMESPACE::map<_T1, _T2>::iterator it = mp.end(), ite = mp.begin();

	std::cout << "printReverse:" << std::endl;
	while (it != ite) {
		it--;
		std::cout << "-> " << printPair(it, false) << std::endl;
	}
	std::cout << "_______________________________________________" << std::endl;
}


template <typename MAP>
void	ft_bound(MAP &mp, const T1 &param)
{
	ft_iterator ite = mp.end(), it[2];
	_pair<ft_iterator, ft_iterator> ft_range;

	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	std::cout << "with key [" << param << "]:" << std::endl;
	it[0] = mp.lower_bound(param); it[1] = mp.upper_bound(param);
	ft_range = mp.equal_range(param);
	std::cout << "lower_bound: " << (it[0] == ite ? "end()" : printPair(it[0], false)) << std::endl;
	std::cout << "upper_bound: " << (it[1] == ite ? "end()" : printPair(it[1], false)) << std::endl;
	std::cout << "equal_range: " << (ft_range.first == it[0] && ft_range.second == it[1]) << std::endl;
}

template <typename MAP>
void	ft_const_bound(const MAP &mp, const T1 &param)
{
	ft_const_iterator ite = mp.end(), it[2];
	_pair<ft_const_iterator, ft_const_iterator> ft_range;

	std::cout << "\t-- [" << iter++ << "] (const) --" << std::endl;
	std::cout << "with key [" << param << "]:" << std::endl;
	it[0] = mp.lower_bound(param); it[1] = mp.upper_bound(param);
	ft_range = mp.equal_range(param);
	std::cout << "lower_bound: " << (it[0] == ite ? "end()" : printPair(it[0], false)) << std::endl;
	std::cout << "upper_bound: " << (it[1] == ite ? "end()" : printPair(it[1], false)) << std::endl;
	std::cout << "equal_range: " << (ft_range.first == it[0] && ft_range.second == it[1]) << std::endl;
}

int		main(void)
{
	std::list<T3> lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(i + 1, (i + 1) * 3));
	TESTED_NAMESPACE::map<T1, T2> mp(lst.begin(), lst.end());
	// printSize(mp);

	ft_const_bound(mp, -10);
	ft_const_bound(mp, 1);
	ft_const_bound(mp, 5);
	ft_const_bound(mp, 10);
	ft_const_bound(mp, 50);

	// printSize(mp);

	mp.lower_bound(3)->second = 404;
	mp.upper_bound(7)->second = 842;
	ft_bound(mp, 5);
	ft_bound(mp, 7);

	// printSize(mp);
	return (0);
}
