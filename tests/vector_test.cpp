#include "cstdlib"
#include "ctime"
#include "test_common.hpp"

template <typename T>
void assign_random_value(ft::vector<T>& ft_v, std::vector<T>& v, std::size_t size) {
  int val;

  for (std::size_t i = 0; i < size; i++) {
    val = rand();
    ft_v.push_back(val);
    v.push_back(val);
  }
}

template <typename T>
void check_all_value(ft::vector<T>& ft_v, std::vector<T>& v)
{
  CHECK_EQ(ft_v.size(), v.size());
  CHECK_EQ(ft_v.capacity(), v.capacity());

  std::size_t s = ft_v.size();
  for (std::size_t i = 0; i < s; i++)
  {
    CHECK_EQ(ft_v[i], v[i]);
  }
}

struct value {
  int x;
  value(int x = 0) : x(x) {}
  int get() const { return x; }
  bool operator!=(value const& right) const { return (x != right.x); }
  bool operator==(value const& right) const { return (x == right.x); }
  bool operator>(value const& right) const { return (x > right.x); }
  bool operator<(value const& right) const { return (x < right.x); }
  bool operator>=(value const& right) const { return (x >= right.x); }
  bool operator<=(value const& right) const { return (x <= right.x); }
};

TEST_CASE("VECTOR") {
  srand(time(NULL));
  SUBCASE("WHOLE FUNCS AND VALUES") {
    std::vector<int> v;
    ft::vector<int> ft_v;

    CHECK_EQ(v.empty(), ft_v.empty());
    CHECK_EQ(v.capacity(), ft_v.capacity());
    CHECK_EQ(v.size(), ft_v.size());
    v.reserve(10);
    ft_v.reserve(10);
    CHECK_EQ(v.empty(), ft_v.empty());
    CHECK_EQ(v.capacity(), ft_v.capacity());
    CHECK_EQ(v.size(), ft_v.size());
    v.reserve(1);
    ft_v.reserve(1);
    CHECK_EQ(v.empty(), ft_v.empty());
    CHECK_EQ(v.capacity(), ft_v.capacity());
    CHECK_EQ(v.size(), ft_v.size());
    assign_random_value(ft_v, v, 3);
    CAPTURE(ft_v);
    check_all_value(ft_v, v);

    SUBCASE("EXCEPTION") {
      try {
        v.at(-1) = 12;
      } catch (std::out_of_range e) {
        std::cout << "STD" << std::endl;
        std::cout << e.what() << std::endl;
      }
      try {
        ft_v.at(-1) = 12;
      } catch (std::out_of_range e) {
        std::cout << "FT" << std::endl;
        std::cout << e.what() << std::endl;
      }
    }
    CHECK_EQ(v.front(), ft_v.front());
    CHECK_EQ(v.back(), ft_v.back());
    v.front() = -1;
    ft_v.front() = -1;
    CHECK_EQ(v.front(), ft_v.front());

    v.resize(2);
    ft_v.resize(2);
    CHECK_EQ(v.capacity(), ft_v.capacity());
    CHECK_EQ(v.size(), ft_v.size());
    v.resize(1000, 20);
    ft_v.resize(1000, 20);
    CHECK_EQ(v.capacity(), ft_v.capacity());
    CHECK_EQ(v.size(), ft_v.size());
    CHECK_EQ(v[999], ft_v[999]);
    CHECK_EQ(v[0], ft_v[0]);
  }
  SUBCASE("NOT INT") {
    ft::vector<value> ft_v(12, 4);
    std::vector<value> v(12, 4);

    CHECK_EQ(v.empty(), ft_v.empty());
    CHECK_EQ(v.capacity(), ft_v.capacity());
    CHECK_EQ(v.size(), ft_v.size());
    CHECK_EQ(v[0], ft_v[0]);
    CHECK_EQ(v[11], ft_v[11]);
    v.clear();
    ft_v.clear();
    CHECK_EQ(v.empty(), ft_v.empty());
    v.push_back(value(1));
    v.push_back(value(2));
    ft_v.push_back(value(1));
    ft_v.push_back(value(2));
    CHECK_EQ(v.empty(), ft_v.empty());
    CHECK_EQ(v.capacity(), ft_v.capacity());
    CHECK_EQ(v.size(), ft_v.size());
    CHECK_EQ(v[0], ft_v[0]);
  }
  SUBCASE("ASSIGNMATION OPEARATOR") {
    ft::vector<int> ft_v1;
    ft::vector<int> ft_v2;
    ft::vector<int> ft_v3;
    ft::vector<int> ft_test;
    std::vector<int> v1;
    std::vector<int> v2;
    std::vector<int> v3;
    std::vector<int> test;

    // capacity < right size
    assign_random_value(ft_v1, v1, 10);
    ft_test = ft_v1;
    test = v1;
    CAPTURE(ft_test);
    check_all_value(ft_test, test);
    // size > right size
    assign_random_value(ft_v2, v2, 4);
    ft_test = ft_v1;
    test = v1;
    CAPTURE(ft_test);
    check_all_value(ft_test, test);
    // size < right size < capacity
    assign_random_value(ft_v3, v3, 5);
    ft_test = ft_v1;
    test = v1;
    CAPTURE(ft_test);
    check_all_value(ft_test, test);
  }
}
