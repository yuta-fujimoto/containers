#include "stack.hpp"

#include <stack>

#include "test_common.hpp"

template <typename _Tp>
void stack_check_all_value(ft::stack<_Tp> ft_st, std::stack<_Tp> st) {
  CHECK_EQ(ft_st.size(), st.size());
  for (; !ft_st.empty(); ft_st.pop(), st.pop()) {
    CHECK_EQ(ft_st.top(), st.top());
  }
  CHECK_EQ(ft_st.empty(), st.empty());
}

TEST_CASE("STACK") {
  TITLE("STACK");
  SUBTITLE("STACK");
  SUBTITLE("SIZE");
  SUBTITLE("EMPTY");
  SUBTITLE("POP");
  SUBTITLE("TOP");

  std::stack<char> test;
  ft::stack<char> ft_test;

  SUBTITLE("PUSH");
  test.push('a');
  ft_test.push('a');

  test.push('b');
  ft_test.push('b');

  test.push('c');
  ft_test.push('c');

  test.top() = 'd';
  ft_test.top() = 'd';

  stack_check_all_value(ft_test, test);

  SUBTITLE("CONSTRUCTOR");
  std::stack<char> con(test);
  ft::stack<char> ft_con(ft_test);

  stack_check_all_value(ft_con, con);

  SUBTITLE("ASSIGNATION OPERATOR");
  std::stack<char> assign;
  ft::stack<char> ft_assign;

  assign = test;
  ft_assign = ft_test;

  stack_check_all_value(ft_assign, assign);

  SUBTITLE("COMPARISON OPERATOR");
  std::stack<char> comp1;
  std::stack<char> comp2;
  ft::stack<char> ft_comp1;
  ft::stack<char> ft_comp2;

  CHECK_EQ((comp1 == comp2), (ft_comp1 == ft_comp2));
  CHECK_EQ((comp1 != comp2), (ft_comp1 != ft_comp2));
  CHECK_EQ((comp1 < comp2), (ft_comp1 < ft_comp2));
  CHECK_EQ((comp1 <= comp2), (ft_comp1 <= ft_comp2));
  CHECK_EQ((comp1 > comp2), (ft_comp1 > ft_comp2));
  CHECK_EQ((comp1 >= comp2), (ft_comp1 >= ft_comp2));

  comp1.push('a');
  ft_comp1.push('a');
  comp2.push('b');
  ft_comp2.push('b');

  CHECK_EQ((comp1 == comp2), (ft_comp1 == ft_comp2));
  CHECK_EQ((comp1 != comp2), (ft_comp1 != ft_comp2));
  CHECK_EQ((comp1 < comp2), (ft_comp1 < ft_comp2));
  CHECK_EQ((comp1 <= comp2), (ft_comp1 <= ft_comp2));
  CHECK_EQ((comp1 > comp2), (ft_comp1 > ft_comp2));
  CHECK_EQ((comp1 >= comp2), (ft_comp1 >= ft_comp2));
}
