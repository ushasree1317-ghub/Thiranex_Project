#include "Account.h"

Account::Account() : balance(0.0), blocked(false) {}

Account::Account(const std::string& accountNumber, const Customer& customer,
                   const std::string& accountType, double balance, const std::string& pin)
    : accountNumber(accountNumber), customer(customer), accountType(accountType),
      balance(balance), pin(pin), blocked(false) {}

void Account::setAccountNumber(const std::string& accNo) { this->accountNumber = accNo; }
std::string Account::getAccountNumber() const { return accountNumber; }

void Account::setCustomer(const Customer& customer) { this->customer = customer; }
Customer Account::getCustomer() const { return customer; }

void Account::setAccountType(const std::string& type) { this->accountType = type; }
std::string Account::getAccountType() const { return accountType; }

void Account::setBalance(double balance) { this->balance = balance; }
double Account::getBalance() const { return balance; }

void Account::setPIN(const std::string& pin) { this->pin = pin; }
std::string Account::getPIN() const { return pin; }

void Account::setBlocked(bool blocked) { this->blocked = blocked; }
bool Account::isBlocked() const { return blocked; }

void Account::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
    }
}

bool Account::withdraw(double amount) {
    if (amount > 0 && balance >= amount) {
        balance -= amount;
        return true;
    }
    return false;
}

bool Account::transfer(Account& recipient, double amount) {
    if (amount > 0 && balance >= amount && accountNumber != recipient.getAccountNumber()) {
        balance -= amount;
        recipient.deposit(amount);
        return true;
    }
    return false;
}
