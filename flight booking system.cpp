#include <iostream>
#include <string>
#include <iomanip>
#include <climits>

using namespace std;

// Maximum number of cities
const int MAX_CITIES = 10;
const int MAX_BOOKINGS = 100;

// ---------------- CITY DATA ----------------

string cities[MAX_CITIES] = {
    "Mumbai",
    "Pune",
    "Nashik",
    "Delhi",
    "Bangalore",
    "Hyderabad",
    "Chennai",
    "Kolkata",
    "Ahmedabad",
    "Goa"
};

int cityCount = 10;

// ---------------- FLIGHT GRAPH ----------------

int graph[MAX_CITIES][MAX_CITIES] = {
    // Mu Pu Na De Ba Hy Ch Ko Ah Go
    {0, 2, 3,  0, 0, 0, 0, 0, 4, 1}, // Mumbai
    {2, 0, 2,  0, 0, 2, 0, 0, 3, 0}, // Pune
    {3, 2, 0,  0, 0, 3, 0, 0, 2, 0}, // Nashik
    {0, 0, 0,  0, 5, 3, 2, 3, 0, 0}, // Delhi
    {0, 0, 0,  5, 0, 2, 2, 0, 0, 0}, // Bangalore
    {0, 2, 3,  3, 2, 0, 2, 0, 0, 0}, // Hyderabad
    {0, 0, 0,  2, 2, 2, 0, 4, 0, 0}, // Chennai
    {0, 0, 0,  3, 0, 0, 4, 0, 0, 0}, // Kolkata
    {4, 3, 2,  0, 0, 0, 0, 0, 0, 2}, // Ahmedabad
    {1, 0, 0,  0, 0, 0, 0, 0, 2, 0}  // Goa
};

// ---------------- BOOKING DATA ----------------

struct Booking
{
    int bookingID;
    string passengerName;
    int age;
    string source;
    string destination;
    int seats;
    double price;
};

Booking bookings[MAX_BOOKINGS];

int bookingCount = 0;
int nextBookingID = 1001;

// ---------------- FIND CITY ----------------

int findCity(string name)
{
    for(int i = 0; i < cityCount; i++)
    {
        if(cities[i] == name)
            return i;
    }

    return -1;
}

// ---------------- DISPLAY CITIES ----------------

void displayCities()
{
    cout << "\n========== AVAILABLE CITIES ==========\n";

    for(int i = 0; i < cityCount; i++)
    {
        cout << i + 1 << ". " << cities[i] << endl;
    }
}

// ---------------- DISPLAY FLIGHT NETWORK ----------------

void displayFlightNetwork()
{
    cout << "\n========== FLIGHT NETWORK ==========\n";

    for(int i = 0; i < cityCount; i++)
    {
        cout << "\n" << cities[i] << " -> ";

        bool found = false;

        for(int j = 0; j < cityCount; j++)
        {
            if(graph[i][j] != 0)
            {
                cout << cities[j]
                     << "(" << graph[i][j] << "00 km) ";

                found = true;
            }
        }

        if(!found)
            cout << "No direct flights";
    }

    cout << endl;
}

// ---------------- DIJKSTRA ALGORITHM ----------------

void shortestRoute(int source, int destination)
{
    int distance[MAX_CITIES];
    bool visited[MAX_CITIES];
    int parent[MAX_CITIES];

    for(int i = 0; i < cityCount; i++)
    {
        distance[i] = INT_MAX;
        visited[i] = false;
        parent[i] = -1;
    }

    distance[source] = 0;

    for(int count = 0; count < cityCount - 1; count++)
    {
        int minDistance = INT_MAX;
        int current = -1;

        for(int i = 0; i < cityCount; i++)
        {
            if(!visited[i] && distance[i] < minDistance)
            {
                minDistance = distance[i];
                current = i;
            }
        }

        if(current == -1)
            break;

        visited[current] = true;

        for(int i = 0; i < cityCount; i++)
        {
            if(graph[current][i] != 0 &&
               !visited[i] &&
               distance[current] != INT_MAX &&
               distance[current] + graph[current][i] < distance[i])
            {
                distance[i] =
                    distance[current] + graph[current][i];

                parent[i] = current;
            }
        }
    }

    if(distance[destination] == INT_MAX)
    {
        cout << "\nNo route available.\n";
        return;
    }

    // Store route
    int route[MAX_CITIES];
    int routeCount = 0;

    int current = destination;

    while(current != -1)
    {
        route[routeCount++] = current;
        current = parent[current];
    }

    cout << "\n========== SHORTEST ROUTE ==========\n";

    for(int i = routeCount - 1; i >= 0; i--)
    {
        cout << cities[route[i]];

        if(i != 0)
            cout << " -> ";
    }

    cout << "\nTotal Distance: "
         << distance[destination] * 100
         << " km";

    cout << "\nEstimated Travel Time: "
         << distance[destination] * 1.5
         << " hours\n";
}

// ---------------- SEARCH FLIGHT ----------------

void searchFlight()
{
    string sourceName;
    string destinationName;

    cout << "\nEnter Source City: ";
    cin >> sourceName;

    cout << "Enter Destination City: ";
    cin >> destinationName;

    int source = findCity(sourceName);
    int destination = findCity(destinationName);

    if(source == -1 || destination == -1)
    {
        cout << "\nInvalid city name!\n";
        return;
    }

    if(graph[source][destination] != 0)
    {
        cout << "\n========== FLIGHT FOUND ==========\n";

        cout << "From: " << cities[source] << endl;
        cout << "To: " << cities[destination] << endl;

        cout << "Distance: "
             << graph[source][destination] * 100
             << " km\n";

        cout << "Estimated Time: "
             << graph[source][destination] * 1.5
             << " hours\n";
    }
    else
    {
        cout << "\nNo direct flight available.\n";

        cout << "\nFinding shortest connecting route...\n";

        shortestRoute(source, destination);
    }
}

// ---------------- BOOK TICKET ----------------

void bookTicket()
{
    if(bookingCount >= MAX_BOOKINGS)
    {
        cout << "\nBooking limit reached!\n";
        return;
    }

    Booking b;

    cout << "\n========== BOOK FLIGHT ==========\n";

    cout << "Passenger Name: ";
    cin >> b.passengerName;

    cout << "Age: ";
    cin >> b.age;

    cout << "\nAvailable Cities:\n";

    for(int i = 0; i < cityCount; i++)
    {
        cout << cities[i] << " ";
    }

    cout << "\n\nSource City: ";
    cin >> b.source;

    cout << "Destination City: ";
    cin >> b.destination;

    int source = findCity(b.source);
    int destination = findCity(b.destination);

    if(source == -1 || destination == -1)
    {
        cout << "\nInvalid city!\n";
        return;
    }

    if(source == destination)
    {
        cout << "\nSource and destination cannot be same.\n";
        return;
    }

    cout << "Number of Seats: ";
    cin >> b.seats;

    if(b.seats <= 0)
    {
        cout << "\nInvalid number of seats.\n";
        return;
    }

    // Base fare
    int distance;

    if(graph[source][destination] != 0)
    {
        distance = graph[source][destination] * 100;
    }
    else
    {
        // Calculate shortest distance
        int dist[MAX_CITIES];
        bool visited[MAX_CITIES];

        for(int i = 0; i < cityCount; i++)
        {
            dist[i] = INT_MAX;
            visited[i] = false;
        }

        dist[source] = 0;

        for(int count = 0; count < cityCount - 1; count++)
        {
            int minDistance = INT_MAX;
            int current = -1;

            for(int i = 0; i < cityCount; i++)
            {
                if(!visited[i] && dist[i] < minDistance)
                {
                    minDistance = dist[i];
                    current = i;
                }
            }

            if(current == -1)
                break;

            visited[current] = true;

            for(int i = 0; i < cityCount; i++)
            {
                if(graph[current][i] != 0 &&
                   !visited[i] &&
                   dist[current] != INT_MAX &&
                   dist[current] + graph[current][i] < dist[i])
                {
                    dist[i] =
                        dist[current] + graph[current][i];
                }
            }
        }

        distance = dist[destination] * 100;
    }

    // ?5 per km
    b.price = distance * 5 * b.seats;

    b.bookingID = nextBookingID++;

    bookings[bookingCount] = b;
    bookingCount++;

    cout << "\n========== BOOKING SUCCESSFUL ==========\n";

    cout << "Booking ID: " << b.bookingID << endl;
    cout << "Passenger: " << b.passengerName << endl;
    cout << "From: " << b.source << endl;
    cout << "To: " << b.destination << endl;
    cout << "Seats: " << b.seats << endl;

    cout << fixed << setprecision(2);

    cout << "Total Price: Rs. "
         << b.price << endl;

    cout << "========================================\n";
}

// ---------------- DISPLAY BOOKINGS ----------------

void displayBookings()
{
    if(bookingCount == 0)
    {
        cout << "\nNo bookings available.\n";
        return;
    }

    cout << "\n========== ALL BOOKINGS ==========\n";

    for(int i = 0; i < bookingCount; i++)
    {
        cout << "\nBooking ID: "
             << bookings[i].bookingID;

        cout << "\nPassenger: "
             << bookings[i].passengerName;

        cout << "\nAge: "
             << bookings[i].age;

        cout << "\nRoute: "
             << bookings[i].source
             << " -> "
             << bookings[i].destination;

        cout << "\nSeats: "
             << bookings[i].seats;

        cout << fixed << setprecision(2);

        cout << "\nPrice: Rs. "
             << bookings[i].price;

        cout << "\n----------------------------------";
    }

    cout << endl;
}

// ---------------- CANCEL BOOKING ----------------

void cancelBooking()
{
    if(bookingCount == 0)
    {
        cout << "\nNo bookings available.\n";
        return;
    }

    int id;

    cout << "\nEnter Booking ID to cancel: ";
    cin >> id;

    int position = -1;

    for(int i = 0; i < bookingCount; i++)
    {
        if(bookings[i].bookingID == id)
        {
            position = i;
            break;
        }
    }

    if(position == -1)
    {
        cout << "\nBooking not found!\n";
        return;
    }

    for(int i = position; i < bookingCount - 1; i++)
    {
        bookings[i] = bookings[i + 1];
    }

    bookingCount--;

    cout << "\nBooking cancelled successfully!\n";
}

// ---------------- MAIN MENU ----------------

int main()
{
    int choice;

    do
    {
        cout << "\n\n";
        cout << "============================================\n";
        cout << "       AIRLINE FLIGHT BOOKING SYSTEM\n";
        cout << "============================================\n";

        cout << "1. Display Cities\n";
        cout << "2. Display Flight Network\n";
        cout << "3. Search Flight\n";
        cout << "4. Find Shortest Route\n";
        cout << "5. Book Flight\n";
        cout << "6. View All Bookings\n";
        cout << "7. Cancel Booking\n";
        cout << "8. Exit\n";

        cout << "============================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                displayCities();
                break;

            case 2:
                displayFlightNetwork();
                break;

            case 3:
                searchFlight();
                break;

            case 4:
            {
                string sourceName;
                string destinationName;

                cout << "\nEnter Source City: ";
                cin >> sourceName;

                cout << "Enter Destination City: ";
                cin >> destinationName;

                int source = findCity(sourceName);
                int destination = findCity(destinationName);

                if(source == -1 || destination == -1)
                {
                    cout << "\nInvalid city name!\n";
                }
                else
                {
                    shortestRoute(source, destination);
                }

                break;
            }

            case 5:
                bookTicket();
                break;

            case 6:
                displayBookings();
                break;

            case 7:
                cancelBooking();
                break;

            case 8:
                cout << "\nThank you for using the Airline System!\n";
                break;

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }

    } while(choice != 8);

    return 0;
}
