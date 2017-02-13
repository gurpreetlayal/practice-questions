#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class MedianFinder {
public:

    priority_queue<int> maxpq;
    priority_queue<int, vector<int>, greater<int>> minpq;
    // Adds a number into the data structure.
    void addNum(int num) {
        if (maxpq.empty() && minpq.empty()) {
            minpq.push(num);
        } else if (num >= minpq.top()) {
            minpq.push(num);
        } else {
            maxpq.push(num);
        }

        int eDiff = (maxpq.size() - minpq.size());
        if (abs(eDiff) > 1) {
            if (maxpq.size() > minpq.size()) {
                int transfer = maxpq.top();
                maxpq.pop();
                minpq.push(transfer);
            } else {
                int transfer = minpq.top();
                minpq.pop();
                maxpq.push(transfer);
            }
        }
    }

    // Returns the median of current data stream
    double findMedian() {
        if (maxpq.size() == minpq.size()) {
            return (double(maxpq.top()) + double(minpq.top()))/2;
        } else if (maxpq.size() > minpq.size()) {
            return double(maxpq.top());
        } else {
            return double(minpq.top());
        }
    }
};


int main () {
    MedianFinder m;
    cout << "going to add -10, 20, 0, -30, 5, 25, 30, -50, -100, -2, 2" << endl;
    m.addNum(-10);
    cout << m.findMedian() << endl;
    m.addNum(20);
    cout << m.findMedian() << endl;
    m.addNum(0);
    cout << m.findMedian() << endl;
    m.addNum(-30);
    cout << m.findMedian() << endl;
    m.addNum(5);
    cout << m.findMedian() << endl;
    m.addNum(25);
    cout << m.findMedian() << endl;
    m.addNum(30);
    cout << m.findMedian() << endl;
    m.addNum(-50);
    cout << m.findMedian() << endl;
    m.addNum(-100);
    cout << m.findMedian() << endl;
    m.addNum(-2);
    cout << m.findMedian() << endl;
    m.addNum(2);
    cout << m.findMedian() << endl;
    return 0;
} 
