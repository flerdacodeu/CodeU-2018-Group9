#include "codeu_test_lib.h"
#include "Dictionary.hpp"

#ifndef UNIT_TESTS
#define UNIT_TESTS

void test_IsWord(const Dictionary& d);

void test_IsPrefix(const Dictionary& d);

void test_IsWordAfterRemoval(Dictionary& d);

void test_IsPrefixAfterRemoval(Dictionary& d);

#endif
