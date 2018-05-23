#include <iostream>
#include <unordered_map>
#include <boost/algorithm/string.hpp>


// input : string a , string b || output : bool 
// determine if one is an anagram of another 
	
std::unordered_map<char, int> count_occurences(std::string& a, const bool c)
{
	//case insensitive
	if (!c)
		boost::algorithm::to_lower(a);	
		
	//to store letter frequency in the first string
	std::unordered_map<char,int> count;

	//count char occurences
	for (size_t i = 0; i < a.length(); i++)
			count[a[i]]++;
	return count;
}	

//technically o(n) but function is called twice which can be avoided 
//TODO: make one map for the first string=> compare frequency of a map with every character from another string
bool isAnagram( std::string& a, std::string& b, const bool c)
{
	return count_occurences(a, c)==count_occurences(b, c);	
}

void remove_spaces(std::string& str) 
{
	std::string::iterator end_pos = std::remove(str.begin(), str.end(), ' ');
	str.erase(end_pos, str.end());
}

int main() 
{
	std::string a, b;
	bool c; 
	std::getline(std::cin, a);
	std::getline(std::cin, b);
	remove_spaces(a);
	remove_spaces(b);
	std::cin >> c;
	std::cout << isAnagram(a, b, c) << std::endl;
	return 0;
}

