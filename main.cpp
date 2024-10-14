// COMSC-210 | Lab 21 | Dan Pokhrel
#include <iostream>
#include <string>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;
const int MAX_AGE = 20, ARR_COUNT = 15;

class Goat{
private:
    int age;
    string name;
    string color;
    string names[ARR_COUNT] = {
        "Bella", "Luna", "Daisy", "Milo", "Chloe",
        "Thor", "Willow", "Oliver", "Hazel", "Archie",
        "Clover", "Finn", "Penny", "Ruby", "Leo"
    };
    string colors[ARR_COUNT] = {
        "Red", "Blue", "Green", "Yellow", "Orange",
        "Purple", "Pink", "Brown", "Black", "White",
        "Gray", "Cyan", "Magenta", "Lime", "Indigo"
    };

public:
    // constructors
    Goat(){
        age = rand() % MAX_AGE + 1; // 1-20
        name = names[rand() % ARR_COUNT]; // choose a name at index 0-14
        color = colors[rand() % ARR_COUNT]; // choose a color at index 0-14
    }
    Goat(int a, string n, string c) {age = a; name = n; color = c;}

    // Setters
    void setAge(int a) {age = a;}
    void setName(string n) {name = n;}
    void setColor(string c) {color = c;}
    // Getters
    int getAge() const {return age;}
    string getName() const {return name;}
    string getColor() const {return color;}

    string getStr() { // Returns data as formatted string
        return name + " (" + color + ", " + to_string(age) + ")";
    }
};

class DoublyLinkedList {
private:
    struct Node {
        Goat data;
        Node* prev;
        Node* next;
        Node(Goat *val, Node* p = nullptr, Node* n = nullptr) {
            data = *val; // copies the actual data, not the pointer
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void push_back(Goat *value) {
        Node* newNode = new Node(value);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(Goat *value) {
        Node* newNode = new Node(value);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(Goat *value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    void delete_node(Goat *value) {
        if (!head) return; // Empty list

        Node* temp = head;
        while (temp && temp->data.getName() != value->getName())
            temp = temp->next;

        if (!temp) return; // Value not found

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }

    void print() {
        Node* current = head;
        if (!current){
            cout << "List Empty";
            return;
        }
        while (current) {
            cout << "    " << current->data.getStr() << endl;
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current){
            cout << "List Empty";
            return;
        }
        while (current) {
            cout << "    " << current->data.getStr() << endl;
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() {
    srand(time(0));

    DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;

    for (int i = 0; i < size; ++i){ // populate list
        Goat *goat = new Goat();
        list.push_back(goat);
    }

    cout << "List forward:\n";
    list.print();

    cout << "List backward:\n";
    list.print_reverse();

    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward:\n";
    list.print();

    return 0;
}
