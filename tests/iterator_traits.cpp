#include "test_common.hpp"

template <class Iterator>
typename ft::iterator_traits<Iterator>::value_type
sum(Iterator first, Iterator last)
{
    typedef typename ft::iterator_traits<Iterator>::value_type value_type;

    value_type result = value_type();
    for (; first != last; ++first) {
        result += *first;
    }
    return result;
}

TEST_CASE("ITERATOR_TRAITS")
{
    ft::vector<double> ft_v(3, 4);
    std::vector<double> v(3, 4);

	ft::vector<double>::const_iterator ft_ci = ft_v.begin();
	ft::vector<double>::const_iterator ft_ce = ft_v.end();
	CHECK_EQ(sum(ft_v.begin(), ft_v.end()), sum(v.begin(), v.end()));
	CHECK_EQ(sum(ft_ci, ft_ce), sum(v.begin(), v.end()));
	CHECK_EQ(sum(ft_v.rbegin(), ft_v.rend()), sum(v.rbegin(), v.rend()));

}
