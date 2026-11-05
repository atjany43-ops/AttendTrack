#pragma once

// ============================================================
// Data Layer — сущность "Посещаемость"
// Связывает Student и Lesson (таблица связи many-to-many)
// ============================================================
enum class Status {
    Present,        // присутствует
    Absent,         // отсутствует
    ExcusedAbsence  // отсутствует по уважительной причине
};

struct AttendanceRecord {
    int id;
    int studentId;
    int lessonId;
    Status status;

    AttendanceRecord(int id_, int studentId_, int lessonId_, Status status_)
        : id(id_), studentId(studentId_), lessonId(lessonId_), status(status_) {}
};

inline const char* statusToString(Status s) {
    switch (s) {
        case Status::Present:        return "Присутствует";
        case Status::Absent:         return "Отсутствует";
        case Status::ExcusedAbsence: return "Уважительная причина";
    }
    return "Неизвестно";
}
