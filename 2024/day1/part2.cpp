#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <vector>

int main() {

  std::vector<unsigned> list;
  std::unordered_map<unsigned, unsigned short> map;
  unsigned a, b;
  unsigned result = 0;

  while (std::cin >> a >> b) {
    list.push_back(a);
    if (map.count(b)) {
      map[b]++;
    } else {
      map[b] = 1;
    }
  }

  for (const auto &val : list) {
    const unsigned score = map.count(val) ? val * map[val] : 0;
    result += score;
  }

  std::cout << result << std::endl;

  return 0;
}
