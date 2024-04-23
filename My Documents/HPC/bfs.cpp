
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

    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            cout << u << " ";

#pragma omp parallel for
            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        cout << endl;
    }

    void SBFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            cout << u << " ";

// #pragma omp parallel for
            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
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


    cout << "BFS Traversal: ";
    start_time = omp_get_wtime();
    g.BFS(0);
    end_time = omp_get_wtime();
    
    cout<<"Parallel BFS Time: "<<end_time-start_time<<endl;

    cout << "BFS Traversal: ";
    start_time = omp_get_wtime();
    g.SBFS(0);
    end_time = omp_get_wtime();
    

    cout<<"Sequential BFS Time: "<<end_time-start_time<<endl;

   // cout << "DFS Traversal: ";
    
    //start_time = omp_get_wtime();
    //g.DFS(0);
    //end_time = omp_get_wtime();

    //cout<<"Parallel DFS Time: "<<end_time-start_time<<endl;

    //start_time = omp_get_wtime();
   // g.SDFS(0);
   // end_time = omp_get_wtime();


   // cout<<"Sequential DFS Time: "<<end_time-start_time<<endl;


    return 0;
}
