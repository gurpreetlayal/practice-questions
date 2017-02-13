#include <iostream>
#include <string>

using namespace std;

bool repeatedSubstringPattern(string s);

int main () {
    cout << repeatedSubstringPattern("aaaabaaaab");
    return 0;
}

#if 0
bool repeatedSubstringPattern(string s) {
    if (s.size() <= 1) {
        return false;
    }
    
    string p;
    string::iterator siter = s.begin();
    
    while (siter != s.end() && *siter != *p.begin()) {
        p.append(1, *siter);
        siter++;
    }
    
    if (siter == s.end()) {
        return false;
    }

    cout << p << endl;
    string::iterator piter = p.begin();
    
    while (siter != s.end()) {
        if (*piter == *siter) {
            piter++; siter++;
            if (piter == p.end()) { // full match
                piter = p.begin();
            }
        } else {
            p.insert(p.end(), p.begin(), piter-1);
            while (*siter != *p.begin() && siter != s.end()) {
                p.append(1, *siter);
                if (siter == s.end()) {
                    return false;
                }
            }
            piter = p.begin();
        }
    }
    
    if (siter == s.end() && piter == p.begin()) {
        return true;
    } else {
        return false;
    }
}
#endif

    bool repeatedSubstringPattern(string s) {
        if (s.size() <= 1) {
            return false;
        }
        
        string p;
        string::iterator siter = s.begin();
        
        while (siter != s.end() && *siter != *p.begin()) {
            p.append(1, *siter);
            siter++;
        }
        
        if (siter == s.end()) {
            return false;
        }
        
        string::iterator piter = p.begin();
       
        cout << p << __LINE__ << endl;
        while (siter != s.end()) {
            if (*piter == *siter) {
                piter++; siter++;
                if (piter == p.end()) { // full match
                    piter = p.begin();
                }
            } else {
                auto ptemp = p.begin();
                auto stemp = s.begin();
                while (ptemp != p.end()) {
                    stemp++;
                    ptemp++;
                }
                cout << p << __LINE__ << endl;
                p.insert(p.end(), stemp, siter);
                cout << p << __LINE__ << endl;
                while (*siter != *p.begin() && siter != s.end()) {
                    cout << *siter << __LINE__ << endl;
                    p.append(1, *siter);
                    siter++;
                    if (siter == s.end()) {
                        return false;
                    }
                }
                cout << p << __LINE__ << endl;
                piter = p.begin();
            }
        }
        
        if (siter == s.end() && piter == p.begin()) {
            return true;
        } else {
            return false;
        }
    }
