#include "json.hpp"
#include "Student.h"

using json = nlohmann::json;

void to_json(json& j, const Student& s) {
    j = json{
        {"id", s.id},
        {"name", s.name},
        {"email", s.email},
        {"password", s.password},
        {"subscriptionStatus", s.subscriptionStatus}
    };
}

void from_json(const json& j, Student& s) {
    j.at("id").get_to(s.id);
    j.at("name").get_to(s.name);
    j.at("email").get_to(s.email);
    j.at("password").get_to(s.password);
    j.at("subscriptionStatus").get_to(s.subscriptionStatus);
}
