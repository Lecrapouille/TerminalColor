# TerminalColor

A single C++11 header-only file to add color in your std::cout.
This project has been inspired by https://github.com/agauniyal/rang and https://github.com/agauniyal/rang/issues/103

Example:

```
#define WARNING_COLOR   termcolor::color(termcolor::style::bold, termcolor::fg::green)
#define ERROR_COLOR     termcolor::color(termcolor::style::bold, termcolor::fg::red)
#define DEFAULT_COLOR   termcolor::color()

termcolor::enable();
std::cout << WARNING_COLOR << "- Warning\n"
          << ERROR_COLOR << "+ Error"
          << DEFAULT_COLOR << std::endl;

termcolor::disable();
std::cout << WARNING_COLOR << "- Warning\n"
          << ERROR_COLOR << "+ Error"
          << DEFAULT_COLOR << std::endl;
```

Will produce something like this in your console:

```diff
- Warning
+ Error
```
```
- Warning
+ Error
```

If you want to ignore color requests call `termcolor::disable();` To enable color back: `termcolor::enable();`. For more examples see the [unit-test file](tests/TerminalColorTests.cpp).
