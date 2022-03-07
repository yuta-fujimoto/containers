#include "test_common.hpp"

struct value {
  int x;
  value(int x = 0) : x(x) {}
  int get() const { return x; }
};

TEST_CASE("ITERATOR")
{
	SUBCASE("FORWARD") {
		// data
		std::vector<int> v(4, 5);
		ft::vector<int> ft_v(4, 5);

		std::vector<value> v2(3, 4);
		ft::vector<value> ft_v2(3, 4);

		// check all value
		std::vector<int>::iterator it = v.begin();
		std::vector<int>::iterator ite = v.end();

		ft::vector<int>::iterator ft_it = ft_v.begin();
		ft::vector<int>::iterator ft_ite = ft_v.end();
		while (it != ite) {
			CHECK_EQ(*it, *ft_it);
			++it;
			++ft_it;
		}

		// overwrite, - operation
		it = v.begin();
		ft_it = ft_v.begin();
		*(it + 3) = 12;
		*(ft_it + 3) = 12;
		it[2] = 18;
		ft_it[2] = 18;
		CHECK_EQ(it[2], ft_it[2]);
		CHECK_EQ(*(it + 3), *(ft_it + 3));
		CHECK_EQ(*(ite - 1), *(ft_ite - 1));

		// check substraction
		CHECK_EQ(v.end() - v.begin(), ft_v.end() - ft_v.begin());

		// operator ->
		ft::vector<value>::iterator ft_it2 = ft_v2.begin();
		std::vector<value>::iterator it2 = v2.begin();
		int x = ft_it2->x;
		int x_get = ft_it2->get();
		CHECK_EQ(it2->x, x);
		CHECK_EQ(it2->get(), x_get);

		// base
		// decltype(v)::iterator base = it.base(); error ?? 
		int* base = it.base();
		decltype(ft_v)::iterator ft_base = ft_it.base();
		CHECK_EQ(*base, *ft_base);
		++base;
		++ft_base;
		CHECK_EQ(*base, *ft_base);
	}

	SUBCASE("CONST FORWARD")
	{
		std::vector<int> v(4, 5);
		ft::vector<int> ft_v(4, 5);

		std::vector<value> v2(3, 4);
		ft::vector<value> ft_v2(3, 4);
	
		std::vector<int>::const_iterator cit = v.begin();
		std::vector<int>::const_iterator cite = v.end();

		ft::vector<int>::const_iterator ft_cit = ft_v.begin();
		ft::vector<int>::const_iterator ft_cite = ft_v.end();
		while (cit != cite) {
			CHECK_EQ(*cit, *ft_cit);
			++cit;
			++ft_cit;
		}

		// error case
		// *ft_cit = 21;
		// *cit = 21;

		// operator ->, []
		ft::vector<value>::const_iterator ft_cit2 = ft_v2.begin();
		std::vector<value>::const_iterator cit2 = v2.begin();
		CHECK_EQ(cit2[2].x, ft_cit2[2].x);
		int x = ft_cit2->x;
		int x_get = ft_cit2->get();
		CHECK_EQ(cit2->x, x);
		CHECK_EQ(cit2->get(), x_get);
	}

	SUBCASE("REVERSE")
	{
		// data
		std::vector<int> v(3, 4);
		ft::vector<int> ft_v(3, 4);

		std::vector<value> v2(3, 4);
		ft::vector<value> ft_v2(3, 4);

		// check all values
		std::vector<int>::reverse_iterator rib = v.rbegin();
		std::vector<int>::reverse_iterator rie = v.rend();

		ft::vector<int>::reverse_iterator ft_rib = ft_v.rbegin();
		ft::vector<int>::reverse_iterator ft_rie = ft_v.rend();

		for (std::vector<int>::reverse_iterator it(rib); it != rie; ++it, ++rib, ++ft_rib)
		{
			CHECK_EQ(*rib, *ft_rib);
		}

		// substraction
		rib = v.rbegin();
		ft_rib = ft_v.rbegin();
		CHECK_EQ(rie - rib, ft_rie - ft_rib);

		ft::vector<value>::reverse_iterator ft_it2 = ft_v2.rbegin();
		std::vector<value>::reverse_iterator it2 = v2.rbegin();
		CHECK_EQ((*(it2 + 2)).x, (*(ft_it2 + 2)).x);
		CHECK_EQ(it2[2].x, ft_it2[2].x);
		int x = ft_it2->x;
		int x_get = ft_it2->get();
		CHECK_EQ(it2->x, x);
		CHECK_EQ(it2->get(), x_get);

		// base member functions
		decltype(v)::iterator base = rie.base();
		decltype(ft_v)::iterator ft_base = ft_rie.base();
		CHECK_EQ(*base, *ft_base);
		++base;
		++ft_base;
		CHECK_EQ(*base, *ft_base);
	}

	SUBCASE("CONST REVERSE")
	{
		std::vector<int> v(4, 5);
		ft::vector<int> ft_v(4, 5);

		std::vector<value> v2(3, 4);
		ft::vector<value> ft_v2(3, 4);
	
		std::vector<int>::const_reverse_iterator cit = v.rbegin();
		std::vector<int>::const_reverse_iterator cite = v.rend();

		ft::vector<int>::const_reverse_iterator ft_cit = ft_v.rbegin();
		ft::vector<int>::const_reverse_iterator ft_cite = ft_v.rend();
		while (cit != cite) {
			CHECK_EQ(*cit, *ft_cit);
			++cit;
			++ft_cit;
		}

		// error case
		// *ft_cit = 21;
		// *cit = 21;

		// operator ->, []
		ft::vector<value>::const_reverse_iterator ft_cit2 = ft_v2.rbegin();
		std::vector<value>::const_reverse_iterator cit2 = v2.rbegin();
		CHECK_EQ(cit2[2].x, ft_cit2[2].x);
		int x = ft_cit2->x;
		int x_get = ft_cit2->get();
		CHECK_EQ(cit2->x, x);
		CHECK_EQ(cit2->get(), x_get);
	}
}
