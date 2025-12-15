#include <iostream>
#include <string>
#include <vector>

constexpr char splitter = '^';
constexpr char start = 'S';

int main() {
  std::size_t result = 0;

  // starting point
  std::string line;
  std::getline(std::cin, line);
  std::vector<bool> beams(line.length(), false);
  beams[line.find(start)] = true;

  // find splitters
  while (std::getline(std::cin, line)) {
    for (std::size_t i = 0; i < beams.size(); ++i) {
      if (beams[i] && line[i] == splitter) {
        beams[i] = false;
        if (i > 0) beams[i-1] = true;
        if (i < beams.size() - 1) beams[i+1] = true;
        result++;
      }
    }
  }

  std::cout << result << std::endl;
}
