
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
  // initialize vector of integers
  std::vector<int> nums = {1, 2, 3, 4, 5, 8, 10, 12};

  int even_count = count_if(nums.begin(), nums.end(),

			    [](int num) { return num % 2 == 0;}
			    
			   );

  std::cout << "There are " << even_count << " even numbers." << std::endl;
  return 0;
}
