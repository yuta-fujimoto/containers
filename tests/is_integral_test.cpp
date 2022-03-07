#include "test_common.hpp"

TEST_CASE("IS_INTEGRAL")
{
	bool a;

	// true case!!
	a = ft::is_integral<int>::value;
	CHECK_EQ(a, std::is_integral<int>::value);
	a = ft::is_integral<char>::value;
	CHECK_EQ(a, std::is_integral<char>::value);
	a = ft::is_integral<wchar_t>::value;
	CHECK_EQ(a, std::is_integral<wchar_t>::value);
	a = ft::is_integral<short>::value;
	CHECK_EQ(a, std::is_integral<short>::value);
	a = ft::is_integral<int>::value;
	CHECK_EQ(a, std::is_integral<int>::value);
	a = ft::is_integral<long>::value;
	CHECK_EQ(a, std::is_integral<long>::value);
	a = ft::is_integral<double>::value;
	CHECK_EQ(a, std::is_integral<double>::value);
	a = ft::is_integral<int&>::value;
	CHECK_EQ(a, std::is_integral<int&>::value);
	a = ft::is_integral<const int>::value;
	CHECK_EQ(a ,std::is_integral<const int>::value);
	a = ft::is_integral<volatile const int>::value;
	CHECK_EQ(a ,std::is_integral<volatile const int>::value);

	// false case
	a = ft::is_integral<double>::value;
	CHECK_EQ(a ,std::is_integral<double>::value);
	a = ft::is_integral<float>::value;
	CHECK_EQ(a ,std::is_integral<float>::value);
}
