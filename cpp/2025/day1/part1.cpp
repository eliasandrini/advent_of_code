#include <iostream>
#include <string>

int pos = 50;
constexpr int circle = 100;
unsigned int counter = 0;

int main() {
  std::string rotation;
  while (std::cin >> rotation) {
    const char dir = rotation.at(0);
    const int multiplier = dir == 'R' ? 1 : -1;
    const int number = std::stoi(rotation.substr(1, rotation.length() - 1));
    pos += multiplier * number;
    pos %= circle;
    if (pos == 0) counter++;
  }

  std::cout << counter << std::endl;
  return 0;
}
