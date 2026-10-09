
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <climits>
#include <algorithm>
#include <iomanip>

using namespace std;

const int INF = INT_MAX;

struct Road
{
    int destination;
    int distance;
};

class AmbulanceRouteFinder
{
private:
    int locations;
    vector<string> name;
    vector<vector<Road> > graph;

public:
    AmbulanceRouteFinder(int n)
    {
        locations = n;
        name.resize(n);
        graph.resize(n);
    }

    void setLocationName(int id, string locationName)
    {
        name[id] = locationName;
    }

    void addRoad(int u, int v, int distance)
    {
        if (u < 0 || u >= locations ||
            v < 0 || v >= locations || distance <= 0)
        {
            cout << "Invalid road details!\n";
            return;
        }

        graph[u].push_back({v, distance});
        graph[v].push_back({u, distance});

        cout << "Road added successfully!\n";
    }

    void displayLocations()
    {
        cout << "\n--- Available Locations ---\n";

        for (int i = 0; i < locations; i++)
        {
            cout << i << " - " << name[i] << "\n";
        }
    }

    void displayRoads()
    {
        cout << "\n--- Road Network ---\n";

        for (int i = 0; i < locations; i++)
        {
            cout << name[i] << " -> ";

            for (int j = 0; j < (int)graph[i].size(); j++)
            {
                cout << name[graph[i][j].destination]
                     << " (" << graph[i][j].distance << " km)  ";
            }

            cout << "\n";
        }
    }

    void findShortestRoute(int source, int destination)
    {
        if (source < 0 || source >= locations ||
            destination < 0 || destination >= locations)
        {
            cout << "Invalid location ID!\n";
            return;
        }

        vector<int> dist(locations, INF);
        vector<int> parent(locations, -1);

        priority_queue<
            pair<int, int>,
            vector<pair<int, int> >,
            greater<pair<int, int> >
        > pq;

        dist[source] = 0;
        pq.push(make_pair(0, source));

        while (!pq.empty())
        {
            int currentDistance = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (currentDistance != dist[u])
                continue;

            for (int i = 0; i < (int)graph[u].size(); i++)
            {
                int v = graph[u][i].destination;
                int weight = graph[u][i].distance;

                if (dist[u] <= INF - weight &&
                    dist[u] + weight < dist[v])
                {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;

                    pq.push(make_pair(dist[v], v));
                }
            }
        }

        if (dist[destination] == INF)
        {
            cout << "\nNo route available between these locations.\n";
            return;
        }

        vector<int> path;
        int current = destination;

        while (current != -1)
        {
            path.push_back(current);
            current = parent[current];
        }

        reverse(path.begin(), path.end());

        cout << "\n====================================\n";
        cout << "     EMERGENCY AMBULANCE ROUTE\n";
        cout << "====================================\n";

        cout << "Starting Location : " << name[source] << "\n";
        cout << "Hospital           : " << name[destination] << "\n";

        cout << "\nShortest Route:\n";

        for (int i = 0; i < (int)path.size(); i++)
        {
            cout << name[path[i]];

            if (i != (int)path.size() - 1)
                cout << " -> ";
        }

        cout << "\n\nTotal Distance: " << dist[destination] << " km\n";

        // Assumption: average ambulance speed is 40 km/h
        double timeMinutes = (dist[destination] / 40.0) * 60.0;

        cout << fixed << setprecision(1);
        cout << "Estimated Travel Time: "
             << timeMinutes << " minutes\n";

        cout << "====================================\n";
    }
};

int main()
{
    // Create 6 sample locations
    AmbulanceRouteFinder finder(6);

    finder.setLocationName(0, "City Center");
    finder.setLocationName(1, "Main Market");
    finder.setLocationName(2, "Bus Stand");
    finder.setLocationName(3, "Railway Station");
    finder.setLocationName(4, "Civil Hospital");
    finder.setLocationName(5, "Medical College");

    // Add sample roads and distances in kilometres
    finder.addRoad(0, 1, 3);
    finder.addRoad(0, 2, 5);
    finder.addRoad(1, 2, 2);
    finder.addRoad(1, 3, 4);
    finder.addRoad(2, 3, 2);
    finder.addRoad(2, 4, 6);
    finder.addRoad(3, 4, 3);
    finder.addRoad(3, 5, 5);
    finder.addRoad(4, 5, 2);

    int choice;

    do
    {
        cout << "\n====================================\n";
        cout << " EMERGENCY AMBULANCE ROUTE FINDER\n";
        cout << "====================================\n";
        cout << "1. Display Locations\n";
        cout << "2. Display Road Network\n";
        cout << "3. Find Shortest Route to Hospital\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                finder.displayLocations();
                break;

            case 2:
                finder.displayRoads();
                break;

            case 3:
            {
                int source, destination;

                finder.displayLocations();

                cout << "\nEnter ambulance starting location ID: ";
                cin >> source;

                cout << "Enter hospital location ID: ";
                cin >> destination;

                finder.findShortestRoute(source, destination);
                break;
            }

            case 4:
                cout << "\nThank you for using the system!\n";
                break;

            default:
                cout << "\nInvalid choice! Try again.\n";
        }

    } while (choice != 4);

    return 0;
}
