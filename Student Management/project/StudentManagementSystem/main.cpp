// =====================================================================
//  Student Management System
//  A console-based application using C++ and binary file handling.
//  Supports: Add, Display, Search, Update, Delete students.
//  Compile:  g++ main.cpp -o student
//  Run:      ./student   (Linux/macOS)   .\student.exe   (Windows)
// =====================================================================

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <limits>
#include <cstdlib>
using namespace std;

const char* DATA_FILE = "students.dat";
const char* TEMP_FILE = "temp.dat";

struct Student {
    int   id;
    char  name[50];
    int   age;
    char  gender[10];
    char  course[50];
    char  phone[20];
    float marks;
};

void   addStudent();
void   displayStudents();
void   searchStudent();
void   updateStudent();
void   deleteStudent();
bool   studentExists(int id);
Student* getStudentById(int id);
bool   validateName(const char* name);
bool   validateAge(int age);
bool   validateGender(const char* gender);
bool   validateCourse(const char* course);
bool   validatePhone(const char* phone);
bool   validateMarks(float marks);
void   printHeader();
void   printTableHeader();
void   printStudentRow(const Student& s);
void   pauseScreen();
int    readInt(const char* prompt);
float  readFloat(const char* prompt);
string readString(const char* prompt, int maxLen);
void   clearInputBuffer();

int main() {
    int choice;

    do {
        printHeader();
        cout << "           STUDENT MANAGEMENT SYSTEM" << endl;
        cout << "==================================================" << endl;
        cout << endl;
        cout << "  1. Add Student" << endl;
        cout << "  2. Display All Students" << endl;
        cout << "  3. Search Student" << endl;
        cout << "  4. Update Student" << endl;
        cout << "  5. Delete Student" << endl;
        cout << "  6. Exit" << endl;
        cout << endl;
        cout << "==================================================" << endl;
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            clearInputBuffer();
            cout << "\n[ERROR] Invalid choice. Please enter a number between 1 and 6." << endl;
            pauseScreen();
            continue;
        }
        clearInputBuffer();  
        cout << endl;
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                cout << "==================================================" << endl;
                cout << "  Thank you for using Student Management System." << endl;
                cout << "  Goodbye!" << endl;
                cout << "==================================================" << endl;
                break;
            default:
                cout << "[ERROR] Invalid choice. Please enter a number between 1 and 6." << endl;
                break;
        }
        if (choice != 6) {
            pauseScreen();
        }
    } while (choice != 6);
    return 0;
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int readInt(const char* prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value > 0) {
            clearInputBuffer();
            return value;
        }
        clearInputBuffer();
        cout << "[ERROR] Please enter a valid positive integer." << endl;
    }
}

float readFloat(const char* prompt) {
    float value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            clearInputBuffer();
            return value;
        }
        clearInputBuffer();
        cout << "[ERROR] Please enter a valid number." << endl;
    }
}

string readString(const char* prompt, int maxLen) {
    char* buffer = new char[maxLen + 1];
    while (true) {
        cout << prompt;
        cin.getline(buffer, maxLen + 1);
        if (cin.fail()) {
            clearInputBuffer();
            cout << "[ERROR] Input too long. Maximum " << maxLen << " characters allowed." << endl;
            continue;
        }
        bool empty = true;
        for (int i = 0; buffer[i] != '\0'; i++) {
            if (!isspace(buffer[i])) { empty = false; break; }
        }
        if (empty) {
            cout << "[ERROR] This field cannot be empty. Please try again." << endl;
            continue;
        }
        string result(buffer);
        delete[] buffer;
        return result;
    }
}
void printHeader() {
    cout << endl;
    cout << "==================================================" << endl;
}

void printTableHeader() {
    cout << "==========================================================================" << endl;
    cout << left << setw(8) << "ID"
         << setw(22) << "Name"
         << setw(6)  << "Age"
         << setw(12) << "Gender"
         << setw(14) << "Course"
         << setw(14) << "Phone"
         << "Marks" << endl;
    cout << "==========================================================================" << endl;
}

void printStudentRow(const Student& s) {
    cout << left << setw(8)  << s.id
         << setw(22) << s.name
         << setw(6)  << s.age
         << setw(12) << s.gender
         << setw(14) << s.course
         << setw(14) << s.phone
         << fixed << setprecision(2) << s.marks << endl;
}

void pauseScreen() {
    cout << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Press Enter to continue...";
    cin.get();  
}

bool validateName(const char* name) {
    if (name[0] == '\0') return false;
    // Must contain at least one non-space character.
    for (int i = 0; name[i] != '\0'; i++) {
        if (!isspace(name[i])) return true;
    }
    return false;
}

bool validateAge(int age) {
    return age >= 1 && age <= 100;
}

bool validateGender(const char* gender) {
    string g(gender);
    for (size_t i = 0; i < g.size(); i++) {
        g[i] = tolower(g[i]);
    }
    return (g == "male" || g == "female" || g == "other");
}
bool validateCourse(const char* course) {
    if (course[0] == '\0') return false;
    for (int i = 0; course[i] != '\0'; i++) {
        if (!isspace(course[i])) return true;
    }
    return false;
}
bool validatePhone(const char* phone) {
    int len = strlen(phone);
    if (len != 10) return false;
    for (int i = 0; i < len; i++) {
        if (!isdigit(phone[i])) return false;
    }
    return true;
}
bool validateMarks(float marks) {
    return marks >= 0.0f && marks <= 100.0f;
}
bool studentExists(int id) {
    ifstream file(DATA_FILE, ios::binary);
    if (!file) return false;  
    Student s;
    while (file.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        if (s.id == id) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}
Student* getStudentById(int id) {
    ifstream file(DATA_FILE, ios::binary);
    if (!file) return NULL;
    Student* s = new Student;
    while (file.read(reinterpret_cast<char*>(s), sizeof(Student))) {
        if (s->id == id) {
            file.close();
            return s;
        }
    }
    file.close();
    delete s;
    return NULL;
}
void addStudent() {
    printHeader();
    cout << "                 ADD NEW STUDENT" << endl;
    cout << "==================================================" << endl;
    Student s;
    s.id = readInt("Enter Student ID: ");
    if (studentExists(s.id)) {
        cout << "\n[ERROR] Student ID already exists." << endl;
        cout << "Please enter a different ID." << endl;
        return;
    }
    string nameStr = readString("Enter Name: ", 49);
    strncpy(s.name, nameStr.c_str(), 49);
    s.name[49] = '\0';
    s.age = readInt("Enter Age: ");
    while (!validateAge(s.age)) {
        cout << "[ERROR] Invalid age. Please enter age between 1 and 100: ";
        if (cin >> s.age) { clearInputBuffer(); }
        else { clearInputBuffer(); s.age = -1; }
    }
    string genderStr = readString("Enter Gender (Male/Female/Other): ", 9);
    while (!validateGender(genderStr.c_str())) {
        cout << "[ERROR] Invalid gender. Please enter Male, Female, or Other: ";
        genderStr = readString("", 9);
    }
    strncpy(s.gender, genderStr.c_str(), 9);
    s.gender[9] = '\0';
    string courseStr = readString("Enter Course: ", 49);
    strncpy(s.course, courseStr.c_str(), 49);
    s.course[49] = '\0';
    string phoneStr = readString("Enter Phone Number (10 digits): ", 19);
    while (!validatePhone(phoneStr.c_str())) {
        cout << "[ERROR] Invalid phone number. Please enter a 10-digit number: ";
        phoneStr = readString("", 19);
    }
    strncpy(s.phone, phoneStr.c_str(), 19);
    s.phone[19] = '\0';
    s.marks = readFloat("Enter Marks (0-100): ");
    while (!validateMarks(s.marks)) {
        cout << "[ERROR] Invalid marks. Please enter marks between 0 and 100: ";
        if (cin >> s.marks) { clearInputBuffer(); }
        else { clearInputBuffer(); s.marks = -1; }
    }
    ofstream file(DATA_FILE, ios::binary | ios::app);
    if (!file) {
        cout << "\n[ERROR] Unable to open data file for writing." << endl;
        return;
    }
    file.write(reinterpret_cast<char*>(&s), sizeof(Student));
    file.close();

    cout << "\n[SUCCESS] Student added successfully!" << endl;
}
void displayStudents() {
    printHeader();
    cout << "               ALL STUDENT RECORDS" << endl;
    cout << "==================================================" << endl;
    ifstream file(DATA_FILE, ios::binary);
    if (!file) {
        cout << "\nNo student records found." << endl;
        return;
    }
    Student s;
    int count = 0;
    printTableHeader();
    while (file.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        printStudentRow(s);
        count++;
    }
    cout << "==========================================================================" << endl;
    file.close();
    if (count == 0) {
        cout << "No student records found." << endl;
    } else {
        cout << "Total Students: " << count << endl;
    }
}
void searchStudent() {
    printHeader();
    cout << "                  SEARCH STUDENT" << endl;
    cout << "==================================================" << endl;
    int id = readInt("Enter Student ID to search: ");
    ifstream file(DATA_FILE, ios::binary);
    if (!file) {
        cout << "\nNo student records found." << endl;
        cout << "Student with ID " << id << " not found." << endl;
        return;
    }
    Student s;
    bool found = false;
    while (file.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        if (s.id == id) {
            found = true;
            break;
        }
    }
    file.close();
    if (found) {
        cout << "\nStudent Found" << endl;
        cout << "--------------------------" << endl;
        cout << left << setw(10) << "ID"     << ": " << s.id     << endl;
        cout << left << setw(10) << "Name"   << ": " << s.name   << endl;
        cout << left << setw(10) << "Age"    << ": " << s.age    << endl;
        cout << left << setw(10) << "Gender" << ": " << s.gender << endl;
        cout << left << setw(10) << "Course" << ": " << s.course << endl;
        cout << left << setw(10) << "Phone"  << ": " << s.phone  << endl;
        cout << left << setw(10) << "Marks"  << ": " << fixed << setprecision(2) << s.marks << endl;
        cout << "--------------------------" << endl;
    } else {
        cout << "\nStudent with ID " << id << " not found." << endl;
    }
}
void updateStudent() {
    printHeader();
    cout << "                  UPDATE STUDENT" << endl;
    cout << "==================================================" << endl;
    int id = readInt("Enter Student ID to update: ");
    fstream file(DATA_FILE, ios::binary | ios::in | ios::out);
    if (!file) {
        cout << "\n[ERROR] Unable to open data file." << endl;
        cout << "Student not found." << endl;
        return;
    }
    Student s;
    bool found = false;
    streampos pos;
    while (file.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        if (s.id == id) {
            found = true;
            pos = file.tellg();
            cout << "\nCurrent Information:" << endl;
            cout << "--------------------------" << endl;
            cout << left << setw(10) << "ID"     << ": " << s.id     << endl;
            cout << left << setw(10) << "Name"   << ": " << s.name   << endl;
            cout << left << setw(10) << "Age"    << ": " << s.age    << endl;
            cout << left << setw(10) << "Gender" << ": " << s.gender << endl;
            cout << left << setw(10) << "Course" << ": " << s.course << endl;
            cout << left << setw(10) << "Phone"  << ": " << s.phone  << endl;
            cout << left << setw(10) << "Marks"  << ": " << fixed << setprecision(2) << s.marks << endl;
            cout << "--------------------------" << endl;
            break;
        }
    }
    if (!found) {
        file.close();
        cout << "\nStudent not found." << endl;
        return;
    }
    cout << "\nEnter new information (ID will remain " << id << "):" << endl;
    s.id = id;
    string nameStr = readString("Enter Name: ", 49);
    strncpy(s.name, nameStr.c_str(), 49);
    s.name[49] = '\0';
    s.age = readInt("Enter Age: ");
    while (!validateAge(s.age)) {
        cout << "[ERROR] Invalid age. Please enter age between 1 and 100: ";
        if (cin >> s.age) { clearInputBuffer(); }
        else { clearInputBuffer(); s.age = -1; }
    }
    string genderStr = readString("Enter Gender (Male/Female/Other): ", 9);
    while (!validateGender(genderStr.c_str())) {
        cout << "[ERROR] Invalid gender. Please enter Male, Female, or Other: ";
        genderStr = readString("", 9);
    }
    strncpy(s.gender, genderStr.c_str(), 9);
    s.gender[9] = '\0';
    string courseStr = readString("Enter Course: ", 49);
    strncpy(s.course, courseStr.c_str(), 49);
    s.course[49] = '\0';
    string phoneStr = readString("Enter Phone Number (10 digits): ", 19);
    while (!validatePhone(phoneStr.c_str())) {
        cout << "[ERROR] Invalid phone number. Please enter a 10-digit number: ";
        phoneStr = readString("", 19);
    }
    strncpy(s.phone, phoneStr.c_str(), 19);
    s.phone[19] = '\0';
    s.marks = readFloat("Enter Marks (0-100): ");
    while (!validateMarks(s.marks)) {
        cout << "[ERROR] Invalid marks. Please enter marks between 0 and 100: ";
        if (cin >> s.marks) { clearInputBuffer(); }
        else { clearInputBuffer(); s.marks = -1; }
    }
    file.clear();
    file.seekp(pos - static_cast<streampos>(sizeof(Student)), ios::beg);
    file.write(reinterpret_cast<char*>(&s), sizeof(Student));
    file.close();
    cout << "\n[SUCCESS] Student updated successfully!" << endl;
}
void deleteStudent() {
    printHeader();
    cout << "                  DELETE STUDENT" << endl;
    cout << "==================================================" << endl;
    int id = readInt("Enter Student ID to delete: ");
    ifstream file(DATA_FILE, ios::binary);
    if (!file) {
        cout << "\n[ERROR] Unable to open data file." << endl;
        cout << "Student not found." << endl;
        return;
    }
    Student s;
    bool found = false;
    while (file.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        if (s.id == id) {
            found = true;
            break;
        }
    }
    if (!found) {
        file.close();
        cout << "\nStudent not found." << endl;
        return;
    }
    cout << "\nStudent found:" << endl;
    cout << "ID   : " << s.id << endl;
    cout << "Name : " << s.name << endl;
    cout << "\nAre you sure you want to delete this student? (Y/N): ";
    char confirm;
    cin >> confirm;
    clearInputBuffer();
    if (confirm != 'Y' && confirm != 'y') {
        file.close();
        cout << "\nDelete operation cancelled. Student record remains." << endl;
        return;
    }
    file.seekg(0, ios::beg);
    ofstream temp(TEMP_FILE, ios::binary);
    if (!temp) {
        file.close();
        cout << "\n[ERROR] Unable to create temporary file." << endl;
        return;
    }
    while (file.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        if (s.id != id) {
            temp.write(reinterpret_cast<char*>(&s), sizeof(Student));
        }
    }
    file.close();
    temp.close();
    if (remove(DATA_FILE) != 0) {
        cout << "\n[ERROR] Unable to delete original data file." << endl;
        remove(TEMP_FILE);
        return;
    }
    if (rename(TEMP_FILE, DATA_FILE) != 0) {
        cout << "\n[ERROR] Unable to rename temporary file." << endl;
        return;
    }
    cout << "\n[SUCCESS] Student deleted successfully!" << endl;
}