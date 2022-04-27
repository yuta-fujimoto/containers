#include "test_common.hpp"

TEST_CASE("IS_INTEGRAL")
{
	// true case!!
	CHECK(ft::is_integral<int>::value);
	CHECK(ft::is_integral<char>::value);
	CHECK(ft::is_integral<unsigned int>::value);
	CHECK(ft::is_integral<wchar_t>::value);
	CHECK(ft::is_integral<short>::value);
	CHECK(ft::is_integral<int>::value);
	CHECK(ft::is_integral<long>::value);
	CHECK(ft::is_integral<const int>::value);
	CHECK(ft::is_integral<volatile const int>::value);

	// false case
	CHECK_FALSE(ft::is_integral<double>::value);
	CHECK_FALSE(ft::is_integral<float>::value);
	CHECK_FALSE(ft::is_integral<int&>::value);
}
