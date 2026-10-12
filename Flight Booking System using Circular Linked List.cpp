
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

struct Booking
{
    int id;
    string name, source, destination;
    Booking *next;
};

class FlightBooking
{
private:
    Booking *tail;

public:
    FlightBooking()
    {
        tail = NULL;
    }

    void bookFlight()
    {
        Booking *temp = new Booking;

        cout << "Enter Booking ID: ";
        cin >> temp->id;

        if (searchID(temp->id))
        {
            cout << "Booking ID already exists!\n";
            delete temp;
            return;
        }

        cin.ignore(10000, '\n');

        cout << "Enter Passenger Name: ";
        getline(cin, temp->name);

        cout << "Enter Source: ";
        getline(cin, temp->source);

        cout << "Enter Destination: ";
        getline(cin, temp->destination);

        if (tail == NULL)
        {
            tail = temp;
            temp->next = temp;
        }
        else
        {
            temp->next = tail->next;
            tail->next = temp;
            tail = temp;
        }

        cout << "Flight booked successfully!\n";
    }

    void display()
    {
        if (tail == NULL)
        {
            cout << "No bookings available.\n";
            return;
        }

        Booking *temp = tail->next;

        cout << "\n--- Flight Bookings ---\n";

        do
        {
            cout << "Booking ID: " << temp->id << endl;
            cout << "Name: " << temp->name << endl;
            cout << "Source: " << temp->source << endl;
            cout << "Destination: " << temp->destination << endl;
            cout << "----------------------\n";

            temp = temp->next;
        } while (temp != tail->next);
    }

    bool searchID(int id)
    {
        if (tail == NULL)
            return false;

        Booking *temp = tail->next;

        do
        {
            if (temp->id == id)
                return true;

            temp = temp->next;
        } while (temp != tail->next);

        return false;
    }

    void search()
    {
        int id;

        cout << "Enter Booking ID to search: ";
        cin >> id;

        if (tail == NULL)
        {
            cout << "No bookings available.\n";
            return;
        }

        Booking *temp = tail->next;

        do
        {
            if (temp->id == id)
            {
                cout << "Booking Found!\n";
                cout << "Name: " << temp->name << endl;
                cout << "Source: " << temp->source << endl;
                cout << "Destination: " << temp->destination << endl;
                return;
            }

            temp = temp->next;
        } while (temp != tail->next);

        cout << "Booking not found.\n";
    }

    void cancel()
    {
        int id;

        cout << "Enter Booking ID to cancel: ";
        cin >> id;

        if (tail == NULL)
        {
            cout << "No bookings available.\n";
            return;
        }

        Booking *current = tail->next;
        Booking *previous = tail;

        do
        {
            if (current->id == id)
            {
                if (current == tail && current->next == tail)
                {
                    tail = NULL;
                }
                else
                {
                    previous->next = current->next;

                    if (current == tail)
                        tail = previous;
                }

                delete current;
                cout << "Booking cancelled successfully!\n";
                return;
            }

            previous = current;
            current = current->next;

        } while (current != tail->next);

        cout << "Booking not found.\n";
    }

    void memoryDemo()
    {
        int *a = (int *)malloc(2 * sizeof(int));

        if (a == NULL)
        {
            cout << "Memory allocation failed.\n";
            return;
        }

        a[0] = 10;
        a[1] = 20;

        cout << "malloc: " << a[0] << " " << a[1] << endl;

        int *b = (int *)calloc(3, sizeof(int));

        if (b == NULL)
        {
            free(a);
            cout << "Memory allocation failed.\n";
            return;
        }

        cout << "calloc: " << b[0] << " " << b[1]
             << " " << b[2] << endl;

        int *temp = (int *)realloc(a, 4 * sizeof(int));

        if (temp == NULL)
        {
            free(a);
            free(b);
            cout << "Memory reallocation failed.\n";
            return;
        }

        a = temp;
        a[2] = 30;
        a[3] = 40;

        cout << "realloc: ";
        for (int i = 0; i < 4; i++)
            cout << a[i] << " ";

        cout << endl;

        free(a);
        free(b);

        cout << "free: Memory released successfully.\n";
    }

    ~FlightBooking()
    {
        if (tail == NULL)
            return;

        Booking *head = tail->next;
        tail->next = NULL;

        while (head != NULL)
        {
            Booking *temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main()
{
    FlightBooking f;
    int choice;

    do
    {
        cout << "\n===== FLIGHT BOOKING SYSTEM =====\n";
        cout << "1. Book Flight\n";
        cout << "2. Display Bookings\n";
        cout << "3. Search Booking\n";
        cout << "4. Cancel Booking\n";
        cout << "5. Memory Functions Demo\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            f.bookFlight();
            break;

        case 2:
            f.display();
            break;

        case 3:
            f.search();
            break;

        case 4:
            f.cancel();
            break;

        case 5:
            f.memoryDemo();
            break;

        case 6:
            cout << "Thank you for using the system!\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 6);

    return 0;
}

