#pragma once
#include "Repository.h"
#include <string>

// ============================================================
// Business Logic Layer
// Реализует правила работы системы: проверки, вычисления,
// формирование отчётов. Не знает о деталях хранения данных —
// работает только через Repository.
// ============================================================
class AttendanceService {
public:
    explicit AttendanceService(Repository& repo) : repo_(repo) {}

    // Отметка посещаемости с проверкой существования студента и занятия
    bool markAttendance(int studentId, int lessonId, Status status, std::string& errorMessage);

    // Процент посещаемости студента по всем занятиям
    double attendanceRateForStudent(int studentId) const;

    // Формирование отчёта по группе за все занятия в формате CSV
    // Возвращает true и путь к файлу, если данные найдены
    bool exportGroupReportCsv(const std::string& groupName, const std::string& filePath, std::string& errorMessage) const;

private:
    Repository& repo_;
};
