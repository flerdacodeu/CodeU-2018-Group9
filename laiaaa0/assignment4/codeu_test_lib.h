#include <iostream>
#include <vector>

// Some convenient macros for simple testing.
// If expectation is fulfilled, prints nothing;
// If expectation is not fulfilled, prints what went wrong (expectation vs.
// actual value) with the filename and line number for convenience.

#define EXPECT_TRUE(statement)                                            \
  if (!(statement)) {                                                     \
    std::cout << __FILE__ << ":" << __LINE__ << " Failed: "               \
              << "Statement (" #statement << ") is false, expected true." \
              << std::endl;                                               \
  }

#define EXPECT_FALSE(statement)                                           \
  if (statement) {                                                        \
    std::cout << __FILE__ << ":" << __LINE__ << " Failed: "               \
              << "Statement (" #statement << ") is true, expected false." \
              << std::endl;                                               \
  }

#define EXPECT_EQ(expected, actual)                                       \
  if ((expected) != (actual)) {                                           \
    std::cout << __FILE__ << ":" << __LINE__ << " Failed: "               \
              << "Statement (" << #actual << ") is " << actual            \
              << ", expected " << (expected) << " (" << #expected << ")." \
              << std::endl;                                               \
  }

#define EXPECT_NULL(statement)                                 \
  if (statement != nullptr) {                                  \
    std::cout << __FILE__ << ":" << __LINE__ << " Failed: "    \
              << "Statement (" << #statement                   \
              << ") is not null, expected null." << std::endl; \
  }

// Print operator for vectors. Must be defined in order to use EXPECT_EQ macro
// with vectors (see example below).
template <class T>
inline std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
  os << "{";
  for (int i = 0; i < v.size(); i++) {
    if (i > 0) {
      os << ", ";
    }
    os << v[i];
  }
  os << "}";
}

// Example usage:

// EXPECT_TRUE(1 < 3);  // Prints nothing.
// EXPECT_TRUE(5 < 3);  // main.cpp:53 Failed: Statement (5 < 3) is
//                      // false, expected true.
// EXPECT_TRUE(true);   // Prints nothing.
// EXPECT_TRUE(false);  // Prints: tests.cpp:56 Failed: Statement (false) is
//                      // false, expected true.
// EXPECT_FALSE(5 > 6);
// EXPECT_FALSE(5 > 0);  // Prints: tests.cpp:59 Failed: Statement (5 > 0) is
//                       // true, expected false.
// EXPECT_EQ(4, 2 + 2);
// EXPECT_EQ(4, 3 + 1);
// EXPECT_EQ(10 * 10, 50 + 51);  // tests:37 Failed: Statement (50 + 51) is 101,
//                               // expected 100 (10 * 10).
// EXPECT_EQ("pizza", std::string("pizz") + "a");
// EXPECT_EQ("pizza", std::string("pizz") + "aaaa");
// // tests.cpp:39 Failed: Statement (std::string("pizz")+"aaaa") is pizzaaaa,
// // expected pizza ("pizza").
//
// int x;
// EXPECT_NULL(&x);  // main.cpp:71 Failed: Statement (&x) is not null,
//                   // expected null.
//
// std::vector<int> expected_vec{1, 2, 3};
// std::vector<int> actual_vec{4, 5, 6};
// EXPECT_EQ(expected_vec, actual_vec);
// // main.cpp:77 Failed: Statement (actual_vec) is {4, 5, 6}, expected
// // {1, 2, 3} (expected_vec).
