#include "codeu_test_lib.h"
#include "Dictionary.h"
#include "q1.h"

void CreateSampleGrid(std::vector<std::vector<char> > &grid){
    grid.clear();
    std::vector<char> line1{'a','a','r'};
    std::vector<char> line2{'t','c','d'};
    grid.push_back(line1);
    grid.push_back(line2);

}


Dictionary * test_CreateDictionaryFromVector(){
    std::vector<std::string> v{"car","card","cart","cat","rat"};
    Dictionary * d = new Dictionary(v);
    return d;
}

void test_IsWordInDictionary(Dictionary * d){
  EXPECT_TRUE(d->IsWord("cat"));
  EXPECT_TRUE(d->IsWord("car"));
  EXPECT_TRUE(d->IsWord("rat"));
  EXPECT_FALSE(d->IsWord("c"));
  EXPECT_FALSE(d->IsWord("RAT"));
  EXPECT_FALSE(d->IsWord("ca"));
}

void test_IsPrefixInDictionary (Dictionary * d){
  EXPECT_TRUE(d->IsPrefix("c"));
  EXPECT_TRUE(d->IsPrefix("ca"));
  EXPECT_TRUE(d->IsPrefix("cat"));
  EXPECT_TRUE(d->IsPrefix("card"));
  EXPECT_FALSE(d->IsPrefix(""));
  EXPECT_FALSE(d->IsPrefix("a"));
  EXPECT_FALSE(d->IsPrefix("Ra"));
}

void test_IsWordAfterRemoval (Dictionary * d){
  EXPECT_TRUE(d->RemoveWord("cat"));
  EXPECT_FALSE(d->IsWord("cat"));
}

void test_IsPrefixAfterRemoval (Dictionary * d){
  EXPECT_TRUE(d->RemoveWord("card"));
  EXPECT_TRUE(d->IsPrefix("c"));
  EXPECT_TRUE(d->IsPrefix("ca"));
  EXPECT_TRUE(d->IsPrefix("car"));
  EXPECT_FALSE(d->IsPrefix("card"));

  EXPECT_TRUE(d->RemoveWord("rat"));
  EXPECT_FALSE(d->IsPrefix("r"));
  EXPECT_FALSE(d->IsPrefix("ra"));
  EXPECT_FALSE(d->IsPrefix("rat"));
}

void test_example(){
  std::vector<std::vector<char> > letter_grid(2, std::vector<char> (3,'.'));
  CreateSampleGrid(letter_grid);
  std::vector<std::string> v{"car","card","cart","cat"};
  Dictionary * d = new Dictionary(v);
  std::vector<std::string> result;
  result = FindAllWords(d,letter_grid);
  EXPECT_EQ(result.size(),3);
}

void all_tests(){
  Dictionary * d = test_CreateDictionaryFromVector();
  test_IsWordInDictionary(d);
  test_IsPrefixInDictionary(d);
  test_IsWordAfterRemoval(d);
  test_IsPrefixAfterRemoval(d);
  test_example();
}
