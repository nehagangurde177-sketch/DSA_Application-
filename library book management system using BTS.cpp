
#include <iostream>
#include <string>
using namespace std;

// Structure for a book node
struct Book
{
    int id;
    string title;
    string author;
    Book* left;
    Book* right;
};

// Create a new book node
Book* createBook(int id, string title, string author)
{
    Book* newBook = new Book;

    newBook->id = id;
    newBook->title = title;
    newBook->author = author;
    newBook->left = NULL;
    newBook->right = NULL;

    return newBook;
}

// Insert a book into the BST
Book* insertBook(Book* root, int id, string title, string author)
{
    if (root == NULL)
    {
        return createBook(id, title, author);
    }

    if (id < root->id)
    {
        root->left = insertBook(root->left, id, title, author);
    }
    else if (id > root->id)
    {
        root->right = insertBook(root->right, id, title, author);
    }
    else
    {
        cout << "\nBook ID already exists!\n";
    }

    return root;
}

// Display books in ascending order of ID
void displayBooks(Book* root)
{
    if (root == NULL)
        return;

    displayBooks(root->left);

    cout << "\nBook ID : " << root->id;
    cout << "\nTitle   : " << root->title;
    cout << "\nAuthor  : " << root->author << "\n";
    cout << "-----------------------------\n";

    displayBooks(root->right);
}

// Search for a book
Book* searchBook(Book* root, int id)
{
    if (root == NULL || root->id == id)
        return root;

    if (id < root->id)
        return searchBook(root->left, id);

    return searchBook(root->right, id);
}

// Find the smallest node in a subtree
Book* findMinimum(Book* root)
{
    while (root != NULL && root->left != NULL)
        root = root->left;

    return root;
}

// Delete a book from the BST
Book* deleteBook(Book* root, int id)
{
    if (root == NULL)
        return root;

    if (id < root->id)
    {
        root->left = deleteBook(root->left, id);
    }
    else if (id > root->id)
    {
        root->right = deleteBook(root->right, id);
    }
    else
    {
        // Node has no left child
        if (root->left == NULL)
        {
            Book* temp = root->right;
            delete root;
            return temp;
        }

        // Node has no right child
        else if (root->right == NULL)
        {
            Book* temp = root->left;
            delete root;
            return temp;
        }

        // Node has two children
        Book* temp = findMinimum(root->right);

        root->id = temp->id;
        root->title = temp->title;
        root->author = temp->author;

        root->right = deleteBook(root->right, temp->id);
    }

    return root;
}

// Count total books
int countBooks(Book* root)
{
    if (root == NULL)
        return 0;

    return 1 + countBooks(root->left)
             + countBooks(root->right);
}

// Free allocated memory
void freeBooks(Book* root)
{
    if (root == NULL)
        return;

    freeBooks(root->left);
    freeBooks(root->right);
    delete root;
}

int main()
{
    Book* root = NULL;
    int choice, id;
    string title, author;

    do
    {
        cout << "\n===== LIBRARY BOOK MANAGEMENT =====\n";
        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Book\n";
        cout << "4. Delete Book\n";
        cout << "5. Count Total Books\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Enter Book ID: ";
                cin >> id;
                cin.ignore(1000, '\n');

                cout << "Enter Book Title: ";
                getline(cin, title);

                cout << "Enter Author Name: ";
                getline(cin, author);

                root = insertBook(root, id, title, author);
                break;

            case 2:
                if (root == NULL)
                {
                    cout << "\nLibrary is empty!\n";
                }
                else
                {
                    cout << "\n--- Library Books ---\n";
                    displayBooks(root);
                }
                break;

            case 3:
                cout << "Enter Book ID to search: ";
                cin >> id;

                {
                    Book* result = searchBook(root, id);

                    if (result != NULL)
                    {
                        cout << "\nBook Found!\n";
                        cout << "Book ID: " << result->id << "\n";
                        cout << "Title: " << result->title << "\n";
                        cout << "Author: " << result->author << "\n";
                    }
                    else
                    {
                        cout << "\nBook not found!\n";
                    }
                }
                break;

            case 4:
                cout << "Enter Book ID to delete: ";
                cin >> id;

                if (searchBook(root, id) != NULL)
                {
                    root = deleteBook(root, id);
                    cout << "\nBook deleted successfully!\n";
                }
                else
                {
                    cout << "\nBook not found!\n";
                }
                break;

            case 5:
                cout << "\nTotal books: "
                     << countBooks(root) << "\n";
                break;

            case 6:
                cout << "\nExiting Library System...\n";
                break;

            default:
                cout << "\nInvalid choice! Try again.\n";
        }

    } while (choice != 6);

    freeBooks(root);

    return 0;
}
