#include<bits/stdc++.h>
#define endl '\n'

using namespace std;

bool anagramCheck(string,string,char);

int main()
{
    char choice, sensitivity;
    cout<<"Please type 'w' if you'd like to enter 2 words or 's' if you'd like to enter 2 sentences: ";
    cin>>choice;
    if(choice=='w' || choice=='W')
    {
        string word1, word2;
        cout<<"Please enter the first word: ";
        cin>>word1;
        cout<<"Please enter the second word: ";
        cin>>word2;

        cout<<"Please type 's' for Case Sensitive Anagram Checking or 'i' for Case Insensitive Anagram Checking: ";
        cin>>sensitivity;

        cout<<(anagramCheck(word1, word2,tolower(sensitivity))?"The two words are anagrams.":"The two words are not anagrams.");

    }

    return 0;
}


bool anagramCheck(string word1, string word2, char sensitivity)
{
    if(word1.length()!=word2.length())
        return false;

    //map: key is a character and value is the list of positions of the character
    map<char,vector<int>> word1_map, word2_map;
    int i, j;
    int length = word1.size();
    for(i=0; i<length; i++)
    {
        if(sensitivity=='i')
        {
            word1[i]=tolower(word1[i]);
            word2[i]=tolower(word2[i]);
        }
        word1_map[word1[i]].push_back(i);
        word2_map[word2[i]].push_back(i);
    }

    bool differentOrder=false;
    bool sameFrequency=true;

    for(i=0; i<length; i++)
    {
        if(word1_map[word1[i]].size() != word2_map[word1[i]].size())
        {
            sameFrequency=false;
            break;
        }

        if (differentOrder==false)
        {
            for(int j=0; j<word1_map[word1[i]].size(); j++)
            {
                if(word1_map[word1[i]][j]!=word2_map[word1[i]][j])
                {
                    differentOrder=true;
                }
            }
        }
    }

    return(differentOrder&&sameFrequency?true:false);
}
