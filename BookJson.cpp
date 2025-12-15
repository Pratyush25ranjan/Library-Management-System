#include "json.hpp"
#include "Book.h"

using json = nlohmann::json;

void to_json(json& j, const Book& b) {
    j = json{
        {"id", b.id},
        {"title", b.title},
        {"author", b.author},
        {"uniqueCode", b.uniqueCode},
        {"location", b.location},
        {"available", b.available}
    };
}

void from_json(const json& j, Book& b) {
    j.at("id").get_to(b.id);
    j.at("title").get_to(b.title);
    j.at("author").get_to(b.author);
    j.at("uniqueCode").get_to(b.uniqueCode);
    j.at("location").get_to(b.location);
    j.at("available").get_to(b.available);
}
