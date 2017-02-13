#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef vector<vector<string>> v2d;
typedef vector<string> v1d;

bool isAnagram(string& s, string::iterator i1, string::iterator i2);
void pBackTracker(string& s, string::iterator itrdx, v1d& onep, v2d& res);

vector<vector<string>> partition(string s) {
    v2d res;
    v1d onep;
    string::iterator itr = s.begin();
    pBackTracker(s, itr, onep, res);
    return res;
}

void pBackTracker(string& s, string::iterator itrdx, v1d& onep, v2d& res) {
    auto x = &(s);

    if (itrdx == s.end()) {
        for (auto& v : onep) { //cout << v << " ";
        }
        //cout << endl;
        res.push_back(onep);
        return;
    }
    
    for (string::iterator itr = itrdx; itr != s.end(); itr++) {
        if (!isAnagram(s, itrdx, itr)) {
            continue;
        }
        auto cacheonep = onep;
        auto itrtemp = itr + 1;
        
        string temp(itrdx, itrtemp);
        onep.push_back(temp);

        for (auto& v : onep) { //cout << v << " ";
        }
        //cout << endl;
        //cout << string(itrtemp, s.end());

        pBackTracker(s, itrtemp, onep, res);

        onep = cacheonep;
    }
}

bool isAnagram(string& s, string::iterator i1, string::iterator i2) {
    while (i1 < i2) {
        if (*i1 != *i2) {
            return false;
        }
        i1++;
        i2--;
    }
    return true;
}

int main () {
    string s("abc");
    /*for (string::iterator itr = s.begin(); itr != s.end(); itr++) {
        cout << *itr;
        cout << endl;
    }
    */
    partition("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

    return 0;
}

