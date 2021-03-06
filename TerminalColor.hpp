//=====================================================================
// Quentin Quadrat <lecrapouille@gmail.com>
// License: Public Domain :)
//=====================================================================

#ifndef TERMINAL_COLOR_HPP
#  define TERMINAL_COLOR_HPP

#  include <atomic>
#  include <utility>
#  include <iostream>

// **************************************************************
//! \brief Namespace for managing colorful messages in console.
//! This code was inspired by https://github.com/agauniyal/rang
//! but contains less stuffs than the original. For example this
//! code will only work with consoles supporting ANSI color.
//!
//! Example:
//! --------
//! termcolor::enable();
//! std::cout << termcolor::fg::green << termcolor::bg::red << "hello"
//!           << std::endl;
//! std::cout << termcolor::state::On << termcolor::fg::red << "hello"
//!           << termcolor::fg::green << termcolor::bg::red << " word"
//!           << termcolor::style::normal
//!           << termcolor::state::Off
//!           << std::endl;
// **************************************************************
namespace termcolor
{
  //------------------------------------------------------------------
  //! \brief Switch on or switch off colorful text. When off even if
  //! you write std::cout << termcolor::fg::green the green color will
  //! be ignored.
  //------------------------------------------------------------------
  enum class state {
    off = 0, //! \brief Color informations are ignored.
    on  = 1  //! \brief Color informations are taken into account.
  };

  //------------------------------------------------------------------
  //! \brief Return if color informations are currently ignored or
  //! taken into account.
  //------------------------------------------------------------------
  inline std::atomic<termcolor::state>& isEnabled()
  {
    static std::atomic<termcolor::state> value(termcolor::state::on);
    return value;
  }

  //------------------------------------------------------------------
  //! \brief Color informations will be taken into account.
  //------------------------------------------------------------------
  inline void enable()
  {
    termcolor::isEnabled() = termcolor::state::on;
  }

  //------------------------------------------------------------------
  //! \brief Color informations will be ignored.
  //------------------------------------------------------------------
  inline void disable()
  {
    termcolor::isEnabled() = termcolor::state::off;
  }

  //------------------------------------------------------------------
  //! \brief Alternative way for isEnabled() using overloaded << operator.
  //------------------------------------------------------------------
  inline std::ostream& operator<<(std::ostream &os, const termcolor::state& value)
  {
     termcolor::isEnabled() = value;
     return os;
  }

  //------------------------------------------------------------------
  //! \brief ANSI text style
  //------------------------------------------------------------------
  enum class style {
    normal = 0, bold, dim, italic, underline, blink, rblink, reversed,
    conceal, crossed
  };

  //------------------------------------------------------------------
  //! \brief ANSI foreground color
  //------------------------------------------------------------------
  enum class fg {
    black = 30, red, green, yellow, blue, magenta, cyan, gray, reset
  };

  //------------------------------------------------------------------
  //! \brief ANSI background color
  //------------------------------------------------------------------
  enum class bg {
    normal = 1, black = 40, red, green, yellow, blue, magenta, cyan,
    gray, reset
  };

  //------------------------------------------------------------------
  //! \brief Structure for holding color information in a local variable
  //------------------------------------------------------------------
  struct color
  {
    color(termcolor::style style = termcolor::style::normal,
          termcolor::fg fg = termcolor::fg::reset)
      : m_style(style), m_fg(fg)
    {}

    termcolor::style m_style;
    termcolor::fg m_fg;
  };

  //------------------------------------------------------------------
  //! \brief Needed by g++-5.4 else it will not compile this file and
  //! fail with operator<< overload. Newest gcc do not complain. This
  //! code allows the template T to be either the struct color or enums
  //! (fg, bg or style).
  //------------------------------------------------------------------
  template <typename T>
    using enableIfColorTyped = typename std::enable_if<
      std::is_same<T, termcolor::color>::value ||
      std::is_same<T, termcolor::style>::value ||
      std::is_same<T, termcolor::fg>::value ||
      std::is_same<T, termcolor::bg>::value, std::ostream&>::type;

  //------------------------------------------------------------------
  //! \brief Change the console background or foreground color or
  //! style given by the template T.
  //------------------------------------------------------------------
  template <typename T>
  inline enableIfColorTyped<T> setColor(std::ostream &os, const T& value)
  {
    return os << "\033[" << static_cast<int>(value) << 'm';
  }

  //------------------------------------------------------------------
  //! \brief Change the console background or foreground color and the
  //! style given by the structure.
  //------------------------------------------------------------------
  template <>
  inline std::ostream& setColor<termcolor::color>(std::ostream &os, 
                                         const termcolor::color& c)
  {
    return os << "\033["
      << static_cast<int>(c.m_style) << ';'
      << static_cast<int>(c.m_fg) << 'm';
  }

  //------------------------------------------------------------------
  //! \brief Overload the << operator. T can be either fg or bg or style
  //! or color.
  //------------------------------------------------------------------
  template <typename T> 
  inline enableIfColorTyped<T> operator<<(std::ostream &os, const T& value)
  {
    if (termcolor::state::on == termcolor::isEnabled())
      return setColor(os, value);

    return os;
  }
}

#endif // TERMINAL_COLOR_HPP
