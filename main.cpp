#include <iostream>
#include <limits>
#include "Repository.h"
#include "AttendanceService.h"

// ============================================================
// Presentation Layer (CLI)
// Отвечает только за ввод/вывод. Вся логика — в AttendanceService.
// ============================================================

static void printMenu() {
    std::cout << "\n===== AttendTrack — учёт посещаемости =====\n"
              << "1. Добавить студента\n"
              << "2. Добавить занятие\n"
              << "3. Отметить посещаемость\n"
              << "4. Показать посещаемость по занятию\n"
              << "5. Показать процент посещаемости студента\n"
              << "6. Сформировать отчёт по группе (CSV)\n"
              << "0. Выход\n"
              << "Выберите пункт: ";
}

static int readInt() {
    int value;
    while (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Введите число: ";
    }
    return value;
}

static std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, line);
    return line;
}

int main() {
    Repository repo;
    AttendanceService service(repo);

    // тестовые данные для проверки работы системы
    int s1 = repo.addStudent("Иванов Иван Иванович", "26-ИВТ-2-2");
    int s2 = repo.addStudent("Петрова Анна Сергеевна", "26-ИВТ-2-2");
    int l1 = repo.addLesson("Информатика", "26-ИВТ-2-2", "10.09.2026");
    std::string err;
    service.markAttendance(s1, l1, Status::Present, err);
    service.markAttendance(s2, l1, Status::Absent, err);

    bool running = true;
    while (running) {
        printMenu();
        int choice = readInt();

        switch (choice) {
            case 1: {
                std::string name = readLine("ФИО студента: ");
                std::string group = readLine("Группа: ");
                int id = repo.addStudent(name, group);
                std::cout << "Добавлен студент с ID = " << id << "\n";
                break;
            }
            case 2: {
                std::string discipline = readLine("Дисциплина: ");
                std::string group = readLine("Группа: ");
                std::string date = readLine("Дата (ДД.ММ.ГГГГ): ");
                int id = repo.addLesson(discipline, group, date);
                std::cout << "Добавлено занятие с ID = " << id << "\n";
                break;
            }
            case 3: {
                std::cout << "ID студента: ";
                int studentId = readInt();
                std::cout << "ID занятия: ";
                int lessonId = readInt();
                std::cout << "Статус (1-присутствует, 2-отсутствует, 3-уваж. причина): ";
                int statusChoice = readInt();
                Status status = statusChoice == 1 ? Status::Present
                               : statusChoice == 3 ? Status::ExcusedAbsence
                               : Status::Absent;
                std::string errorMessage;
                if (service.markAttendance(studentId, lessonId, status, errorMessage))
                    std::cout << "Посещаемость отмечена.\n";
                else
                    std::cout << "Ошибка: " << errorMessage << "\n";
                break;
            }
            case 4: {
                std::cout << "ID занятия: ";
                int lessonId = readInt();
                auto records = repo.getAttendanceByLesson(lessonId);
                if (records.empty()) {
                    std::cout << "Нет данных по этому занятию.\n";
                    break;
                }
                for (const auto& rec : records) {
                    auto student = repo.findStudent(rec.studentId);
                    std::cout << (student ? student->fullName : "???") << " — "
                              << statusToString(rec.status) << "\n";
                }
                break;
            }
            case 5: {
                std::cout << "ID студента: ";
                int studentId = readInt();
                double rate = service.attendanceRateForStudent(studentId);
                std::cout << "Посещаемость: " << rate << "%\n";
                break;
            }
            case 6: {
                std::string group = readLine("Группа: ");
                std::string path = "report_" + group + ".csv";
                std::string errorMessage;
                if (service.exportGroupReportCsv(group, path, errorMessage))
                    std::cout << "Отчёт сохранён в файл: " << path << "\n";
                else
                    std::cout << "Ошибка: " << errorMessage << "\n";
                break;
            }
            case 0:
                running = false;
                break;
            default:
                std::cout << "Неверный пункт меню.\n";
        }
    }

    std::cout << "Работа программы завершена.\n";
    return 0;
}
