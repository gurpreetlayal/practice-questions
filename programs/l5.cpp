#include "l.h"

void print (vector<vector<int>> v);

string longestPalindrome(string s1) {
        vector<vector<int>> cache(s1.size() + 1, vector<int>(s1.size() + 1, 0));
        string s2 = s1;
        reverse(s2.begin(), s2.end());
        
        for (int i = 0; i <= s1.size(); i++) {
            for (int j = 0; j <= s1.size(); j++) {
                if (i == 0 || j == 0) {
                    cache[i][j] = 0;
                } else if (s1[i-1] == s2[j-1]) {
                    cache[i][j] = 1 + cache[i-1][j-1];
                } else {
                    cache[i][j] = 0;
                }
            }
        }
        
        print(cache);
        
        int idx1, idx2;
        int max = 0;
         for (int i = 0; i <= s1.size(); i++) {
            for (int j = 0; j <= s1.size(); j++) {
                if (cache[i][j] > max) { idx1 = i; idx2 = j; max = cache[i][j]; }
            }
         }
         
        cout << s1.size() << " " <<  idx1 << " " << idx2 << " " << max << endl;
        return s1.substr(idx1 - max, max);
        
    }
    
    void print (vector<vector<int>> v) {
        for (auto& c : v) {
            for (auto k : c) {
                cout << k << " ";
            }
            cout << endl;
        }
        cout << endl;
    }


int main (int argc, char* argv[]) {

    if (argc < 2) {
        return 0;
    }

    string s(argv[1]);
    cout << longestPalindrome(s) << endl;

    return 0;
}
