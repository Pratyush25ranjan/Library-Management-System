#pragma once

#include <string>

class Book {
public:
    int id;
    std::string title;
    std::string author;
    std::string uniqueCode;
    std::string location;
    bool available;

    Book();

    Book(
        int id,
        const std::string& title,
        const std::string& author,
        const std::string& code,
        const std::string& location,
        bool available = true
    );

    void display() const;
};
