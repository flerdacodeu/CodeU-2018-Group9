#include <fstream>
#include <iostream>
#include <unordered_set>
#include <string>


class Dictionary {
public:
	Dictionary();
    Dictionary(std::string);
    ~Dictionary();
	void Fill(std::string);
	bool isPrefix(const std::string&); 

    std::unordered_set<std::string> words;
    std::unordered_set<std::string> prefixes;
	std::string path;
};

Dictionary::Dictionary() {};
Dictionary::Dictionary(std::string path):
	path(path)
{}
// Load the word dictionary and prefixes dictionary from a given file
void Dictionary::Fill(std::string path) 
{
    std::string line;
    std::ifstream file(path);
    if (file.is_open()) {
        while (std::getline(file, line)) {
                // Add to word dictionary
                this->words.insert(line);
                // Add to prefixes dictionary
				this->prefixes.insert(line);
                for (size_t i = 1; i < line.length(); i++) {
                    this->prefixes.insert(line.substr(0, i));
                }
            }
        }
    file.close();
}
Dictionary::~Dictionary() {};
