#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <unordered_map>
#include <map>
#include <string>
#include <limits>
#include <cctype>

using namespace std;

struct Student {
    int id;
    string name;
};

class StudentDB {
public:
    virtual void addStudent(int id, const string& name) = 0;
    virtual void removeStudent(int id) = 0;
    virtual Student* searchStudent(int id) = 0;
    virtual void displayAll() = 0;
    virtual ~StudentDB() {}
};

class VectorDB : public StudentDB {
private:
    vector<Student> students;
public:
    void addStudent(int id, const string& name) override {
        for (const auto& s : students) {
            if (s.id == id) {
                cout << "Error: Student ID already exists!\n";
                return;
            }
        }
        students.push_back({id, name});
        cout << "Student added successfully!\n";
    }

    void removeStudent(int id) override {
        auto it = find_if(students.begin(), students.end(), 
            [id](const Student& s) { return s.id == id; });
        
        if (it != students.end()) {
            students.erase(it);
            cout << "Student removed successfully!\n";
        } else {
            cout << "Error: Student not found!\n";
        }
    }

    Student* searchStudent(int id) override {
        for (auto& s : students) {
            if (s.id == id) {
                return &s;
            }
        }
        return nullptr;
    }

    void displayAll() override {
        if (students.empty()) {
            cout << "Database is empty!\n";
            return;
        }
        for (const auto& s : students) {
            cout << "ID: " << s.id << "\tName: " << s.name << endl;
        }
    }
};

class ListDB : public StudentDB {
private:
    list<Student> students;
public:
    void addStudent(int id, const string& name) override {
        for (const auto& s : students) {
            if (s.id == id) {
                cout << "Error: Student ID already exists!\n";
                return;
            }
        }
        students.push_back({id, name});
        cout << "Student added successfully!\n";
    }

    void removeStudent(int id) override {
        students.remove_if([id](const Student& s) { return s.id == id; });
        cout << "Operation completed!\n"; // List always "succeeds" even if not found
    }

    Student* searchStudent(int id) override {
        for (auto& s : students) {
            if (s.id == id) {
                return &s;
            }
        }
        return nullptr;
    }

    void displayAll() override {
        if (students.empty()) {
            cout << "Database is empty!\n";
            return;
        }
        for (const auto& s : students) {
            cout << "ID: " << s.id << "\tName: " << s.name << endl;
        }
    }
};

class HashMapDB : public StudentDB {
private:
    unordered_map<int, Student> students;
public:
    void addStudent(int id, const string& name) override {
        if (students.find(id) != students.end()) {
            cout << "Error: Student ID already exists!\n";
            return;
        }
        students[id] = {id, name};
        cout << "Student added successfully!\n";
    }

    void removeStudent(int id) override {
        if (students.erase(id)) {
            cout << "Student removed successfully!\n";
        } else {
            cout << "Error: Student not found!\n";
        }
    }

    Student* searchStudent(int id) override {
        auto it = students.find(id);
        if (it != students.end()) {
            return &it->second;
        }
        return nullptr;
    }

    void displayAll() override {
        if (students.empty()) {
            cout << "Database is empty!\n";
            return;
        }
        for (const auto& pair : students) {
            cout << "ID: " << pair.first << "\tName: " << pair.second.name << endl;
        }
    }
};

class MapDB : public StudentDB {
private:
    map<int, Student> students;
public:
    void addStudent(int id, const string& name) override {
        if (students.find(id) != students.end()) {
            cout << "Error: Student ID already exists!\n";
            return;
        }
        students[id] = {id, name};
        cout << "Student added successfully!\n";
    }

    void removeStudent(int id) override {
        if (students.erase(id)) {
            cout << "Student removed successfully!\n";
        } else {
            cout << "Error: Student not found!\n";
        }
    }

    Student* searchStudent(int id) override {
        auto it = students.find(id);
        if (it != students.end()) {
            return &it->second;
        }
        return nullptr;
    }

    void displayAll() override {
        if (students.empty()) {
            cout << "Database is empty!\n";
            return;
        }
        for (const auto& pair : students) {
            cout << "ID: " << pair.first << "\tName: " << pair.second.name << endl;
        }
    }
};

bool askToContinue() {
    while (true) {
        cout << "\nContinue? (y/n): ";
        char choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        choice = tolower(choice);
        if (choice == 'y') return true;
        if (choice == 'n') return false;
        
        cout << "Invalid input! Please enter 'y' or 'n'.\n";
    }
}

void clearScreen() {
    cout << "\033[2J\033[1;1H"; // ANSI escape codes for clearing screen
}

void manualTest(StudentDB* db) {
    while (true) {
        clearScreen();
        cout << "STUDENT DATABASE SYSTEM\n";
        cout << "1. Add Student\n2. Remove Student\n";
        cout << "3. Search Student\n4. Display All\n5. Exit\n";
        cout << "Enter choice (1-5): ";
        
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                int id;
                string name;
                cout << "Enter student ID: ";
                cin >> id;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid ID! Must be a number.\n";
                    break;
                }
                cout << "Enter student name: ";
                cin.ignore();
                getline(cin, name);
                db->addStudent(id, name);
                break;
            }
            case 2: {
                int id;
                cout << "Enter student ID to remove: ";
                cin >> id;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid ID! Must be a number.\n";
                    break;
                }
                db->removeStudent(id);
                break;
            }
            case 3: {
                int id;
                cout << "Enter student ID to search: ";
                cin >> id;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid ID! Must be a number.\n";
                    break;
                }
                Student* s = db->searchStudent(id);
                if (s) {
                    cout << "FOUND: ID " << s->id << " - " << s->name << endl;
                } else {
                    cout << "Student not found!\n";
                }
                break;
            }
            case 4:
                db->displayAll();
                break;
            case 5:
                return;
            default:
                cout << "Invalid choice! Please enter 1-5.\n";
        }

        if (!askToContinue()) break;
    }
}

int main() {
    while (true) {
        clearScreen();
        cout << "SELECT DATA STRUCTURE\n";
        cout << "1. Vector\n2. Linked List\n";
        cout << "3. Hash Map\n4. Balanced Tree (Map)\n5. Exit\n";
        cout << "Enter choice (1-5): ";
        
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        StudentDB* db = nullptr;
        switch (choice) {
            case 1: db = new VectorDB(); break;
            case 2: db = new ListDB(); break;
            case 3: db = new HashMapDB(); break;
            case 4: db = new MapDB(); break;
            case 5: return 0;
            default:
                cout << "Invalid choice! Please enter 1-5.\n";
                continue;
        }

        manualTest(db);
        delete db;
        
        cout << "\nTest another data structure? (y/n): ";
        char restart;
        cin >> restart;
        if (tolower(restart) != 'y') break;
    }
    return 0;
}
