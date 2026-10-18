#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

struct Booking
{
    int id;
    string name, source, destination;
    Booking *prev, *next;
};

class FlightBooking
{
    Booking *head;

public:
    FlightBooking()
    {
        head = NULL;
    }

    void bookFlight()
    {
        Booking *n = new Booking;

        cout << "Enter Booking ID: ";
        cin >> n->id;

        if (searchID(n->id))
        {
            cout << "Booking ID already exists!\n";
            delete n;
            return;
        }

        cout << "Passenger Name: ";
        cin >> n->name;
        cout << "Source: ";
        cin >> n->source;
        cout << "Destination: ";
        cin >> n->destination;

        n->prev = NULL;
        n->next = head;

        if (head != NULL)
            head->prev = n;

        head = n;

        cout << "Flight booked successfully!\n";
    }

    bool searchID(int id)
    {
        Booking *t = head;

        while (t != NULL)
        {
            if (t->id == id)
                return true;

            t = t->next;
        }

        return false;
    }

    void display()
    {
        Booking *t = head;

        if (t == NULL)
        {
            cout << "No bookings available.\n";
            return;
        }

        while (t != NULL)
        {
            cout << "\nID: " << t->id;
            cout << "\nName: " << t->name;
            cout << "\nSource: " << t->source;
            cout << "\nDestination: " << t->destination << "\n";

            t = t->next;
        }
    }

    void displayBackward()
    {
        if (head == NULL)
        {
            cout << "No bookings available.\n";
            return;
        }

        Booking *t = head;

        while (t->next != NULL)
            t = t->next;

        cout << "\nBookings in reverse order:\n";

        while (t != NULL)
        {
            cout << t->id << " - " << t->name << "\n";
            t = t->prev;
        }
    }

    void search()
    {
        int id;

        cout << "Enter Booking ID: ";
        cin >> id;

        Booking *t = head;

        while (t != NULL)
        {
            if (t->id == id)
            {
                cout << "Booking Found!\n";
                cout << "Passenger: " << t->name << "\n";
                cout << "Route: " << t->source
                     << " to " << t->destination << "\n";
                return;
            }

            t = t->next;
        }

        cout << "Booking not found.\n";
    }

    void cancel()
    {
        int id;

        cout << "Enter Booking ID to cancel: ";
        cin >> id;

        Booking *t = head;

        while (t != NULL && t->id != id)
            t = t->next;

        if (t == NULL)
        {
            cout << "Booking not found.\n";
            return;
        }

        if (t->prev != NULL)
            t->prev->next = t->next;
        else
            head = t->next;

        if (t->next != NULL)
            t->next->prev = t->prev;

        delete t;

        cout << "Booking cancelled successfully!\n";
    }

    void memoryDemo()
    {
        // malloc(): allocate memory for characters
        char *data = (char *)malloc(10 * sizeof(char));

        if (data == NULL)
        {
            cout << "Memory allocation failed!\n";
            return;
        }

        // calloc(): allocate and initialize integers to zero
        int *arr = (int *)calloc(5, sizeof(int));

        if (arr == NULL)
        {
            free(data);
            cout << "Memory allocation failed!\n";
            return;
        }

        cout << "\ncalloc array values: ";
        for (int i = 0; i < 5; i++)
            cout << arr[i] << " ";

        // realloc(): resize previously allocated memory
        char *temp = (char *)realloc(data, 20 * sizeof(char));

        if (temp == NULL)
        {
            free(data);
            free(arr);
            cout << "\nReallocation failed!\n";
            return;
        }

        data = temp;

        cout << "\nMemory resized using realloc().\n";

        // free(): release allocated memory
        free(data);
        free(arr);

        cout << "Memory released using free().\n";
    }

    ~FlightBooking()
    {
        while (head != NULL)
        {
            Booking *t = head;
            head = head->next;
            delete t;
        }
    }
};

int main()
{
    FlightBooking f;
    int ch;

    do
    {
        cout << "\n--- FLIGHT BOOKING SYSTEM ---\n";
        cout << "1. Book Flight\n";
        cout << "2. Display Bookings\n";
        cout << "3. Search Booking\n";
        cout << "4. Cancel Booking\n";
        cout << "5. Display Backward\n";
        cout << "6. Demonstrate malloc/calloc/realloc/free\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> ch;

        switch (ch)
        {
            case 1: f.bookFlight(); break;
            case 2: f.display(); break;
            case 3: f.search(); break;
            case 4: f.cancel(); break;
            case 5: f.displayBackward(); break;
            case 6: f.memoryDemo(); break;
            case 7: cout << "Thank you!\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (ch != 7);

    return 0;
}

