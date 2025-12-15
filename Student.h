#pragma once

#include <string>

class Student {
public:
    int id;
    std::string name;
    std::string email;
    std::string password;
    bool subscriptionStatus;

    Student();

    Student(
        int id,
        const std::string& name,
        const std::string& email,
        const std::string& password,
        bool status = true
    );

    void display() const;
};
