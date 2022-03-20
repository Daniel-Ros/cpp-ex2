#include "Direction.hpp"
#include "Notebook.hpp"
#include "doctest.h"
#include <array>
#include <string>
/**
 * Auther: Daniel Rosenberg
 *
 * All test are written in such manner to provide the most covarge that i s[]
 */
// gives us a full line of text
std::string fullLine(char c) {
  std::string str;
  for (int i = 0; i < 100; i++) {
    str += c;
  }
  return str;
}

TEST_CASE("Bad input") {
  ariel::Notebook notebook;
  /**
   * This test is for for bad input.
   * Testing for any out of range input that may be includeing negative and 0
   * numbers also checking that we do not write out of bounds of the notebook
   * (in column more then 100)
   *
   */
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
  CHECK_THROWS(notebook.read(1, 1, 1, ariel::Direction::Horizontal, 0));
  CHECK_THROWS(notebook.read(1, 1, 1, ariel::Direction::Horizontal, -1));

  CHECK_THROWS(notebook.read(-1, 1, 0, ariel::Direction::Vertical, 1));
  CHECK_THROWS(notebook.read(1, 1, -1, ariel::Direction::Vertical, 1));
  CHECK_THROWS(notebook.read(1, -1, 0, ariel::Direction::Vertical, 1));
  CHECK_THROWS(notebook.read(1, 1, 1, ariel::Direction::Vertical, 0));
  CHECK_THROWS(notebook.read(1, 1, 1, ariel::Direction::Vertical, -1));

  CHECK_THROWS(notebook.erase(-1, 1, 0, ariel::Direction::Horizontal, 1));
  CHECK_THROWS(notebook.erase(1, -1, 0, ariel::Direction::Horizontal, 1));
  CHECK_THROWS(notebook.erase(1, 1, -1, ariel::Direction::Horizontal, 1));
  CHECK_THROWS(notebook.erase(1, 1, 1, ariel::Direction::Horizontal, 0));
  CHECK_THROWS(notebook.erase(1, 1, 1, ariel::Direction::Horizontal, -1));

  CHECK_THROWS(notebook.erase(-1, 1, 0, ariel::Direction::Vertical, 1));
  CHECK_THROWS(notebook.erase(1, 1, -1, ariel::Direction::Vertical, 1));
  CHECK_THROWS(notebook.erase(1, -1, 0, ariel::Direction::Vertical, 1));
  CHECK_THROWS(notebook.erase(1, 1, 1, ariel::Direction::Vertical, 0));
  CHECK_THROWS(notebook.erase(1, 1, 1, ariel::Direction::Vertical, -1));
}

/**
 * A basic test for sainty checking. to see that every thing that shoud work
 * works.
 */
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

/**
 * A test to see if the usage is right, checking for functionaslity and stabilty
 * in the code
 */
TEST_CASE("Usage test") {
  ariel::Notebook notebook;
  // this is for testing the write functionality, test that it does not return
  // errors on valid input and that we cannot use it to write data on exsiting
  // data
  SUBCASE("write")
  notebook.write(0, 100, 0, ariel::Direction::Horizontal, "abcds");
  CHECK_THROWS(notebook.write(0, 100, 0, ariel::Direction::Horizontal,
                              "abcds")); // this shold throw an errror becuase
                                         // we writing on exsisting data
  notebook.write(0, 100, 0, ariel::Direction::Vertical, "abcds");
  CHECK_THROWS(notebook.write(0, 100, 0, ariel::Direction::Vertical,
                              "abcds")); // this shold throw an errror becuase
                                         // we writing on exsisting data

  // this is for the read functionality, checking that the function indeed read
  // the right data
  SUBCASE("read") {
    CHECK(notebook.read(0, 0, 0, ariel::Direction::Horizontal, 5) == "_____");
    notebook.write(0, 0, 0, ariel::Direction::Horizontal, "test1");
    CHECK(notebook.read(0, 0, 0, ariel::Direction::Horizontal, 5) == "test1");
  }

  // this is for the erase method, checking that we can erase
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
// using the stress test to write a lot of data and checking that everything is
// fine and working
TEST_CASE("Stress test") {
  ariel::Notebook notebook;
  for (int i = 0; i < 1000; i++) {
    CHECK(notebook.read(i, i, 0, ariel::Direction::Horizontal, 5) == "_____");
  }

  std::string line = fullLine('a');

  for (int i = 0; i < 1000; i++) {
    notebook.write(0, i, 0, ariel::Direction::Horizontal, line);
  }

  for (int i = 0; i < 1000; i++) {
    CHECK(notebook.read(0, i, 0, ariel::Direction::Horizontal, 100) == line);
  }
  line = fullLine('~');

  for (int i = 0; i < 1000; i++) {
    notebook.erase(0, i, 0, ariel::Direction::Horizontal, 100);
  }

  for (int i = 0; i < 1000; i++) {
    CHECK(notebook.read(0, i, 0, ariel::Direction::Horizontal, 100) == line);
  }

  line = fullLine('a');

  for (int i = 0; i < 1000; i++) {
    notebook.write(1, i, 0, ariel::Direction::Vertical, line);
  }

  for (int i = 0; i < 1000; i++) {
    CHECK(notebook.read(1, i, 0, ariel::Direction::Vertical, 100) == line);
  }
  line = fullLine('~');

  for (int i = 0; i < 1000; i++) {
    notebook.erase(1, i, 0, ariel::Direction::Vertical, 100);
  }

  for (int i = 0; i < 1000; i++) {
    CHECK(notebook.read(1, i, 0, ariel::Direction::Vertical, 100) == line);
  }
}
