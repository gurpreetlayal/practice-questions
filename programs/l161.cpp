#include "l.h"
bool isOneEditDistance(string A, string B) {
        
        vector<vector<int>> cache(A.size()+1, vector<int>(B.size()+1, 0));

        for (int i = 0; i <= A.size(); i++) {
            cache[i][0] = i;
        }
        
        for (int i = 0; i <= B.size(); i++) {
            cache[0][i] = i;
        }
        
        for (int i = 1; i <= A.size(); i++) {
            for (int j = 1; j <= B.size(); j++) {
                if (A[i-1] == B[j-1]) {
                    cache[i][j] = cache[i-1][j-1];
                } else {
                    cache[i][j] = 1+min(cache[i][j-1], min(cache[i-1][j], cache[i-1][j-1]));
                }
            }
        }
        
        return ((cache[A.size()][B.size()] == 1) ? true : false);
    }

int main (int argc, char* argv[]) {
    if (argc < 3) {
        return -1;
    }

    cout << isOneEditDistance(string(argv[1]), string(argv[2])) << endl;
    return 0;
}    
