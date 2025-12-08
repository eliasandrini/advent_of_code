#include <iostream>
#include <string>
#include <algorithm>

int main() {
  std::string line;
  unsigned long result = 0;

  while (std::cin >> line) {
    // find highest in n-1 numbers
    auto substr = line.substr(0, line.length()-1);
    const __gnu_cxx::__normal_iterator<char *, std::string> index = std::max_element(substr.begin(), substr.end());

    // find the max in the remaining values
    auto substr2 = line.substr((index-substr.begin())+1);
    const char second = *std::max_element(substr2.begin(), substr2.end());

    // get numbers
    const auto first = substr[(index-substr.begin())];
    const auto val1 = first - '0';
    const auto val2 = second - '0';

    const unsigned max_joltage = val1 * 10 + val2;
    result += max_joltage;
  }

  std::cout << result << std::endl;

  return 0;
}