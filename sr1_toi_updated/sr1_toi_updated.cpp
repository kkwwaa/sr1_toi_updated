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
        cout << "������� ID ��������: ";
        cin >> id;
        cin.ignore();
        cout << "������� ���: ";
        getline(cin, name);
        cout << "������� ���� ����� (��.��.����): ";
        cin >> submissionDate;
        cout << "������� ���� �������� (��.��.����): ";
        cin >> reviewDate;
        cout << "������� ������ �� �����: ";
        cin >> gradeReport;
        cout << "������� ������ �� ������: ";
        cin >> gradeDefense;
        cin.ignore();
        cout << "������� ������� ������������: ";
        getline(cin, reviewer);
        cout << "������� ������� �����������: ";
        getline(cin, seminarist);
    }

    void print() {
        cout << "ID: " << id << ", ���: " << name
            << ", ���� �����: " << submissionDate
            << ", ���� ��������: " << reviewDate
            << ", ������ �� �����: " << gradeReport
            << ", ������ �� ������: " << gradeDefense
            << ", �����������: " << reviewer
            << ", ����������: " << seminarist << endl;
    }

    void edit() {
        string newName, newSubmissionDate, newReviewDate, newReviewer, newSeminarist;
        int newId, newGradeReport, newGradeDefense;

        cout << "������� ����� ID (��� -1, ����� ��������): ";
        cin >> newId;
        if (newId != -1) id = newId;

        cin.ignore();
        cout << "������� ����� ��� (��� enter, ����� ��������): ";
        getline(cin, newName);
        if (!newName.empty()) name = newName;

        cout << "������� ����� ���� ����� (��� enter, ����� ��������): ";
        getline(cin, newSubmissionDate);
        if (!newSubmissionDate.empty()) submissionDate = newSubmissionDate;

        cout << "������� ����� ���� �������� (��� enter, ����� ��������): ";
        getline(cin, newReviewDate);
        if (!newReviewDate.empty()) reviewDate = newReviewDate;

        cout << "������� ����� ������ �� ����� (��� -1, ����� ��������): ";
        cin >> newGradeReport;
        if (newGradeReport != -1) gradeReport = newGradeReport;

        cout << "������� ����� ������ �� ������ (��� -1, ����� ��������): ";
        cin >> newGradeDefense;
        if (newGradeDefense != -1) gradeDefense = newGradeDefense;

        cin.ignore();
        cout << "������� ����� ������� ������������ (��� enter, ����� ��������): ";
        getline(cin, newReviewer);
        if (!newReviewer.empty()) reviewer = newReviewer;

        cout << "������� ����� ������� ����������� (��� enter, ����� ��������): ";
        getline(cin, newSeminarist);
        if (!newSeminarist.empty()) seminarist = newSeminarist;
    }
};

Student students[MAX_STUDENTS] = {
    {3, "�������� ��������� ���������", "27.11.2024", "03.12.2024", 6, 9, "���������", "�����"},
    {5, "����� ����� ����������", "01.12.2024", "10.12.2024", 4, 6, "���������", "���������"},
    {9, "��������� ������ ��������", "01.12.2024", "10.12.2024", 6, 8, "�����", "���������"},
    {10, "������� ������ �������", "01.12.2024", "10.12.2024", 0, 0, "���������", "�����"},
    {1, "������ ������� ����������", "25.11.2024", "30.11.2024", 7, 9, "���������", "���������"},
    {8, "�������� ������� ����������", "25.11.2024", "05.12.2024", 8, 8, "�����", "���������"},
    {2, "������� ������� �������������", "25.11.2024", "30.11.2024", 5, 8, "���������", "�����"},
    {6, "������� ����� ������������", "25.11.2024", "01.12.2024", 8, 8, "�����", "���������"},
    {4, "������ ����� �������", "28.11.2024", "03.12.2024", 2, 9, "���������", "���������"},
    {7, "����� ���� ������������", "25.11.2024", "01.12.2024", 7, 7, "�����", "���������"}
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
            if (c >= '�' && c <= '�') c += 32;
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

// ���������� �������� �� �����
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

// ���������� ��������
void updateIndexes() {
    for (int i = 0; i < studentsNumber; i++) {
        indexID[i] = { students[i].id, i };
        indexName[i] = { students[i].name, i };
    }
    sortByID(indexID, studentsNumber);
    sortByName(indexName, studentsNumber);
}

// �������� ����� �� ID
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

// �������� ����� �� �����
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

// �������� �������
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
        cout << "������� ����:\n";
        cout << "1. �������� ���������\n";
        cout << "2. ������� ������ ���������\n";
        cout << "3. ������������� ������ ���������\n";
        cout << "4. ����� �������� �� ID\n5. ����� �������� �� ���\n6. �����\n������� �������: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            printStudents();
            break;
        case 3:
            cout << "\n���������� �� ID:\n";
            printStudentsSort(true);
            cout << "\n���������� �� ���:\n";
            printStudentsSort(false);
            break;
        case 4:
            cout << "������� ID: ";
            cin >> id;
            key = searchById(id);
            if (key != -1) {
                students[key].print();
                cout << "1. ������������� ������\n2. ������� ������\n3. �����\n������� �������: ";
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
                cout << "������� �� ������\n";
            }
            break;
        case 5:
            cout << "������� ���: ";
            cin.ignore();
            getline(cin, name);
            key = searchByName(name);
            if (key != -1) {
                students[key].print();
                cout << "1. ������������� ������\n2. ������� ������\n3. �����\n������� �������: ";
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
                cout << "������� �� ������\n";
            }
            break;
        case 6:
            exit = true;
            break;
        default:
            cout << "������������ ����. ���������� ���)\n";
            break;
        }
    }
}