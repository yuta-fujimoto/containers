#include "test_common.hpp"

bool compare_test(ft::vector<int>& ft_v1, ft::vector<int>& ft_v2,
                  std::vector<int>& v1, std::vector<int>& v2) {
  const bool ft_lexi_comp = ft::lexicographical_compare(ft_v1.begin(), ft_v1.end(),
                                                 ft_v2.begin(), ft_v2.end());
  const bool std_lexi_comp =
      std::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end());

  const bool ft_equal = ft::equal(ft_v1.begin(), ft_v1.end(), ft_v2.begin(), std::less<int>());
  const bool std_equal = std::equal(v1.begin(), v1.end(), v2.begin(), std::less<int>());
  return ((ft_lexi_comp == std_lexi_comp) && (ft_equal == std_equal));
}

TEST_CASE("lexicographical_compare/equal") {
  ft::vector<int> ft_v1;
  ft::vector<int> ft_v2;
  std::vector<int> v1;
  std::vector<int> v2;

  // empty vs empty
  CHECK(compare_test(ft_v1, ft_v2, v1, v2));

  // (1) vs (1)
  ft_v1.push_back(1);
  ft_v2.push_back(1);
  v1.push_back(1);
  v2.push_back(1);
  CHECK(compare_test(ft_v1, ft_v2, v1, v2));

  // (1) vs (1, 1, 1)
  ft_v2.push_back(1);
  ft_v2.push_back(1);
  v2.push_back(1);
  v2.push_back(1);
  CHECK(compare_test(ft_v1, ft_v2, v1, v2));

  // (1, 2) vs (1, 1, 1)
  ft_v1.push_back(2);
  v1.push_back(2);
  CHECK(compare_test(ft_v1, ft_v2, v1, v2));

  // (1, 2, -1) vs (1, 1, 1)
  ft_v1.push_back(-1);
  v1.push_back(-1);
  CHECK(compare_test(ft_v1, ft_v2, v1, v2));
}
