#pragma once
#include <vector>
#include <optional>
#include "Student.h"
#include "Lesson.h"
#include "AttendanceRecord.h"

// ============================================================
// Data Access Layer (Repository)
// Изолирует бизнес-логику от способа физического хранения данных.
// На текущем этапе — хранение в памяти (векторы).
// В дальнейшем реализация может быть заменена на файловую БД
// или SQL без изменения кода бизнес-логики.
// ============================================================
class Repository {
public:
    // --- Students ---
    int addStudent(const std::string& fullName, const std::string& groupName);
    const std::vector<Student>& getStudents() const { return students_; }
    std::vector<Student> getStudentsByGroup(const std::string& groupName) const;
    std::optional<Student> findStudent(int id) const;

    // --- Lessons ---
    int addLesson(const std::string& discipline, const std::string& groupName, const std::string& date);
    const std::vector<Lesson>& getLessons() const { return lessons_; }
    std::optional<Lesson> findLesson(int id) const;

    // --- Attendance ---
    void markAttendance(int studentId, int lessonId, Status status);
    std::vector<AttendanceRecord> getAttendanceByLesson(int lessonId) const;
    std::vector<AttendanceRecord> getAttendanceByStudent(int studentId) const;

private:
    std::vector<Student> students_;
    std::vector<Lesson> lessons_;
    std::vector<AttendanceRecord> attendance_;

    int nextStudentId_ = 1;
    int nextLessonId_ = 1;
    int nextAttendanceId_ = 1;
};
