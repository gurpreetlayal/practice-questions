#include <iostream>
#include <string.h>

using namespace std;

void reverseOne(char* s, int firstIdx, int lastIdx) {
    while (firstIdx < lastIdx) {
        char temp = *(s + firstIdx);
        *(s + firstIdx) = *(s + lastIdx);
        *(s + lastIdx) = temp;
        firstIdx++; lastIdx--;
    }
}

void reverseWords(char *s) {
    int lastIdx = 0;
    int firstIdx = 0;
    while (*(s + lastIdx) != '\0') {
        lastIdx++;
    }
    lastIdx--;
    
    reverseOne(s, firstIdx, lastIdx);
    
    firstIdx = 0;
    while (*(s + firstIdx) != '\0') {
        int curFirstIdx, curLastIdx;
        curFirstIdx = firstIdx;
        while (*(s + curFirstIdx) == ' ' && *(s + curFirstIdx) != '\0') {
            curFirstIdx++;
        }
        if (*(s + curFirstIdx) == '\0') {
            break;
        }
        curLastIdx = curFirstIdx;
        
        while (*(s + curLastIdx) != ' ' && *(s + curLastIdx) != '\0') {
            curLastIdx++;
        }
        curLastIdx--;
        
        reverseOne(s, curFirstIdx, curLastIdx);
        
        firstIdx = curLastIdx + 1;
    }
}

int main () {
    char *s = new char[20];
    strcpy(s, "this is   red book\0");
    reverseWords(s);
    string str(s);
    cout << s;
}

