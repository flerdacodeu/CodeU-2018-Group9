#ifndef TEST_H_
#define TEST_H_

#include <iostream>
#include <vector>

// Some convenient macros for simple testing.
// If expectation is fulfilled, prints nothing;
// If expectation is not fulfilled, prints what went wrong (expectation vs.
// actual value) with the filename and line number for convenience.

#define EXPECT_EQ(expected, actual)                                       \
  if ((expected) != (actual)) {                                           \
    std::cout << __FILE__ << ":" << __LINE__ << " Failed: "               \
              << "Statement (" << #actual << ") is " << actual            \
              << ", expected " << (expected) << " (" << #expected << ")." \
              << std::endl;                                               \
  }

// Print operator for vectors. Must be defined in order to use EXPECT_EQ macro
// with vectors (see example below).
template <class Type>
inline std::ostream& operator<<(std::ostream& os, const std::vector<Type>& v) {
  os << "{";
  for (int i = 0; i < v.size(); i++) {
    if (i > 0) {
      os << ", ";
    }
    os << v[i];
  }
  os << "}";
  return os;
}

#endif /* TEST_H_ */