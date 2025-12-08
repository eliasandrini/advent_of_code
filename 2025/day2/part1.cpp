#include <iostream>
#include <string>
#include <cmath>
#define MAX_POW 20

static unsigned long pow10arr[MAX_POW] = {};

void initialize() {
  constexpr unsigned int x = 10;
  pow10arr[0] = 1;
  for (unsigned int i = 1; i < MAX_POW; i++)
    pow10arr[i] = pow10arr[i - 1] * x;
}

inline unsigned long pow10(const unsigned long& i) {
  if (i < MAX_POW) return pow10arr[i];
  std::cout << "POWER OUT OF RANGE\n" << std::endl;
  return -1;
}

unsigned long split_half(const unsigned long& value, const bool higher) {
  const std::string start = std::to_string(value);
  const std::string fhalf1 = start.substr(0, start.length()/2);
  const std::string fhalf2 = start.substr(start.length()/2);
  unsigned long output = std::stol(fhalf1);
  const unsigned long fnum2 = std::stol(fhalf2);
  if (higher) {
    if (fnum2 > output) output++;
  } else {
    if (fnum2 < output) output--;
  }
  return output;
}

unsigned long mirror_parts(const unsigned long& value) {
  const unsigned int digits = std::floor(std::log10(value)) + 1;
  const unsigned long fhalf = value * pow10(digits);
  return fhalf + value;
}


int main() {
  std::string line;
  std::cin >> line;

  unsigned long curr = 0;
  unsigned long prev = 0;
  unsigned long result = 0;

  initialize();

  while (curr != std::string::npos) {
    prev = curr;
    if (prev > 0) prev++;
    curr = line.find(',', prev);
    const std::string range = line.substr(prev, curr-prev);

    // get the start and end of the range
    const std::string fnum = range.substr(0, range.find('-'));
    const std::string snum = range.substr(range.find('-') + 1, range.find(','));
    // std::cout << "fnum: " << fnum << " snum: " << snum << std::endl;

    // if the length is odd then they cannot be made of a string repeated twice
    if (fnum.length() == snum.length() && fnum.length() % 2 == 1) {
      // std::cout << "SKIPPED" << std::endl;
      continue;
    }
    // if the starting point is higher than the end point then skip
    unsigned long first_value = std::stol(fnum);
    unsigned long second_value = std::stol(snum);
    if (fnum.length() % 2 == 1) first_value = pow10(fnum.length());
    if (snum.length() % 2 == 1) second_value = pow10(snum.length()-1) - 1;

    // find even more strict ranges based on the halfs of fnum and snum
    const unsigned long starting_value = split_half(first_value, true);
    const unsigned long stop_value = split_half(second_value, false);
    if (starting_value > stop_value) {
      // std::cout << "SKIPPED" << std::endl;
      continue;
    }

    for (unsigned long i = starting_value; i <= stop_value; i++) {
      result += mirror_parts(i);
      // std::cout << "added: " << mirror_half(i) << std::endl;
    }

  }

  std::cout << result << std::endl;
  return 0;
}