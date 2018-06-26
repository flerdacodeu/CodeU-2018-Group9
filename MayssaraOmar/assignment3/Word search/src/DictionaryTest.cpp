#include "DictionaryTest.h"
#include "test.h"
#include "dictionary.h"

void DictionaryTest::run_all_tests() {
	insert_remove_oneword();
	insert_remove_vector();
	isWord_true();
	isWord_false();
	isPrefix_true();
	isPrefix_false();
	clear_empty();
	empty_dictionary();
}

void DictionaryTest::insert_remove_oneword() {
	dictionary dic;
	// test insert
	dic.insert("hello");
	dic.insert("world");
	EXPECT_TRUE(dic.isWord("hello"));
	EXPECT_TRUE(dic.isWord("world"));
	// test remove
	dic.remove("hello");
	dic.remove("wor");
	EXPECT_FALSE(dic.isWord("hello"));
	EXPECT_TRUE(dic.isWord("world"));
}

void DictionaryTest::insert_remove_vector() {
	dictionary dic;
	vector<string> words_insert(4);
	words_insert[0] = "cat";
	words_insert[1] = "cart";
	words_insert[2] = "card";
	words_insert[3] = "car";
	// test insert
	dic.insert(words_insert);
	EXPECT_TRUE(dic.isWord("cat"));
	EXPECT_TRUE(dic.isWord("car"));
	EXPECT_TRUE(dic.isWord("cart"));
	EXPECT_TRUE(dic.isWord("card"));
	// test remove
	vector<string> words_remove(2);
	words_remove[0] = "car";
	words_remove[1] = "card";
	dic.remove(words_remove);
	EXPECT_TRUE(dic.isWord("cat"));
	EXPECT_FALSE(dic.isWord("car"));
	EXPECT_TRUE(dic.isWord("cart"));
	EXPECT_FALSE(dic.isWord("card"));
}

void DictionaryTest::isWord_true() {
	dictionary dic;
	dic.insert("world");
	dic.insert("cat");
	dic.insert("cart");
	dic.insert("CARD");
	dic.insert("CAR");
	EXPECT_TRUE(dic.isWord("world"));
	EXPECT_TRUE(dic.isWord("cat"));
	EXPECT_TRUE(dic.isWord("cart"));
	EXPECT_TRUE(dic.isWord("CARD"));
	EXPECT_TRUE(dic.isWord("CAR"));
}

void DictionaryTest::isWord_false() {
	dictionary dic;
	dic.insert("cat");
	dic.insert("cart");
	dic.insert("CARD");
	dic.insert("CAR");
	EXPECT_FALSE(dic.isWord("CAT"));
	EXPECT_FALSE(dic.isWord("CART"));
	EXPECT_FALSE(dic.isWord("card"));
	EXPECT_FALSE(dic.isWord("car"));
	EXPECT_FALSE(dic.isWord(""));
	EXPECT_FALSE(dic.isWord("Î"));
}

void DictionaryTest::isPrefix_true() {
	dictionary dic;
	dic.insert("world");
	dic.insert("cat");
	dic.insert("car");
	dic.insert("cart");
	dic.insert("CARD");
	dic.insert("CAR");
	dic.insert("„—Õ»«");
	EXPECT_TRUE(dic.isPrefix(""));
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
	EXPECT_TRUE(dic.isPrefix("C"));
	EXPECT_TRUE(dic.isPrefix("CA"));
	EXPECT_TRUE(dic.isPrefix("CARD"));
	EXPECT_TRUE(dic.isPrefix("CAR"));
	EXPECT_TRUE(dic.isPrefix("„"));
	EXPECT_TRUE(dic.isPrefix("„—"));
	EXPECT_TRUE(dic.isPrefix("„—Õ"));
	EXPECT_TRUE(dic.isPrefix("„—Õ»"));
	EXPECT_TRUE(dic.isPrefix("„—Õ»"));
	EXPECT_TRUE(dic.isPrefix("„—Õ»«"));
}

void DictionaryTest::isPrefix_false() {
	dictionary dic;
	dic.insert("hello");
	dic.insert("earth");
	EXPECT_FALSE(dic.isPrefix("E"));
	EXPECT_FALSE(dic.isPrefix("EARTH"));
	EXPECT_FALSE(dic.isPrefix("EaRtH"));
	EXPECT_FALSE(dic.isPrefix("ERH"));
	EXPECT_FALSE(dic.isPrefix("H"));
	EXPECT_FALSE(dic.isPrefix("HELLO"));
	EXPECT_FALSE(dic.isPrefix("HeLlO"));
	EXPECT_FALSE(dic.isPrefix("HLO"));
	EXPECT_FALSE(dic.isPrefix(" "));
	EXPECT_FALSE(dic.isPrefix("Î"));
}

void DictionaryTest::clear_empty() {
	dictionary dic;
	dic.insert("hi");
	EXPECT_FALSE(dic.empty());
	dic.clear();
	EXPECT_TRUE(dic.empty());
}

void DictionaryTest::empty_dictionary() {
	dictionary dic;
	EXPECT_TRUE(dic.empty());
	dic.remove("hi");
	dic.clear();
	EXPECT_FALSE(dic.isPrefix("h"));
	EXPECT_FALSE(dic.isPrefix("hi"));
	EXPECT_FALSE(dic.isWord("hi"));
	dic.insert("hi");
	EXPECT_TRUE(dic.isPrefix("h"));
	EXPECT_TRUE(dic.isPrefix("hi"));
	EXPECT_TRUE(dic.isWord("hi"));
	EXPECT_FALSE(dic.empty());
}
