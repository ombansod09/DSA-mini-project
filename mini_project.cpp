#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <map>
#include <chrono>
#include <random>
#include <algorithm>
#include <string>

struct Student {
    int id;
    std::string name;
};

class StudentDB {
public:
    virtual void addStudent(int id, const std::string& name) = 0;
    virtual void removeStudent(int id) = 0;
    virtual Student* searchStudent(int id) = 0;
    virtual void displayAll() = 0;
    virtual ~StudentDB() {}
};

class VectorDB : public StudentDB {
private:
    std::vector<Student> students;
public:
    void addStudent(int id, const std::string& name) override {
        for (const auto& s : students) {
            if (s.id == id) {
                std::cout << "Student ID already exists.\n";
                return;
            }
        }
        students.push_back({id, name});
    }

    void removeStudent(int id) override {
        auto it = std::find_if(students.begin(), students.end(), [id](const Student& s) {
            return s.id == id;
        });
        if (it != students.end()) {
            students.erase(it);
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
        for (const auto& s : students) {
            std::cout << "ID: " << s.id << ", Name: " << s.name << std::endl;
        }
    }
};

class ListDB : public StudentDB {
private:
    std::list<Student> students;
public:
    void addStudent(int id, const std::string& name) override {
        for (const auto& s : students) {
            if (s.id == id) {
                std::cout << "Student ID already exists.\n";
                return;
            }
        }
        students.push_back({id, name});
    }

    void removeStudent(int id) override {
        students.remove_if([id](const Student& s) { return s.id == id; });
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
        for (const auto& s : students) {
            std::cout << "ID: " << s.id << ", Name: " << s.name << std::endl;
        }
    }
};

class HashMapDB : public StudentDB {
private:
    std::unordered_map<int, Student> students;
public:
    void addStudent(int id, const std::string& name) override {
        if (students.find(id) != students.end()) {
            std::cout << "Student ID already exists.\n";
            return;
        }
        students[id] = {id, name};
    }

    void removeStudent(int id) override {
        students.erase(id);
    }

    Student* searchStudent(int id) override {
        auto it = students.find(id);
        if (it != students.end()) {
            return &it->second;
        }
        return nullptr;
    }

    void displayAll() override {
        for (const auto& pair : students) {
            std::cout << "ID: " << pair.first << ", Name: " << pair.second.name << std::endl;
        }
    }
};

class MapDB : public StudentDB {
private:
    std::map<int, Student> students;
public:
    void addStudent(int id, const std::string& name) override {
        if (students.find(id) != students.end()) {
            std::cout << "Student ID already exists.\n";
            return;
        }
        students[id] = {id, name};
    }

    void removeStudent(int id) override {
        students.erase(id);
    }

    Student* searchStudent(int id) override {
        auto it = students.find(id);
        if (it != students.end()) {
            return &it->second;
        }
        return nullptr;
    }

    void displayAll() override {
        for (const auto& pair : students) {
            std::cout << "ID: " << pair.first << ", Name: " << pair.second.name << std::endl;
        }
    }
};

int main() {
    std::cout << "Select data structure:\n";
    std::cout << "1. Vector\n2. List\n3. Hash Map\n4. Map\n";
    int choice;
    std::cin >> choice;

    StudentDB* db = nullptr;
    switch(choice) {
        case 1: db = new VectorDB(); break;
        case 2: db = new ListDB(); break;
        case 3: db = new HashMapDB(); break;
        case 4: db = new MapDB(); break;
        default: std::cout << "Invalid choice.\n"; return 1;
    }

    const int N = 10000;
    const int M = 1000;
    const int K = 1000;

    std::vector<int> ids(N);
    for (int i = 0; i < N; ++i) {
        ids[i] = i;
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(ids.begin(), ids.end(), g);

    // Add Students
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        db->addStudent(ids[i], "Student" + std::to_string(ids[i]));
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Added " << N << " students in " << duration.count() << " ms\n";

    // Search Students
    std::shuffle(ids.begin(), ids.end(), g);
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < M; ++i) {
        db->searchStudent(ids[i]);
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Performed " << M << " searches in " << duration.count() << " ms\n";

    // Remove Students
    std::shuffle(ids.begin(), ids.end(), g);
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < K; ++i) {
        db->removeStudent(ids[i]);
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Removed " << K << " students in " << duration.count() << " ms\n";

    delete db;
    return 0;
}