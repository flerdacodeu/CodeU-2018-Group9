#include <iostream>
#include <unordered_map>
#include <boost/algorithm/string.hpp>
	
std::unordered_map<char, int> count_occurences_word(std::string& str, const bool isCaseSensitive)
{
	//case insensitive
	if (!isCaseSensitive)
		boost::algorithm::to_lower(str);	
		
	//to store letter frequency in the first string
	std::unordered_map<char,int> count;

	//count char occurences
	for (char c : str) 
			count[c]++;
	return count;
}	

//technically o(n) but function is called twice which can be avoided 
//TODO: make one map for the first string=> compare frequency of a map with every character from another string
bool isAnagram( std::string& f_str, std::string& s_str, const bool isCaseSensitive)
{
	return count_occurences_word(f_str, isCaseSensitive)==count_occurences_word(s_str, isCaseSensitive);	
}

void remove_spaces(std::string& str) 
{
	std::string::iterator end_pos = std::remove(str.begin(), str.end(), ' ');
	str.erase(end_pos, str.end());
}

int main() 
{
	std::string a, b;
	char case_sensitive; 
	std::cout << "Input first string: " << std::endl;
	std::getline(std::cin, a);
	std::cout << "Input second string: " << std::endl;
	std::getline(std::cin, b);
	std::cout << "Case Sensitive?(c|i) (c => sensitive || i => insensitive)" << std::endl;
	std::cin >> case_sensitive;
	const std::string word = "Words aren`t anagrams";
		remove_spaces(a);
		remove_spaces(b);	
		if (a.length() == b.length())
		{
	   	    bool res = isAnagram(a, b, case_sensitive);
			if(res) std::cout << "Words are anagrams" << std::endl;
			else std::cout << word << std::endl;
		} else std::cout << word << std::endl;
	return 0;
}

