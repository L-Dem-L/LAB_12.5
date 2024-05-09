#include <iostream>
#include <fstream>
#include <stack>

struct Node {
    int data;
    Node* next;
};

void createList(Node*& head, Node*& tail, int values[], int size) {
    head = nullptr;
    tail = nullptr;

    for (int i = 0; i < size; i++) {
        Node* newNode = new Node();
        newNode->data = values[i];
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }
}

void readFromFile(const std::string& filename, int& n, int*& values) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file " << filename << std::endl;
        exit(1);
    }

    file >> n;
    values = new int[n];

    for (int i = 0; i < n; i++) {
        file >> values[i];
    }

    file.close();
}

int main() {
    int n;
    int* values;

    readFromFile("numbers.txt", n, values);

    Node* head;
    Node* tail;

    createList(head, tail, values, n);

    delete[] values; // Free memory allocated for values array

    std::stack<int> stack;

    Node* current = head;
    while (current != nullptr) {
        stack.push(current->data);
        current = current->next;
    }

    int max_val = stack.top();
    int min_val = stack.top();
    int max_pos = 1;
    int min_pos = 1;
    int pos = 1;

    stack.pop();

    while (!stack.empty()) {
        pos++;
        int val = stack.top();
        if (val > max_val) {
            max_val = val;
            max_pos = pos;
        }
        if (val < min_val) {
            min_val = val;
            min_pos = pos;
        }
        stack.pop();
    }

    std::cout << "Max value: " << max_val << ", position: " << n - max_pos + 1 << std::endl;
    std::cout << "Min value: " << min_val << ", position: " << n - min_pos + 1 << std::endl;

    // Free memory allocated for the linked list
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
