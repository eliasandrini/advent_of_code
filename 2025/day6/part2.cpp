#include <iostream>
#include <numeric>
#include <string>
#include <vector>

int main() {
  std::vector<std::string> text;
  std::string input;

  while (std::getline(std::cin, input)) {
    // exit if we reach last line
    if (input.find_first_of("+*") != std::string::npos) break;

    text.push_back(input);
  }

  // find max length
  std::size_t length = 0;
  for (const auto& line : text) length = std::max(length, line.length());

  // parse input again and create vectors of numbers
  std::vector<std::vector<unsigned>> problems;
  unsigned counter = 0;

  for (unsigned i = 0; i < length; ++i) {
    // search vertically to find a number
    unsigned number = 0;
    bool numberFound = false;
    for (unsigned j = 0; j < text.size(); ++j) {
      // ensure no out of range
      if (i >= text[j].size()) continue;
      const char& c = text[j][i];
      if (c >= '0' && c <= '9') {
        number = number * 10 + c - '0';
        numberFound = true;
      }
    }

    // add number to problem or go to next problem if there is no number
    if (numberFound) {
      if (problems.size() <= counter) problems.emplace_back();
      problems[counter].push_back(number);
    } else {
      ++counter;
    }
  }

  // do operations
  std::size_t index = 0;
  std::size_t result = 0;
  for (const auto& prob : problems) {
    index = input.find_first_of("+*", index);
    switch (input[index]) {
    case '+':
      result += std::accumulate(prob.begin(), prob.end(), 0UL);
      break;
    case '*':
      result += std::accumulate(prob.begin(), prob.end(), 1UL, std::multiplies<>());
    default:
      break;
    }
    ++index;
  }

  std::cout << result << std::endl;
}
