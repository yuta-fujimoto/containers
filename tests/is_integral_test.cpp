#include "test_common.hpp"

TEST_CASE("IS_INTEGRAL")
{
	bool a;

	// true case!!
	a = ft::is_integral<int>::value;
	CHECK(a);
	a = ft::is_integral<char>::value;
	CHECK(a);
	a = ft::is_integral<wchar_t>::value;
	CHECK(a);
	a = ft::is_integral<short>::value;
	CHECK(a);
	a = ft::is_integral<int>::value;
	CHECK(a);
	a = ft::is_integral<long>::value;
	CHECK(a);
	a = ft::is_integral<const int>::value;
	CHECK(a);
	a = ft::is_integral<volatile const int>::value;
	CHECK(a);

	// false case
	a = ft::is_integral<double>::value;
	CHECK_FALSE(a);
	a = ft::is_integral<float>::value;
	CHECK_FALSE(a);
	a = ft::is_integral<int&>::value;
	CHECK_FALSE(a);
}
