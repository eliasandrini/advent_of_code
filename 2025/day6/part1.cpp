#include <iostream>
#include <numeric>
#include <string>
#include <vector>

int main() {
  std::vector<std::vector<unsigned long>> problems;
  std::string input;

  while (std::getline(std::cin, input)) {
    // exit if we reach last line
    if (input.find_first_of("+*") != std::string::npos) break;

    unsigned int counter = 0;
    std::size_t index = 0;
    while (true) {
      // find next number
      index = input.find_first_not_of(' ', index);
      if (index == std::string::npos) break;
      // ensure there are enough problems
      if (problems.size() <= counter) problems.emplace_back();
      // convert string into number
      std::size_t end = input.find_first_of(' ', index);
      if (end == std::string::npos) end = input.size();
      problems[counter].push_back(std::stol(input.substr(index, end - index)));
      counter++;
      index = end+1;
    }
  }

  // do operations based on the operand
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
    index++;
  }

  std::cout << result << std::endl;
}
