/*
 * getkw -- a simple input parser
 * Copyright (C) 2019 Jonas Juselius and contributors.
 *
 * This file is part of getkw.

 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * For information on the complete list of contributors to the
 * getkw library, see: <http://getkw.readthedocs.io/>
 */

/** @file messages.hpp
 *
 * @brief Collection of assertions and a standard error/warn/info/debug
 * message interface.
 *
 * Written by Jonas Juselius <jonas.juselius@chem.uit.no>
 * CTCC, University of Tromsø, July 2009
 *
 */

#pragma once

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#include "GetkwError.hpp"

namespace GetkwMessageStream {
struct msg {
  static int DebugLevel;
  static std::ostream * out;
  static void setOutputStream(std::ostream & o) { out = &o; }
  static void setDebugLevel(int i) { DebugLevel = i; }
};
} // namespace GetkwMessageStream

#define STR_DEBUG(S, X)                                                             \
  {                                                                                 \
    std::ostringstream _str;                                                        \
    _str << "Debug: " << __func__ << ",  line " << __LINE__ << " in  " << __FILE__  \
         << ": " << X << std::endl;                                                 \
    S = _str.str();                                                                 \
  }
#define STR_INFO(S, X)                                                              \
  {                                                                                 \
    std::ostringstream _str;                                                        \
    _str << "Info: " << __func__ << ",  line " << __LINE__ << " in  " << __FILE__   \
         << ": " << X << std::endl;                                                 \
    S = _str.str();                                                                 \
  }
#define STR_WARN(S, X)                                                              \
  {                                                                                 \
    std::ostringstream _str;                                                        \
    _str << "Warning: " << __func__ << ",  line " << __LINE__ << " in  "            \
         << __FILE__ << ": " << X << std::endl;                                     \
    S = _str.str();                                                                 \
  }
#define STR_ERROR(S, X)                                                             \
  {                                                                                 \
    std::ostringstream _str;                                                        \
    _str << "Error: " << __func__ << ",  line " << __LINE__ << " in  " << __FILE__  \
         << ": " << X << std::endl;                                                 \
    S = _str.str();                                                                 \
  }

#ifdef NDEBUG
#define PRINT(STR)
#define SPRINT(STR)
#else
#define PRINT(STR) *GetkwMessageStream::msg::out << STR;
#define SPRINT(_out, STR) _out << STR;
#endif

#define debug(level, STR)                                                           \
  if (level < GetkwMessageStream::msg::DebugLevel)                                  \
    *GetkwMessageStream::msg::out << STR;
#define sdebug(level, _out, STR)                                                    \
  if (level < GetkwMessageStream::msg::DebugLevel)                                  \
    _out << STR;

#define SET_DEBUG_LEVEL(a) GetkwMessageStream::msg::setDebugLevel(a);
#define SET_MESSAGE_STREAM(s) GetkwMessageStream::msg::setOutputStrem(s);
#define DEBUG_LEVEL GetkwMessageStream::msg::DebugLevel

#define MSG_DEBUG(X)                                                                \
  {                                                                                 \
    *GetkwMessageStream::msg::out << "Debug: " << __func__ << "(), line "           \
                                  << __LINE__ << "in " << __FILE__ << ": " << X     \
                                  << std::endl;                                     \
  }
#define MSG_INFO(X)                                                                 \
  {                                                                                 \
    *GetkwMessageStream::msg::out << "Info: " << __FILE__ << ": " << __func__       \
                                  << "(), line " << __LINE__ << ": " << X           \
                                  << std::endl;                                     \
  }
#define MSG_NOTE(X)                                                                 \
  {                                                                                 \
    *GetkwMessageStream::msg::out << "Note: " << __FILE__ << ": " << __func__       \
                                  << "(), line " << __LINE__ << ": " << X           \
                                  << std::endl;                                     \
  }
#define MSG_WARN(X)                                                                 \
  {                                                                                 \
    *GetkwMessageStream::msg::out << "Warning: " << __func__ << "(), line "         \
                                  << __LINE__ << ": " << X << std::endl;            \
  }
#define MSG_ERROR(X)                                                                \
  {                                                                                 \
    *GetkwMessageStream::msg::out << "Error: " << __func__ << "(), line "           \
                                  << __LINE__ << ": " << X << std::endl;            \
  }
#define MSG_FATAL(X)                                                                \
  {                                                                                 \
    *GetkwMessageStream::msg::out << "Error: " << __FILE__ << ": " << __func__      \
                                  << "(), line " << __LINE__ << ": " << X           \
                                  << std::endl;                                     \
    std::exit(EXIT_FAILURE);                                                        \
  }

#define MSG_INVALID_ARG(X)                                                          \
  {                                                                                 \
    *GetkwMessageStream::msg::out << "Error, invalid argument passed: " << __func__ \
                                  << "(), line " << __LINE__ << ": " << X           \
                                  << std::endl;                                     \
  }
#define INVALID_ARG_ABORT                                                           \
  {                                                                                 \
    *GetkwMessageStream::msg::out << "Error, invalid argument passed: " << __func__ \
                                  << "(), line " << __LINE__ << std::endl;          \
    std::exit(EXIT_FAILURE);                                                        \
  }
#define NOT_REACHED_ABORT                                                           \
  {                                                                                 \
    *GetkwMessageStream::msg::out << "Error, should not be reached: " << __func__   \
                                  << "(), line " << __LINE__ << std::endl;          \
    std::exit(EXIT_FAILURE);                                                        \
  }
#define INTERNAL_INCONSISTENCY                                                      \
  {                                                                                 \
    *GetkwMessageStream::msg::out                                                   \
        << "Internal inconsistency! You have found a bug: " << __func__             \
        << "(), line " << __LINE__ << std::endl;                                    \
    std::exit(EXIT_FAILURE);                                                        \
  }

#define NEEDS_TESTING                                                               \
  {                                                                                 \
    static bool __once = true;                                                      \
    if (__once) {                                                                   \
      __once = false;                                                               \
      *GetkwMessageStream::msg::out << "NEEDS TESTING: " << __FILE__ << ", "        \
                                    << __func__ << "(), line " << __LINE__          \
                                    << std::endl;                                   \
    }                                                                               \
  }

#define ASSERT_FILE(A, B)                                                           \
  {                                                                                 \
    if (A == NULL) {                                                                \
      *GetkwMessageStream::msg::out << "Error: " << __func__ << "(), line "         \
                                    << __LINE__ << ": No such file, " << B          \
                                    << std::endl;                                   \
      std::exit(EXIT_FAILURE);                                                      \
    }                                                                               \
  }

#define NOT_IMPLEMENTED_ABORT                                                       \
  {                                                                                 \
    *GetkwMessageStream::msg::out << "Error: Not implemented, " << __FILE__ ", "    \
                                  << __func__ << "(), line " << __LINE__            \
                                  << std::endl;                                     \
    std::exit(EXIT_FAILURE);                                                        \
  }

#define NOTE(X)                                                                     \
  {                                                                                 \
    static bool __once = true;                                                      \
    if (__once) {                                                                   \
      __once = false;                                                               \
      *GetkwMessageStream::msg::out << "NOTE: " << __FILE__ << ", " << __func__     \
                                    << "(), line " << __LINE__ << ": " << X         \
                                    << std::endl;                                   \
    }                                                                               \
  }

#define NEEDS_FIX(X)                                                                \
  {                                                                                 \
    static bool __once = true;                                                      \
    if (__once) {                                                                   \
      __once = false;                                                               \
      *GetkwMessageStream::msg::out << "NEEDS FIX: " << __FILE__ << ", "            \
                                    << __func__ << "(), line " << __LINE__ << ": "  \
                                    << X << std::endl;                              \
    }                                                                               \
  }

#define WRONG(X)                                                                    \
  {                                                                                 \
    *GetkwMessageStream::msg::out << "WRONG: " << __FILE__ << ", " << __func__      \
                                  << "(), line " << __LINE__ << ": " << X           \
                                  << std::endl;                                     \
    std::exit(EXIT_FAILURE);                                                        \
  }

#define STR_DEBUG(S, X)                                                             \
  {                                                                                 \
    std::ostringstream _str;                                                        \
    _str << "Debug: " << __func__ << ",  line " << __LINE__ << " in  " << __FILE__  \
         << ": " << X << std::endl;                                                 \
    S = _str.str();                                                                 \
  }
#define STR_INFO(S, X)                                                              \
  {                                                                                 \
    std::ostringstream _str;                                                        \
    _str << "Info: " << __func__ << ",  line " << __LINE__ << " in  " << __FILE__   \
         << ": " << X << std::endl;                                                 \
    S = _str.str();                                                                 \
  }
#define STR_WARN(S, X)                                                              \
  {                                                                                 \
    std::ostringstream _str;                                                        \
    _str << "Warning: " << __func__ << ",  line " << __LINE__ << " in  "            \
         << __FILE__ << ": " << X << std::endl;                                     \
    S = _str.str();                                                                 \
  }
#define STR_ERROR(S, X)                                                             \
  {                                                                                 \
    std::ostringstream _str;                                                        \
    _str << "Error: " << __func__ << ",  line " << __LINE__ << " in  " << __FILE__  \
         << ": " << X << std::endl;                                                 \
    S = _str.str();                                                                 \
  }
