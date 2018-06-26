#include "WordSearchTest.h"
#include "word search.h"
#include "test.h"

void WordSearchTest::setup(dictionary* dic) {
	dic->insert("car");
	dic->insert("card");
	dic->insert("cart");
	dic->insert("cat");
	dic->insert("m");
	dic->insert("match");
}

void WordSearchTest::run_all_tests() {
	empty_grid();
	one_cell_grid_with_match_in_dictionary();
	one_cell_grid_with_no_match_in_dictionary();
	same_char_grid_with_match_in_dictionary();
	same_char_grid_with_no_match_in_dictionary();
	case_sensitive();
	grid_with_nonascii_chars();
	uneven_columns_grid();
	simple_test();
}

void WordSearchTest::empty_grid() {
	// setup
	dictionary dic;
	setup(&dic);
	// build grid
	vector<vector<char> > grid;
	// build expected set
	unordered_set<string> expected;
	// test
	unordered_set<string> actual;
	get_words_from_grid(grid, dic, &actual);
	EXPECT_EQ(expected, actual);
}

void WordSearchTest::one_cell_grid_with_match_in_dictionary() {
	// setup
	dictionary dic;
	setup(&dic);
	// build grid
	vector<vector<char> > grid(1);
	grid[0].push_back('m');
	// build expected set
	unordered_set<string> expected;
	expected.insert("m");
	// test
	unordered_set<string> actual;
	get_words_from_grid(grid, dic, &actual);
	EXPECT_EQ(expected, actual);
}

void WordSearchTest::one_cell_grid_with_no_match_in_dictionary() {
	// setup
	dictionary dic;
	setup(&dic);
	// build grid
	vector<vector<char> > grid(1);
	grid[0].push_back('z');
	// build expected set
	unordered_set<string> expected;
	// test
	unordered_set<string> actual;
	get_words_from_grid(grid, dic, &actual);
	EXPECT_EQ(expected, actual);
}

void WordSearchTest::same_char_grid_with_match_in_dictionary() {
	// setup
	dictionary dic;
	setup(&dic);
	// build grid
	vector<vector<char> > grid(2);
	grid[0].push_back('m');
	grid[0].push_back('m');
	grid[1].push_back('m');
	grid[1].push_back('m');
	// build expected set
	unordered_set<string> expected;
	expected.insert("m");
	// test
	unordered_set<string> actual;
	get_words_from_grid(grid, dic, &actual);
	EXPECT_EQ(expected, actual);
}

void WordSearchTest::same_char_grid_with_no_match_in_dictionary() {
	// setup
	dictionary dic;
	setup(&dic);
	// build grid
	vector<vector<char> > grid(2);
	grid[0].push_back('z');
	grid[0].push_back('z');
	grid[1].push_back('z');
	grid[1].push_back('z');
	// build expected set
	unordered_set<string> expected;
	// test
	unordered_set<string> actual;
	get_words_from_grid(grid, dic, &actual);
	EXPECT_EQ(expected, actual);
}

void WordSearchTest::case_sensitive() {
	// setup
	dictionary dic;
	setup(&dic);
	// build grid
	vector<vector<char> > grid(3);
	grid[0].push_back('a');
	grid[0].push_back('a');
	grid[0].push_back('r');
	grid[1].push_back('t');
	grid[1].push_back('c');
	grid[1].push_back('D');
	// build expected set
	unordered_set<string> expected;
	expected.insert("cat");
	expected.insert("car");
	// test
	unordered_set<string> actual;
	get_words_from_grid(grid, dic, &actual);
	EXPECT_EQ(expected, actual);
}

void WordSearchTest::grid_with_nonascii_chars() {
	// setup
	dictionary dic;
	setup(&dic);
	// build grid
	vector<vector<char> > grid(2);
	grid[0].push_back('ë');
	grid[0].push_back('0');
	grid[1].push_back('Ã');
	grid[1].push_back('ã');
	// build expected set
	unordered_set<string> expected;
	// test
	unordered_set<string> actual;
	get_words_from_grid(grid, dic, &actual);
	EXPECT_EQ(expected, actual);
}

void WordSearchTest::uneven_columns_grid() {
	// setup
	dictionary dic;
	setup(&dic);
	// build grid
	vector<vector<char> > grid(3);
	grid[0].push_back('c');
	grid[0].push_back('a');
	grid[1].push_back('t');
	grid[2].push_back('r');
	grid[2].push_back('d');
	grid[2].push_back('d');
	// build expected set
	unordered_set<string> expected;
	expected.insert("cat");
	// test
	unordered_set<string> actual;
	get_words_from_grid(grid, dic, &actual);
	EXPECT_EQ(expected, actual);
}

void WordSearchTest::simple_test() {
	// setup
	dictionary dic;
	setup(&dic);
	// build grid
	vector<vector<char> > grid(3);
	grid[0].push_back('a');
	grid[0].push_back('a');
	grid[0].push_back('r');
	grid[1].push_back('t');
	grid[1].push_back('c');
	grid[1].push_back('d');
	// build expected set
	unordered_set<string> expected;
	expected.insert("cat");
	expected.insert("car");
	expected.insert("card");
	// test
	unordered_set<string> actual;
	get_words_from_grid(grid, dic, &actual);
	EXPECT_EQ(expected, actual);
}
