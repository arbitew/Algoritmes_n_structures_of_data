#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <queue>
#include <stack>

using namespace std;

class Graph {
private:
    vector<vector<int>> adjMatrix;
    vector<pair<int, int>> edgeList;
    vector<vector<int>> incMatrix;
    vector<vector<int>> adjList;
    int numVertices;
    int numEdges;
    bool directed;

public:
    Graph(int minVertices, int maxVertices, int minEdges, int maxEdges, int maxEdgesPerVertex, bool isDirected) {
        numVertices = rand() % (maxVertices - minVertices + 1) + minVertices;
        numEdges = rand() % (maxEdges - minEdges + 1) + minEdges;
        directed = isDirected;

        // Initialize adjacency matrix and incidence matrix with zeros
        adjMatrix.assign(numVertices, vector<int>(numVertices, 0));
        incMatrix.assign(numVertices, vector<int>(numEdges, 0));

        // Generate edges
        int edgeCount = 0;
        while (edgeCount < numEdges) {
            int src = rand() % numVertices;
            int dest = rand() % numVertices;
            if (src != dest && adjMatrix[src][dest] == 0 && (directed || adjMatrix[dest][src] == 0)) {
                adjMatrix[src][dest] = 1;
                if (!directed)
                    adjMatrix[dest][src] = 1;
                edgeList.push_back({ src, dest });
                edgeCount++;
            }
        }

        // Generate incidence matrix
        for (int i = 0; i < numVertices; ++i) {
            int edgeIndex = 0;
            for (int j = 0; j < numVertices; ++j) {
                if (adjMatrix[i][j] == 1) {
                    incMatrix[i][edgeIndex] = 1;
                    if (!directed)
                        incMatrix[j][edgeIndex] = 1;
                    edgeIndex++;
                }
            }
        }

        // Generate adjacency list
        adjList.resize(numVertices);
        for (const auto& edge : edgeList) {
            adjList[edge.first].push_back(edge.second);
            if (!directed)
                adjList[edge.second].push_back(edge.first);
        }
    }

    void printAdjMatrix() {
        for (const auto& row : adjMatrix) {
            for (int val : row) {
                cout << val << " ";
            }
            cout << endl;
        }
    }

    void printIncMatrix() {
        for (const auto& row : incMatrix) {
            for (int val : row) {
                cout << val << " ";
            }
            cout << endl;
        }
    }

    void printAdjList() {
        for (int i = 0; i < numVertices; ++i) {
            cout << i << ": ";
            for (int neighbor : adjList[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    void printEdgeList() {
        for (const auto& edge : edgeList) {
            cout << "(" << edge.first << ", " << edge.second << ") ";
        }
        cout << endl;
    }

    vector<int> BFS(int start, int end) {
        vector<bool> visited(numVertices, false);
        vector<int> parent(numVertices, -1);
        queue<int> q;

        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            if (current == end) {
                vector<int> path;
                while (current != -1) {
                    path.push_back(current);
                    current = parent[current];
                }
                reverse(path.begin(), path.end());
                return path;
            }

            for (int neighbor : adjList[current]) {
                if (!visited[neighbor]) {
                    q.push(neighbor);
                    visited[neighbor] = true;
                    parent[neighbor] = current;
                }
            }
        }
        return vector<int>(); // No path found
    }

    vector<int> DFS(int start, int end) {
        vector<bool> visited(numVertices, false);
        vector<int> parent(numVertices, -1);
        stack<int> s;

        s.push(start);
        visited[start] = true;

        while (!s.empty()) {
            int current = s.top();
            s.pop();

            if (current == end) {
                vector<int> path;
                while (current != -1) {
                    path.push_back(current);
                    current = parent[current];
                }
                reverse(path.begin(), path.end());
                return path;
            }

            for (int neighbor : adjList[current]) {
                if (!visited[neighbor]) {
                    s.push(neighbor);
                    visited[neighbor] = true;
                    parent[neighbor] = current;
                }
            }
        }
        return vector<int>(); // No path found
    }
};

int main() {
    srand(time(nullptr));

    int minVertices = 5;
    int maxVertices = 15;
    int minEdges = 8;
    int maxEdges = 15;
    int maxEdgesPerVertex = 3;
    bool isDirected = false;

    for (int i = minVertices; i <= maxVertices; ++i) {
        Graph graph(minVertices, maxVertices, minEdges, maxEdges, maxEdgesPerVertex, isDirected);
        //cout << "Graph with " << i << " vertices and " << graph.printEdgeList().size() << " edges:" << endl;
        graph.printEdgeList();
        graph.printAdjMatrix();
        graph.printIncMatrix();
        graph.printAdjList();

        // Select random start and end vertices
        int start = rand() % (i - 1);
        int end = rand() % (i - 1);

        auto start_time = chrono::steady_clock::now();
        vector<int> pathBFS = graph.BFS(start, end);
        auto end_time = chrono::steady_clock::now();
        auto durationBFS = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();

        start_time = chrono::steady_clock::now();
        vector<int> pathDFS = graph.DFS(start, end);
        end_time = chrono::steady_clock::now();
        auto durationDFS = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();

        cout << "Shortest path from vertex " << start << " to vertex " << end << " using BFS: ";
        if (pathBFS.empty()) {
            cout << "BFS is empty";
        }
        else {
            for (int vertex : pathBFS) {
                cout << vertex << " ";
            }
        }
        
        cout << " Duration: " << durationBFS << " microseconds" << endl;

        cout << "Shortest path from vertex " << start << " to vertex " << end << " using DFS: ";
        if (pathDFS.empty()) {
            cout << "DFS is empty";
        }
        {
            for (int vertex : pathDFS) {
                cout << vertex << " ";
            }
        }
        
        cout << " Duration: " << durationDFS << " microseconds" << endl << endl;
    }

    return 0;
}