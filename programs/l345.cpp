/*
345. Reverse Vowels of a String

Write a function that takes a string as input and reverse only the vowels of a string.

Example 1:
Given s = "hello", return "holle".

Example 2:
Given s = "leetcode", return "leotcede".

Note:
The vowels does not include the letter "y".

string reverseVowels(string s);

*/
#include <string>
#include <iostream>

using namespace std;

bool isVowel(char s);
string reverseVowels(string s);

int main(int argc, char* argv[]) {
    cout << reverseVowels(string(argv[1]));
    return 0;
}

string reverseVowels(string s) {

    int i = 0;
    int j = s.size() - 1;

    while (i < j) {
        if (isVowel(s[i]) && isVowel(s[j])) {
            char temp = s[i];
            s[i] = s[j];
            s[j] = temp;
            i++;
            j--;
        } else if (isVowel(s[i])) {
            j--;
        } else if (isVowel(s[j])) {
            i++;
        } else {
            i++;
            j--;
        }    
    }
    return s;
}

bool isVowel(char s) {
    switch(s) {
        case 'a' :
        case 'e' :
        case 'i' :
        case 'o' :
        case 'u' :
            return true;
        default : 
            return false;
    }
}



