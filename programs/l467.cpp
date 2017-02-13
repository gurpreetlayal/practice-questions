/*
int findSubstringInWraproundString(string p);
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int findSubstringInWraproundString(string p) {
    vector<int> v(26, 0);

    int len = 0;
    int res = 0;
    for (int i = 0; i < p.size(); i++) {
        
        char cur = p[i] - 'a';
        if (i > 0 && p[i-1] != (cur + 26 - 1) % 26 + 'a') {
            len = 1;
        } else {
            len++;
        }

        if (len > v[cur]) {
            res = res - v[cur] + len;
            v[cur] = len;
        }
    }
    return res;
}

int main (int argv, char* argc[] ) {

    if (!argc[1]) { cout << "wrong input\n"; return -1; }
    cout << findSubstringInWraproundString(string(argc[1]));
    return 0;
}

