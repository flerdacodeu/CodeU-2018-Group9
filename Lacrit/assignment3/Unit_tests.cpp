#include "Unit_tests.h"

void test_IsWord(Dictionary &d){
  EXPECT_TRUE(d.words.find("cat") != d.words.end());
  EXPECT_TRUE(d.words.find("car") != d.words.end());
  EXPECT_FALSE(d.words.find("rat") != d.words.end());
  EXPECT_FALSE(d.words.find("ca") != d.words.end());
  EXPECT_FALSE(d.words.find("CAT") != d.words.end());
}

void test_IsPrefix(Dictionary& d){
  EXPECT_TRUE(d.prefixes.find("c") != d.prefixes.end());
  EXPECT_TRUE(d.prefixes.find("ca") != d.prefixes.end());
  EXPECT_TRUE(d.prefixes.find("cat") != d.prefixes.end());
  EXPECT_TRUE(d.prefixes.find("card") != d.prefixes.end());
  EXPECT_FALSE(d.prefixes.find("") != d.prefixes.end());
  EXPECT_FALSE(d.prefixes.find("a") != d.prefixes.end());
  EXPECT_FALSE(d.prefixes.find("Ra") != d.prefixes.end());
}

void test_IsWordAfterRemoval(Dictionary & d){
  d.words.erase("car");
  EXPECT_FALSE(d.words.find("car") != d.words.end());
}

void test_IsPrefixAfterRemoval(Dictionary & d){
  EXPECT_TRUE(d.prefixes.find("c") != d.prefixes.end());
  EXPECT_TRUE(d.prefixes.find("ca") != d.prefixes.end());
  EXPECT_TRUE(d.prefixes.find("car") != d.prefixes.end());
  d.prefixes.erase("card");
  EXPECT_FALSE(d.prefixes.find("card") != d.prefixes.end());

  d.words.erase("bicycle");
  EXPECT_FALSE(d.prefixes.find("b") != d.prefixes.end());
  EXPECT_FALSE(d.prefixes.find("bi") != d.prefixes.end());
  EXPECT_FALSE(d.prefixes.find("bic") != d.prefixes.end());
}

int main (){
  Dictionary d("dict.txt");
  d.Fill("dict.txt");
  test_IsWord(d);
  test_IsPrefix(d);
  test_IsWordAfterRemoval(d);
  test_IsPrefixAfterRemoval(d);
  return 0;
}
