#include <chrono>
#include "l.h"
class Solution {
public:
    void print (vector<string>& board) {
        cout << "************" << endl;
        for (auto& c: board) {
            cout << c << endl;
        }
        cout << "************" << endl;
    }

    bool isValid(int x, int y,vector<string> board) {
        int tx = x, ty = 0;
        while (ty < board.size()) {
            if (board[tx][ty] == 'Q') {
                return false;
            }
            ty++;
        }
        
        tx = 0;
        ty = y;
        while (tx < board.size()) {
            if (board[tx][ty] == 'Q') {
                return false;
            }
            tx++;
        }
        
        tx = x;
        ty = y;
        while(tx >= 0 && ty >= 0) {
            if (board[tx][ty] == 'Q') {
                return false;
            }
            tx--;
            ty--;
        }
        
        tx = x;
        ty = y;
        while(tx < board.size() && ty < board.size()) {
            if (board[tx][ty] == 'Q') {
                return false;
            }
            tx++;
            ty++;
        }
        
        tx = x;
        ty = y;
        while(tx >= 0 && ty < board.size()) {
            if (board[tx][ty] == 'Q') {
                return false;
            }
            tx--;
            ty++;
        }
        
        tx = x;
        ty = y;
        while(tx < board.size() && ty >= 0) {
            if (board[tx][ty] == 'Q') {
                return false;
            }
            tx++;
            ty--;
        }
        
        return true;
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        int x = 0, y = 0;
     //   for (;x < n; x++) {
       //     for (; y < n; y++) {
                vector<string> board(n, string(n, '.'));
                int sidx = x;
                int sidy = y;
                int sn = n;
                //cout << __LINE__ << endl;
                qdp(sn, board, res, sidx, sidy);    
         //   }
        //}
        return res;
    }
    
    void qdp(int& n, vector<string>& board, vector<vector<string>>& res, int& x, int& y) {
        if (n == 0) {
        //    cout << __LINE__ << endl;
            res.push_back(board);
            return;
        }
        
        auto cacheb = board;
        auto newn = n;

        int i = x;
        int j = y;
        for (; i < board.size(); i++) {
            for (; j < board.size(); j++) {
                if (isValid(i, j, board)) {
                    //make choice
                    auto ln = n;
                    n--;
                    board[i][j] = 'Q';
                  //  cout << i << " " << j << endl; 
                   // print(board);
                    int newi = i;
                    int newj = (j + 1) % board.size();
                    if (!j) newi = i + 1;
                    qdp(n, board, res, newi, newj);
                    
                    board[i][j] = '.';
                    n = ln;
                }
            }
            j = 0;
        }
    //   n = newn;
     //   board = cacheb;
    }
};

int main(int argc, char* argv[]) {
    Solution s;
    if (argc < 2) { return 1; }
    for (int i = 0; i < 10; i++) {
        auto cur = std::chrono::system_clock::now();
        auto v = s.solveNQueens(i);
        cout <<  (std::chrono::system_clock::now() - cur).count() << endl;
    }
    return 0;
}
