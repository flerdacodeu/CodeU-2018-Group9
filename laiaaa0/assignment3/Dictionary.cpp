#include "Dictionary.h"

bool Dictionary::IsPrefixOfWord(std::string prefix, std::string word){
  if (prefix.size()>word.size()) return false;
  else {
    for (int i=0; i<prefix.size(); ++i){
      if (word[i]!=prefix[i]) return false;
    }
    return true;
  }
}


Dictionary::Dictionary(std::vector<std::string> &word_list){
  this->dictionary_words_ = word_list;

}
bool Dictionary::IsWord (std::string query_word){
  for (int i = 0; i<this->dictionary_words_.size(); ++i){
    if (dictionary_words_[i] ==query_word) return true;
  }
  return false;

}
bool Dictionary::IsPrefix (std::string query_prefix){
  for (int i = 0; i<this->dictionary_words_.size(); ++i){
    if (IsPrefixOfWord(query_prefix,dictionary_words_[i])) return true;
  }
  return false;


}
