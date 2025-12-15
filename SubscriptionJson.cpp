#include "json.hpp"
#include "Subscription.h"

using json = nlohmann::json;

void to_json(json& j, const Subscription& s) {
    j = json{
        {"studentId", s.studentId},
        {"startDate", s.startDate},
        {"endDate", s.endDate}
    };
}

void from_json(const json& j, Subscription& s) {
    j.at("studentId").get_to(s.studentId);
    j.at("startDate").get_to(s.startDate);
    j.at("endDate").get_to(s.endDate);
}
