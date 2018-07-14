#include <iostream>
#include <vector>
#include <set>
#include <map>

#include "codeu_test_lib.h"

void test_PositionWordsDiffer();
void test_ExampleDictionary();


void UpdatePrecedenceRules(const char last_added_letter, std::map<char,std::set<char>> *rules ){
  for (auto key : (*rules)){
    if ((*rules)[key.first].count(last_added_letter)){
      (*rules)[key.first].erase(last_added_letter);
    }
  }
}

bool FindLeastRestrictedLetter(const std::set<char> &letters_set, std::map<char,std::set<char>> *rules, char * least_restricted_letter){
  for (char letter:letters_set){
    std::set<char> current_set = (*rules)[letter];
    if (current_set.size() == 0){
      (*least_restricted_letter) = letter;
      return true;
    }
  }
  return false;
}

void AddPrecedenceRule(const char first, const char second, std::map<char, std::set<char> > *rules){
  if ((*rules).count(first)){
    (*rules)[first].insert(second);
  }
  else {
    (*rules)[first] = std::set<char>();
    (*rules)[first].insert(second);
  }
}
int PositionWordsDiffer(const std::string & word1, const std::string & word2){
  int size1 = word1.size();
  int size2 = word2.size();
  for (int i = 0; i<size1 && i<size2; ++i){
      if (word1[i]!=word2[i]) return i;
  }
  return -1;
}
void AddLettersToSet(const std::string & word, std::set<char> * letters){
    for (char c : word) {
      (*letters).insert(c);
    }
}
std::vector<char> GetAlphabetFromDictionary(const std::vector<std::string> &words){
  //precedence_rules[a] = list of all letters that must come before a.
  std::map<char,std::set<char> > precedence_rules;
  std::vector<char> alphabet;
  std::set<char> all_letters;
  for (int i = 0; i<words.size()-1; ++i){
      AddLettersToSet (words[i],&all_letters);
      int index = PositionWordsDiffer(words[i],words[i+1]);
      if (index >= 0){
        char letter_before = words[i][index];
        char letter_after = words[i+1][index];
        AddPrecedenceRule(letter_after,letter_before,&precedence_rules);
      }
  }

  bool is_possible = true;
  while (!all_letters.empty() && is_possible){
    char least_restricted_letter;
    is_possible = FindLeastRestrictedLetter(all_letters,&precedence_rules,&least_restricted_letter);
    alphabet.push_back(least_restricted_letter);
    all_letters.erase(least_restricted_letter);
    UpdatePrecedenceRules(least_restricted_letter,&precedence_rules);
  }

  return alphabet;
}

int main (){
  test_PositionWordsDiffer();
  test_ExampleDictionary();
}

void test_PositionWordsDiffer(){
  EXPECT_EQ(PositionWordsDiffer("caterpillar","cat"),-1);
  EXPECT_EQ(PositionWordsDiffer("mouse","mice"),1);
  EXPECT_EQ(PositionWordsDiffer("use","mice"),0);
  EXPECT_EQ(PositionWordsDiffer("moooo","mooooo"),-1);
}

void test_ExampleDictionary(){
  std::vector<char> a;
  std::vector<std::string> d{"ART","RAT","CAT","CAR"};
  a = GetAlphabetFromDictionary(d);
}
