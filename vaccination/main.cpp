#include <iostream>
#include <string>
using namespace std;

// ==========================================
// 1. HASHING (Linear Probing) - Citizen Registry
// ==========================================
const int TABLE_SIZE = 101; // Prime number reduces collisions

struct Citizen {
    int id;
    string name;
    int age;
    int bookedSlot;   // -1 if not booked
    bool isVaccinated;
    bool isOccupied;

    Citizen() : id(-1), name(""), age(0), bookedSlot(-1), isVaccinated(false), isOccupied(false) {}
};

class CitizenHashTable {
private:
    Citizen table[TABLE_SIZE];

    int hashFunction(int id) {
        return id % TABLE_SIZE;
    }

public:
    bool registerCitizen(int id, string name, int age) {
        int index = hashFunction(id);
        int startIndex = index;

        while (table[index].isOccupied) {
            if (table[index].id == id) {
                cout << "Error: Citizen ID " << id << " is already registered.\n";
                return false;
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == startIndex) {
                cout << "Error: Hash table is full!\n";
                return false;
            }
        }

        table[index].id = id;
        table[index].name = name;
        table[index].age = age;
        table[index].bookedSlot = -1;
        table[index].isVaccinated = false;
        table[index].isOccupied = true;
        return true;
    }

    Citizen* searchCitizen(int id) {
        int index = hashFunction(id);
        int startIndex = index;

        while (table[index].isOccupied) {
            if (table[index].id == id) {
                return &table[index];
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == startIndex) break;
        }
        return nullptr;
    }
};

// ==========================================
// 2. ARRAY - Vaccination Time Slots
// ==========================================
const int MAX_SLOTS = 4;

struct Slot {
    int slotId;
    string timeRange;
    int capacity;
    int bookedCount;
};

// ==========================================
// 3. CIRCULAR QUEUE - Active Vaccination Booth
// ==========================================
const int BOOTH_CAPACITY = 5;

class CircularQueue {
private:
    int arr[BOOTH_CAPACITY]; // Stores Citizen IDs
    int front, rear, count;

public:
    CircularQueue() : front(0), rear(-1), count(0) {}

    bool isFull() { return count == BOOTH_CAPACITY; }
    bool isEmpty() { return count == 0; }

    bool enqueue(int citizenId) {
        if (isFull()) return false;
        rear = (rear + 1) % BOOTH_CAPACITY;
        arr[rear] = citizenId;
        count++;
        return true;
    }

    int dequeue() {
        if (isEmpty()) return -1;
        int citizenId = arr[front];
        front = (front + 1) % BOOTH_CAPACITY;
        count--;
        return citizenId;
    }

    void display() {
        if (isEmpty()) {
            cout << "  [Active Booth Queue is empty]\n";
            return;
        }
        cout << "  Active Booth Queue (Front -> Rear): ";
        for (int i = 0; i < count; i++) {
            int idx = (front + i) % BOOTH_CAPACITY;
            cout << arr[idx] << (i < count - 1 ? " -> " : "");
        }
        cout << "\n";
    }
};

// ==========================================
// 4. STANDARD QUEUE (Linked List) - Waitlist
// ==========================================
struct Node {
    int citizenId;
    Node* next;
    Node(int id) : citizenId(id), next(nullptr) {}
};

class WaitlistQueue {
private:
    Node *front, *rear;

public:
    WaitlistQueue() : front(nullptr), rear(nullptr) {}

    bool isEmpty() { return front == nullptr; }

    void enqueue(int citizenId) {
        Node* newNode = new Node(citizenId);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    int dequeue() {
        if (isEmpty()) return -1;
        Node* temp = front;
        int id = temp->citizenId;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        delete temp;
        return id;
    }

    void display() {
        if (isEmpty()) {
            cout << "  [Waitlist is empty]\n";
            return;
        }
        cout << "  Waitlist Queue (FIFO): ";
        Node* curr = front;
        while (curr != nullptr) {
            cout << curr->citizenId << (curr->next ? " -> " : "");
            curr = curr->next;
        }
        cout << "\n";
    }
};

// ==========================================
// MAIN SYSTEM CONTROLLER
// ==========================================
int main() {
    CitizenHashTable registry;
    CircularQueue activeBooth;
    WaitlistQueue waitlist;

    // Initialize Slots Array
    Slot slots[MAX_SLOTS] = {
        {1, "09:00 AM - 10:00 AM", 3, 0},
        {2, "10:00 AM - 11:00 AM", 3, 0},
        {3, "11:00 AM - 12:00 PM", 3, 0},
        {4, "02:00 PM - 03:00 PM", 3, 0}
    };

    int choice;
    while (true) {
        cout << "\n====== VACCINATION SLOT BOOKING SYSTEM ======\n";
        cout << "1. Register Citizen (Hashing)\n";
        cout << "2. View Available Slots (Array)\n";
        cout << "3. Book Slot / Join Queue (Circular Queue & Waitlist)\n";
        cout << "4. Process Next Vaccination (Dequeue)\n";
        cout << "5. Check Citizen Status (Hash Lookup)\n";
        cout << "6. Display Booth Queue & Waitlist\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 0) break;

        switch (choice) {
            case 1: {
                int id, age;
                string name;
                cout << "Enter Citizen ID (numeric): ";
                cin >> id;
                cin.ignore();
                cout << "Enter Full Name: ";
                getline(cin, name);
                cout << "Enter Age: ";
                cin >> age;

                if (registry.registerCitizen(id, name, age)) {
                    cout << "Success: Citizen registered!\n";
                }
                break;
            }

            case 2: {
                cout << "\n--- Daily Vaccination Slots ---\n";
                for (int i = 0; i < MAX_SLOTS; i++) {
                    cout << "Slot " << slots[i].slotId << " [" << slots[i].timeRange << "] - "
                         << "Available: " << (slots[i].capacity - slots[i].bookedCount)
                         << "/" << slots[i].capacity << "\n";
                }
                break;
            }

            case 3: {
                int id, slotChoice;
                cout << "Enter Citizen ID: ";
                cin >> id;

                Citizen* c = registry.searchCitizen(id);
                if (!c) {
                    cout << "Error: Citizen not found. Please register first.\n";
                    break;
                }
                if (c->isVaccinated) {
                    cout << "Info: Citizen is already vaccinated.\n";
                    break;
                }
                if (c->bookedSlot != -1) {
                    cout << "Info: Citizen already has a booking in Slot " << c->bookedSlot << ".\n";
                    break;
                }

                cout << "Select Slot ID (1-" << MAX_SLOTS << "): ";
                cin >> slotChoice;

                if (slotChoice < 1 || slotChoice > MAX_SLOTS) {
                    cout << "Invalid Slot ID.\n";
                    break;
                }

                Slot& selected = slots[slotChoice - 1];
                if (selected.bookedCount < selected.capacity && !activeBooth.isFull()) {
                    selected.bookedCount++;
                    c->bookedSlot = selected.slotId;
                    activeBooth.enqueue(c->id);
                    cout << "Confirmed! " << c->name << " added to Active Booth Queue for Slot " << selected.slotId << ".\n";
                } else {
                    waitlist.enqueue(c->id);
                    cout << "Slot or Booth is currently full. " << c->name << " added to the Waitlist Queue.\n";
                }
                break;
            }

            case 4: {
                if (activeBooth.isEmpty()) {
                    cout << "No citizens currently in the Active Booth Queue.\n";
                    break;
                }

                int servedId = activeBooth.dequeue();
                Citizen* c = registry.searchCitizen(servedId);
                if (c) {
                    c->isVaccinated = true;
                    cout << "Vaccinated: " << c->name << " (ID: " << c->id << ")\n";
                }

                // Automatically move next person from Waitlist to Active Booth
                if (!waitlist.isEmpty() && !activeBooth.isFull()) {
                    int nextId = waitlist.dequeue();
                    Citizen* nextC = registry.searchCitizen(nextId);
                    if (nextC) {
                        activeBooth.enqueue(nextId);
                        nextC->bookedSlot = 1; // Assigned to next available slot
                        cout << "Waitlist Update: " << nextC->name << " (ID: " << nextId << ") moved to Active Booth Queue.\n";
                    }
                }
                break;
            }

            case 5: {
                int id;
                cout << "Enter Citizen ID to search: ";
                cin >> id;
                Citizen* c = registry.searchCitizen(id);
                if (!c) {
                    cout << "Citizen not found.\n";
                } else {
                    cout << "\n--- Citizen Details ---\n";
                    cout << "ID: " << c->id << "\nName: " << c->name << "\nAge: " << c->age << "\n";
                    cout << "Status: " << (c->isVaccinated ? "Vaccinated" : (c->bookedSlot != -1 ? "Slot Booked" : "Registered (No Slot)")) << "\n";
                }
                break;
            }

            case 6: {
                cout << "\n--- Queue Status ---\n";
                activeBooth.display();
                waitlist.display();
                break;
            }

            default:
                cout << "Invalid choice. Try again.\n";
        }
    }

    cout << "Exiting system. Stay safe!\n";
    return 0;
}