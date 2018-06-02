
#include <iostream>
#include<vector>
using namespace std;

/*anagram words */
//My assumption:the words alphabet is english letters.    


/*auxiliary function for updating the given histogram, according to the value of the flag add
  increments the counters if its true and decrements them otherwise*/
bool updateHistogram(vector<int>& histogram,string word,bool add, bool caseSensetive){
     const int LEN= 'z' -'a' +1;
    int factor=0;
    if(add){
        factor=1;
    }else{
        factor=-1;
    }
    for(char c: word){
        if((c <'a' || c> 'z') && (c <'A' || c> 'Z')){
            return false;
        }
        if(!caseSensetive){
            char lowerLetter=tolower(c);
            histogram[lowerLetter - 'a']+=factor;
            continue;
        }
        if(c <='a' && c>='z'){
            histogram[c - 'a']+=factor;
        }else{
           histogram[c - 'A'+ LEN]+=factor; 
        }
    }
    return true;
}



//---------------------------------------------------------------------------------------------------------
/*A function that determines if two strings are anagrams ,
	able to handle both case sensitive and case insensitive anagrams,
	according to value of caseSensetive flag variable */
bool areAnagrams(string s1, string s2, bool caseSensetive){
    const int LEN= 'z' -'a' +1;

    if(s1.size()!= s2.size()){
        return false;
    }
    vector<int> histogram(LEN*2,0);
    if(!updateHistogram(histogram,s1,true,caseSensetive)){
        return false;
    }
    if(!updateHistogram(histogram,s2,false,caseSensetive)){
        return false; 
    }

    for(int i=0;i<histogram.size();i++){
        if(histogram[i]!=0){
            return false;
        }
    }
    return true;
}

//---------------------------------------------------------------------------------------------------------
/*sentences anagrams*/
//My assumption:the sentence words alphabet is english letters, delimiters between the are spaces.
//Here are some auxiliary functions.
int countWords(string sentence){
    if(sentence.empty()){
        return 0;
    }
    int count=0;
    for(char c : sentence){
        if(c==' '){
            count++;
        }
    }
    return count+1;
}

string getKWord(string sentence, int k){
    int start, end,count=0;
    int wordsNum=countWords(sentence);
    if(k<=0 || sentence.empty()){
        return "";
    }

    bool startFlag=false;
    bool endFlag=false;
    int i=0;
    for(char c: sentence){
        if(c==' '){
            count++;
        }
        if(count==k-1 && !startFlag){
            start=i+1;
            startFlag=true;
            if(k==wordsNum){
                end=sentence.size()-1;
                endFlag=true;
                break;
            }
        }
        if(count==k && !endFlag){
            end=i-1;
            endFlag=true;
            if(k==1){
                start=0;
                startFlag=true;
                break;
            }
        }
        i++;
    }
    return sentence.substr(start,end-start+1);
}


vector<string> splitIntoWords(string sentence){
    vector<string> words=vector<string>();
    for(int i=0;i<=countWords(sentence);i++){
        words.push_back(getKWord(sentence,i));        
    }
    return words;
}

/*areAnagarmSentences: checks if the given sentences are anagrams,
    the function handles both sensetive and insensitive cases
    according to the caseSensetive flag value*/
bool areAnagarmSentences(string sen1, string sen2, bool caseSensetive){
    vector <string> sentence1=splitIntoWords(sen1);
    vector <string> sentence2=splitIntoWords(sen2);
    
    if(sentence1.size()!=sentence2.size()){
        return false;
    }
    /*a histogram for every sentence, to count for each words
    the number of anagrams in the other sentence*/
    vector<int> counts1(sentence1.size(),0);
    vector<int> counts2(sentence2.size(),0);
    
    for(int i=0;i<sentence1.size();i++){
        for(string word2: sentence2){
            if(areAnagrams(sentence1[i],word2,caseSensetive)){
                counts1[i]++;
            }
        }
    }
    
    for(int i=0;i<sentence2.size();i++){
        for(string word1: sentence1){
            if(areAnagrams(sentence2[i],word1,caseSensetive)){
                counts2[i]++;
            }
        }
    }
    
    /*checking for every sentence if every word
    is an anagram of one word exactly in the other sentence*/
    for(int c: counts1){
        if(c!=1){
            return false;
        }
    }
    for(int c: counts2){
        if(c!=1){
            return false;
        }
    }
    return true;
}



