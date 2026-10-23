
#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

class Graph {
private:
    int V;
    bool directed;

    vector<string> vertices;
    vector<vector<int> > adj;

    // Save the graph before the latest update
    vector<string> oldVertices;
    vector<vector<int> > oldAdj;
    bool hasSnapshot;
    string updateDescription;

    int findVertex(const vector<string>& names, string name) const {
        for (int i = 0; i < (int)names.size(); i++) {
            if (names[i] == name)
                return i;
        }
        return -1;
    }

    int getIndex(string name) const {
        return findVertex(vertices, name);
    }

    void saveSnapshot(string description) {
        oldVertices = vertices;
        oldAdj = adj;
        updateDescription = description;
        hasSnapshot = true;
    }

    vector<string> traverse(
        const vector<string>& names,
        const vector<vector<int> >& matrix,
        int start,
        bool useBFS
    ) const {
        vector<string> result;
        int n = (int)names.size();

        if (start < 0 || start >= n)
            return result;

        vector<bool> visited(n, false);

        if (useBFS) {
            queue<int> q;
            q.push(start);
            visited[start] = true;

            while (!q.empty()) {
                int u = q.front();
                q.pop();
                result.push_back(names[u]);

                for (int v = 0; v < n; v++) {
                    if (matrix[u][v] && !visited[v]) {
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
        } else {
            // Iterative DFS
            vector<int> st;
            st.push_back(start);
            visited[start] = true;

            while (!st.empty()) {
                int u = st.back();
                st.pop_back();
                result.push_back(names[u]);

                // Reverse order preserves ascending visit order
                for (int v = n - 1; v >= 0; v--) {
                    if (matrix[u][v] && !visited[v]) {
                        visited[v] = true;
                        st.push_back(v);
                    }
                }
            }
        }

        return result;
    }

    void printTraversal(const vector<string>& result) const {
        if (result.empty()) {
            cout << "No vertices visited.";
            return;
        }

        for (int i = 0; i < (int)result.size(); i++) {
            if (i > 0)
                cout << " -> ";
            cout << result[i];
        }
    }

    void showUnreachable(
        const vector<string>& names,
        const vector<string>& result
    ) const {
        bool found = false;

        cout << "\nUnreachable vertices: ";

        for (int i = 0; i < (int)names.size(); i++) {
            bool visited = false;

            for (int j = 0; j < (int)result.size(); j++) {
                if (names[i] == result[j]) {
                    visited = true;
                    break;
                }
            }

            if (!visited) {
                cout << names[i] << " ";
                found = true;
            }
        }

        if (!found)
            cout << "None";

        cout << "\n";
    }

public:
    Graph() {
        V = 0;
        directed = false;
        hasSnapshot = false;
    }

    void createGraph() {
        int n, type;

        cout << "Enter number of vertices: ";
        cin >> n;

        if (n <= 0) {
            cout << "Number of vertices must be positive!\n";
            return;
        }

        cout << "Enter 1 for Directed, 0 for Undirected: ";
        cin >> type;

        vector<string> newVertices;
        vector<vector<int> > newAdj;

        for (int i = 0; i < n; i++) {
            string name;
            cout << "Enter vertex " << i + 1 << ": ";
            cin >> name;

            if (findVertex(newVertices, name) != -1) {
                cout << "Duplicate vertex! Enter another name.\n";
                i--;
                continue;
            }

            newVertices.push_back(name);
        }

        V = n;
        directed = (type == 1);
        vertices = newVertices;
        adj.assign(V, vector<int>(V, 0));

        hasSnapshot = false;
        updateDescription = "";

        cout << "Graph created successfully!\n";
        cout << "Vertices: " << V << "\n";
        cout << "Type: " << (directed ? "Directed" : "Undirected")
             << "\n";
    }

    void insertVertex() {
        string name;

        if (V == 0) {
            cout << "Create a graph first!\n";
            return;
        }

        cout << "Enter new vertex name: ";
        cin >> name;

        if (getIndex(name) != -1) {
            cout << "Vertex already exists!\n";
            return;
        }

        saveSnapshot("Inserted vertex " + name);

        vertices.push_back(name);
        V++;

        for (int i = 0; i < V - 1; i++)
            adj[i].push_back(0);

        adj.push_back(vector<int>(V, 0));

        cout << "Vertex " << name << " added successfully!\n";
        cout << "Updated vertex count: " << V << "\n";
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
            cout << "Invalid vertex! Insert the vertex first.\n";
            return;
        }

        if (adj[u][v] == 1) {
            cout << "Edge already exists!\n";
            return;
        }

        saveSnapshot("Inserted edge " + from + " -> " + to);

        adj[u][v] = 1;

        if (!directed)
            adj[v][u] = 1;

        cout << "Edge inserted successfully!\n";
        cout << "Updated edge: " << from << " -> " << to << "\n";
    }

    void displayMatrix() {
        if (V == 0) {
            cout << "Graph is empty!\n";
            return;
        }

        cout << "\nUPDATED ADJACENCY MATRIX\n    ";

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

        cout << "\nUPDATED ADJACENCY LIST\n";

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

        vector<string> result = traverse(vertices, adj, s, true);

        cout << "BFS Traversal: ";
        printTraversal(result);
        cout << "\n";

        showUnreachable(vertices, result);
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

        vector<string> result = traverse(vertices, adj, s, false);

        cout << "DFS Traversal: ";
        printTraversal(result);
        cout << "\n";

        showUnreachable(vertices, result);
    }

    // Modification B: Compare traversal before and after an update
    void compareTraversal() {
        if (!hasSnapshot) {
            cout << "No update available for comparison.\n";
            cout << "Insert a vertex or edge first.\n";
            return;
        }

        string start;
        cout << "Latest update: " << updateDescription << "\n";
        cout << "Enter a starting vertex: ";
        cin >> start;

        int oldStart = findVertex(oldVertices, start);
        int newStart = getIndex(start);

        cout << "\n--- BEFORE UPDATE ---\n";

        vector<string> before;

        if (oldStart == -1) {
            cout << "Starting vertex was not present before the update.\n";
        } else {
            before = traverse(oldVertices, oldAdj, oldStart, true);
            cout << "BFS: ";
            printTraversal(before);
            cout << "\n";
            showUnreachable(oldVertices, before);
        }

        cout << "\n--- AFTER UPDATE ---\n";

        if (newStart == -1) {
            cout << "Starting vertex not found in current graph.\n";
            return;
        }

        vector<string> after = traverse(vertices, adj, newStart, true);
        cout << "BFS: ";
        printTraversal(after);
        cout << "\n";
        showUnreachable(vertices, after);

        cout << "\n--- COMPARISON RESULT ---\n";

        if (oldStart == -1) {
            cout << "Comparison of traversals is unavailable because "
                 << start << " did not exist before the update.\n";
        } else {
            bool changed = (before.size() != after.size());

            if (!changed) {
                for (int i = 0; i < (int)before.size(); i++) {
                    if (before[i] != after[i]) {
                        changed = true;
                        break;
                    }
                }
            }

            if (changed)
                cout << "BFS traversal changed after the update.\n";
            else
                cout << "BFS traversal order is unchanged.\n";

            cout << "Newly reachable vertices: ";

            bool found = false;

            for (int i = 0; i < (int)after.size(); i++) {
                bool existedBefore = false;

                for (int j = 0; j < (int)before.size(); j++) {
                    if (after[i] == before[j]) {
                        existedBefore = true;
                        break;
                    }
                }

                if (!existedBefore) {
                    cout << after[i] << " ";
                    found = true;
                }
            }

            if (!found)
                cout << "None";

            cout << "\n";
        }
    }

    // Modification C: Check whether a path exists
    void checkPath() {
        if (V == 0) {
            cout << "Create a graph first!\n";
            return;
        }

        string source, destination;

        cout << "Enter source vertex: ";
        cin >> source;
        cout << "Enter destination vertex: ";
        cin >> destination;

        int s = getIndex(source);
        int d = getIndex(destination);

        if (s == -1 || d == -1) {
            cout << "Invalid source or destination vertex!\n";
            return;
        }

        vector<int> parent(V, -1);
        vector<bool> visited(V, false);
        queue<int> q;

        visited[s] = true;
        q.push(s);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v = 0; v < V; v++) {
                if (adj[u][v] == 1 && !visited[v]) {
                    visited[v] = true;
                    parent[v] = u;
                    q.push(v);
                }
            }
        }

        if (!visited[d]) {
            cout << "NO PATH EXISTS from " << source
                 << " to " << destination << ".\n";
            cout << "The vertices are disconnected in this direction.\n";
            return;
        }

        vector<int> path;
        int current = d;

        while (current != -1) {
            path.push_back(current);
            current = parent[current];
        }

        cout << "PATH EXISTS: ";

        for (int i = (int)path.size() - 1; i >= 0; i--) {
            cout << vertices[path[i]];

            if (i > 0)
                cout << " -> ";
        }

        cout << "\n";
        cout << "Number of edges in shortest path: "
             << (int)path.size() - 1 << "\n";
    }
};

int main() {
    Graph g;
    int choice;

    do {
        cout << "\n========== MODIFIED GRAPH TOOLKIT ==========\n";
        cout << "1. Create Graph\n";
        cout << "2. Insert Additional Vertex\n";
        cout << "3. Insert Additional Edge\n";
        cout << "4. Display Adjacency Matrix\n";
        cout << "5. Display Adjacency List\n";
        cout << "6. Perform BFS\n";
        cout << "7. Perform DFS\n";
        cout << "8. Compare BFS Before and After Update\n";
        cout << "9. Check Path Between Two Vertices\n";
        cout << "10. Exit\n";
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
                g.compareTraversal();
                break;
            case 9:
                g.checkPath();
                break;
            case 10:
                cout << "Exiting Graph Toolkit. Thank you!\n";
                break;
            default:
                cout << "Invalid choice! Enter 1 to 10.\n";
        }

    } while (choice != 10);

    return 0;
}

