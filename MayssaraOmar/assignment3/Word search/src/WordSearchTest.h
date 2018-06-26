#ifndef WordSearchTest_H_
#define WordSearchTest_H_

#include "dictionary.h"

class WordSearchTest {
public:
	static void setup(dictionary*);
	static void empty_grid();
	static void one_cell_grid_with_match_in_dictionary();
	static void one_cell_grid_with_no_match_in_dictionary();
	static void same_char_grid_with_match_in_dictionary();
	static void same_char_grid_with_no_match_in_dictionary();
	static void case_sensitive();
	static void grid_with_nonascii_chars();
	static void uneven_columns_grid();
	static void simple_test();
	static void run_all_tests();
};

#endif /* WordSearchTest_H_ */
