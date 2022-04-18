#include "test_common.hpp"

template <typename _Tp>
bool ft_enable_if_test(_Tp t, typename ft::enable_if<ft::is_integral<_Tp>::value>::type* = 0) {
  return (true);
}

bool ft_enable_if_test(...) {
  return (false);
}

TEST_CASE("ENABLE_IF") {
  CHECK(ft_enable_if_test(10) == true);
  CHECK(ft_enable_if_test('K') == true);
  CHECK(ft_enable_if_test(2.3) == false);
  CHECK(ft_enable_if_test("HELLO") == false);
}
