#pragma once

#include "json.hpp"
#include "Book.h"
#include "Student.h"
#include "Subscription.h"

// Tell compiler these functions exist
void to_json(nlohmann::json& j, const Book& b);
void from_json(const nlohmann::json& j, Book& b);

void to_json(nlohmann::json& j, const Student& s);
void from_json(const nlohmann::json& j, Student& s);

void to_json(nlohmann::json& j, const Subscription& s);
void from_json(const nlohmann::json& j, Subscription& s);
