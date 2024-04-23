// #include <iostream>
// #include <vector>
// #include <queue>
// #include <omp.h>

// using namespace std;

// class Graph {
//     int V;  
//     vector<vector<int>> adj; 


// public:
//     Graph(int V) : V(V), adj(V) {}

   
//     void addEdge(int v, int w) {
//         adj[v].push_back(w);
//     }

//     // Parallel Depth-First Search
//     void parallelDFS(int startVertex) {
//         vector<bool> visited(V, false);
//         parallelDFSUtil(startVertex, visited);
//     }

//     void SequentialDFS(int startVertex) {
//         vector<bool> visited(V, false);
//         SequentialDFSUtil(startVertex, visited);
//     }

 
//     void parallelDFSUtil(int v, vector<bool>& visited) {
//         visited[v] = true;
//         cout << v << " ";

//         #pragma omp parallel for
//         for (int i = 0; i < adj[v].size(); ++i) {
//             int n = adj[v][i];
//             if (!visited[n])
//                 parallelDFSUtil(n, visited);
//         }
//     }
//     void SequentialDFSUtil(int v, vector<bool>& visited) {
//         visited[v] = true;
//         cout << v << " ";

        
//         for (int i = 0; i < adj[v].size(); ++i) {
//             int n = adj[v][i];
//             if (!visited[n])
//                 parallelDFSUtil(n, visited);
//         }
//     }

    
//     void parallelBFS(int startVertex) {
//         vector<bool> visited(V, false);
//         queue<int> q;

//         visited[startVertex] = true;
//         q.push(startVertex);

//         while (!q.empty()) {
//             int v = q.front();
//             q.pop();
//             cout << v << " ";

//             #pragma omp parallel for
//             for (int i = 0; i < adj[v].size(); ++i) {
//                 int n = adj[v][i];
//                 if (!visited[n]) {
//                     visited[n] = true;
//                     q.push(n);
//                 }
//             }
//         }
//     }

//     void SequentialBFS(int startVertex) {
//         vector<bool> visited(V, false);
//         queue<int> q;

//         visited[startVertex] = true;
//         q.push(startVertex);

//         while (!q.empty()) {
//             int v = q.front();
//             q.pop();
//             cout << v << " ";

            
//             for (int i = 0; i < adj[v].size(); ++i) {
//                 int n = adj[v][i];
//                 if (!visited[n]) {
//                     visited[n] = true;
//                     q.push(n);
//                 }
//             }
//         }
//     }
// };

// int main() {
    
//     Graph g(7);
//     g.addEdge(0, 1);
//     g.addEdge(0, 2);
//     g.addEdge(1, 3);
//     g.addEdge(1, 4);
//     g.addEdge(2, 5);
//     g.addEdge(2, 6);
//     double start_time,end_time,start_time1,end_time1;
    
    

//     cout << "Depth-First Search (DFS): ";
//     start_time = omp_get_wtime();
//     g.parallelDFS(0);
//     end_time = omp_get_wtime();
//     cout<<endl;

//     start_time1 = omp_get_wtime();
//     g.SequentialDFS(0);
//     end_time1 = omp_get_wtime();
//     cout<<endl;

//     cout << "Parallel DFS took :"<<end_time-start_time<<" seconds  "<<"Sequential DFS took :"<< end_time1-start_time1<<" seconds"<<endl;

//     cout << "Breadth-First Search (DFS): ";
//     start_time = omp_get_wtime();
//     g.parallelBFS(0);
//     end_time = omp_get_wtime();
//     cout<<endl;

//     start_time1 = omp_get_wtime();
//     g.SequentialBFS(0);
//     end_time1 = omp_get_wtime();
//     cout<<endl;

//     cout << "Parallel BFS took :"<<end_time-start_time<<" seconds "<<"Sequential BFS took : "<< end_time1-start_time1<<" seconds";
//     return 0;
// }


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
