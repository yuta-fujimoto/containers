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

template <typename T>
void assign_random_value(ft::vector<T>& ft_v, std::vector<T>& v,
                         std::size_t size) {
  int val;

  for (std::size_t i = 0; i < size; i++) {
    ft_v.push_back(i);
    v.push_back(i);
  }
}

template <typename T>
void check_all_value(ft::vector<T>& ft_v, std::vector<T>& v) {
  CHECK_EQ(ft_v.size(), v.size());
  CHECK_EQ(ft_v.capacity(), v.capacity());

  std::size_t s = ft_v.size();
  for (std::size_t i = 0; i < s; i++) {
    INFO(i);
    CHECK_EQ(ft_v[i], v[i]);
  }
}

TEST_CASE("VECTOR") {
  // need to split into unit funcs
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
  SUBCASE("ASSIGNMATION OPEARATOR/COPY_CONSTRUCTOR") {
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
  SUBCASE("ASSIGN") {
    SUBCASE("ITERATOR") {
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

      // it works properly...
      ft_test.assign('f', 'g');
      test.assign('f', 'g');
      // ft_test.assign(1.23, 3.22);
      // test.assign(1.23, 3.22);
      check_all_value(ft_test, test);
    }
    SUBCASE("RANGE") {
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
  }
  SUBCASE("NUMERICAL LIMITS") {
    ft::vector<int> ft_test;
    std::vector<int> test;
    ft::vector<value> ft_test2;
    std::vector<value> test2;

    CHECK_EQ(ft_test.max_size(), test.max_size());
    CHECK_EQ(ft_test2.max_size(), test2.max_size());
  }
  SUBCASE("POP BACK") {
    // ft::vector<int> ft_test;
    // std::vector<int> test;
    ft::vector<int> ft_test2;
    std::vector<int> test2;

    // to avoid segv this will return error(ex: pop_back => reserve),
    // thus these tests don't carry out.
    // ft_test.pop_back();
    // test.pop_back();
    // CHECK_EQ(test.empty(), ft_test.empty());
    // CHECK_EQ(test.capacity(), ft_test.capacity());
    // CHECK_EQ(test.size(), ft_test.size());
    assign_random_value(ft_test2, test2, 2);
    ft_test2.pop_back();
    test2.pop_back();
    check_all_value(ft_test2, test2);
  }
  SUBCASE("INSERT-RANGE") {
    ft::vector<int> ft_test;
    ft::vector<int> ft_v1;
    ft::vector<int> ft_v2;
    std::vector<int> test;
    std::vector<int> v1;
    std::vector<int> v2;

    // assign_random_value(ft_v1, v1, 10);
    ft_test.insert(ft_test.begin(), 10, 10);
    test.insert(test.begin(), 10, 10);
    check_all_value(ft_test, test);

    ft_test.insert(ft_test.begin(), 20, 20);
    test.insert(test.begin(), 20, 20);
    check_all_value(ft_test, test);

    ft_test.insert(ft_test.end(), 1);
    test.insert(test.end(), 1);
    check_all_value(ft_test, test);

    ft_test.insert(ft_test.begin(), 1);
    test.insert(test.begin(), 1);
    check_all_value(ft_test, test);
  }
  SUBCASE("INSERT-INTERATOR") {
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
  SUBCASE("ERASE") {
    ft::vector<int> ft_test;
    std::vector<int> test;
    ft::vector<int>::iterator ft_it;
    std::vector<int>::iterator it;

    assign_random_value(ft_test, test, 10);
    ft_it = ft_test.erase(ft_test.begin());
    it = test.erase(test.begin());
    check_all_value(ft_test, test);
    CHECK_EQ(*ft_it, *it);

    ft_it = ft_test.erase(ft_test.begin() + 1, ft_test.begin() + 4);
    it = test.erase(test.begin() + 1, test.begin() + 4);
    check_all_value(ft_test, test);
    CHECK_EQ(*ft_it, *it);

    // segv
    // test.erase(test.end());
    // ft_test.erase(ft_test.end());
    // check_all_value(ft_test, test);

    ft_it = ft_test.erase(ft_test.end() - 1);
    it = test.erase(test.end() - 1);
    check_all_value(ft_test, test);
    CHECK_EQ(*ft_it, *it);

    ft_it = ft_test.erase(ft_test.begin(), ft_test.end() - 1);
    it = test.erase(test.begin(), test.end() - 1);
    check_all_value(ft_test, test);
    CHECK_EQ(*ft_it, *it);
  }
  SUBCASE("SWAP")
  {
    ft::vector<int> ft_test(5, 3);
    ft::vector<int> ft_test1(3, 5);
    std::vector<int> test(5, 3);
    std::vector<int> test1(3, 5);

    ft_test.swap(ft_test1);
    test.swap(test1);
    check_all_value(ft_test, test);
    check_all_value(ft_test1, test1);

    ft_test.swap(ft_test);
    test.swap(test);
    check_all_value(ft_test, test);
  }
  SUBCASE("GET_ALLOCATOR")
  {
    std::allocator<int> alloc;
    ft::vector<int> v(alloc);

    std::allocator<int> result = v.get_allocator();
    CHECK(result == alloc);
  }
}
