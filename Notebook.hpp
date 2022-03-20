#include "Direction.hpp"
#include <array>
#include <string>
#include <vector>

namespace ariel {

class Page {
public:
  Page() {}
  ~Page() {}

  void write(int, int, Direction, const std::string) {}
  void read(int, int, Direction, int) {}
  void earse(int, int, Direction, int) {}
  void show() {}

private:
  std::vector<std::array<char, 100>> data;
};

class Notebook {
public:
  Notebook() {}
  ~Notebook() {}

  void write(int, int, int, Direction, const std::string) {}
  std::string read(int, int, int, Direction, int) { return ""; }
  void erase(int, int, int, Direction, int) {}
  void show(int) {}

private:
  std::vector<Page> pages;
};

} // namespace ariel
