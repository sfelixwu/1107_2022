
#include <iostream>
#include <vector>
// #include <algorithm>

using namespace std;

template <class InputIterator, class UnaryPredicate>
  typename iterator_traits<InputIterator>::difference_type
    count_if_ecs36b (InputIterator first, InputIterator last, UnaryPredicate pred)
{
  typename iterator_traits<InputIterator>::difference_type ret = 0;
  while (first!=last) {
    if (pred(*first)) ++ret;
    ++first;
  }
  return ret;
}

int main()
{
  // initialize vector of integers
  std::vector<int> nums = {1, 2, 3, 4, 5, 8, 10, 12};

  int even_count = count_if_ecs36b(nums.begin(), nums.end(), [](int num) {
    return num % 2 == 0;
  });

  std::cout << "There are " << even_count << " even numbers." << std::endl;
  return 0;
}
