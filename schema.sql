-- ============================================================
-- AttendTrack — схема базы данных (SQLite)
-- Лабораторная работа №3: проектирование и реализация БД
-- ============================================================

PRAGMA foreign_keys = ON;

-- ------------------------------------------------------------
-- Таблица: Groups (учебные группы)
-- ------------------------------------------------------------
CREATE TABLE IF NOT EXISTS Groups (
    id          INTEGER PRIMARY KEY AUTOINCREMENT,
    name        TEXT NOT NULL UNIQUE          -- например, 26-ИВТ-2-2
);

-- ------------------------------------------------------------
-- Таблица: Students (студенты)
-- Связь: Groups (1) -> Students (N)
-- ------------------------------------------------------------
CREATE TABLE IF NOT EXISTS Students (
    id              INTEGER PRIMARY KEY AUTOINCREMENT,
    last_name       TEXT NOT NULL,             -- Фамилия
    first_name      TEXT NOT NULL,             -- Имя
    middle_name     TEXT,                      -- Отчество (необязательно)
    group_id        INTEGER NOT NULL,
    login           TEXT NOT NULL UNIQUE,
    password_hash   TEXT NOT NULL,
    FOREIGN KEY (group_id) REFERENCES Groups(id)
);

-- ------------------------------------------------------------
-- Таблица: Lessons (занятия)
-- Связь: Groups (1) -> Lessons (N)
-- ------------------------------------------------------------
CREATE TABLE IF NOT EXISTS Lessons (
    id          INTEGER PRIMARY KEY AUTOINCREMENT,
    discipline  TEXT NOT NULL,
    group_id    INTEGER NOT NULL,
    lesson_date TEXT NOT NULL,                -- формат YYYY-MM-DD
    FOREIGN KEY (group_id) REFERENCES Groups(id)
);

-- ------------------------------------------------------------
-- Таблица: Attendance (посещаемость)
-- Связь: Students (M) <-> Lessons (N) — реализация M:N
-- через две связи 1:N (Students->Attendance, Lessons->Attendance)
-- ------------------------------------------------------------
CREATE TABLE IF NOT EXISTS Attendance (
    id          INTEGER PRIMARY KEY AUTOINCREMENT,
    student_id  INTEGER NOT NULL,
    lesson_id   INTEGER NOT NULL,
    status      TEXT NOT NULL CHECK (status IN ('present', 'absent', 'excused')),
    FOREIGN KEY (student_id) REFERENCES Students(id),
    FOREIGN KEY (lesson_id)  REFERENCES Lessons(id),
    UNIQUE (student_id, lesson_id)            -- одна отметка на студента за занятие
);

-- ============================================================
-- Тестовые данные
-- ============================================================

INSERT INTO Groups (name) VALUES
    ('26-ИВТ-2-2');

INSERT INTO Students (last_name, first_name, middle_name, group_id, login, password_hash) VALUES
    ('Иванов',  'Иван',  'Иванович',    1, 'ivanov_ii',  'a1b2c3d4e5'),
    ('Петрова', 'Анна',  'Сергеевна',   1, 'petrova_as', 'f6g7h8i9j0'),
    ('Сидоров', 'Пётр',  'Алексеевич',  1, 'sidorov_pa', 'k1l2m3n4o5');

INSERT INTO Lessons (discipline, group_id, lesson_date) VALUES
    ('Информатика', 1, '2026-09-10'),
    ('Информатика', 1, '2026-09-17');

INSERT INTO Attendance (student_id, lesson_id, status) VALUES
    (1, 1, 'present'),
    (2, 1, 'absent'),
    (3, 1, 'excused'),
    (1, 2, 'present'),
    (2, 2, 'present'),
    (3, 2, 'absent');
