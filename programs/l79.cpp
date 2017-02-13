#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void resetVisited(bool** v, int r, int c);
bool search_board(char** b, int r, int c, int i, int j, char* word, bool** v);

bool exist(char** b, int r, int c, char* word) {
    bool** v = (bool**)malloc(sizeof(bool*)*r);
    for (int i = 0; i < r; i++) {
        v[i] = (bool*)malloc(sizeof(bool)*c);
    }
    resetVisited(v, r, c);
    bool res = false;
     
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            resetVisited(v, r, c);
            //cache
            char* cacheword = word;
            
            res |= search_board(b, r, c, i, j, word, v);
            if (res) { return res; }
            
            word = cacheword;
        }
    }
    return res;   
}
    
bool search_board(char** b, int r, int c, int i, int j, char* word, bool** v) {
    
    if (i > r || i < 0 || j > c || j < 0) {
        return false;
    }
    
    while (*word != '\0' && *word == b[i][j] && v[i][j] == false) {
        v[i][j] = true;
        return (search_board(b, r, c, i, j - 1, word + 1, v) ||
                search_board(b, r, c, i, j + 1, word + 1, v) ||
                search_board(b, r, c, i - 1, j, word + 1, v) ||
                search_board(b, r, c, i + 1, j, word + 1, v));
    }
    
    if (*word == '\0') {
        return true;
    } else {
        return false;
    }
}

void resetVisited(bool** v, int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            v[i][j] = false;
        }
    }
}

int main () {

    return 0;
}

