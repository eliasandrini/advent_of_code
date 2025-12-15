#include <chrono>
#include <iostream>
#include <map>
#include <string>
#include <vector>

constexpr char splitter = '^';
constexpr char start = 'S';
std::size_t counter = 0;
std::size_t cache_hits = 0;

std::vector<std::vector<bool>> map;
std::map<std::pair<unsigned int, unsigned int>, std::size_t> cache;

void parse() {
  std::string line;

  while (std::getline(std::cin, line)) {
    if (line.find(splitter) == std::string::npos) continue;
    std::vector<bool> row(line.length(), false);

    for (std::size_t i = 0; i < line.length(); ++i)
      if (line[i] == splitter) row[i] = true;

    map.push_back(row);
  }
}


// dfs
std::size_t paths(const std::size_t pos, const std::size_t row) {
  counter++;
  // base case
  if (row >= map.size()) return 1;
  if (pos >= map[row].size()) return 0;

  if (cache.find({pos,row}) != cache.end()) {
    // cache hit
    cache_hits++;
    return cache[{pos,row}];
  }

  // splitting
  if (map[row][pos]) {
    const std::size_t output = paths(pos - 1, row + 1) + paths(pos + 1, row + 1);
    cache[{pos,row}] = output;
    return output;
  }

  // no splitting
  const std::size_t output = paths(pos, row + 1);
  cache[{pos,row}] = output;
  return output;
}


int main() {
  // starting point
  std::string line;
  std::getline(std::cin, line);
  const std::size_t pos = line.find(start);

  // find splitters
  parse();

  // find num paths
  // const auto timer = std::chrono::high_resolution_clock::now();
  const std::size_t result = paths(pos, 0);
  // const std::chrono::duration<double, std::milli> duration = std::chrono::high_resolution_clock::now() - timer;

  std::cout << result << std::endl;
  // std::cout << "counter: " << counter << std::endl;
  // std::cout << "cache_hits: " << cache_hits << std::endl;
  // std::cout << "duration: " << duration.count() << " milliseconds" << std::endl;
}
