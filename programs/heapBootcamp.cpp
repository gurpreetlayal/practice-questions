#include <iostream>
#include <vector>
#include <string>

using namespace std;

void swap(vector<int>& v, int i, int j) {
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int heapify(vector<int>& v, int i) {
    if (i >= v.size()/2) {
        return 0;
    }

    int lc = 2*i + 1;
    int rc = 2*i + 2;
    int chosen = i;

    if (lc >= v.size()) { lc = i; }
    if (rc >= v.size()) { rc = i; }

    if (v[chosen] > v[lc]) {
        chosen = lc;
    }

    if (v[chosen] > v[rc]) {
        chosen = rc;
    }
    
    if (chosen != i) {
        swap(v, i, chosen);
        heapify(v, chosen);
    }
    return 0;
}

int makeHeap(vector<int>& v) {
    if (v.size() <= 1) {
        return 0;
    }

    for (int i = v.size()/2 - 1; i >= 0; i--) {
        heapify(v, i);
    }
}

int findMin(vector<int>& v, int& res) {
    if (v.size() == 0) {
        return 0;
    }
    res = v[0];

    v[0] = v[v.size() - 1];
    v.erase(v.end() - 1);
    heapify(v, 0);
    return 1;
}

int heapSort(vector<int>& v) {
    makeHeap(v);

    vector<int> res;
    while(!v.empty()) {
        int minElem;
        if (findMin(v, minElem))
            res.push_back(minElem);
    }
    v = res;
    return 0;
}


void printVec(vector<int>& v) {
    for (auto& y: v) {
        cout << y << " ";
    }
    cout << endl;
}

int main (int argc, char* argv[]) {

    if (argc < 2) { cout << "less args\n"; return -1; }

    vector<int> v;
    for (auto& c:string(argv[1])) {
        v.push_back(c - '0');
    }
    makeHeap(v);
    printVec(v);

    heapSort(v);
    printVec(v);
    return 0;
}
