
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct Node {
    int data, height;
    Node *left, *right;

    Node(int value) {
        data = value;
        height = 1;
        left = right = NULL;
    }
};

int height(Node* root) {
    return (root == NULL) ? 0 : root->height;
}

int getBalance(Node* root) {
    if (root == NULL)
        return 0;
    return height(root->left) - height(root->right);
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* t = x->right;

    x->right = y;
    y->left = t;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* t = y->left;

    y->left = x;
    x->right = t;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

Node* insert(Node* root, int value) {
    if (root == NULL)
        return new Node(value);

    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);
    else {
        cout << "Duplicate value ignored: " << value << endl;
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    // Left Left
    if (balance > 1 && value < root->left->data)
        return rightRotate(root);

    // Right Right
    if (balance < -1 && value > root->right->data)
        return leftRotate(root);

    // Left Right
    if (balance > 1 && value > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left
    if (balance < -1 && value < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Print node value and its balance factor
void printNode(Node* root) {
    cout << root->data << "(BF=" << getBalance(root) << ") ";
}

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printNode(root);
        inorder(root->right);
    }
}

void preorder(Node* root) {
    if (root != NULL) {
        printNode(root);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printNode(root);
    }
}

void levelOrder(Node* root) {
    if (root == NULL)
        return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        printNode(current);

        if (current->left != NULL)
            q.push(current->left);

        if (current->right != NULL)
            q.push(current->right);
    }
}

// Verify that inorder values are sorted
bool verifySorted(Node* root, int &previous, bool &first) {
    if (root == NULL)
        return true;

    if (!verifySorted(root->left, previous, first))
        return false;

    if (!first && root->data <= previous)
        return false;

    previous = root->data;
    first = false;

    return verifySorted(root->right, previous, first);
}

void displayTraversals(Node* root) {
    cout << "\nInorder Traversal: ";
    inorder(root);

    cout << "\nPreorder Traversal: ";
    preorder(root);

    cout << "\nPostorder Traversal: ";
    postorder(root);

    cout << "\nLevel-order Traversal: ";
    levelOrder(root);

    int previous = 0;
    bool first = true;

    cout << "\n\nInorder Sorted Verification: ";
    if (verifySorted(root, previous, first))
        cout << "PASS - Values are in sorted order.";
    else
        cout << "FAIL - Values are not sorted.";

    cout << "\n";
}

int main() {
    Node* root = NULL;
    int n, value, choice;

    cout << "Enter number of initial nodes: ";
    cin >> n;

    if (n <= 0) {
        cout << "Please enter a positive number of nodes.\n";
        return 0;
    }

    cout << "Enter " << n << " integers:\n";

    for (int i = 0; i < n; i++) {
        cin >> value;
        root = insert(root, value);
    }

    do {
        cout << "\n===== AVL TREE MENU =====\n";
        cout << "1. Insert additional value\n";
        cout << "2. Display all traversals\n";
        cout << "3. Verify inorder is sorted\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                root = insert(root, value);
                cout << "Tree updated successfully.\n";
                displayTraversals(root);
                break;

            case 2:
                displayTraversals(root);
                break;

            case 3: {
                int previous = 0;
                bool first = true;

                if (verifySorted(root, previous, first))
                    cout << "PASS - Inorder is sorted.\n";
                else
                    cout << "FAIL - Inorder is not sorted.\n";
                break;
            }

            case 4:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}

