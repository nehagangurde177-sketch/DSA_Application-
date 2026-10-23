
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Graph {
private:
    int V;
    bool directed;
    vector<string> vertices;
    vector<vector<int> > adj;

    int getIndex(string name) {
        for (int i = 0; i < V; i++) {
            if (vertices[i] == name)
                return i;
        }
        return -1;
    }

public:
    Graph() {
        V = 0;
        directed = false;
    }

    void createGraph() {
        int n, type;

        cout << "Enter number of vertices: ";
        cin >> n;

        if (n <= 0) {
            cout << "Number of vertices must be positive!\n";
            return;
        }

        V = 0;
        vertices.clear();
        adj.clear();

        cout << "Enter 1 for Directed Graph, 0 for Undirected Graph: ";
        cin >> type;
        directed = (type == 1);

        for (int i = 0; i < n; i++) {
            string name;
            cout << "Enter name of vertex " << i + 1 << ": ";
            cin >> name;

            if (getIndex(name) != -1) {
                cout << "Vertex already exists! Enter a different name.\n";
                i--;
                continue;
            }

            vertices.push_back(name);
            V++;
            adj.push_back(vector<int>(V, 0));

            for (int j = 0; j < V - 1; j++)
                adj[j].push_back(0);
        }

        cout << "Graph created successfully!\n";
    }

    void insertVertex() {
        string name;
        cout << "Enter new vertex name: ";
        cin >> name;

        if (getIndex(name) != -1) {
            cout << "Vertex already exists!\n";
            return;
        }

        vertices.push_back(name);
        V++;

        for (int i = 0; i < V - 1; i++)
            adj[i].push_back(0);

        adj.push_back(vector<int>(V, 0));

        cout << "Vertex inserted successfully!\n";
    }

    void insertEdge() {
        string from, to;

        if (V == 0) {
            cout << "Create a graph first!\n";
            return;
        }

        cout << "Enter source vertex: ";
        cin >> from;
        cout << "Enter destination vertex: ";
        cin >> to;

        int u = getIndex(from);
        int v = getIndex(to);

        if (u == -1 || v == -1) {
            cout << "Invalid vertex name!\n";
            return;
        }

        adj[u][v] = 1;

        if (!directed)
            adj[v][u] = 1;

        cout << "Edge inserted successfully: "
             << from << " -> " << to << "\n";
    }

    void displayMatrix() {
        if (V == 0) {
            cout << "Graph is empty!\n";
            return;
        }

        cout << "\nADJACENCY MATRIX\n";
        cout << "    ";

        for (int i = 0; i < V; i++)
            cout << vertices[i] << " ";

        cout << "\n";

        for (int i = 0; i < V; i++) {
            cout << vertices[i] << "   ";

            for (int j = 0; j < V; j++)
                cout << adj[i][j] << " ";

            cout << "\n";
        }
    }

    void displayList() {
        if (V == 0) {
            cout << "Graph is empty!\n";
            return;
        }

        cout << "\nADJACENCY LIST\n";

        for (int i = 0; i < V; i++) {
            cout << vertices[i] << " -> ";

            bool found = false;

            for (int j = 0; j < V; j++) {
                if (adj[i][j] == 1) {
                    cout << vertices[j] << " ";
                    found = true;
                }
            }

            if (!found)
                cout << "No adjacent vertices";

            cout << "\n";
        }
    }

    void BFS() {
        if (V == 0) {
            cout << "Create a graph first!\n";
            return;
        }

        string start;
        cout << "Enter starting vertex for BFS: ";
        cin >> start;

        int s = getIndex(start);

        if (s == -1) {
            cout << "Invalid starting vertex!\n";
            return;
        }

        vector<bool> visited(V, false);
        queue<int> q;

        visited[s] = true;
        q.push(s);

        cout << "BFS Traversal: ";

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            cout << vertices[u] << " ";

            for (int v = 0; v < V; v++) {
                if (adj[u][v] == 1 && !visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }

        cout << "\n";
        cout << "Note: Only vertices reachable from the start are shown.\n";
    }

    void DFS() {
        if (V == 0) {
            cout << "Create a graph first!\n";
            return;
        }

        string start;
        cout << "Enter starting vertex for DFS: ";
        cin >> start;

        int s = getIndex(start);

        if (s == -1) {
            cout << "Invalid starting vertex!\n";
            return;
        }

        vector<bool> visited(V, false);

        cout << "DFS Traversal: ";
        dfsHelper(s, visited);
        cout << "\n";
        cout << "Note: Only vertices reachable from the start are shown.\n";
    }

    void dfsHelper(int u, vector<bool>& visited) {
        visited[u] = true;
        cout << vertices[u] << " ";

        for (int v = 0; v < V; v++) {
            if (adj[u][v] == 1 && !visited[v])
                dfsHelper(v, visited);
        }
    }
};

int main() {
    Graph g;
    int choice;

    do {
        cout << "\n========== GRAPH TOOLKIT ==========\n";
        cout << "1. Create Graph\n";
        cout << "2. Insert Vertex\n";
        cout << "3. Insert Edge\n";
        cout << "4. Display Adjacency Matrix\n";
        cout << "5. Display Adjacency List\n";
        cout << "6. Breadth First Search (BFS)\n";
        cout << "7. Depth First Search (DFS)\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                g.createGraph();
                break;

            case 2:
                g.insertVertex();
                break;

            case 3:
                g.insertEdge();
                break;

            case 4:
                g.displayMatrix();
                break;

            case 5:
                g.displayList();
                break;

            case 6:
                g.BFS();
                break;

            case 7:
                g.DFS();
                break;

            case 8:
                cout << "Exiting Graph Toolkit. Thank you!\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 8);

    return 0;
}

