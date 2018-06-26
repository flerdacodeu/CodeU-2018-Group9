#include <vector>
#include <string>
#include <iostream>
#include <map>

#ifndef DICTIONARY_H
#define DICTIONARY_H

class Dictionary{

  private:
    std::map<std::string, bool> dictionary_words_;
    std::map<std::string, int> dictionary_prefixes_;
    bool IsPrefixOfWord(std::string prefix, std::string word) const;
    bool InsertWord(const std::string & word);

  public:
    Dictionary(const std::vector<std::string> &word_list);
    //Returns if a word is in the dictionary
    bool IsWord(const std::string & query_word) const;
    //Returns if a non-empty prefix belongs to any word in the dictionary
    bool IsPrefix(const std::string & query_prefix) const;
    bool RemoveWord(const std::string & word);
};

#endif
