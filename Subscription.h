#pragma once

#include <string>

class Subscription {
public:
    int studentId;
    std::string startDate;
    std::string endDate;

    Subscription();

    Subscription(
        int studentId,
        const std::string& startDate,
        const std::string& endDate
    );

    void display() const;
    bool isExpired(const std::string& currentDate) const;
};
