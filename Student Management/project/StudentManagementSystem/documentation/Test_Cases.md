# Test Cases — Student Management System

## Test Case Table

| #  | Test Case         | Input                              | Expected Result                              | Status |
|----|-------------------|------------------------------------|----------------------------------------------|--------|
| 1  | Add valid student | ID=101, Name=Usha, Age=20, Gender=Female, Course=CSE, Phone=9876543210, Marks=90 | "[SUCCESS] Student added successfully!" | Pass |
| 2  | Add second student | ID=102, Name=Ravi, Age=21, Gender=Male, Course=CSE, Phone=9876543211, Marks=85 | "[SUCCESS] Student added successfully!" | Pass |
| 3  | Duplicate ID      | ID=101 (already exists)            | "[ERROR] Student ID already exists."         | Pass   |
| 4  | Display all       | Menu choice 2                      | Both students displayed in table format      | Pass   |
| 5  | Search existing   | ID=101                             | "Student Found" with all details displayed   | Pass   |
| 6  | Search invalid    | ID=999 (non-existing)              | "Student with ID 999 not found."             | Pass   |
| 7  | Update existing   | ID=101, change Marks to 95         | "[SUCCESS] Student updated successfully!"    | Pass   |
| 8  | Update invalid    | ID=999 (non-existing)              | "Student not found."                         | Pass   |
| 9  | Delete existing   | ID=102, confirm with Y             | "[SUCCESS] Student deleted successfully!"    | Pass   |
| 10 | Delete cancelled  | ID=101, confirm with N             | "Delete operation cancelled."               | Pass   |
| 11 | Delete invalid    | ID=999 (non-existing)              | "Student not found."                         | Pass   |
| 12 | Invalid marks     | Marks=150                          | "[ERROR] Invalid marks. Please enter marks between 0 and 100:" | Pass |
| 13 | Invalid age       | Age=150                            | "[ERROR] Invalid age. Please enter age between 1 and 100:" | Pass |
| 14 | Invalid gender    | Gender=XYZ                         | "[ERROR] Invalid gender. Please enter Male, Female, or Other:" | Pass |
| 15 | Invalid phone     | Phone=abc123                       | "[ERROR] Invalid phone number. Please enter a 10-digit number:" | Pass |
| 16 | Invalid menu choice | Choice=9                         | "[ERROR] Invalid choice. Please enter a number between 1 and 6." | Pass |
| 17 | Non-numeric menu input | Choice="abc"                 | "[ERROR] Invalid choice. Please enter a number between 1 and 6." | Pass |
| 18 | Empty name        | Name="" (just Enter)               | "[ERROR] This field cannot be empty. Please try again." | Pass |
| 19 | Persistence test  | Close app, reopen, Display         | Records still present from previous session  | Pass   |
| 20 | Exit application  | Menu choice 6                      | "Thank you for using Student Management System." and program closes | Pass |

---

## Detailed Test Execution

### Test 1: Add Student (ID: 101)

**Input:**
```
1
101
Usha
20
Female
CSE
9876543210
90
```

**Expected Output:**
```
[SUCCESS] Student added successfully!
```

**Actual Result:** Passed — student added successfully.

---

### Test 2: Add Student (ID: 102)

**Input:**
```
1
102
Ravi
21
Male
CSE
9876543211
85
```

**Expected Output:**
```
[SUCCESS] Student added successfully!
```

**Actual Result:** Passed — student added successfully.

---

### Test 3: Display All Students

**Input:**
```
2
```

**Expected Output:**
```
==========================================================================
ID      Name                  Age   Gender      Course        Phone         Marks
==========================================================================
101     Usha                  20    Female      CSE           9876543210    90.00
102     Ravi                  21    Male        CSE           9876543211    85.00
==========================================================================
Total Students: 2
```

**Actual Result:** Passed — both students displayed correctly.

---

### Test 4: Search Student (ID: 101)

**Input:**
```
3
101
```

**Expected Output:**
```
Student Found
--------------------------
ID        : 101
Name      : Usha
Age       : 20
Gender    : Female
Course    : CSE
Phone     : 9876543210
Marks     : 90.00
--------------------------
```

**Actual Result:** Passed — student details displayed correctly.

---

### Test 5: Update Student (ID: 101, Marks → 95)

**Input:**
```
4
101
Usha
20
Female
CSE
9876543210
95
```

**Expected Output:**
```
[SUCCESS] Student updated successfully!
```

**Verification:** Search ID 101 again → Marks shows 95.00

**Actual Result:** Passed — marks updated from 90.00 to 95.00.

---

### Test 6: Delete Student (ID: 102)

**Input:**
```
5
102
Y
```

**Expected Output:**
```
Student found:
ID   : 102
Name : Ravi
[SUCCESS] Student deleted successfully!
```

**Verification:** Display all students → only student 101 remains.

**Actual Result:** Passed — student 102 deleted, only 101 remains.

---

### Test 7: Persistence Test

**Steps:**
1. Close the application (choice 6)
2. Run `./student` again
3. Select Display All Students (choice 2)

**Expected Output:**
```
101     Usha                  20    Female      CSE           9876543210    95.00
Total Students: 1
```

**Actual Result:** Passed — records persisted after restart.
