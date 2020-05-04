#include "../TerminalColor.hpp"
#include <sstream>
#include <cassert>

//--------------------------------------------------------------------------
// g++ -W -Wall TerminalColorTests.cpp -o test
//--------------------------------------------------------------------------
int main()
{
  // Disable colorful text
  {
    std::stringstream ss;
    ss << termcolor::state::off << termcolor::fg::green << "Hello" << termcolor::style::normal << "world";
    assert(ss.str() == "Helloworld");
  }

  // Enable colorful text
  {
    std::stringstream ss;
    ss << termcolor::state::on << termcolor::fg::green << "Hello" << termcolor::style::normal << "world";
    assert(ss.str() == "\033[32mHello\033[0mworld");
  }

  // Disable colorful text
  {
    termcolor::disable();
    std::stringstream ss;
    ss << termcolor::fg::green << "Hello" << termcolor::bg::red << "world" << termcolor::style::normal;
    assert(ss.str() == "Helloworld");
  }

  // Enable colorful text
  {
    termcolor::enable();
    std::stringstream ss;
    ss << termcolor::fg::green << "Hello" << termcolor::bg::red << "world" << termcolor::style::normal;
    assert(ss.str() == "\033[32mHello\033[41mworld\033[0m");
  }

  // Disable colorful text
  {
    termcolor::disable();
    termcolor::color c1(termcolor::style::bold, termcolor::fg::red);
    termcolor::color c2(termcolor::style::italic, termcolor::fg::green);
    std::stringstream ss;
    ss << c1 << "Hello" << c2 << "world" << termcolor::style::normal;
    assert(ss.str() == "Helloworld");
  }

  // Enable colorful text
  {
    termcolor::enable();
    termcolor::color c1(termcolor::style::bold, termcolor::fg::red);
    termcolor::color c2(termcolor::style::italic, termcolor::fg::green);
    std::stringstream ss;
    ss << c1 << "Hello" << c2 << "world" << termcolor::style::normal;
    assert(ss.str() == "\033[1;31mHello\033[3;32mworld\033[0m");
  }

  std::cout << termcolor::color(termcolor::style::bold, termcolor::fg::green)
            << "Unit tests passed!" << termcolor::style::normal << std::endl;
  return 0;
}
