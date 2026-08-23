# Bank Management Application using C++ OOP and File Handling

## 1. Project Title

**Bank Management Application using C++ OOP and File Handling**

## 2. Project Description

A console-based banking application written in C++ that demonstrates Object-Oriented Programming (OOP) and file handling. The application maintains customer and account records persistently using binary files, so data is preserved across restarts. It supports account creation, authentication, deposits, withdrawals, transfers, transaction history, PIN management, and an administrator module.

## 3. Objectives

- Demonstrate OOP concepts: encapsulation, abstraction, composition, and inheritance where appropriate.
- Implement persistent storage using C++ file handling (no database).
- Provide a clean, menu-driven console interface.
- Validate all user input and handle errors gracefully.
- Maintain transaction history per account.
- Provide an admin module for managing accounts.

## 4. Features

- **Account Creation** with validation (unique account number, valid age, phone, PIN, minimum deposit).
- **Login / Authentication** with limited PIN attempts and hidden PIN entry.
- **Customer Dashboard** with balance inquiry, deposit, withdraw, transfer, account details, transaction history, and PIN change.
- **Deposit** with positive-amount validation and transaction recording.
- **Withdrawal** with insufficient-balance and minimum-balance checks.
- **Money Transfer** between accounts with recipient verification and dual transaction recording.
- **Transaction History** with transaction ID, date/time, type, amount, and balance after.
- **Change PIN** with old-PIN verification and confirmation.
- **Admin Module** with view all accounts, search by account number, search by name, total accounts, total bank balance, delete account, block/unblock account, view all transactions.

## 5. Technologies Used

- Language: C++ (C++11 standard)
- Compiler: GCC / MinGW
- Storage: Binary file handling (`accounts.dat`, `transactions.dat`)
- No external libraries or frameworks.

## 6. OOP Concepts Demonstrated

| Concept | Where |
|---|---|
| **Encapsulation** | All classes use private data members with public getters/setters. |
| **Abstraction** | `Bank` exposes high-level operations (deposit, withdraw, transfer) hiding file I/O details. |
| **Composition** | `Account` contains a `Customer` object; `Bank` contains collections of `Account` and `Transaction`. |
| **Constructors** | Every class has parameterized and default constructors. |
| **Separation of Concerns** | `Validation`, `FileManager`, `Authentication`, `Admin`, `Bank`, `Account`, `Customer`, `Transaction` each have a single responsibility. |
| **Static Methods** | `Validation` and `Authentication` use static utility methods. |

## 7. File Handling Approach

- **`data/accounts.dat`** — Binary file storing all account records (account number, customer details, type, balance, PIN, blocked status).
- **`data/transactions.dat`** — Binary file storing all transaction records (transaction ID, account number, date/time, type, amount, balance after).
- Files are created automatically if they do not exist.
- Data is loaded at startup and saved after every modification.
- Records use length-prefixed string serialization for variable-length fields.

## 8. Project Structure

```
BankManagementSystem/
├── main.cpp
├── Account.h
├── Account.cpp
├── Customer.h
├── Customer.cpp
├── Transaction.h
├── Transaction.cpp
├── Bank.h
├── Bank.cpp
├── Admin.h
├── Admin.cpp
├── Authentication.h
├── Authentication.cpp
├── FileManager.h
├── FileManager.cpp
├── Validation.h
├── Validation.cpp
├── data/
│   ├── accounts.dat
│   └── transactions.dat
├── README.md
└── Makefile
```

## 9. Installation Requirements

- A C++ compiler supporting C++11 (GCC 4.8+ or MinGW).
- GNU Make (optional, for using the Makefile).
- Any operating system with a terminal/console (Linux, macOS, Windows).

## 10. Compilation Instructions

**Using the Makefile (Linux/macOS/MinGW):**

```bash
cd BankManagementSystem
make
```

**Manual compilation:**

```bash
g++ -std=c++11 -Wall -O2 -o bank main.cpp Account.cpp Customer.cpp Transaction.cpp Bank.cpp Admin.cpp Authentication.cpp FileManager.cpp Validation.cpp
```

**On Windows with MinGW:**

```cmd
g++ -std=c++11 -Wall -O2 -o bank.exe main.cpp Account.cpp Customer.cpp Transaction.cpp Bank.cpp Admin.cpp Authentication.cpp FileManager.cpp Validation.cpp
```

## 11. Execution Instructions

```bash
./bank        # Linux/macOS
bank.exe      # Windows
```

Or via Makefile:

```bash
make run
```

## 12. Sample Login Information for Testing

**Admin credentials:**
- Username: `admin`
- Password: `admin123`

**Sample customer account** (create one via "Create Account" option, or use any you create):
- Account Number: `1001`
- PIN: `1234`

## 13. Sample Test Cases

| # | Test Case | Expected Result |
|---|---|---|
| 1 | Create account with valid details | Account created successfully |
| 2 | Create account with duplicate account number | "Account number already exists" |
| 3 | Login with correct account number and PIN | Login successful, dashboard shown |
| 4 | Login with wrong PIN | "Incorrect PIN" message |
| 5 | Enter wrong PIN 3 times | "Too many incorrect attempts" |
| 6 | Deposit valid amount | Balance updated, transaction recorded |
| 7 | Deposit negative amount | "Deposit failed" |
| 8 | Withdraw valid amount | Balance reduced, transaction recorded |
| 9 | Withdraw more than balance | "Insufficient balance" |
| 10 | Transfer to valid recipient | Both balances updated |
| 11 | Transfer to non-existent account | "Transfer failed" |
| 12 | Transfer to same account | "Transfer failed" |
| 13 | Check balance | Correct balance displayed |
| 14 | Change PIN with correct old PIN | PIN changed |
| 15 | Change PIN with wrong old PIN | "PIN change failed" |
| 16 | View transaction history | All transactions listed |
| 17 | Admin login with correct credentials | Admin dashboard shown |
| 18 | Admin search by account number | Account details displayed |
| 19 | Admin delete account | Account removed |
| 20 | Admin block/unblock account | Status changed |
| 21 | Restart app and check data | All data persists |

## 14. Expected Outputs

```
==================================================
         BANK MANAGEMENT SYSTEM
==================================================
1. Customer Login
2. Create Account
3. Admin Login
4. Exit
Enter your choice:
```

After creating an account and logging in:

```
==================================================
          CUSTOMER DASHBOARD
==================================================
1. Check Balance
2. Deposit Money
3. Withdraw Money
4. Transfer Money
5. View Account Details
6. View Transaction History
7. Change PIN
8. Logout
Enter your choice:
```

## 15. Limitations

- This is an academic simulation. Plain-text/binary file storage is **not** production-secure.
- PINs are stored in binary files without hashing (academic scope).
- No concurrency control — single-user access assumed.
- No interest calculation or statement generation.
- Console-based UI only.

## 16. Future Enhancements

- PIN hashing (e.g., SHA-256).
- GUI with Qt or a web frontend.
- Database integration (SQLite/PostgreSQL).
- Multi-currency support.
- Interest calculation and automated statements.
- Concurrency and locking for multi-user access.
- Email/SMS notifications for transactions.
