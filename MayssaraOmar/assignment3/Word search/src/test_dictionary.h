#ifndef TEST_DICTIONARY_H_
#define TEST_DICTIONARY_H_

#include "dictionary.h"

class test_dictionary {
	static dictionary dic;
	static void insert_oneword();
	static void insert_vector();
	static void remove_oneword();
	static void remove_vector();
	static void isWord_true();
	static void isWord_false();
	static void isPrefix_true();
	static void isPrefix_false();
	static void clear_empty();
	static void empty_dictionary();
public:
	static void run_all_tests();
};

#endif /* TEST_DICTIONARY_H_ */
