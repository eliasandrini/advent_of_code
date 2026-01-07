#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>

int main() {

  std::vector<int> list1, list2;
  int a, b;
  unsigned result = 0;

  while (std::cin >> a >> b) {
    list1.push_back(a);
    list2.push_back(b);
  }

  assert(list1.size() == list2.size());
  std::sort(list1.begin(), list1.end());
  std::sort(list2.begin(), list2.end());

  for (auto i{0ul}; i < list1.size(); ++i) {
    const auto diff = std::abs(list1[i] - list2[i]);
    result += diff;
  }

  std::cout << result << std::endl;

  return 0;
}
