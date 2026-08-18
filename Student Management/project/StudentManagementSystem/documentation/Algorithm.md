# Algorithms — Student Management System

## Main Menu Algorithm

```
START
  ↓
Initialize choice variable
  ↓
REPEAT (do-while loop)
  ↓
Display main menu with 6 options
  ↓
Read user choice
  ↓
IF choice is not a valid integer THEN
  ↓
  Display error message
  ↓
  Continue to next iteration
  ↓
END IF
  ↓
SWITCH (choice)
  ↓
  CASE 1: Call addStudent()
  CASE 2: Call displayStudents()
  CASE 3: Call searchStudent()
  CASE 4: Call updateStudent()
  CASE 5: Call deleteStudent()
  CASE 6: Display goodbye message, exit loop
  DEFAULT: Display invalid choice error
  ↓
END SWITCH
  ↓
IF choice != 6 THEN
  ↓
  Pause screen, wait for Enter
  ↓
END IF
  ↓
WHILE (choice != 6)
  ↓
END
```

---

## Add Student Algorithm

```
START
  ↓
Display "ADD NEW STUDENT" header
  ↓
Read Student ID
  ↓
IF ID is not a positive integer THEN
  ↓
  Display error, re-prompt
  ↓
  Go back to read ID
  ↓
END IF
  ↓
Call studentExists(ID)
  ↓
IF ID already exists THEN
  ↓
  Display "[ERROR] Student ID already exists."
  ↓
  Return to menu
  ↓
END IF
  ↓
Read Name (non-empty, spaces allowed)
  ↓
Read Age
  ↓
IF Age < 1 OR Age > 100 THEN
  ↓
  Display error, re-prompt
  ↓
END IF
  ↓
Read Gender
  ↓
IF Gender is not Male/Female/Other THEN
  ↓
  Display error, re-prompt
  ↓
END IF
  ↓
Read Course (non-empty)
  ↓
Read Phone Number
  ↓
IF Phone is not exactly 10 digits THEN
  ↓
  Display error, re-prompt
  ↓
END IF
  ↓
Read Marks
  ↓
IF Marks < 0 OR Marks > 100 THEN
  ↓
  Display error, re-prompt
  ↓
END IF
  ↓
Open students.dat in binary append mode
  ↓
IF file fails to open THEN
  ↓
  Display error
  ↓
  Return to menu
  ↓
END IF
  ↓
Write Student record to file
  ↓
Close file
  ↓
Display "[SUCCESS] Student added successfully!"
  ↓
END
```

---

## Display All Students Algorithm

```
START
  ↓
Display "ALL STUDENT RECORDS" header
  ↓
Open students.dat in binary read mode
  ↓
IF file fails to open THEN
  ↓
  Display "No student records found."
  ↓
  Return to menu
  ↓
END IF
  ↓
Initialize count = 0
  ↓
Print table header
  ↓
WHILE (read Student record from file succeeds)
  ↓
  Print student record as table row
  ↓
  Increment count
  ↓
END WHILE
  ↓
Print table footer
  ↓
Close file
  ↓
IF count == 0 THEN
  ↓
  Display "No student records found."
  ↓
ELSE
  ↓
  Display "Total Students: count"
  ↓
END IF
  ↓
END
```

---

## Search Student Algorithm

```
START
  ↓
Display "SEARCH STUDENT" header
  ↓
Read Student ID to search
  ↓
Open students.dat in binary read mode
  ↓
IF file fails to open THEN
  ↓
  Display "Student with ID not found."
  ↓
  Return to menu
  ↓
END IF
  ↓
Initialize found = false
  ↓
WHILE (read Student record from file succeeds)
  ↓
  IF record.id == search ID THEN
    ↓
    Set found = true
    ↓
    Break out of loop
    ↓
  END IF
  ↓
END WHILE
  ↓
Close file
  ↓
IF found THEN
  ↓
  Display "Student Found"
  ↓
  Display all student details (ID, Name, Age, Gender, Course, Phone, Marks)
  ↓
ELSE
  ↓
  Display "Student with ID not found."
  ↓
END IF
  ↓
END
```

---

## Update Student Algorithm

```
START
  ↓
Display "UPDATE STUDENT" header
  ↓
Read Student ID to update
  ↓
Open students.dat in binary read+write mode
  ↓
IF file fails to open THEN
  ↓
  Display "Student not found."
  ↓
  Return to menu
  ↓
END IF
  ↓
Initialize found = false
  ↓
WHILE (read Student record from file succeeds)
  ↓
  IF record.id == update ID THEN
    ↓
    Set found = true
    ↓
    Save record file position
    ↓
    Display current student information
    ↓
    Break out of loop
    ↓
  END IF
  ↓
END WHILE
  ↓
IF NOT found THEN
  ↓
  Close file
  ↓
  Display "Student not found."
  ↓
  Return to menu
  ↓
END IF
  ↓
Read new Name, Age, Gender, Course, Phone, Marks
  ↓
(Validate each field with re-prompt on invalid input)
  ↓
Keep ID unchanged
  ↓
Seek put pointer to start of this record
  ↓
Write updated record (overwrite in place)
  ↓
Close file
  ↓
Display "[SUCCESS] Student updated successfully!"
  ↓
END
```

---

## Delete Student Algorithm

```
START
  ↓
Display "DELETE STUDENT" header
  ↓
Read Student ID to delete
  ↓
Open students.dat in binary read mode
  ↓
IF file fails to open THEN
  ↓
  Display "Student not found."
  ↓
  Return to menu
  ↓
END IF
  ↓
Initialize found = false
  ↓
WHILE (read Student record from file succeeds)
  ↓
  IF record.id == delete ID THEN
    ↓
    Set found = true
    ↓
    Break out of loop
    ↓
  END IF
  ↓
END WHILE
  ↓
IF NOT found THEN
  ↓
  Close file
  ↓
  Display "Student not found."
  ↓
  Return to menu
  ↓
END IF
  ↓
Display student ID and Name
  ↓
Ask "Are you sure you want to delete? (Y/N)"
  ↓
Read confirmation character
  ↓
IF confirmation is NOT 'Y' or 'y' THEN
  ↓
  Close file
  ↓
  Display "Delete operation cancelled."
  ↓
  Return to menu
  ↓
END IF
  ↓
Reset file pointer to beginning
  ↓
Open temp.dat in binary write mode
  ↓
WHILE (read Student record from original file succeeds)
  ↓
  IF record.id != delete ID THEN
    ↓
    Write record to temp.dat
    ↓
  END IF
  ↓
END WHILE
  ↓
Close both files
  ↓
Delete students.dat
  ↓
Rename temp.dat to students.dat
  ↓
Display "[SUCCESS] Student deleted successfully!"
  ↓
END
```

---

## Exit Algorithm

```
START
  ↓
Display "Thank you for using Student Management System."
  ↓
Display "Goodbye!"
  ↓
Exit the program (return 0 from main)
  ↓
END
```

---

## Student Exists (Duplicate Check) Algorithm

```
START
  ↓
Open students.dat in binary read mode
  ↓
IF file fails to open THEN
  ↓
  Return false (file doesn't exist, no duplicates)
  ↓
END IF
  ↓
WHILE (read Student record from file succeeds)
  ↓
  IF record.id == search ID THEN
    ↓
    Close file
    ↓
    Return true (ID exists)
    ↓
  END IF
  ↓
END WHILE
  ↓
Close file
  ↓
Return false (ID does not exist)
  ↓
END
```
