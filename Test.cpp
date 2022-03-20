#include "Direction.hpp"
#include "Notebook.hpp"
#include "doctest.h"

TEST_CASE("Bad input") {
  ariel::Notebook notebook;
  CHECK_THROWS(notebook.write(-1, 1, 0, ariel::Direction::Horizontal, "test"));
  CHECK_THROWS(notebook.write(1, -1, 0, ariel::Direction::Horizontal, "test"));
  CHECK_THROWS(notebook.write(1, 1, -1, ariel::Direction::Horizontal, "test"));
  CHECK_THROWS(notebook.write(1, -1, 99, ariel::Direction::Horizontal, "test"));

  CHECK_THROWS(notebook.write(-1, 1, 0, ariel::Direction::Vertical, "test"));
  CHECK_THROWS(notebook.write(1, 1, -1, ariel::Direction::Vertical, "test"));
  CHECK_THROWS(notebook.write(1, -1, 0, ariel::Direction::Vertical, "test"));

  CHECK_THROWS(notebook.read(-1, 1, 0, ariel::Direction::Horizontal, 1));
  CHECK_THROWS(notebook.read(1, -1, 0, ariel::Direction::Horizontal, 1));
  CHECK_THROWS(notebook.read(1, 1, -1, ariel::Direction::Horizontal, 1));
  CHECK_THROWS(notebook.read(1, 1, 1, ariel::Direction::Horizontal, -1));

  CHECK_THROWS(notebook.read(-1, 1, 0, ariel::Direction::Vertical, 1));
  CHECK_THROWS(notebook.read(1, 1, -1, ariel::Direction::Vertical, 1));
  CHECK_THROWS(notebook.read(1, -1, 0, ariel::Direction::Vertical, 1));
  CHECK_THROWS(notebook.read(1, 1, 1, ariel::Direction::Vertical, -1));

  CHECK_THROWS(notebook.erase(-1, 1, 0, ariel::Direction::Horizontal, 1));
  CHECK_THROWS(notebook.erase(1, -1, 0, ariel::Direction::Horizontal, 1));
  CHECK_THROWS(notebook.erase(1, 1, -1, ariel::Direction::Horizontal, 1));
  CHECK_THROWS(notebook.erase(1, 1, 1, ariel::Direction::Horizontal, -1));

  CHECK_THROWS(notebook.erase(-1, 1, 0, ariel::Direction::Vertical, 1));
  CHECK_THROWS(notebook.erase(1, 1, -1, ariel::Direction::Vertical, 1));
  CHECK_THROWS(notebook.erase(1, -1, 0, ariel::Direction::Vertical, 1));
  CHECK_THROWS(notebook.erase(1, 1, 1, ariel::Direction::Vertical, -1));
}

TEST_CASE("Good input") {
  ariel::Notebook notebook;
  CHECK_NOTHROW(notebook.write(1, 1, 0, ariel::Direction::Horizontal, "test"));
  CHECK_NOTHROW(notebook.write(1, 1, 0, ariel::Direction::Horizontal, "test"));
  CHECK_NOTHROW(notebook.write(1, 1, 1, ariel::Direction::Horizontal, "test"));

  CHECK_NOTHROW(notebook.write(1, 1, 0, ariel::Direction::Vertical, "test"));
  CHECK_NOTHROW(notebook.write(1, 1, 1, ariel::Direction::Vertical, "test"));
  CHECK_NOTHROW(notebook.write(1, 1, 0, ariel::Direction::Vertical, "test"));
  CHECK_NOTHROW(notebook.write(1, 1, 0, ariel::Direction::Vertical, "test"));
}

TEST_CASE("Usage test") {
  ariel::Notebook notebook;
  SUBCASE("write") {
    notebook.write(0, 100, 0, ariel::Direction::Horizontal, "abcds");
    CHECK_THROWS(
        notebook.write(0, 100, 0, ariel::Direction::Horizontal, "abcds"));
  }

  SUBCASE("read") {
    CHECK(notebook.read(0, 0, 0, ariel::Direction::Horizontal, 5) == "_____");
    notebook.write(0, 0, 0, ariel::Direction::Horizontal, "test1");
    CHECK(notebook.read(0, 0, 0, ariel::Direction::Horizontal, 5) == "test1");
  }

  SUBCASE("erase") {
    CHECK(notebook.read(0, 0, 0, ariel::Direction::Horizontal, 5) == "_____");
    notebook.write(0, 0, 0, ariel::Direction::Horizontal, "test1");
    CHECK(notebook.read(0, 0, 0, ariel::Direction::Horizontal, 5) == "test1");
    notebook.erase(0, 0, 0, ariel::Direction::Horizontal, 5);
    CHECK(notebook.read(0, 0, 0, ariel::Direction::Horizontal, 5) == "~~~~~");

    CHECK(notebook.read(1, 0, 0, ariel::Direction::Vertical, 5) == "_____");
    notebook.write(1, 0, 0, ariel::Direction::Vertical, "test1");
    CHECK(notebook.read(1, 0, 0, ariel::Direction::Vertical, 5) == "test1");
    notebook.erase(1, 0, 0, ariel::Direction::Vertical, 5);
    CHECK(notebook.read(1, 0, 0, ariel::Direction::Vertical, 5) == "~~~~~");
  }
}

TEST_CASE("Stress test") {
  ariel::Notebook notebook;
  for (int i = 0; i < 1000; i++) {
    CHECK(notebook.read(i, i, 0, ariel::Direction::Horizontal, 5) == "_____");
  }
}
