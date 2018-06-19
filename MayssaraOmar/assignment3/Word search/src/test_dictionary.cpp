#include "test_dictionary.h"
#include "test.h"
#include "exception"

dictionary test_dictionary::dic;

void test_dictionary::run_all_tests() {
	insert_oneword();
	insert_vector();
	remove_oneword();
	remove_vector();
	isWord_true();
	isWord_false();
	isPrefix_true();
	isPrefix_false();
	clear_empty();
	empty_dictionary();
}
void test_dictionary::insert_oneword() {
	dic.insert("hello");
	dic.insert("world");

}
void test_dictionary::insert_vector() {
	vector<string> words(4);
	words[0] = "cat";
	words[1] = "cart";
	words[2] = "card";
	words[3] = "car";

	dic.insert(words);

}

void test_dictionary::remove_oneword() {

	dic.remove("hello");
	dic.remove("wor");

}
void test_dictionary::remove_vector() {
	vector<string> words(2);
	words[0] = "car";
	words[1] = "card";

	dic.remove(words);

}
void test_dictionary::isWord_true() {
	EXPECT_TRUE(dic.isWord("cat"));
	EXPECT_TRUE(dic.isWord("cart"));
	EXPECT_TRUE(dic.isWord("world"));
}
void test_dictionary::isWord_false() {
	EXPECT_FALSE(dic.isWord("CAT"));
	EXPECT_FALSE(dic.isWord("CART"));
	EXPECT_FALSE(dic.isWord("card"));
	EXPECT_FALSE(dic.isWord("car"));
	EXPECT_FALSE(dic.isWord(""));
	EXPECT_FALSE(dic.isWord("ë"));
}
void test_dictionary::isPrefix_true() {
	EXPECT_TRUE(dic.isPrefix("w"));
	EXPECT_TRUE(dic.isPrefix("wo"));
	EXPECT_TRUE(dic.isPrefix("wor"));
	EXPECT_TRUE(dic.isPrefix("worl"));
	EXPECT_TRUE(dic.isPrefix("world"));
	EXPECT_TRUE(dic.isPrefix("cat"));
	EXPECT_TRUE(dic.isPrefix("ca"));
	EXPECT_TRUE(dic.isPrefix("c"));
	EXPECT_TRUE(dic.isPrefix("car"));
	EXPECT_TRUE(dic.isPrefix("cart"));
	EXPECT_TRUE(dic.isPrefix(""));
}
void test_dictionary::isPrefix_false() {
	EXPECT_FALSE(dic.isPrefix(" "));
	EXPECT_FALSE(dic.isPrefix("ë"));
}
void test_dictionary::clear_empty() {
	EXPECT_FALSE(dic.empty());
	dic.clear();
	EXPECT_TRUE(dic.empty());
}
void test_dictionary::empty_dictionary() {
	dic.remove("hi");
	dic.clear();
	EXPECT_FALSE(dic.isPrefix("hi"));
	EXPECT_FALSE(dic.isWord("hi"));
	dic.insert("hi");
	EXPECT_TRUE(dic.isPrefix("hi"));
	EXPECT_TRUE(dic.isWord("hi"));
	EXPECT_FALSE(dic.empty());
}
