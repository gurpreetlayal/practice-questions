#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>


using namespace std;

struct Node {
    int val;
    vector<Node> neighbors;
    Node(int v, vector<Node> n) : val(v), neighbors(n) {}
};

struct Graph {
    int nvertices;
    vector<Node> vertices;
    Graph(int nv, vector<Node> v) : nvertices(nv), vertices(v) {}
};

void addEdge(Graph& g, int s, int d) {
    g.vertices[s-1].neighbors.push_back(g.vertices[d-1]);
}

// DFS is equivalent to pre-order traversal in trees.
void printdfs(Graph& g, int sidx) {
    vector<int> order;
    set<int> visited;
    dfsrecur(g, sidx, visited, order);

    for (auto& o: order) {
        cout << o << " ";
    }
    cout << endl;
}

void dfsrecur(Graph& g, int sidx, set<int>& visited, vector<int>& order) {
    visited.insert(sidx);
    order.push_back(sidx);
    for (auto& n : g.vertices[sidx-1].neighbors) {
        if (visited.find(n.val) == visited.end()) {
            dfsrecur(g, n.val, visited, order);
        }
    }
}

// Use queue - same as tree level order traversal
void printbfs(Graph& g, int sidx) {
    vector<int> order;
    set<int> visited;

    visited.insert(sidx);
    queue<int> q;
    q.push(sidx);

    while (!q.empty()) {
        order.push_back(q.front());
        
        for (auto& c : g.vertices[q.front()-1].neighbors) {
            if (visited.find(c.val) == visited.end()) {
                visited.insert(c.val);
                q.push(c.val);
            }
        }
        q.pop();
    }

    for (auto& o : order) {
        cout << o << " ";
    }
    cout << endl;
}

// Topological ordering is do post order traversal(slightly changed dfs, since dfs is pre order)  and reverse the order.
void printtopo(Graph& g) {

}

int main () {
    {
        int nv = 5;
        vector<Node> v;
        for (int i = 1; i <= nv; i++) {
            v.emplace_back(i, vector<Node>());
        }

        Graph g(nv, v);
        addEdge(g, 1, 2);
        addEdge(g, 1, 4);
        addEdge(g, 2, 3);
        addEdge(g, 3, 4);
        addEdge(g, 3, 5);
        addEdge(g, 4, 5);
        
        printdfs(g, 1);

        printbfs(g, 1);

        printtopo(g);
    }

    {
        int nv = 4;
        vector<Node> v;
        for (int i = 1; i <= nv; i++) {
            v.emplace_back(i, vector<Node>());
        }

        Graph g(nv, v);
        addEdge(g, 1, 2);
        addEdge(g, 1, 3);
        addEdge(g, 2, 3);
        addEdge(g, 3, 1);
        addEdge(g, 3, 4);
        addEdge(g, 4, 4);
        
        printdfs(g, 3);

        printbfs(g, 3);

        printtopo(g);

    }

    return 0;
}

    


