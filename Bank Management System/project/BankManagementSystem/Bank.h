#ifndef BANK_H
#define BANK_H

#include <vector>
#include <string>
#include "Account.h"
#include "Transaction.h"

class Bank {
private:
    std::vector<Account> accounts;
    std::vector<Transaction> transactions;
    std::string accountsFile;
    std::string transactionsFile;

    std::string generateTransactionId() const;
    std::string getCurrentDateTime() const;

public:
    Bank(const std::string& accountsFile, const std::string& transactionsFile);

    void loadData();
    void saveData();

    bool createAccount(const Account& account);
    Account* findAccount(const std::string& accountNumber);
    int findAccountIndex(const std::string& accountNumber) const;

    bool deposit(const std::string& accountNumber, double amount);
    bool withdraw(const std::string& accountNumber, double amount);
    bool transfer(const std::string& fromAccount, const std::string& toAccount, double amount);

    std::vector<Transaction> getTransactionHistory(const std::string& accountNumber) const;
    void recordTransaction(const std::string& accountNumber, const std::string& type, double amount, double balanceAfter);

    bool changePIN(const std::string& accountNumber, const std::string& oldPIN, const std::string& newPIN);

    std::vector<Account> getAllAccounts() const;
    int getTotalAccounts() const;
    double getTotalBankBalance() const;

    bool deleteAccount(const std::string& accountNumber);
    bool blockAccount(const std::string& accountNumber);
    bool unblockAccount(const std::string& accountNumber);

    std::vector<Account> searchByName(const std::string& name) const;
};

#endif
