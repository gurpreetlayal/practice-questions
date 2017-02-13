#include <iostream>
#include <string> 

using namespace std;

bool interleave(string a, string b, string c) {

    cache[a.size() + 1][b.size() + 1];

    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            if (i == 0 && j == 0) {
                if (c.size()) cache[i][j] = false;
                else cache[i][j] = true;
            }
        }
    }
}

int main () {



}

