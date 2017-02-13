#include <iostream>
#include <vector>

using namespace std;

int maxP(vector<int>& v) {
    int has1_sell;
    int has1_donothing;
    int has0_buy;
    int has0_donothing;

    // On every day i can take 1 of these above 4 decisions. The profit will be max of
    // doing these activities up until and including the last day.

    // for day 0, init these paths;
    
    has1_sell = 0; // because it's not possible to sell on 1st day.
    has1_donothing = -v[0]; // because on day 2, to have this option valid it means that stock was acquired earlier. That's why acquire price of day 1 is added.
    has0_buy = -v[0]; // cost of acquiring the stock on day 1.
    has0_donothing = 0; // profit will be 0 since no order executed.

    for (int i = 1; i < v.size(); i++) {
        has1_sell = v[i] + max(has1_donothing, has0_buy);
        has1_donothing = max(has1_donothing, has0_buy);
        has0_buy = -v[i] + has0_donothing;
        has0_donothing = max(has0_donothing, has1_sell);
    }
    return max(has1_sell, has0_donothing);
}

#if 0
for(int i=1; i<L; i++) {
        has1_doNothing = has1_doNothing > has0_Buy ? has1_doNothing : has0_Buy;
        has0_Buy = -prices[i] + has0_doNothing;
        has0_doNothing = has0_doNothing > has1_Sell ? has0_doNothing : has1_Sell;
        has1_Sell = prices[i] + has1_doNothing;
    }
    return has1_Sell > has0_doNothing ? has1_Sell : has0_doNothing;

#endif

int main(int argc, char* argv[]) {

    if (argc < 2) {
        cout << "insufficient args\n";
        return 0;
    }

    vector<int> v;
    for (auto& c : string(argv[1])) {
        v.push_back(c - '0');
    }

    cout << maxP(v);
    return 0;
}
