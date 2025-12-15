#include "Student.h"



Student::Student()
    : id(0), subscriptionStatus(true) {
}

Student::Student(int id,
    const std::string& name,
    const std::string& email,
    const std::string& password,
    bool status)
    : id(id),
    name(name),
    email(email),
    password(password),
    subscriptionStatus(status) {
}

void Student::display() const {
   
}
