

#ifndef TEST_WORDSEARCH_H_
#define TEST_WORDSEARCH_H_

#include "dictionary.h"

class test_wordSearch {
	static dictionary dic;
public:
	static void setup();
	static void run_all_tests();
	static void empty_grid();
	static void one_cell_grid_with_match_in_dictionary();
	static void one_cell_grid_with_no_match_in_dictionary();
	static void same_char_grid_with_match_in_dictionary();
	static void same_char_grid_with_no_match_in_dictionary();
	static void case_sensitive();
	static void grid_with_nonascii_chars();
	static void uneven_columns_grid();
	static void simple_test();
};



#endif /* TEST_WORDSEARCH_H_ */
