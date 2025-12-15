#include "Book.h"



Book::Book()
    : id(0), available(true) {
}

Book::Book(
    int id,
    const std::string& title,
    const std::string& author,
    const std::string& code,
    const std::string& location,
    bool available
)
    : id(id),
    title(title),
    author(author),
    uniqueCode(code),
    location(location),
    available(available) {
}

void Book::display() const {
   
}
