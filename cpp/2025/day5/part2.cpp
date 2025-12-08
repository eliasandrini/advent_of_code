#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

std::vector<std::pair<unsigned long, unsigned long>> ranges;

// parse ONLY the ranges and return the first non-range
void parse_input() {
  std::string line;
  while (std::cin >> line) {

    const std::size_t index = line.find('-');
    // if there is no - then we parsed all the ranges
    if (index == std::string::npos) break;
    unsigned long first = std::stol(line.substr(0, index));
    unsigned long second = std::stol(line.substr(index + 1));
    ranges.push_back(std::make_pair(first, second));
  }

  // sort for ascending lower bound and descending upper bound (to reduce computations)
  std::sort(ranges.begin(), ranges.end(),
    [](const std::pair<unsigned long, unsigned long>& a, const std::pair<unsigned long, unsigned long>& b) {
    if (a.first < b.first) return true;
    if (a.first == b.first && a.second >= b.second) return true;
    return false;
  });
}

int main() {
  // parse the ranges
  parse_input();

  unsigned long result = 1;
  unsigned long curr = ranges.front().first;
  for (const auto&[lower, upper] : ranges) {
    if (upper <= curr) continue;
    if (lower > curr) {
      curr = lower;
      result++;
    }
    result += upper - curr;
    curr = upper;
  }

  std::cout << result << std::endl;

  return 0;
}
