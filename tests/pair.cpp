#include "test_common.hpp"

TEST_CASE("PAIR")
{
	std::pair<int, char> p1 = std::make_pair(1, 'y');
	ft::pair<int, char> ft_p1 = ft::make_pair(1, 'y');

	std::pair<int, char> p2 = std::make_pair(2, 'a');
	ft::pair<int, char> ft_p2 = ft::make_pair(2, 'a');

	CHECK_EQ(ft_p1.first, p1.first);
	CHECK_EQ(ft_p1.second, p1.second);
	// swap is since C++11
	// p1.swap(p2);
	// ft_p1.swap(ft_p2);
	// CHECK_EQ(ft_p1.first, p1.first);
	// CHECK_EQ(ft_p1.second, p1.second);
	CHECK_EQ(ft_p1 > ft_p2, p1 > p2);
	CHECK_EQ(ft_p1 < ft_p2, p1 < p2);
}
