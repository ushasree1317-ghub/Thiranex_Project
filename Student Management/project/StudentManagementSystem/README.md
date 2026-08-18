# Student Management System

## Description

A console-based Student Management System written in C++ that manages student records using binary file handling. The application provides a menu-driven interface to add, display, search, update, and delete student records. All data is stored permanently in a binary file (`students.dat`), so records persist across program restarts.

## Features

- **Add Student** — Create a new student record with unique ID validation
- **Display All Students** — View all records in a formatted table
- **Search Student** — Find a student by ID and display full details
- **Update Student** — Modify an existing student's information (ID remains unchanged)
- **Delete Student** — Remove a student record with confirmation prompt
- **File Persistence** — Records stored permanently in `students.dat` using binary file handling
- **Input Validation** — Validates ID, name, age, gender, course, phone, and marks
- **Duplicate ID Prevention** — Prevents adding students with existing IDs

## Technologies

- **C++** (C++11 or later)
- **File Handling** — `fstream`, `ifstream`, `ofstream` with binary mode
- **Console I/O** — `iostream`, `iomanip`

## Requirements

A C++ compiler is required to build the application.

### Installing a C++ Compiler

**Linux (Debian/Ubuntu):**
```bash
sudo apt update
sudo apt install build-essential
```

**Linux (Fedora/RHEL):**
```bash
sudo dnf install gcc-c++
```

**macOS:**
```bash
xcode-select --install
```

**Windows:**
- Install [MinGW](https://www.mingw-w64.org/) or [MSYS2](https://www.msys2.org/)
- Or install [Visual Studio](https://visualstudio.microsoft.com/) with C++ workload

## Compilation

```bash
g++ main.cpp -o student
```

## Run

**Linux/macOS:**
```bash
./student
```

**Windows (PowerShell):**
```powershell
.\student.exe
```

**Windows (Command Prompt):**
```cmd
student.exe
```

## Data Storage

Student records are stored in a binary file named `students.dat` in the same directory as the executable. The file is automatically created when the first student is added — no manual file creation is required.

Each record stores:
- Student ID (integer)
- Name (up to 49 characters)
- Age (1–100)
- Gender (Male/Female/Other)
- Course (up to 49 characters)
- Phone Number (10-digit)
- Marks (0.0–100.0)

## Project Structure

```
StudentManagementSystem/
├── main.cpp              # Complete source code
├── students.dat          # Binary data file (auto-created)
├── README.md             # This file
└── documentation/
    ├── Project_Report.md # Detailed project report
    ├── Algorithm.md      # Step-by-step algorithms
    ├── Test_Cases.md     # Test case table
    └── Flowchart.md      # Text-based flowchart
```

## Usage

1. Compile the program using the command above.
2. Run the executable.
3. Use the numbered menu to perform operations:
   - Press `1` to add a new student
   - Press `2` to display all students
   - Press `3` to search for a student by ID
   - Press `4` to update an existing student
   - Press `5` to delete a student
   - Press `6` to exit the application
