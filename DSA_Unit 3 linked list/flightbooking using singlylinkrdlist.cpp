#include <iostream>
#include <string>
using namespace std;

struct Flight
{
    int flightNo;
    string source, destination;
    float fare;
    Flight* next;
};

class FlightManagement
{
    Flight* head;

public:
    FlightManagement()
    {
        head = NULL;
    }

    void addFlight()
    {
        Flight* newFlight = new Flight;

        cout << "Enter Flight Number: ";
        cin >> newFlight->flightNo;

        cout << "Enter Source: ";
        cin >> newFlight->source;

        cout << "Enter Destination: ";
        cin >> newFlight->destination;

        cout << "Enter Fare: ";
        cin >> newFlight->fare;

        newFlight->next = NULL;

        if (head == NULL)
            head = newFlight;
        else
        {
            Flight* temp = head;
            while (temp->next != NULL)
                temp = temp->next;

            temp->next = newFlight;
        }

        cout << "Flight added successfully!\n";
    }

    void displayFlights()
    {
        Flight* temp = head;

        if (temp == NULL)
        {
            cout << "No flights available.\n";
            return;
        }

        while (temp != NULL)
        {
            cout << "\nFlight Number: " << temp->flightNo;
            cout << "\nSource: " << temp->source;
            cout << "\nDestination: " << temp->destination;
            cout << "\nFare: Rs. " << temp->fare << "\n";

            temp = temp->next;
        }
    }

    void searchFlight()
    {
        int no;
        cout << "Enter Flight Number to Search: ";
        cin >> no;

        Flight* temp = head;

        while (temp != NULL)
        {
            if (temp->flightNo == no)
            {
                cout << "Flight Found!\n";
                cout << "Source: " << temp->source << "\n";
                cout << "Destination: " << temp->destination << "\n";
                cout << "Fare: Rs. " << temp->fare << "\n";
                return;
            }

            temp = temp->next;
        }

        cout << "Flight not found.\n";
    }

    void deleteFlight()
    {
        int no;
        cout << "Enter Flight Number to Delete: ";
        cin >> no;

        Flight* temp = head;
        Flight* prev = NULL;

        while (temp != NULL && temp->flightNo != no)
        {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL)
        {
            cout << "Flight not found.\n";
            return;
        }

        if (prev == NULL)
            head = temp->next;
        else
            prev->next = temp->next;

        delete temp;
        cout << "Flight deleted successfully!\n";
    }

    ~FlightManagement()
    {
        while (head != NULL)
        {
            Flight* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main()
{
    FlightManagement fm;
    int choice;

    do
    {
        cout << "\n--- FLIGHT MANAGEMENT SYSTEM ---\n";
        cout << "1. Add Flight\n";
        cout << "2. Display Flights\n";
        cout << "3. Search Flight\n";
        cout << "4. Delete Flight\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                fm.addFlight();
                break;

            case 2:
                fm.displayFlights();
                break;

            case 3:
                fm.searchFlight();
                break;

            case 4:
                fm.deleteFlight();
                break;

            case 5:
                cout << "Thank you!\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}

