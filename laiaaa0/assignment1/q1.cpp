#include <iostream>
#include <vector>
using namespace std;

bool anagrams_caseSensitive (string & s1, string & s2){
  // Compare lengths. If they are not the same, return false.
  if (s1.size() != s2.size()) return false;

  // Create a vector of the size of the ascii table.
  std::vector<int> counts(128);

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
  string lowCaps_s1 = "";
  string lowCaps_s2 = "";

//for each character in string 1
  for (int i=0; i<s1.size(); ++i){
    //if it is a mayus letter
    if (s1[i]>='A' && s1[i]<='Z'){
      //append the equivalent lower letter
      lowCaps_s1.append(1,s1[i]-('A'-'a'));
    }
    else {
      //directly append the value
      lowCaps_s1.append(1,s1[i]);
    }
  }
  for (int i=0; i<s2.size(); ++i){
    if (s2[i]>='A' && s2[i]<='Z'){
      lowCaps_s2.append(1,s2[i]-('A'-'a'));
    }
    else {
      lowCaps_s2.append(1,s2[i]);
    }
  }

  return anagrams_caseSensitive(lowCaps_s1,lowCaps_s2);
}
int main (){
  string s1, s2;
  cout<<"Enter two strings"<<endl;
  cin>>s1>>s2;
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
