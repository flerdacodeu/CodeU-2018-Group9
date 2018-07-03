
#include "codeu_test_lib.h"
#include "Dictionary.h"
#include "q1.h"


#ifndef TESTING_FUNCTIONS
#define TESTING_FUNCTIONS

void CreateSampleGrid(std::vector<std::vector<char> > &grid);

Dictionary test_CreateDictionaryFromVector();

void test_IsWordInDictionary(const Dictionary & d);

void test_IsPrefixInDictionary (const Dictionary & d);

void test_IsWordAfterRemoval (Dictionary & d);

void test_IsPrefixAfterRemoval (Dictionary & d);

void test_example();

void all_tests();


#endif
