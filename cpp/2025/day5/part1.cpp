#include <iostream>
#include <vector>
#include <string>

std::vector<std::pair<unsigned long, unsigned long>> ranges;

// parse ONLY the ranges and return the first non-range
unsigned long parse_input() {
  std::string line;
  while (std::cin >> line) {

    const std::size_t index = line.find('-');
    // if there is no - then we parsed all the ranges
    if (index == std::string::npos) break;
    unsigned long first = std::stol(line.substr(0, index));
    unsigned long second = std::stol(line.substr(index + 1));
    ranges.push_back(std::make_pair(first, second));
  }

  return std::stol(line);
}

int main() {
  // parse the ranges
  unsigned long input = parse_input();

  unsigned long result = 0;
  do {
    for (const auto&[lower, upper] : ranges) {
      if (input >= lower && input <= upper) {
        result++;
        break;
      }
    }
  } while (std::cin >> input);

  std::cout << result << std::endl;

  return 0;
}
