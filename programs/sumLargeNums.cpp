#include <iostream>
#include <string>

using namespace std;

string sumLarge (string s1, string s2) {

    string res(max(s1.length(), s2.length()) + 1, '0');
    int i, j;

    for (i = s1.length() - 1, j = s2.length() - 1;
         i >= 0 && j >= 0;
         i--, j--) {
        int temp = (s1[i] - '0') + (s2[j] - '0') + res[max(i, j) + 1] - '0';
        res[max(i, j) + 1] = (temp % 10) + '0';
        res[max(i, j)] += temp / 10;
    }

    if (i < 0) {
        while (j >= 0) {
            int temp = (res[j + 1] - '0') + (s2[j] - '0');
            res[j + 1] = (temp % 10) + '0';
            res[j] += temp / 10;
            j--;
        }
    } else {
        while (i >= 0) {
            int temp = (res[i + 1] - '0') + (s1[i] - '0');
            res[i + 1] = (temp % 10) + '0';
            res[i] += temp / 10;
            i--;
        }
    }

    auto found = res.find_first_not_of('0');
    return res.substr(found);
}


int main (int argc, char* argv[]) {
    cout << sumLarge(argv[1], argv[2]);
}

