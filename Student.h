#pragma once
#include <string>

// ============================================================
// Data Layer — сущность "Студент"
// ============================================================
struct Student {
    int id;
    std::string fullName;
    std::string groupName;

    Student(int id_, std::string fullName_, std::string groupName_)
        : id(id_), fullName(std::move(fullName_)), groupName(std::move(groupName_)) {}
};
