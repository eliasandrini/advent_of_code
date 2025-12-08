#include <iostream>
#include <string>
#include <cmath>
#include <map>
#define MAX_POW 25

static unsigned long pow10arr[MAX_POW] = {};

void initialize() {
  constexpr unsigned int x = 10;
  pow10arr[0] = 1;
  for (unsigned int i = 1; i < MAX_POW; i++)
    pow10arr[i] = pow10arr[i - 1] * x;
}

unsigned long split_parts(unsigned long value, const unsigned short num_parts, const bool higher) {
  // split in equally divided parts
  unsigned long parts[num_parts];
  const unsigned digits = std::floor(std::log10(value)) + 1;
  const unsigned digits_per_part = digits / num_parts;
  // get all blocks
  for (int i = num_parts-1; i >= 0; i--) {
    parts[i] = value % pow10arr[digits_per_part];
    value /= pow10arr[digits_per_part];
  }

  // determine limit
  for (int i = num_parts - 2; i >= 0; i--) {
    if (higher) {
      if (parts[i] < parts[i+1]) parts[i]++;
    } else {
      if (parts[i] > parts[i+1]) parts[i]--;
    }
  }

  return parts[0];
}

unsigned long mirror_parts(unsigned long value, unsigned short num_parts) {
  const unsigned int digits = std::floor(std::log10(value)) + 1;
  const unsigned long power = pow10arr[digits];
  unsigned long output = 0;
  while (num_parts) {
    output += value;
    value *= power;
    num_parts--;
  }
  return output;
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

    const unsigned long first_value = std::stol(fnum);
    const unsigned long second_value = std::stol(snum);

    std::map<unsigned long, bool> invalid;

    // for every possible length
    for (unsigned total_digits = fnum.length(); total_digits <= snum.length(); total_digits++) {
      // for every possible partition
      for (unsigned parts = 2; parts <= total_digits; parts++) {
        if (total_digits % parts != 0) continue;

        // determine ranges based on current length compared to fnum and snum
        unsigned long lower_bound = pow10arr[total_digits/parts-1];
        if (total_digits == fnum.length()) {
          lower_bound = split_parts(first_value, parts, true);
        }
        unsigned long upper_bound = pow10arr[total_digits/parts] - 1;
        if (total_digits == snum.length()) {
          upper_bound = split_parts(second_value, parts, false);
        }

        if (lower_bound > upper_bound) continue;

        for (unsigned long i = lower_bound; i <= upper_bound; i++) {
          const unsigned long val = mirror_parts(i, parts);
          // check if already added
          const auto [_,added] = invalid.insert(std::pair(val, true));
          if (!added) continue;
          result += val;
        }
      }
    }
  }

  std::cout << result << std::endl;
  return 0;
}