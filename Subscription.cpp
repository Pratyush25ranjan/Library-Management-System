#include "Subscription.h"



Subscription::Subscription()
    : studentId(0) {
}

Subscription::Subscription(int studentId,
    const std::string& startDate,
    const std::string& endDate)
    : studentId(studentId),
    startDate(startDate),
    endDate(endDate) {
}

void Subscription::display() const {
   
}

bool Subscription::isExpired(const std::string& currentDate) const {
    return currentDate > endDate;
}
