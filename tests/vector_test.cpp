#include "test_common.hpp"

struct value {
  int x;
  value(int x = 0) : x(x) {}
  int get() const { return x; }
  bool operator!=(value const& right) const{ return (x != right.x); }
  bool operator==(value const& right) const{ return (x == right.x); }
  bool operator>(value const& right) const{ return (x > right.x); }
  bool operator<(value const& right) const{ return (x < right.x); }
  bool operator>=(value const& right) const{ return (x >= right.x); }
  bool operator<=(value const& right) const{ return (x <= right.x); }};

TEST_CASE("VECTOR") {
  SUBCASE("WHOLE FUNCS AND VALUES") {
    std::vector<int> v;
    ft::vector<int> ft_v;

    CHECK_EQ(v.empty(), ft_v.empty());
    CHECK_EQ(v.capacity(), ft_v.capacity());
    CHECK_EQ(v.size(), ft_v.size());
    v.reserve(1);
    ft_v.reserve(1);
    CHECK_EQ(v.empty(), ft_v.empty());
    CHECK_EQ(v.capacity(), ft_v.capacity());
    CHECK_EQ(v.size(), ft_v.size());
    v.reserve(10);
    ft_v.reserve(10);
    CHECK_EQ(v.empty(), ft_v.empty());
    CHECK_EQ(v.capacity(), ft_v.capacity());
    CHECK_EQ(v.size(), ft_v.size());
    v.push_back(42);
    v.push_back(21);
    v.push_back(7);
    ft_v.push_back(42);
    ft_v.push_back(21);
    ft_v.push_back(7);
    CHECK_EQ(v[0], ft_v[0]);
    CHECK_EQ(v[0], ft_v[0]);
    CHECK_EQ(v[1], ft_v[1]);

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
}
