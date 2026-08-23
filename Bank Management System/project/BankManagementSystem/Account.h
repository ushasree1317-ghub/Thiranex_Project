#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include "Customer.h"

class Account {
private:
    std::string accountNumber;
    Customer customer;
    std::string accountType;
    double balance;
    std::string pin;
    bool blocked;

public:
    Account();
    Account(const std::string& accountNumber, const Customer& customer,
             const std::string& accountType, double balance, const std::string& pin);

    void setAccountNumber(const std::string& accNo);
    std::string getAccountNumber() const;

    void setCustomer(const Customer& customer);
    Customer getCustomer() const;

    void setAccountType(const std::string& type);
    std::string getAccountType() const;

    void setBalance(double balance);
    double getBalance() const;

    void setPIN(const std::string& pin);
    std::string getPIN() const;

    void setBlocked(bool blocked);
    bool isBlocked() const;

    void deposit(double amount);
    bool withdraw(double amount);
    bool transfer(Account& recipient, double amount);
};

#endif
