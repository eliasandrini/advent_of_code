#include <iostream>
#include <string>

// problem data
int pos = 50;
constexpr int circle = 100;
unsigned int counter = 0;

int main() {
  std::string rotation;
  while (std::cin >> rotation) {
    const char dir = rotation.at(0);
    int number = std::stoi(rotation.substr(1, rotation.length() - 1));

    // number of full rotations
    counter += number / circle;
    number %= circle;

    if (dir == 'R') {
      // remaining rotations
      pos += number;
      if (pos >= circle) {
        counter++;
        pos -= circle;
      }
    } else {
      // remaining rotations
      pos -= number;
      if (pos <= 0) {
        // avoid counting 0 twice if the previous pos was 0
        if (pos != -number) counter++;
        if (pos < 0) pos += circle;
      }
    }
  }

  std::cout << counter << std::endl;
  return 0;
}
