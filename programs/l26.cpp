// remove duplicates from sorted array.
#include <iostream>
#include <vector>

using namespace std;


int remove(vector<int>& v) {
    if (v.size() <= 1) {
        return v.size();
    }

    int cur = 0, next = 1;
    
    while (next < v.size()) {
        if (v[next] != v[cur]) {
            next++; cur++;
            continue;
        }

        while (next < v.size() && v[next] == v[cur]) {
            next++;
        }
        
        if (next < v.size()) {
            cur++;
            v[cur] = v[next];
        }
    }
    for (auto&k : v ) { cout << k << ","; }
    cout << endl;
    return cur + 1;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "less number of arguments\n";
        return -1;
    }
    vector<int> v;
    for (auto& c: string(argv[1])) {
        v.push_back(c - '0');
    }
    cout << remove(v);
    return 0;
}
