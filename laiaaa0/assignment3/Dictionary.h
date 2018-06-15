#include <vector>
#include <iostream>
class Dictionary{
  private:
    std::vector<std::string> dictionary_words_;

    bool IsPrefixOfWord(std::string prefix, std::string word);
  public:
    Dictionary(std::vector<std::string> &word_list);
    bool IsWord (std::string query_word);
    bool IsPrefix (std::string query_prefix);



};
