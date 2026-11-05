#include "Repository.h"
#include <algorithm>

int Repository::addStudent(const std::string& fullName, const std::string& groupName) {
    int id = nextStudentId_++;
    students_.emplace_back(id, fullName, groupName);
    return id;
}

std::vector<Student> Repository::getStudentsByGroup(const std::string& groupName) const {
    std::vector<Student> result;
    for (const auto& s : students_)
        if (s.groupName == groupName) result.push_back(s);
    return result;
}

std::optional<Student> Repository::findStudent(int id) const {
    for (const auto& s : students_)
        if (s.id == id) return s;
    return std::nullopt;
}

int Repository::addLesson(const std::string& discipline, const std::string& groupName, const std::string& date) {
    int id = nextLessonId_++;
    lessons_.emplace_back(id, discipline, groupName, date);
    return id;
}

std::optional<Lesson> Repository::findLesson(int id) const {
    for (const auto& l : lessons_)
        if (l.id == id) return l;
    return std::nullopt;
}

void Repository::markAttendance(int studentId, int lessonId, Status status) {
    // если отметка уже есть — обновляем, иначе создаём новую
    for (auto& rec : attendance_) {
        if (rec.studentId == studentId && rec.lessonId == lessonId) {
            rec.status = status;
            return;
        }
    }
    attendance_.emplace_back(nextAttendanceId_++, studentId, lessonId, status);
}

std::vector<AttendanceRecord> Repository::getAttendanceByLesson(int lessonId) const {
    std::vector<AttendanceRecord> result;
    for (const auto& rec : attendance_)
        if (rec.lessonId == lessonId) result.push_back(rec);
    return result;
}

std::vector<AttendanceRecord> Repository::getAttendanceByStudent(int studentId) const {
    std::vector<AttendanceRecord> result;
    for (const auto& rec : attendance_)
        if (rec.studentId == studentId) result.push_back(rec);
    return result;
}
