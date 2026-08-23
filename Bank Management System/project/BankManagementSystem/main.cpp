#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
#include "Bank.h"
#include "Account.h"
#include "Customer.h"
#include "Transaction.h"
#include "Admin.h"
#include "Authentication.h"
#include "Validation.h"
#include "FileManager.h"

const std::string ACCOUNTS_FILE = "data/accounts.dat";
const std::string TRANSACTIONS_FILE = "data/transactions.dat";
const double MIN_INITIAL_DEPOSIT = 500.0;
const double MIN_BALANCE = 100.0;

void customerDashboard(Bank& bank, const std::string& accountNumber);
void adminDashboard(Bank& bank);

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void printHeader(const std::string& title) {
    std::cout << "\n";
    for (int i = 0; i < 50; i++) std::cout << "=";
    std::cout << "\n";
    std::cout << std::setw((50 + title.length()) / 2) << " " << title << "\n";
    for (int i = 0; i < 50; i++) std::cout << "=";
    std::cout << "\n";
}

void pause() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string getHiddenInput(const std::string& prompt) {
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);
    return input;
}

std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    std::getline(std::cin, line);
    return line;
}

int readInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            clearInput();
            return value;
        } else {
            std::cout << "Invalid input. Please enter a number.\n";
            clearInput();
        }
    }
}

double readDouble(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            clearInput();
            return value;
        } else {
            std::cout << "Invalid input. Please enter a valid amount.\n";
            clearInput();
        }
    }
}

void createAccountFlow(Bank& bank) {
    printHeader("CREATE NEW ACCOUNT");

    std::string accountNumber;
    while (true) {
        accountNumber = readLine("Enter Account Number (min 4 digits): ");
        if (!Validation::isValidAccountNumber(accountNumber)) {
            std::cout << "Invalid account number. Must be at least 4 digits.\n";
            continue;
        }
        if (bank.findAccount(accountNumber) != nullptr) {
            std::cout << "Account number already exists. Please choose a different one.\n";
            continue;
        }
        break;
    }

    std::string name;
    while (true) {
        name = readLine("Enter Full Name: ");
        if (!Validation::isValidName(name)) {
            std::cout << "Invalid name. Use letters, spaces, hyphens, and apostrophes only.\n";
            continue;
        }
        break;
    }

    int age;
    while (true) {
        age = readInt("Enter Age (18-120): ");
        if (!Validation::isValidAge(age)) {
            std::cout << "Invalid age. Must be between 18 and 120.\n";
            continue;
        }
        break;
    }

    std::string phone;
    while (true) {
        phone = readLine("Enter Phone Number: ");
        if (!Validation::isValidPhone(phone)) {
            std::cout << "Invalid phone number. Use 7-15 digits (with optional + or -).\n";
            continue;
        }
        break;
    }

    std::string address;
    while (true) {
        address = readLine("Enter Address: ");
        if (!Validation::isValidAddress(address)) {
            std::cout << "Invalid address. Cannot be empty or exceed 200 characters.\n";
            continue;
        }
        break;
    }

    std::string accountType;
    while (true) {
        accountType = readLine("Enter Account Type (Savings/Current): ");
        if (!Validation::isValidAccountType(accountType)) {
            std::cout << "Invalid account type. Choose 'Savings' or 'Current'.\n";
            continue;
        }
        break;
    }

    double initialDeposit;
    while (true) {
        initialDeposit = readDouble("Enter Initial Deposit (min " + std::to_string(MIN_INITIAL_DEPOSIT) + "): ");
        if (initialDeposit < MIN_INITIAL_DEPOSIT) {
            std::cout << "Initial deposit must be at least " << MIN_INITIAL_DEPOSIT << ".\n";
            continue;
        }
        break;
    }

    std::string pin;
    while (true) {
        pin = getHiddenInput("Set 4-digit PIN: ");
        if (!Validation::isValidPIN(pin)) {
            std::cout << "Invalid PIN. Must be exactly 4 digits.\n";
            continue;
        }
        std::string confirmPin = getHiddenInput("Confirm PIN: ");
        if (pin != confirmPin) {
            std::cout << "PINs do not match. Try again.\n";
            continue;
        }
        break;
    }

    Customer customer(name, age, phone, address);
    Account account(accountNumber, customer, accountType, initialDeposit, pin);

    if (bank.createAccount(account)) {
        bank.recordTransaction(accountNumber, "Initial Deposit", initialDeposit, initialDeposit);
        bank.saveData();
        std::cout << "\nAccount created successfully!\n";
        std::cout << "Account Number: " << accountNumber << "\n";
    } else {
        std::cout << "\nFailed to create account. Account number may already exist.\n";
    }
}

void customerLoginFlow(Bank& bank) {
    printHeader("CUSTOMER LOGIN");

    std::string accountNumber = readLine("Enter Account Number: ");
    Account* account = bank.findAccount(accountNumber);

    if (account == nullptr) {
        std::cout << "Account not found.\n";
        return;
    }

    if (account->isBlocked()) {
        std::cout << "This account is blocked. Please contact the administrator.\n";
        return;
    }

    int attempts = 0;
    while (attempts < Authentication::getMaxAttempts()) {
        std::string pin = getHiddenInput("Enter PIN: ");
        Account* authed = Authentication::login(bank, accountNumber, pin);
        if (authed != nullptr) {
            std::cout << "\nLogin successful! Welcome, " << authed->getCustomer().getName() << ".\n";
            customerDashboard(bank, accountNumber);
            return;
        } else {
            attempts++;
            std::cout << "Incorrect PIN. Attempts remaining: "
                      << (Authentication::getMaxAttempts() - attempts) << "\n";
        }
    }

    std::cout << "Too many incorrect attempts. Returning to main menu.\n";
}

void customerDashboard(Bank& bank, const std::string& accountNumber) {
    int choice;
    do {
        printHeader("CUSTOMER DASHBOARD");
        std::cout << "1. Check Balance\n";
        std::cout << "2. Deposit Money\n";
        std::cout << "3. Withdraw Money\n";
        std::cout << "4. Transfer Money\n";
        std::cout << "5. View Account Details\n";
        std::cout << "6. View Transaction History\n";
        std::cout << "7. Change PIN\n";
        std::cout << "8. Logout\n";
        choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1: {
                Account* acc = bank.findAccount(accountNumber);
                if (acc) {
                    std::cout << "\n--- Balance Inquiry ---\n";
                    std::cout << "Account Number: " << acc->getAccountNumber() << "\n";
                    std::cout << "Customer Name: " << acc->getCustomer().getName() << "\n";
                    std::cout << "Account Type: " << acc->getAccountType() << "\n";
                    std::cout << "Current Balance: " << acc->getBalance() << "\n";
                }
                pause();
                break;
            }
            case 2: {
                double amount = readDouble("Enter deposit amount: ");
                if (bank.deposit(accountNumber, amount)) {
                    std::cout << "Deposit successful. New balance: "
                              << bank.findAccount(accountNumber)->getBalance() << "\n";
                } else {
                    std::cout << "Deposit failed. Invalid amount.\n";
                }
                pause();
                break;
            }
            case 3: {
                double amount = readDouble("Enter withdrawal amount: ");
                Account* acc = bank.findAccount(accountNumber);
                if (acc && (acc->getBalance() - amount) < MIN_BALANCE) {
                    std::cout << "Withdrawal failed. Minimum balance of "
                              << MIN_BALANCE << " must be maintained.\n";
                } else if (bank.withdraw(accountNumber, amount)) {
                    std::cout << "Withdrawal successful. New balance: "
                              << bank.findAccount(accountNumber)->getBalance() << "\n";
                } else {
                    std::cout << "Withdrawal failed. Insufficient balance or invalid amount.\n";
                }
                pause();
                break;
            }
            case 4: {
                std::string recipient = readLine("Enter recipient account number: ");
                double amount = readDouble("Enter transfer amount: ");
                if (bank.transfer(accountNumber, recipient, amount)) {
                    std::cout << "Transfer successful.\n";
                } else {
                    std::cout << "Transfer failed. Check recipient, balance, and amount.\n";
                }
                pause();
                break;
            }
            case 5: {
                Account* acc = bank.findAccount(accountNumber);
                if (acc) {
                    Customer c = acc->getCustomer();
                    std::cout << "\n--- Account Details ---\n";
                    std::cout << "Account Number: " << acc->getAccountNumber() << "\n";
                    std::cout << "Name: " << c.getName() << "\n";
                    std::cout << "Age: " << c.getAge() << "\n";
                    std::cout << "Phone: " << c.getPhone() << "\n";
                    std::cout << "Address: " << c.getAddress() << "\n";
                    std::cout << "Account Type: " << acc->getAccountType() << "\n";
                    std::cout << "Current Balance: " << acc->getBalance() << "\n";
                    std::cout << "Status: " << (acc->isBlocked() ? "Blocked" : "Active") << "\n";
                }
                pause();
                break;
            }
            case 6: {
                std::vector<Transaction> history = bank.getTransactionHistory(accountNumber);
                std::cout << "\n--- Transaction History ---\n";
                if (history.empty()) {
                    std::cout << "No transactions found.\n";
                } else {
                    std::cout << std::left << std::setw(20) << "Transaction ID"
                              << std::setw(22) << "Date/Time"
                              << std::setw(16) << "Type"
                              << std::setw(12) << "Amount"
                              << "Balance After\n";
                    for (const Transaction& t : history) {
                        std::cout << std::left << std::setw(20) << t.getTransactionId()
                                  << std::setw(22) << t.getDateTime()
                                  << std::setw(16) << t.getType()
                                  << std::setw(12) << t.getAmount()
                                  << t.getBalanceAfter() << "\n";
                    }
                }
                pause();
                break;
            }
            case 7: {
                std::string oldPin = getHiddenInput("Enter current PIN: ");
                std::string newPin = getHiddenInput("Enter new 4-digit PIN: ");
                if (!Validation::isValidPIN(newPin)) {
                    std::cout << "Invalid new PIN format.\n";
                } else {
                    std::string confirmPin = getHiddenInput("Confirm new PIN: ");
                    if (newPin != confirmPin) {
                        std::cout << "PINs do not match.\n";
                    } else if (bank.changePIN(accountNumber, oldPin, newPin)) {
                        std::cout << "PIN changed successfully.\n";
                    } else {
                        std::cout << "PIN change failed. Current PIN is incorrect.\n";
                    }
                }
                pause();
                break;
            }
            case 8:
                std::cout << "Logging out...\n";
                break;
            default:
                std::cout << "Invalid choice. Please select 1-8.\n";
                pause();
                break;
        }
    } while (choice != 8);
}

void adminLoginFlow(Bank& bank) {
    printHeader("ADMIN LOGIN");
    Admin admin;

    std::string username = readLine("Enter Admin Username: ");
    std::string password = getHiddenInput("Enter Admin Password: ");

    if (!admin.authenticate(username, password)) {
        std::cout << "Invalid admin credentials.\n";
        return;
    }

    std::cout << "\nAdmin login successful!\n";
    adminDashboard(bank);
}

void adminDashboard(Bank& bank) {
    int choice;
    do {
        printHeader("ADMIN DASHBOARD");
        std::cout << "1. View All Customer Accounts\n";
        std::cout << "2. Search Account by Account Number\n";
        std::cout << "3. Search Customer by Name\n";
        std::cout << "4. View Total Number of Accounts\n";
        std::cout << "5. View Total Bank Balance\n";
        std::cout << "6. Delete an Account\n";
        std::cout << "7. Block/Unblock an Account\n";
        std::cout << "8. View Transaction Records\n";
        std::cout << "9. Logout\n";
        choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1: {
                std::vector<Account> accounts = bank.getAllAccounts();
                std::cout << "\n--- All Accounts ---\n";
                if (accounts.empty()) {
                    std::cout << "No accounts found.\n";
                } else {
                    for (const Account& acc : accounts) {
                        Customer c = acc.getCustomer();
                        std::cout << "Acc No: " << acc.getAccountNumber()
                                  << " | Name: " << c.getName()
                                  << " | Type: " << acc.getAccountType()
                                  << " | Balance: " << acc.getBalance()
                                  << " | Status: " << (acc.isBlocked() ? "Blocked" : "Active")
                                  << "\n";
                    }
                }
                pause();
                break;
            }
            case 2: {
                std::string accNo = readLine("Enter account number to search: ");
                Account* acc = bank.findAccount(accNo);
                if (acc) {
                    Customer c = acc->getCustomer();
                    std::cout << "\nAccount Found:\n";
                    std::cout << "Account Number: " << acc->getAccountNumber() << "\n";
                    std::cout << "Name: " << c.getName() << "\n";
                    std::cout << "Age: " << c.getAge() << "\n";
                    std::cout << "Phone: " << c.getPhone() << "\n";
                    std::cout << "Address: " << c.getAddress() << "\n";
                    std::cout << "Account Type: " << acc->getAccountType() << "\n";
                    std::cout << "Balance: " << acc->getBalance() << "\n";
                    std::cout << "Status: " << (acc->isBlocked() ? "Blocked" : "Active") << "\n";
                } else {
                    std::cout << "Account not found.\n";
                }
                pause();
                break;
            }
            case 3: {
                std::string name = readLine("Enter customer name to search: ");
                std::vector<Account> results = bank.searchByName(name);
                std::cout << "\n--- Search Results ---\n";
                if (results.empty()) {
                    std::cout << "No matching customers found.\n";
                } else {
                    for (const Account& acc : results) {
                        Customer c = acc.getCustomer();
                        std::cout << "Acc No: " << acc.getAccountNumber()
                                  << " | Name: " << c.getName()
                                  << " | Balance: " << acc.getBalance() << "\n";
                    }
                }
                pause();
                break;
            }
            case 4:
                std::cout << "\nTotal Number of Accounts: " << bank.getTotalAccounts() << "\n";
                pause();
                break;
            case 5:
                std::cout << "\nTotal Bank Balance: " << bank.getTotalBankBalance() << "\n";
                pause();
                break;
            case 6: {
                std::string accNo = readLine("Enter account number to delete: ");
                std::string confirm = readLine("Are you sure? Type YES to confirm: ");
                if (confirm == "YES") {
                    if (bank.deleteAccount(accNo)) {
                        std::cout << "Account deleted successfully.\n";
                    } else {
                        std::cout << "Account not found.\n";
                    }
                } else {
                    std::cout << "Deletion cancelled.\n";
                }
                pause();
                break;
            }
            case 7: {
                std::string accNo = readLine("Enter account number: ");
                Account* acc = bank.findAccount(accNo);
                if (!acc) {
                    std::cout << "Account not found.\n";
                } else if (acc->isBlocked()) {
                    if (bank.unblockAccount(accNo)) {
                        std::cout << "Account unblocked successfully.\n";
                    }
                } else {
                    if (bank.blockAccount(accNo)) {
                        std::cout << "Account blocked successfully.\n";
                    }
                }
                pause();
                break;
            }
            case 8: {
                std::vector<Account> allAccounts = bank.getAllAccounts();
                std::cout << "\n--- All Transaction Records ---\n";
                bool any = false;
                for (const Account& acc : allAccounts) {
                    std::vector<Transaction> hist = bank.getTransactionHistory(acc.getAccountNumber());
                    if (!hist.empty()) {
                        any = true;
                        std::cout << "\nAccount: " << acc.getAccountNumber()
                                  << " (" << acc.getCustomer().getName() << ")\n";
                        for (const Transaction& t : hist) {
                            std::cout << "  " << t.getTransactionId()
                                      << " | " << t.getDateTime()
                                      << " | " << t.getType()
                                      << " | " << t.getAmount()
                                      << " | Bal: " << t.getBalanceAfter() << "\n";
                        }
                    }
                }
                if (!any) {
                    std::cout << "No transactions found.\n";
                }
                pause();
                break;
            }
            case 9:
                std::cout << "Admin logging out...\n";
                break;
            default:
                std::cout << "Invalid choice. Please select 1-9.\n";
                pause();
                break;
        }
    } while (choice != 9);
}

int main() {
    Bank bank(ACCOUNTS_FILE, TRANSACTIONS_FILE);
    bank.loadData();

    int choice;
    do {
        printHeader("BANK MANAGEMENT SYSTEM");
        std::cout << "1. Customer Login\n";
        std::cout << "2. Create Account\n";
        std::cout << "3. Admin Login\n";
        std::cout << "4. Exit\n";
        choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1:
                customerLoginFlow(bank);
                break;
            case 2:
                createAccountFlow(bank);
                break;
            case 3:
                adminLoginFlow(bank);
                break;
            case 4:
                std::cout << "Thank you for using the Bank Management System. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please select 1-4.\n";
                pause();
                break;
        }
    } while (choice != 4);

    return 0;
}
