#include "test_wordSearch.h"
#include "word search.h"
#include "test.h"

dictionary test_wordSearch::dic;

void test_wordSearch::setup() {
	dic.insert("car");
	dic.insert("card");
	dic.insert("cart");
	dic.insert("cat");
	dic.insert("m");
}
void test_wordSearch::run_all_tests() {
	setup();
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
void test_wordSearch::empty_grid() {
	vector<vector<char> > grid;
	unordered_set<string> expected;
	unordered_set<string> actual;
	get_words_from_grid(grid, dic, actual);
	EXPECT_EQ(expected, actual);
}
void test_wordSearch::one_cell_grid_with_match_in_dictionary() {
	vector<vector<char> > grid(1);
	grid[0].push_back('m');
	unordered_set<string> expected;
	expected.insert("m");
	unordered_set<string> actual;
	get_words_from_grid(grid, dic, actual);
	EXPECT_EQ(expected, actual);
}
void test_wordSearch::one_cell_grid_with_no_match_in_dictionary() {
	vector<vector<char> > grid(1);
	grid[0].push_back('z');
	unordered_set<string> expected;
	unordered_set<string> actual;
	get_words_from_grid(grid, dic, actual);
	EXPECT_EQ(expected, actual);
}
void test_wordSearch::same_char_grid_with_match_in_dictionary() {
	vector<vector<char> > grid(2);
	grid[0].push_back('m');
	grid[0].push_back('m');
	grid[1].push_back('m');
	grid[1].push_back('m');

	unordered_set<string> expected;
	expected.insert("m");
	unordered_set<string> actual;
	get_words_from_grid(grid, dic, actual);
	EXPECT_EQ(expected, actual);
}
void test_wordSearch::same_char_grid_with_no_match_in_dictionary() {
	vector<vector<char> > grid(2);
	grid[0].push_back('z');
	grid[0].push_back('z');
	grid[1].push_back('z');
	grid[1].push_back('z');

	unordered_set<string> expected;
	unordered_set<string> actual;
	get_words_from_grid(grid, dic, actual);
	EXPECT_EQ(expected, actual);

}
void test_wordSearch::case_sensitive() {
	vector<vector<char> > grid(3);

	grid[0].push_back('a');
	grid[0].push_back('a');
	grid[0].push_back('r');
	grid[1].push_back('t');
	grid[1].push_back('c');
	grid[1].push_back('D');
	unordered_set<string> expected;
	expected.insert("cat");
	expected.insert("car");
	unordered_set<string> actual;
	get_words_from_grid(grid, dic, actual);
	EXPECT_EQ(expected, actual);

}
void test_wordSearch::grid_with_nonascii_chars() {
	vector<vector<char> > grid(2);
	grid[0].push_back('ë');
	grid[0].push_back('0');
	grid[1].push_back('Ã');
	grid[1].push_back('ã');

	unordered_set<string> expected;
	unordered_set<string> actual;
	get_words_from_grid(grid, dic, actual);
	EXPECT_EQ(expected, actual);
}
void test_wordSearch::uneven_columns_grid() {
	vector<vector<char> > grid(3);
	grid[0].push_back('c');
	grid[0].push_back('a');
	grid[1].push_back('t');
	grid[2].push_back('r');
	grid[2].push_back('d');
	grid[2].push_back('d');
	unordered_set<string> expected;
	expected.insert("cat");
	unordered_set<string> actual;
	get_words_from_grid(grid, dic, actual);
	EXPECT_EQ(expected, actual);
}
void test_wordSearch::simple_test() {
	vector<vector<char> > grid(3);

	grid[0].push_back('a');
	grid[0].push_back('a');
	grid[0].push_back('r');
	grid[1].push_back('t');
	grid[1].push_back('c');
	grid[1].push_back('d');
	unordered_set<string> expected;
	expected.insert("cat");
	expected.insert("car");
	expected.insert("card");
	unordered_set<string> actual;
	get_words_from_grid(grid, dic, actual);
	EXPECT_EQ(expected, actual);
}

