#pragma once
#include <string>

// ============================================================
// Data Layer — сущность "Занятие"
// ============================================================
struct Lesson {
    int id;
    std::string discipline;
    std::string groupName;
    std::string date; // формат ДД.ММ.ГГГГ

    Lesson(int id_, std::string discipline_, std::string groupName_, std::string date_)
        : id(id_), discipline(std::move(discipline_)), groupName(std::move(groupName_)), date(std::move(date_)) {}
};
