#pragma once

#ifndef TESTING_HPP
#define TESTING_HPP

#include <iostream>

#define fail_if(condition)                                                     \
  if (condition) {                                                             \
    std::cerr << "Test failed (" __FILE__ << ":" << __LINE__                   \
              << "):\n - Condition: " #condition << "\n"                       \
              << std::endl;                                                    \
    return false;                                                              \
  }

#define fail_if_msg(condition, msg)                                            \
  if (condition) {                                                             \
    std::cerr << "Test failed (" __FILE__ << ":" << __LINE__                   \
              << "):\n - Condition: " #condition << "\n - Message:   " << msg  \
              << "\n"                                                          \
              << std::endl;                                                    \
    return false;                                                              \
  }

#define fail_unless(condition) fail_if(!(condition))
#define fail_unless_msg(condition, msg) fail_if_msg(!(condition), msg)

#define fail_unless_eq(a, b)                                                   \
  do {                                                                         \
    auto a_ = a;                                                               \
    auto b_ = b;                                                               \
    fail_unless_msg(a_ == b_, "expected " #a " ("                              \
                                  << a_ << ") to be equal to " #b " (" << b_   \
                                  << ")");                                     \
  } while (0)

#define fail_if_eq(a, b)                                                       \
  do {                                                                         \
    auto a_ = a;                                                               \
    auto b_ = b;                                                               \
    fail_if_msg(a_ == b_, "expected " #a " ("                                  \
                              << a_ << ") to be different from " #b " (" << b_ \
                              << ")");                                         \
  } while (0)

#define run_test_impl(func, name)                                              \
  do {                                                                         \
    std::cout << "Running test: " name << std::endl;                           \
    if (func()) {                                                              \
      std::cout << "\033[0;32mTest succeeded: " name << "\033[0m"              \
                << std::endl;                                                  \
    } else {                                                                   \
      std::cout << "\033[0;31mTest failed: " name << "\033[0m" << std::endl;   \
    }                                                                          \
  } while (0)

#define run_test(func) run_test_impl(func, #func)

#endif // TESTING_HPP
