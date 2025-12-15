#pragma once

#include <vector>
#include <string>

#include "Book.h"
#include "Student.h"
#include "Subscription.h"

class Library {
private:
    std::vector<Book> books;
    std::vector<Student> students;
    std::vector<Subscription> subscriptions;

    const std::string adminId = "admin";
    const std::string adminPass = "1234";

public:
    void Control();
    void addSampleData();

    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);

private:
    // Admin
    void adminPanel();

    // Student
    void studentLogin();
    void studentPanel(int studentId);

    // Book CRUD
    void addBook();
    void listBooks() const;
    void updateBook();
    void removeBook();

    // Student CRUD
    void addStudent();
    void listStudents() const;
    void updateStudent();
    void removeStudent();

    // Subscription
    void manageSubscriptionsAdmin();
    void listSubscriptionsForStudent(int studentId) const;

    // Search / Reserve
    void searchBook();
    void reserveBook(int studentId);

    // Password
    void changePassword(int studentId);
};
