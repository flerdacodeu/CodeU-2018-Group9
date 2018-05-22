//ASSUMPTIONS
/*
- Restricting to the 128 ASCII characters.
- "  Good   morning   world " is an anagram to "dooG gninrom dlrow" // spaces don't matter
- "GoOd" is an anagram to "dogo" // case insensitive
- it separates input sentences based on spaces which means: "GoO,d" is an anagram to "dogo," but "GoOd," is not an anagram to "dogo ,"
                                                            " GoOd ," is an anagram to " , dogo"
*/

#include <iostream>
#include <map>
#include <vector>
using namespace std;

vector<string> split_spaces(string sentence){

    vector <string> tokens;
    int last = 0;
     while(last<sentence.length()){
        int next = sentence.find(' ', last);
        string word = sentence.substr(last, next-last);
        if(word != "")
            tokens.push_back(word);
        if(next ==  string::npos)
            break;
        last = next+1;
    }

    return tokens;

}

map< vector<int>,int > get_map(string sentence1){

    vector<string> words = split_spaces(sentence1);
    map< vector<int>,int > words_freq;
    for(int i=0; i<words.size(); i++){
        vector<int> letters_freq(128); //The ASCII table has 128 characters
        for(int j=0; j<words[i].length(); j++){
            letters_freq[toupper(words[i][j])]++; // toupper Converts the char to its uppercase equivalent if c is a lowercase letter, else the char value returned is unchanged.
        }
        words_freq[letters_freq]++;
    }
    return   words_freq;

}

//returns 0 if both sentences are not anagrams
//returns 1 if both sentences are anagrams
bool are_anagrams(string sentence1, string sentence2){

    map< vector<int>,int > map1 = get_map(sentence1);
    map< vector<int>,int > map2 = get_map(sentence2);

    if(map1 == map2)
        return true;

    return false;
}

int main()
{
    // test
    cout << are_anagrams( "  Good   morning   world " , "dooG gninrom dlrow") << endl;
    cout << are_anagrams( "GoOd" , "dogo") << endl;
    cout << are_anagrams( "GoO,d" , "dogo,") << endl;
    cout << are_anagrams( "GoOd," , "dogo ,") << endl;
    cout << are_anagrams( " GoOd ," , " , dogo") << endl;

    return 0;
}
