# DSA-mini-project
# Student Database Performance Comparison Project 
## 🚀 What's This Project About? 
Ever wondered how different data structures affect your program's speed? This mini-project demonstrates exactly that! We built a simple student database system using four common data structures in C++ and measured how fast they perform basic operations like adding, searching, and removing records.

The goal? To show why choosing the right data structure matters—especially when dealing with large amounts of data. 

## 🔍 What Data Structures Are We Testing?
We compared four different ways to store student records: 
1. Array (Vector) – Simple but can be slow for large datasets.
2. Linked List – Flexible but also slow for searching.
3. Hash Table (Unordered Map) – Super fast for lookups!
4. Balanced Tree (Map) – Slower than a hash table but keeps data sorted.
  
## ⏱️ Performance Results (Spoiler Alert!) 
Here’s what we found:  
| Data Structure       | Insertion Time | Search Time | Deletion Time | Best For                          |
|----------------------|----------------|-------------|--------------|-----------------------------------|
| **Vector**           | O(n)           | O(n)        | O(n)         | Small datasets, sequential access |
| **Linked List**      | O(n)           | O(n)        | O(n)         | Frequent insertions/deletions     |
| **Hash Map**         | O(1) ⚡        | O(1) ⚡     | O(1) ⚡      | Fast lookups, unsorted data       |
| **Balanced Tree**    | O(log n)       | O(log n)    | O(log n)     | Sorted data needs                 |

### 🏆 Key Takeaways
- **Hash Map** wins for raw speed (constant time operations)
- **Balanced Tree** is best when you need sorted data
- **Vector/List** only suitable for very small datasets

## 🛠️ How to Run This Yourself
### Requirements 
- C++ compiler (like g++)
- C++17 or later 
### Steps 
#### 1. Compile the code:
> bash
> >  g++ -std=c++17 student_db.cpp -o student_db 
 
#### 2. Run it:
> bash
> >   ./student_db  

#### 3. Choose a data structure to test: 
> Select data structure:
> > 1. Vector
> > 2. List
> > 3. Hash Map
> > 4. Map
#### 4. See the performance results!
The program will automatically test: 
Adding 10,000 students  
Searching for 1,000 students  
Removing 1,000 students
Example output:  
> Added 10000 students in 120 ms

> Performed 1000 searches in 5 ms

> Removed 1000 students in 8 ms
## 📌 Why Does This Matter? 
### Real-world impact: 
Choosing the wrong data structure can make your app sluggish. 
### Optimization matters:
If you’re working with big datasets (like student records, user accounts, etc.), a Hash Map can be 100x faster than a Vector or Linked List!  
### Learning by doing: 
This project helps visualize what "O(1)" vs "O(n)" actually means in practice.  
## 🔄 Want to Modify It? 
You can tweak the test sizes in the code:  
> cpp
> > const int N = 10000;  // Number of students to add

> > const int M = 1000;   // Number of searches

> > const int K = 1000;   // Number of deletions   

Try increasing N to 100,000 and see how much slower Vector and List become compared to Hash Map!
