#include <iostream>
#include <string>
#include <algorithm>
#define BATTERIES 12

int main() {
  std::string line;
  unsigned long result = 0;

  while (std::cin >> line) {
    unsigned long max_joltage = 0;
    unsigned long prev_index = 0;
    for (int last_index = line.length() - BATTERIES; last_index < line.length(); last_index++) {
      std::string substr = line.substr(prev_index, last_index-prev_index+1);
      const std::string::iterator index = std::max_element(substr.begin(), substr.end());
      const int pos = index - substr.begin();

      max_joltage *= 10;
      max_joltage += substr[pos] - '0';
      prev_index += pos + 1;
    }

    result += max_joltage;
  }

  std::cout << result << std::endl;

  return 0;
}