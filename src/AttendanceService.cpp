#include "AttendanceService.h"
#include <fstream>
#include <set>

bool AttendanceService::markAttendance(int studentId, int lessonId, Status status, std::string& errorMessage) {
    if (!repo_.findStudent(studentId)) {
        errorMessage = "Студент с указанным ID не найден.";
        return false;
    }
    if (!repo_.findLesson(lessonId)) {
        errorMessage = "Занятие с указанным ID не найдено.";
        return false;
    }
    repo_.markAttendance(studentId, lessonId, status);
    return true;
}

double AttendanceService::attendanceRateForStudent(int studentId) const {
    auto records = repo_.getAttendanceByStudent(studentId);
    if (records.empty()) return 0.0;

    int present = 0;
    for (const auto& r : records)
        if (r.status == Status::Present) present++;

    return 100.0 * static_cast<double>(present) / static_cast<double>(records.size());
}

bool AttendanceService::exportGroupReportCsv(const std::string& groupName, const std::string& filePath, std::string& errorMessage) const {
    auto students = repo_.getStudentsByGroup(groupName);
    if (students.empty()) {
        errorMessage = "Нет данных: в указанной группе не найдено студентов.";
        return false;
    }

    std::ofstream out(filePath);
    if (!out.is_open()) {
        errorMessage = "Не удалось создать файл отчёта.";
        return false;
    }

    out << "ID;FullName;Group;LessonID;Discipline;Date;Status\n";
    for (const auto& student : students) {
        auto records = repo_.getAttendanceByStudent(student.id);
        for (const auto& rec : records) {
            auto lesson = repo_.findLesson(rec.lessonId);
            if (!lesson) continue;
            out << student.id << ";" << student.fullName << ";" << student.groupName << ";"
                << lesson->id << ";" << lesson->discipline << ";" << lesson->date << ";"
                << statusToString(rec.status) << "\n";
        }
    }
    out.close();
    return true;
}
