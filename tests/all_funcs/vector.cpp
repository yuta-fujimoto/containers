#include "vector.hpp"

#include <vector>

#include "test_common.hpp"

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

template <typename _Tp>
void assign_random_value(ft::vector<_Tp>& ft_v, std::vector<_Tp>& v,
                         std::size_t size) {
  for (std::size_t i = 0; i < size; i++) {
    ft_v.push_back(i);
    v.push_back(i);
  }
}

template <typename _Tp>
void check_all_value(ft::vector<_Tp>& ft_v, std::vector<_Tp>& v) {
  CHECK_EQ(ft_v.size(), v.size());
  CHECK_EQ(ft_v.capacity(), v.capacity());

  std::size_t s = ft_v.size();
  for (std::size_t i = 0; i < s; i++) {
    INFO(i);
    CHECK_EQ(ft_v[i], v[i]);
  }
}

TEST_CASE("VECTOR") {
  TITLE("VECTOR");
  SUBTITLE("SIZE");
  SUBTITLE("CAPACITY");
  SUBTITLE("PUSH_BACK");
  std::vector<int> v;
  ft::vector<int> ft_v;

  CHECK_EQ(v.empty(), ft_v.empty());

  SUBTITLE("RESERVE");
  v.reserve(10);
  ft_v.reserve(10);
  CHECK_EQ(v.empty(), ft_v.empty());
  CHECK_EQ(v.capacity(), ft_v.capacity());
  CHECK_EQ(v.size(), ft_v.size());
  v.reserve(1);
  ft_v.reserve(1);
  CHECK_EQ(v.empty(), ft_v.empty());
  assign_random_value(ft_v, v, 3);
  check_all_value(ft_v, v);

  SUBTITLE("AT");
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

  SUBTITLE("FRONT");
  CHECK_EQ(v.front(), ft_v.front());
  CHECK_EQ(v.back(), ft_v.back());
  v.front() = -1;
  ft_v.front() = -1;
  CHECK_EQ(v.front(), ft_v.front());

  SUBTITLE("RESIZE");
  v.resize(2);
  ft_v.resize(2);
  CHECK_EQ(v.capacity(), ft_v.capacity());
  CHECK_EQ(v.size(), ft_v.size());
  v.resize(100, 20);
  ft_v.resize(100, 20);
  CHECK_EQ(v.capacity(), ft_v.capacity());
  CHECK_EQ(v.size(), ft_v.size());

  SUBTITLE("ASSIGNMATION OPEARATOR/COPY_CONSTRUCTOR");
  {
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
    check_all_value(ft_test, test);
    // size > right size (10 => 4!!)
    assign_random_value(ft_v2, v2, 4);
    ft_test = ft_v2;
    test = v2;
    check_all_value(ft_test, test);
    // size < right size < capacity (4 => 5)
    assign_random_value(ft_v3, v3, 5);
    ft_test = ft_v3;
    test = v3;
    check_all_value(ft_test, test);

    // copy constructor
    ft::vector<int> ft_copy_v(ft_test);
    std::vector<int> copy_v(test);

    check_all_value(ft_copy_v, copy_v);
  }
  SUBTITLE("ASSIGN-ITERATOR");
  {
    ft::vector<int> ft_v1;
    ft::vector<int> ft_v2;
    ft::vector<int> ft_test;
    std::vector<int> v1;
    std::vector<int> v2;
    std::vector<int> test;

    assign_random_value(ft_v1, v1, 14);
    ft_test.assign(ft_v1.begin(), ft_v1.end());
    test.assign(v1.begin(), v1.end());
    check_all_value(ft_test, test);

    assign_random_value(ft_v2, v2, 7);
    ft_test.assign(ft_v2.begin(), ft_v2.end());
    test.assign(v2.begin(), v2.end());
    check_all_value(ft_test, test);

    check_all_value(ft_test, test);
  }
  SUBTITLE("ASSIGN-RANGE");
  {
    ft::vector<int> ft_test;
    std::vector<int> test;
    const int value = 10;

    ft_test.assign(20, value);
    test.assign(20, value);
    check_all_value(ft_test, test);

    ft_test.assign(10, value);
    test.assign(10, value);
    check_all_value(ft_test, test);
  }
  SUBTITLE("NUMERICAL LIMITS");
  {
    ft::vector<int> ft_test;
    std::vector<int> test;
    ft::vector<value> ft_test2;
    std::vector<value> test2;

    CHECK_EQ(ft_test.max_size(), test.max_size());
    CHECK_EQ(ft_test2.max_size(), test2.max_size());
  }
  SUBTITLE("POP BACK");
  {
    ft::vector<int> ft_test;
    std::vector<int> test;

    assign_random_value(ft_test, test, 2);
    ft_test.pop_back();
    test.pop_back();
    check_all_value(ft_test, test);
  }
  SUBTITLE("INSERT-RANGE");
  {
    ft::vector<int> ft_test;
    ft::vector<int> ft_v1;
    ft::vector<int> ft_v2;
    ft::vector<int>::iterator ft_it;
    std::vector<int> test;
    std::vector<int> v1;
    std::vector<int> v2;
    std::vector<int>::iterator it;

    ft_test.insert(ft_test.begin(), 10, 10);
    test.insert(test.begin(), 10, 10);
    check_all_value(ft_test, test);

    ft_test.insert(ft_test.begin(), 20, 20);
    test.insert(test.begin(), 20, 20);
    check_all_value(ft_test, test);

    ft_it = ft_test.insert(ft_test.end(), 1);
    it = test.insert(test.end(), 1);
    check_all_value(ft_test, test);
    CHECK_EQ(*ft_it, *it);

    ft_it = ft_test.insert(ft_test.begin(), 1);
    it = test.insert(test.begin(), 1);
    check_all_value(ft_test, test);
    CHECK_EQ(*ft_it, *it);

    try {
      ft_test.insert(ft_test.begin(), ft_test.max_size() + 1, 3);
    } catch (const std::exception& e) {
      std::cout << "FT" << std::endl;
      std::cout << e.what() << std::endl;
    }
    try {
      test.insert(test.begin(), test.max_size() + 1, 3);
    } catch (const std::exception& e) {
      std::cout << "STD" << std::endl;
      std::cout << e.what() << std::endl;
    }
  }
  SUBTITLE("INSERT-ITERATOR");
  {
    ft::vector<int> ft_v1;
    ft::vector<int> ft_v2;
    ft::vector<int> ft_test;
    std::vector<int> v1;
    std::vector<int> v2;
    std::vector<int> test;

    assign_random_value(ft_v1, v1, 3);
    ft_test.insert(ft_test.begin(), ft_v1.begin(), ft_v1.end());
    test.insert(test.begin(), v1.begin(), v1.end());
    check_all_value(ft_test, test);

    assign_random_value(ft_v2, v2, 7);
    ft_test.insert(ft_test.begin(), ft_v2.begin(), ft_v2.end());
    test.insert(test.begin(), v2.begin(), v2.end());
    check_all_value(ft_test, test);

    ft_test.insert(ft_test.end(), ft_v2.begin(), ft_v2.end());
    test.insert(test.end(), v2.begin(), v2.end());
    check_all_value(ft_test, test);
  }

  SUBTITLE("ERASE");
  {
    ft::vector<int> ft_test;
    std::vector<int> test;
    ft::vector<int>::iterator ft_it;
    std::vector<int>::iterator it;

    assign_random_value(ft_test, test, 10);
    ft_it = ft_test.erase(ft_test.begin());
    it = test.erase(test.begin());
    check_all_value(ft_test, test);
    CHECK_EQ(*ft_it, *it);

    // iterator
    ft_it = ft_test.erase(ft_test.begin() + 1, ft_test.begin() + 4);
    it = test.erase(test.begin() + 1, test.begin() + 4);
    check_all_value(ft_test, test);
    CHECK_EQ(*ft_it, *it);

    // segv
    // test.erase(test.end());
    // ft_test.erase(ft_test.end());
    // check_all_value(ft_test, test);

    ft_it = ft_test.erase(ft_test.end() - 2);
    it = test.erase(test.end() - 2);
    check_all_value(ft_test, test);
    CHECK_EQ(*ft_it, *it);

    ft_it = ft_test.erase(ft_test.begin(), ft_test.end() - 2);
    it = test.erase(test.begin(), test.end() - 2);
    check_all_value(ft_test, test);
    CHECK_EQ(*ft_it, *it);
  }
  SUBTITLE("SWAP");
  {
    ft::vector<int> ft_test(5, 3);
    ft::vector<int> ft_test1(3, 5);
    std::vector<int> test(5, 3);
    std::vector<int> test1(3, 5);

    ft::swap(ft_test1, ft_test);
    std::swap(test, test1);
    check_all_value(ft_test, test);
    check_all_value(ft_test1, test1);

    ft_test.swap(ft_test);
    test.swap(test);
    check_all_value(ft_test, test);
  }
  SUBTITLE("GET_ALLOCATOR");
  {
    std::allocator<int> alloc;
    ft::vector<int> v(alloc);

    std::allocator<int> result = v.get_allocator();
    CHECK(result == alloc);
  }
  SUBTITLE("COMPARISON OPERATOR");
  {
    ft::vector<value> ft_v1;
    ft::vector<value> ft_v2;
    std::vector<value> v1;
    std::vector<value> v2;

    //  (0) vs (0)
    // COMPARE
    v1.push_back(value(0));
    v2.push_back(value(0));
    ft_v1.push_back(value(0));
    ft_v2.push_back(value(0));
    CHECK_EQ((v1 == v2), (ft_v1 == ft_v2));
    CHECK_EQ((ft_v1 != ft_v2), (v1 != v2));
    CHECK_EQ((ft_v1 > ft_v2), (v1 > v2));
    CHECK_EQ((ft_v1 < ft_v2), (v1 < v2));
    CHECK_EQ((ft_v1 >= ft_v2), (v1 >= v2));
    CHECK_EQ((ft_v1 <= ft_v2), (v1 <= v2));

    // (0, 1) vs (0)
    v1.push_back(value(1));
    ft_v1.push_back(value(1));
    CHECK_EQ((ft_v1 == ft_v2), (v1 == v2));
    CHECK_EQ((ft_v1 != ft_v2), (v1 != v2));
    CHECK_EQ((ft_v1 > ft_v2), (v1 > v2));
    CHECK_EQ((ft_v1 < ft_v2), (v1 < v2));
    CHECK_EQ((ft_v1 >= ft_v2), (v1 >= v2));
    CHECK_EQ((ft_v1 <= ft_v2), (v1 <= v2));

    //  (0, 1) vs (0, 2)
    ft_v2.push_back(value(2));
    v2.push_back(value(2));
    CHECK_EQ((ft_v1 == ft_v2), (v1 == v2));
    CHECK_EQ((ft_v1 != ft_v2), (v1 != v2));
    CHECK_EQ((ft_v1 > ft_v2), (v1 > v2));
    CHECK_EQ((ft_v1 < ft_v2), (v1 < v2));
    CHECK_EQ((ft_v1 >= ft_v2), (v1 >= v2));
    CHECK_EQ((ft_v1 <= ft_v2), (v1 <= v2));

    //  (0, 1, 1) vs (0, 2)
    ft_v1.push_back(value(1));
    v1.push_back(value(1));
    CHECK_EQ((ft_v1 == ft_v2), (v1 == v2));
    CHECK_EQ((ft_v1 != ft_v2), (v1 != v2));
    CHECK_EQ((ft_v1 > ft_v2), (v1 > v2));
    CHECK_EQ((ft_v1 < ft_v2), (v1 < v2));
    CHECK_EQ((ft_v1 >= ft_v2), (v1 >= v2));
    CHECK_EQ((ft_v1 <= ft_v2), (v1 <= v2));
  }
  SUBTITLE("NOT INT");
  {
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
    CHECK_EQ(v.max_size(), ft_v.max_size());
  }
  SUBTITLE("STRING");
  {
    ft::vector<std::string> ft_str_v;
    ft::vector<std::string> ft_str_v_copy;
    std::vector<std::string> str_v;
    std::vector<std::string> str_v_copy;

    ft_str_v.reserve(100);
    str_v.reserve(100);

    str_v_copy.push_back("HELLO");
    str_v_copy.push_back("HELLO");
    ft_str_v_copy.push_back("HELLO");
    ft_str_v_copy.push_back("HELLO");

    ft_str_v = ft_str_v_copy;
    str_v = str_v_copy;

    ft_str_v.insert(ft_str_v.begin(), ft_str_v_copy.begin(),
                    ft_str_v_copy.end());
    str_v.insert(str_v.begin(), str_v_copy.begin(), str_v_copy.end());

    ft_str_v.insert(ft_str_v.begin(), "HELLO");
    str_v.insert(str_v.begin(), "HELLO");

    size_t size = ft_str_v.size();
    for (size_t i = 0; i < size; ++i) {
      ft_str_v.erase(ft_str_v.begin());
      str_v.erase(str_v.begin());
    }
    check_all_value(ft_str_v, str_v);

    ft_str_v.assign(10, "HEE");
    str_v.assign(10, "HEE");
    check_all_value(ft_str_v, str_v);
  }
}
