//ASSUMPTIONS
/*
- Restricted to the 128 ASCII characters.
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
        string word = sentence.substr(last, next-last); // when next is npos (-1), next-last is a very big number because the second parameter of substr is unsigned
        if(!word.empty()){
            tokens.push_back(word);
        }
        if(next ==  string::npos){
            break;
        }
        last = next+1;
    }

    return tokens;

}

map< vector<int>,int > get_map(string sentence1, bool *error){
    vector<string> words = split_spaces(sentence1);
    map< vector<int>,int > words_freq;
    for (const string &word : words) {
        vector<int> chars_freq(128); //The ASCII table has 128 characters
        for (char c : word){
            if(c<0 || c>127){
                cout << "ERROR: This program is restricted to ASCII characters, The sentence you entered has non-ASCII characters ";
                if(error){
                  *error = 1;
                }
                return {};
            }
            chars_freq[toupper(c)]++; // toupper Converts the char to its uppercase equivalent if c is a lowercase letter, else the char value returned is unchanged.
        }
        words_freq[chars_freq]++;
    }
    return words_freq;
}

//returns false if both sentences are not anagrams or if an error occurred
//returns true if both sentences are anagrams
bool are_anagrams(string sentence1, string sentence2, bool *error){
    if(error){
      *error = 0;
    }

    map< vector<int>,int > map1 = get_map(sentence1, error);
    if(error && *error){
        return 0;
    }

    map< vector<int>,int > map2 = get_map(sentence2, error);
    if(error && *error){
        return 0;
    }

    return map1 == map2;
}

int main()
{
    // test
    bool error;
    cout << are_anagrams("", "", &error)<< endl;
    cout << are_anagrams("ãÑÍÈÇð" , "ãÑÍÈÇð", &error) << endl;
    cout << are_anagrams( "  Good   morning   world " , "dooG gninrom dlrow", &error) << endl;
    cout << are_anagrams( "GoOd" , "dogo", &error) << endl;
    cout << are_anagrams( "GoO,d" , "dogo,", &error) << endl;
    cout << are_anagrams( "GoOd," , "dogo ,", &error) << endl;
    cout << are_anagrams( " GoOd ," , " , dogo", &error) << endl;

    return 0;
}
