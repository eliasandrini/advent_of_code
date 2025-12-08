#include <iostream>
#include <string>
#include <vector>
#define NUM_DIR 8
#define MAX_ADJ 4

// custom operator for QOL
std::pair<short, short> operator+(const std::pair<short, short>& lhs, const std::pair<short, short>& rhs) {
  return std::make_pair(lhs.first + rhs.first, lhs.second + rhs.second);
}

// preload directions
static const std::pair<short, short> directions[NUM_DIR] = {
  {-1, -1},
  {-1, 0},
  {-1, 1},
  {0, -1},
  {0, 1},
  {1, -1},
  {1, 0},
  {1, 1}
};

// -- GLOBAL GRID --
std::vector<std::vector<bool>> grid;

// -- INPUT PARSING --
void parse_input() {
  std::string line;
  unsigned short row = 0;
  while (std::cin >> line) {
    std::vector<bool> curr;
    curr.reserve(line.length());
    for (const char& val : line) curr.push_back(val != '.');
    grid.push_back(curr);
    row++;
  }
}

// -- BOUND CHECKING --
inline bool inside(const std::pair<short, short>& pos) {
  return pos.first >= 0 && pos.second >= 0 && pos.first < grid.size() && pos.second < grid[0].size();
}

void print() {
  for (const auto & i : grid) {
    for (const bool& j : i) std::cout << j;
    std::cout << std::endl;
  }
}


int main() {
  parse_input();

  // iterate through all positions and check surroundings
  unsigned long result = 0;
  for (unsigned int row = 0; row < grid.size(); ++row) {
    for (unsigned int col = 0; col < grid[row].size(); ++col) {
      // check if there is a roll of paper
      if (!grid[row][col]) continue;

      // count surrounding rolls of paper
      unsigned short counter = 0;
      // check every direction
      for (const auto&[x, y] : directions) {
        const std::pair<short, short> pos = std::make_pair(row + y, col + x);
        if (!inside(pos)) continue;
        if (grid[pos.first][pos.second]) counter++;
        if (counter >= MAX_ADJ) break;
      }

      if (counter < MAX_ADJ) result++;
    }
  }

  std::cout << result << std::endl;
  return 0;
}
