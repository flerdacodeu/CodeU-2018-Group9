
#include <iostream>
#define LEN 'z' -'a' +1
using namespace std;

/*anagram words */
//My assumption:the words alphabet is english letters.    



char lowerIt(char c){
    if(c>='a' && c<='z'){
        return c;
    }
    return 'a' + c-'A';
}
//---------------------------------------------------------------------------------------------------------
/*A function that determines if two strings are anagrams ,
	able to handle both case sensitive and case insensitive anagrams */
bool areAnagrams(string s1, string s2){
    if(s1.size()!= s2.size()){
        return false;
    }
    int histogram[LEN];
    for(int i=0;i<LEN;i++){
        histogram[i]=0;
    }
    for(int i=0;i<s1.size();i++){
        char lowerLetter=lowerIt(s1[i]);
        histogram[lowerLetter - 'a']++;
    }
    for(int i=0;i<s2.size();i++){
        char lowerLetter=lowerIt(s2[i]);
        histogram[lowerLetter - 'a']--;
    } 
    
    for(int i=0;i<LEN;i++){
        if(histogram[i]!=0){
            return false;
        }
    }
    return true;
}

//---------------------------------------------------------------------------------------------------------
/*sentences anagrams*/
//My assumption:the sentence words alphabet is english letters, delimiters between the are spaces.
#define DEL ' ' 
int countWords(string sentence){
    if(sentence.empty()){
        return -1;
    }
    int count=0;
    if(sentence==""){
        return 0;
    }
    for(int i=0;i< sentence.size();i++){
        if(sentence[i]==DEL){
            count++;
        }
    }
    return count+1;
}

string getKWord(string sentence, int k){
    int start, end,count=0;
    int wordsNum=countWords(sentence);
    if(k<=0 || sentence.empty() || sentence== ""){
        return "";
    }

    bool startFlag=false;
    bool endFlag=false;
    for(int i=0;i<sentence.size();i++){
        if(sentence[i]==DEL){
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
    }
    return sentence.substr(start,end-start+1);
}

bool areAnagarmSentences(string sen1, string sen2){
    if(sen1.empty() || sen1.empty()){
        return false;
    }
    int sen1WordsNum=countWords(sen1);
    int sen2WordsNum=countWords(sen2);
    if(sen1WordsNum<0 || sen2WordsNum<0){
        return false;
    }
    if(sen1WordsNum!=sen2WordsNum){
        return false;
    }
    for(int i=1;i<=sen1WordsNum;i++){
        string current1=getKWord(sen1,i);
        bool found=false;
        for(int j=1;j<=sen2WordsNum;j++){
            string current2=getKWord(sen2,j);
            if(areAnagrams(current1,current2)){
                found=true;
            }
        }
        if(!found){
            return false;
        }
    }
    return true;
    
}


