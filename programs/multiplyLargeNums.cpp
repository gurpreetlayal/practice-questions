#include <iostream>
#include <string>

using namespace std;

string multiply(string s1, string s2) {
    string res(s1.length() + s2.length(), '0');

    cout << res << endl;
    for (int i = s1.length() - 1; i >= 0; i--) {
        for (int j = s2.length() - 1; j >= 0; j--) {
            int is1 = (s1[i] - '0');
            int is2 = (s2[j] - '0');
            int ires = is1 + is2 + (res[i + j] - '0');
            res[i + j]  = '0' + (ires % 10);
            res[i + j + 1] += ires / 10 + '0';
            cout << s1[i] << s2[j] << "ires: " << ires << "(" << i << "," << j << ") -> " << res << endl;
        }
    }

    cout << "Final " << res << endl;
    return res;
}


string multiply2(string num1, string num2) {
        string ans = string(num1.length() + num2.length(), '0');

        for (int i = num1.length() - 1; i >= 0; i--) {
            int carry = 0;
            for (int j = num2.length() - 1; j >= 0; j--) {
                int tempInt = (num1[i] - '0') * (num2[j] - '0') + (ans[i + j + 1] - '0') + carry;
                ans[i + j + 1] = '0' + tempInt % 10;
                carry = tempInt / 10;
            }
            ans[i] += carry;
        }
        
        size_t found = ans.find_first_not_of('0');
        if (found == string::npos) { return "0"; }
        return ans.substr(found);
}

int main () {
    cout << multiply2("22", "999");
    return 0;
}


