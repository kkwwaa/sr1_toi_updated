#include <iostream>
#include <string>
#include <Windows.h>
#include <algorithm>

using namespace std;

const int MAX_STUDENTS = 100;
int studentsNumber = 10;

struct Student {
    int id;
    string name;
    string submissionDate;
    string reviewDate;
    int gradeReport;
    int gradeDefense;
    string reviewer;
    string seminarist;

    void input() {
        cout << "Введите ID студента: ";
        cin >> id;
        cin.ignore();
        cout << "Введите ФИО: ";
        getline(cin, name);
        cout << "Введите дату сдачи (ДД.ММ.ГГГГ): ";
        cin >> submissionDate;
        cout << "Введите дату проверки (ДД.ММ.ГГГГ): ";
        cin >> reviewDate;
        cout << "Введите оценку за отчет: ";
        cin >> gradeReport;
        cout << "Введите оценку за защиту: ";
        cin >> gradeDefense;
        cin.ignore();
        cout << "Введите фамилию проверяющего: ";
        getline(cin, reviewer);
        cout << "Введите фамилию семинариста: ";
        getline(cin, seminarist);
    }

    void print() {
        cout << "ID: " << id << ", ФИО: " << name
            << ", Дата сдачи: " << submissionDate
            << ", Дата проверки: " << reviewDate
            << ", Оценка за отчет: " << gradeReport
            << ", Оценка за защиту: " << gradeDefense
            << ", Проверяющий: " << reviewer
            << ", Семинарист: " << seminarist << endl;
    }

    void edit() {
        string newName, newSubmissionDate, newReviewDate, newReviewer, newSeminarist;
        int newId, newGradeReport, newGradeDefense;

        cout << "Введите новый ID (или -1, чтобы оставить): ";
        cin >> newId;
        if (newId != -1) id = newId;

        cin.ignore();
        cout << "Введите новое ФИО (или enter, чтобы оставить): ";
        getline(cin, newName);
        if (!newName.empty()) name = newName;

        cout << "Введите новую дату сдачи (или enter, чтобы оставить): ";
        getline(cin, newSubmissionDate);
        if (!newSubmissionDate.empty()) submissionDate = newSubmissionDate;

        cout << "Введите новую дату проверки (или enter, чтобы оставить): ";
        getline(cin, newReviewDate);
        if (!newReviewDate.empty()) reviewDate = newReviewDate;

        cout << "Введите новую оценку за отчет (или -1, чтобы оставить): ";
        cin >> newGradeReport;
        if (newGradeReport != -1) gradeReport = newGradeReport;

        cout << "Введите новую оценку за защиту (или -1, чтобы оставить): ";
        cin >> newGradeDefense;
        if (newGradeDefense != -1) gradeDefense = newGradeDefense;

        cin.ignore();
        cout << "Введите новую фамилию проверяющего (или enter, чтобы оставить): ";
        getline(cin, newReviewer);
        if (!newReviewer.empty()) reviewer = newReviewer;

        cout << "Введите новую фамилию семинариста (или enter, чтобы оставить): ";
        getline(cin, newSeminarist);
        if (!newSeminarist.empty()) seminarist = newSeminarist;
    }
};

Student students[MAX_STUDENTS] = {
    {3, "Борисова Екатерина Андреевна", "27.11.2024", "03.12.2024", 6, 9, "Долныкова", "Будин"},
    {5, "Дуров Павел Валерьевич", "01.12.2024", "10.12.2024", 4, 6, "Долныкова", "Цидвинцев"},
    {9, "Косвинцев Богдан Павлович", "01.12.2024", "10.12.2024", 6, 8, "Осока", "Цидвинцев"},
    {10, "Никитин Никита Никитич", "01.12.2024", "10.12.2024", 0, 0, "Долныкова", "Будин"},
    {1, "Петров Арсений Николаевич", "25.11.2024", "30.11.2024", 7, 9, "Долныкова", "Цидвинцев"},
    {8, "Понькина Татьяна Евгеньевна", "25.11.2024", "05.12.2024", 8, 8, "Осока", "Цидвинцев"},
    {2, "Семенов Евгений Александрович", "25.11.2024", "30.11.2024", 5, 8, "Долныкова", "Будин"},
    {6, "Симонов Антон Владимирович", "25.11.2024", "01.12.2024", 8, 8, "Осока", "Цидвинцев"},
    {4, "Юрьева София Юрьевна", "28.11.2024", "03.12.2024", 2, 9, "Долныкова", "Цидвинцев"},
    {7, "Янина Анна Владимировна", "25.11.2024", "01.12.2024", 7, 7, "Осока", "Цидвинцев"}
};

struct IndexEntryId {
    int id;
    int recNum;
};

struct IndexArrayName {
    string name;
    int recNum;
};

IndexEntryId indexID[MAX_STUDENTS];
IndexArrayName indexName[MAX_STUDENTS];

string normalize(const string& str) {
    string result;
    for (char c : str) {
        if (c != ' ') {
            if (c >= 'А' && c <= 'Я') c += 32;
            result += c;
        }
    }
    return result;
}

void sortByID(IndexEntryId* arr, int size) {
    for (int i = 1; i < size; i++) {
        IndexEntryId key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].id > key.id) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Сортировка индексов по имени
void sortByName(IndexArrayName* arr, int size) {
    for (int i = 1; i < size; i++) {
        IndexArrayName key = arr[i];
        int j = i - 1;
        while (j >= 0 && normalize(arr[j].name) < normalize(key.name)) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Обновление индексов
void updateIndexes() {
    for (int i = 0; i < studentsNumber; i++) {
        indexID[i] = { students[i].id, i };
        indexName[i] = { students[i].name, i };
    }
    sortByID(indexID, studentsNumber);
    sortByName(indexName, studentsNumber);
}

// Бинарный поиск по ID
int searchById(int target) {
    int left = 0, right = studentsNumber - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (indexID[mid].id == target) return indexID[mid].recNum;
        if (indexID[mid].id < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// Бинарный поиск по имени
int searchByName(const string& target) {
    string normTarget = normalize(target);
    int left = 0, right = studentsNumber - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        string current = normalize(indexName[mid].name);
        if (current == normTarget) return indexName[mid].recNum;
        if (current > normTarget) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// Основные функции
void printStudentsSort(bool byId = true) {
    if (byId) {
        for (int i = 0; i < studentsNumber; i++)
            students[indexID[i].recNum].print();
    }
    else {
        for (int i = 0; i < studentsNumber; i++)
            students[indexName[i].recNum].print();
    }
}

void printStudents() {
    for (int i = 0; i < studentsNumber; i++) {
        students[i].print();
    }
}

void addStudent() {
    students[studentsNumber].input();
    studentsNumber++;
    updateIndexes();
}

void deleteStudent(int index) {
    for (int i = index; i < studentsNumber - 1; i++) {
        students[i] = students[i + 1];
    }
    studentsNumber--;
    updateIndexes();
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    updateIndexes();

    int choice, subchoice, id, key;
    bool exit = false;
    string name;

    while (!exit) {
        cout << "Главное меню:\n";
        cout << "1. Добавить студентов\n";
        cout << "2. Вывести список студентов\n";
        cout << "3. Отсортировать список студентов\n";
        cout << "4. Поиск студента по ID\n5. Поиск студента по ФИО\n6. Выход\nВведите команду: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            printStudents();
            break;
        case 3:
            cout << "\nСортировка по ID:\n";
            printStudentsSort(true);
            cout << "\nСортировка по ФИО:\n";
            printStudentsSort(false);
            break;
        case 4:
            cout << "Введите ID: ";
            cin >> id;
            key = searchById(id);
            if (key != -1) {
                students[key].print();
                cout << "1. Редактировать запись\n2. Удалить запись\n3. Назад\nВведите команду: ";
                cin >> subchoice;
                if (subchoice == 1) {
                    students[key].edit();
                    updateIndexes();
                }
                else if (subchoice == 2) {
                    deleteStudent(key);
                }
            }
            else {
                cout << "Студент не найден\n";
            }
            break;
        case 5:
            cout << "Введите ФИО: ";
            cin.ignore();
            getline(cin, name);
            key = searchByName(name);
            if (key != -1) {
                students[key].print();
                cout << "1. Редактировать запись\n2. Удалить запись\n3. Назад\nВведите команду: ";
                cin >> subchoice;
                if (subchoice == 1) {
                    students[key].edit();
                    updateIndexes();
                }
                else if (subchoice == 2) {
                    deleteStudent(key);
                }
            }
            else {
                cout << "Студент не найден\n";
            }
            break;
        case 6:
            exit = true;
            break;
        default:
            cout << "Неправильный ввод. Попробуйте еще)\n";
            break;
        }
    }
}