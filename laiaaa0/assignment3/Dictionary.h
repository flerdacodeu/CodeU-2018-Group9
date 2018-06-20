#include <vector>
#include <iostream>
#include <map>
class Dictionary{
  private:

    std::map<std::string, bool> dictionary_words_;
    std::map<std::string, int> dictionary_prefixes_;

    bool IsPrefixOfWord(std::string prefix, std::string word);
  public:
    Dictionary(const std::vector<std::string> &word_list);
    bool IsWord (const std::string & query_word);
    bool IsPrefix (const std::string & query_prefix);
    bool InsertWord(const std::string & word);
    bool RemoveWord(const std::string & word);



};

std::vector<std::string> FindAllWords (Dictionary *d, std::vector<std::vector<char> > &grid);
