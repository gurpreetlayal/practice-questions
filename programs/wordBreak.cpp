#include "l.h"

    bool bt (string s, int& idx, int& cur, unordered_set<string>& dict) {
        if (cur == s.length()) {
            return true;
        } else if (idx >= s.length()) {
            return false;
        }
        
        string st;
        bool res = false;
        for (int i = idx; i < s.length(); i++) {
            st += s[i];
            if (dict.find(st) == dict.end()) {
                continue;
            }
            cout << st << endl;
            cur += st.size();
            auto nextIdx = i + 1;
            res |= bt(s, nextIdx, cur, dict);
            cur -= st.size();
            if (res) {
                return res;
            }
        }
        return false;
    }

bool wordBreak(string s, unordered_set<string>& dict) {
        int cur = 0;
        int idx = 0;
        return bt(s, idx, cur, dict);
    }
    

int main () {
    string s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";
    unordered_set<string> dict = {"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"};
    cout << wordBreak(s, dict);
    return 0;
}
