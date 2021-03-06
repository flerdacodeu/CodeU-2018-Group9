#include "Dictionary.h"

bool Dictionary::IsPrefixOfWord(std::string prefix, std::string word) const{
  if (prefix.size() > word.size()) return false;
  for (int i = 0; i < prefix.size(); ++i) {
    if (word[i] != prefix[i]) return false;
  }
  return true;
}


Dictionary::Dictionary(const std::vector<std::string> &word_list) {
  for (int i = 0; i < word_list.size(); ++i) {
      InsertWord(word_list[i]);
  }
}

bool Dictionary::IsWord(const std::string & query_word) const {
  auto query_iterator =this->dictionary_words_.find(query_word);
  if (query_iterator == this->dictionary_words_.end()) return false;

  return query_iterator->second;
}


bool Dictionary::IsPrefix(const std::string & query_prefix) const {
  auto query_iterator = this->dictionary_prefixes_.find(query_prefix);
  if (query_iterator == this->dictionary_prefixes_.end()) return false;

  if (query_iterator->second > 0) return true;
  return false;
}
bool Dictionary::InsertWord(const std::string & word) {
  //word already exists
  if (this->dictionary_words_.find(word) != this->dictionary_words_.end()) return false;
  else {//word doesnt exist

    this->dictionary_words_[word] = true;
    std::string prefix = "";
    for (int j = 0; j < word.size(); ++j) {
        prefix = prefix+word[j];
        if (this->dictionary_prefixes_.find(prefix) == this->dictionary_prefixes_.end()) {
            this->dictionary_prefixes_[prefix] = 1;
        }
        else {
          this->dictionary_prefixes_[prefix]++;
        }

    }
    return true;
  }
}
bool Dictionary::RemoveWord(const std::string & word) {
  //word doesnt exist
  if (this->dictionary_words_.find(word) == this->dictionary_words_.end()) return false;
  else { // word exists
    this->dictionary_words_[word] = false;
    std::string prefix = "";
    for (int j = 0; j<word.size(); ++j){
        prefix = prefix+word[j];
        this->dictionary_prefixes_[prefix]--;
    }
    return true;
  }
}
