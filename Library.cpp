#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

#include "Library.h"
#include "ConsoleUI.h"
#include "JsonAdapters.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

void Library::Control() {
    int choice;

    loadFromFile("library.json");
    addSampleData();

    while (true) {
        clearScreen();
        setConsoleColor(15, 1);

        const int X = 20;
        int Y = 3;

        printAt(X, Y++, "+--------------------------------------+");
        printAt(X, Y++, "|     LIBRARY MANAGEMENT SYSTEM        |");
        printAt(X, Y++, "+--------------------------------------+");

        Y++;
        printAt(X, Y++, "1. Admin Login");
        printAt(X, Y++, "2. Student Login");
        printAt(X, Y++, "3. Exit");

        Y++;
        printAt(X, Y++, "+--------------------------------------+");

        Y++;
        inputAt(X, Y, "Enter Choice: ");
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            adminPanel();
            break;
        case 2:
            studentLogin();
            break;
        case 3:
            saveToFile("library.json");
            return;
        default:
            printAt(X, Y + 2, "Invalid choice!");
            pauseScreen();
        }
    }
}

void Library::adminPanel() {
    int choice;

    while (true) {
        clearScreen();
        setConsoleColor(15, 1);

        const int X = 20;
        int Y = 3;

        printAt(X, Y++, "+--------------------------------------+");
        printAt(X, Y++, "|             ADMIN PANEL              |");
        printAt(X, Y++, "+--------------------------------------+");

        Y++;
        printAt(X, Y++, "1. Add Book");
        printAt(X, Y++, "2. List Books");
        printAt(X, Y++, "3. Update Book");
        printAt(X, Y++, "4. Remove Book");
        printAt(X, Y++, "5. Add Student");
        printAt(X, Y++, "6. List Students");
        printAt(X, Y++, "7. Update Student");
        printAt(X, Y++, "8. Remove Student");
        printAt(X, Y++, "9. Manage Subscriptions");
        printAt(X, Y++, "10. Back");

        Y++;
        inputAt(X, Y, "Enter Choice: ");
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1: addBook(); break;
        case 2: listBooks(); break;
        case 3: updateBook(); break;
        case 4: removeBook(); break;
        case 5: addStudent(); break;
        case 6: listStudents(); break;
        case 7: updateStudent(); break;
        case 8: removeStudent(); break;
        case 9: manageSubscriptionsAdmin(); break;
        case 10: return;
        default:
            printAt(X, Y + 2, "Invalid choice!");
            pauseScreen();
        }
    }
}

void Library::studentLogin() {
    int id;
    string pass;

    clearScreen();
    setConsoleColor(15, 1);

    const int X = 20;
    int Y = 5;

    printAt(X, Y++, "+--------------------------------------+");
    printAt(X, Y++, "|           STUDENT LOGIN              |");
    printAt(X, Y++, "+--------------------------------------+");

    Y++;
    inputAt(X, Y++, "Student ID: ");
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    inputAt(X, Y++, "Password: ");
    getline(cin, pass);

    for (auto& s : students) {
        if (s.id == id && s.password == pass) {
            studentPanel(id);
            return;
        }
    }

    printAt(X, Y + 1, "Invalid credentials!");
    pauseScreen();
}

void Library::studentPanel(int studentId) {
    int choice;

    while (true) {
        clearScreen();
        setConsoleColor(15, 1);

        const int X = 20;
        int Y = 3;

        printAt(X, Y++, "+--------------------------------------+");
        printAt(X, Y++, "|            STUDENT PANEL             |");
        printAt(X, Y++, "+--------------------------------------+");

        Y++;
        printAt(X, Y++, "1. Search Book");
        printAt(X, Y++, "2. Reserve Book");
        printAt(X, Y++, "3. View All Books");
        printAt(X, Y++, "4. View My Subscriptions");
        printAt(X, Y++, "5. Change Password");
        printAt(X, Y++, "6. Logout");

        Y++;
        inputAt(X, Y, "Enter Choice: ");
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1: searchBook(); break;
        case 2: reserveBook(studentId); break;
        case 3: listBooks(); break;
        case 4: listSubscriptionsForStudent(studentId); break;
        case 5: changePassword(studentId); break;
        case 6: return;
        default:
            printAt(X, Y + 2, "Invalid choice!");
            pauseScreen();
        }

        saveToFile("library.json");
    }
}

void Library::searchBook() {
    clearScreen();
    setConsoleColor(15, 1);

    const int X = 20;
    int Y = 4;

    string keyword;
    inputAt(X, Y++, "Enter book title or author: ");
    getline(cin, keyword);

    bool found = false;
    Y++;

    for (const auto& b : books) {
        if (b.title.find(keyword) != string::npos ||
            b.author.find(keyword) != string::npos) {
            printAt(X, Y++, "--------------------------------------");
            printAt(X, Y++, "ID: " + to_string(b.id));
            printAt(X, Y++, "Title: " + b.title);
            printAt(X, Y++, "Author: " + b.author);
            printAt(X, Y++, "Status: " + string(b.available ? "Available" : "Reserved"));
            found = true;
        }
    }

    if (!found)
        printAt(X, Y + 1, "No matching books found.");

    pauseScreen();
}


void Library::reserveBook(int studentId) {
    clearScreen();
    setConsoleColor(15, 1);

    const int X = 20;
    int Y = 4;

    int bookId;
    inputAt(X, Y++, "Enter Book ID to reserve: ");
    cin >> bookId;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (auto& b : books) {
        if (b.id == bookId && b.available) {
            b.available = false;
            subscriptions.emplace_back(studentId, "01-11-2025", "30-11-2025");
            printAt(X, Y + 1, "Book reserved successfully!");
            pauseScreen();
            return;
        }
    }

    printAt(X, Y + 1, "Book not available!");
    pauseScreen();
}
void Library::addBook() {
    clearScreen();
    setConsoleColor(15, 1);

    const int X = 20;
    int Y = 4;

    Book b;
    b.available = true;

    inputAt(X, Y++, "Book ID: ");
    cin >> b.id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    inputAt(X, Y++, "Title: ");
    getline(cin, b.title);

    inputAt(X, Y++, "Author: ");
    getline(cin, b.author);

    inputAt(X, Y++, "Unique Code: ");
    getline(cin, b.uniqueCode);

    inputAt(X, Y++, "Location: ");
    getline(cin, b.location);

    books.push_back(b);

    printAt(X, Y + 1, "Book added successfully!");
    pauseScreen();
}

void Library::listBooks() const {
    clearScreen();
    setConsoleColor(15, 1);

    const int X = 20;
    int Y = 3;

    printAt(X, Y++, "+--------------------------------------+");
    printAt(X, Y++, "|              BOOK LIST               |");
    printAt(X, Y++, "+--------------------------------------+");

    Y++;
    for (const auto& b : books) {
        printAt(X, Y++, "ID: " + to_string(b.id));
        printAt(X, Y++, "Title: " + b.title);
        printAt(X, Y++, "Author: " + b.author);
        printAt(X, Y++, "Code: " + b.uniqueCode);
        printAt(X, Y++, "Location: " + b.location);
        printAt(X, Y++, "Status: " + string(b.available ? "Available" : "Reserved"));
        printAt(X, Y++, "--------------------------------------");
    }

    pauseScreen();
}

void Library::updateBook() {
    clearScreen();
    setConsoleColor(15, 1);

    const int X = 20;
    int Y = 4;

    int id;
    inputAt(X, Y++, "Enter Book ID to update: ");
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (auto& b : books) {
        if (b.id == id) {
            inputAt(X, Y++, "New Title: ");
            getline(cin, b.title);

            inputAt(X, Y++, "New Author: ");
            getline(cin, b.author);

            inputAt(X, Y++, "New Location: ");
            getline(cin, b.location);

            printAt(X, Y + 1, "Book updated successfully!");
            pauseScreen();
            return;
        }
    }

    printAt(X, Y + 1, "Book not found!");
    pauseScreen();
}

void Library::removeBook() {
    clearScreen();
    setConsoleColor(15, 1);

    const int X = 20;
    int Y = 4;

    int id;
    inputAt(X, Y++, "Enter Book ID to remove: ");
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    auto oldSize = books.size();

    books.erase(
        remove_if(books.begin(), books.end(),
            [id](const Book& b) { return b.id == id; }),
        books.end()
    );

    if (books.size() < oldSize)
        printAt(X, Y + 1, "Book removed successfully!");
    else
        printAt(X, Y + 1, "Book not found!");

    pauseScreen();
}


void Library::addStudent() {
    clearScreen();
    setConsoleColor(15, 1);

    const int X = 20;
    int Y = 4;

    Student s;
    s.subscriptionStatus = true;

    inputAt(X, Y++, "Student ID: ");
    cin >> s.id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    inputAt(X, Y++, "Name: ");
    getline(cin, s.name);

    inputAt(X, Y++, "Email: ");
    getline(cin, s.email);

    inputAt(X, Y++, "Password: ");
    getline(cin, s.password);

    students.push_back(s);

    printAt(X, Y + 1, "Student added successfully!");
    pauseScreen();
}

void Library::listStudents() const {
    clearScreen();
    setConsoleColor(15, 1);

    const int X = 20;
    int Y = 3;

    printAt(X, Y++, "+--------------------------------------+");
    printAt(X, Y++, "|             STUDENT LIST             |");
    printAt(X, Y++, "+--------------------------------------+");

    Y++;
    for (const auto& s : students) {
        printAt(X, Y++, "ID: " + to_string(s.id));
        printAt(X, Y++, "Name: " + s.name);
        printAt(X, Y++, "Email: " + s.email);
        printAt(X, Y++, "Status: " +
            string(s.subscriptionStatus ? "Active" : "Inactive"));
        printAt(X, Y++, "--------------------------------------");
    }

    pauseScreen();
}


void Library::updateStudent() {
    clearScreen();
    setConsoleColor(15, 1);

    const int X = 20;
    int Y = 4;

    int id;
    inputAt(X, Y++, "Enter Student ID to update: ");
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (auto& s : students) {
        if (s.id == id) {
            inputAt(X, Y++, "New Name: ");
            getline(cin, s.name);

            inputAt(X, Y++, "New Email: ");
            getline(cin, s.email);

            inputAt(X, Y++, "Subscription Active (1/0): ");
            int flag;
            cin >> flag;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            s.subscriptionStatus = (flag == 1);

            printAt(X, Y + 1, "Student updated successfully!");
            pauseScreen();
            return;
        }
    }

    printAt(X, Y + 1, "Student not found!");
    pauseScreen();
}

void Library::removeStudent() {
    clearScreen();
    setConsoleColor(15, 1);

    const int X = 20;
    int Y = 4;

    int id;
    inputAt(X, Y++, "Enter Student ID to remove: ");
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    auto oldSize = students.size();

    students.erase(
        remove_if(students.begin(), students.end(),
            [id](const Student& s) { return s.id == id; }),
        students.end()
    );

    if (students.size() < oldSize)
        printAt(X, Y + 1, "Student removed successfully!");
    else
        printAt(X, Y + 1, "Student not found!");

    pauseScreen();
}


void Library::manageSubscriptionsAdmin() {
    clearScreen();
    setConsoleColor(15, 1);

    const int X = 20;
    int Y = 4;

    int studentId;
    inputAt(X, Y++, "Enter Student ID: ");
    cin >> studentId;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string start, end;
    inputAt(X, Y++, "Start Date (DD-MM-YYYY): ");
    getline(cin, start);

    inputAt(X, Y++, "End Date (DD-MM-YYYY): ");
    getline(cin, end);

    subscriptions.emplace_back(studentId, start, end);

    printAt(X, Y + 1, "Subscription added successfully!");
    pauseScreen();
}


void Library::listSubscriptionsForStudent(int studentId) const {
    clearScreen();
    setConsoleColor(15, 1);

    const int X = 20;
    int Y = 4;

    bool found = false;

    for (const auto& sub : subscriptions) {
        if (sub.studentId == studentId) {
            printAt(X, Y++, "Start Date: " + sub.startDate);
            printAt(X, Y++, "End Date: " + sub.endDate);
            printAt(X, Y++, "--------------------------------------");
            found = true;
        }
    }

    if (!found)
        printAt(X, Y + 1, "No subscriptions found.");

    pauseScreen();
}


void Library::changePassword(int studentId) {
    clearScreen();
    setConsoleColor(15, 1);

    const int X = 20;
    int Y = 4;

    string oldPass, newPass;

    inputAt(X, Y++, "Old Password: ");
    getline(cin, oldPass);

    for (auto& s : students) {
        if (s.id == studentId && s.password == oldPass) {
            inputAt(X, Y++, "New Password: ");
            getline(cin, newPass);
            s.password = newPass;

            printAt(X, Y + 1, "Password changed successfully!");
            pauseScreen();
            return;
        }
    }

    printAt(X, Y + 1, "Incorrect password!");
    pauseScreen();
}

void Library::addSampleData() {
    if (!books.empty()) return;

    books.emplace_back(1, "C++ Programming", "Bjarne Stroustrup",
        "CPP101", "Shelf A1", true);
    books.emplace_back(2, "Data Structures", "Mark Allen Weiss",
        "DS102", "Shelf A2", true);

    students.emplace_back(101, "John Doe", "john@mail.com", "1234", true);

    subscriptions.emplace_back(101, "01-01-2025", "31-12-2025");
}

void Library::saveToFile(const string& filename) {
    json j;

    j["books"] = json::array();
    for (const auto& b : books) {
        json jb;
        to_json(jb, b);
        j["books"].push_back(jb);
    }

    j["students"] = json::array();
    for (const auto& s : students) {
        json js;
        to_json(js, s);
        j["students"].push_back(js);
    }

    j["subscriptions"] = json::array();
    for (const auto& sub : subscriptions) {
        json jsub;
        to_json(jsub, sub);
        j["subscriptions"].push_back(jsub);
    }

    ofstream file(filename);
    file << j.dump(4);
}

void Library::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return;

    json j;
    file >> j;

    books.clear();
    students.clear();
    subscriptions.clear();

    if (j.contains("books")) {
        for (const auto& jb : j["books"]) {
            Book b;
            from_json(jb, b);
            books.push_back(b);
        }
    }

    if (j.contains("students")) {
        for (const auto& js : j["students"]) {
            Student s;
            from_json(js, s);
            students.push_back(s);
        }
    }

    if (j.contains("subscriptions")) {
        for (const auto& jsub : j["subscriptions"]) {
            Subscription sub;
            from_json(jsub, sub);
            subscriptions.push_back(sub);
        }
    }
}


