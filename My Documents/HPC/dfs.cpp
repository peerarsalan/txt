#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <omp.h>

using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V) : V(V) {
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Assuming undirected graph
    }

   void DFS(int start) {
        vector<bool> visited(V, false);
        stack<int> s;

        s.push(start);

        while (!s.empty()) {
            int u = s.top();
            s.pop();

            if (!visited[u]) {
                cout << u << " ";
                visited[u] = true;

#pragma omp parallel for
                for (int v : adj[u]) {
                    if (!visited[v]) {
                        s.push(v);
                    }
                }
            }
        }
        cout << endl;
    }

    void SDFS(int start) {
        vector<bool> visited(V, false);
        stack<int> s;

        s.push(start);

        while (!s.empty()) {
            int u = s.top();
            s.pop();

            if (!visited[u]) {
                cout << u << " ";
                visited[u] = true;

// #pragma omp parallel for
                for (int v : adj[u]) {
                    if (!visited[v]) {
                        s.push(v);
                    }
                }
            }
        }
        cout << endl;
    }
};
int main() {
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);

    double start_time,end_time;


    cout << "DFS Traversal: ";
    
    start_time = omp_get_wtime();
    g.DFS(0);
    end_time = omp_get_wtime();

    cout<<"Parallel DFS Time: "<<end_time-start_time<<endl;

    start_time = omp_get_wtime();
    g.SDFS(0);
    end_time = omp_get_wtime();


    cout<<"Sequential DFS Time: "<<end_time-start_time<<endl;


    return 0;
}

