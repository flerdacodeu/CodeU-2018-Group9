#include <iostream>
#include <vector>
#include <ctype.h>
#include <algorithm>
using namespace std;
/*
Possible solutions
option 1 )
  order the letters in the word. and compare
  cost : O(nlogn)
option 2 )
  count characters (128 or 256?
  cost : O (n)
  )
*/
bool anagrams_caseSensitive (const string & s1, const string & s2){
  // Compare lengths. If they are not the same, return false.
  if (s1.size() != s2.size()) return false;

  // Create a vector of the size of the EXTENDED ascii table.

  std::vector<int> counts(256);

  // For each of the characters in the strings
  for (int i=0; i<s1.size(); i++){
    //Add one count to the ascii position of the current character of the first string
    counts[s1[i]]++;
    //Delete one count from the ascii position of the current character of the second string
    counts[s2[i]]--;

  }

  //Check if any value in the vector is not 0

  for (int i = 0; i<counts.size(); ++i){

    if (counts[i]!=0){
      return false;

    }
  }
  return true;
}
bool anagrams_caseInsensitive (string & s1, string & s2){

  //Create the equivalent low caps strings for each string
  std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
  std::transform(s2.begin(), s2.end(), s2.begin(), ::tolower);

  return anagrams_caseSensitive(s1,s2);
}
int main (){
  string s1, s2;
  cout<<"Enter two strings (one in each line)"<<endl;

  getline(cin,s1);
  getline(cin,s2);
  if (anagrams_caseSensitive(s1,s2)){
    cout<<"These strings are anagrams!"<<endl;
  }
  else{
    if (anagrams_caseInsensitive(s1,s2)){
      cout<<"These strings are case-insensitive-anagrams!"<<endl;

    }
    else {
      cout<<"These strings are not anagrams"<<endl;
    }
  }
}
