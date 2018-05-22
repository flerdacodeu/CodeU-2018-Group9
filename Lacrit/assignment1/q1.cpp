#include <iostream>
#include <unordered_map>
#include <boost/algorithm/string.hpp>

// input : string a , string b || output : bool 
// determine if one is an anagram of another 
	
std::unordered_map<char, int> count_occurences(std::string& a)
{
	//case insensitive
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
bool isAnagram( std::string& a, std::string& b)
{
	return count_occurences(a)==count_occurences(b);	
}


int main() 
{
	std::string a, b;
	std::cin >> a;
	std::cin >> b;
	std::cout << a << " : " << b << std::endl;
	std::cout << isAnagram(a, b) << std::endl;
	return 0;
}

