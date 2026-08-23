#include "Bank.h"
#include "FileManager.h"
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <sstream>

Bank::Bank(const std::string& accountsFile, const std::string& transactionsFile)
    : accountsFile(accountsFile), transactionsFile(transactionsFile) {}

std::string Bank::generateTransactionId() const {
    time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    std::ostringstream oss;
    oss << "TXN" << std::put_time(localTime, "%Y%m%d%H%M%S");
    static int counter = 0;
    oss << std::setw(3) << std::setfill('0') << (counter++);
    return oss.str();
}

std::string Bank::getCurrentDateTime() const {
    time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(localTime, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

void Bank::loadData() {
    FileManager::ensureDataDirectory("data");
    accounts = FileManager::loadAccounts(accountsFile);
    transactions = FileManager::loadTransactions(transactionsFile);
}

void Bank::saveData() {
    FileManager::saveAccounts(accountsFile, accounts);
    FileManager::saveTransactions(transactionsFile, transactions);
}

bool Bank::createAccount(const Account& account) {
    for (const Account& acc : accounts) {
        if (acc.getAccountNumber() == account.getAccountNumber()) {
            return false;
        }
    }
    accounts.push_back(account);
    saveData();
    return true;
}

Account* Bank::findAccount(const std::string& accountNumber) {
    for (size_t i = 0; i < accounts.size(); i++) {
        if (accounts[i].getAccountNumber() == accountNumber) {
            return &accounts[i];
        }
    }
    return nullptr;
}

int Bank::findAccountIndex(const std::string& accountNumber) const {
    for (size_t i = 0; i < accounts.size(); i++) {
        if (accounts[i].getAccountNumber() == accountNumber) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

void Bank::recordTransaction(const std::string& accountNumber, const std::string& type, double amount, double balanceAfter) {
    Transaction t(generateTransactionId(), accountNumber, getCurrentDateTime(), type, amount, balanceAfter);
    transactions.push_back(t);
}

bool Bank::deposit(const std::string& accountNumber, double amount) {
    Account* acc = findAccount(accountNumber);
    if (!acc || acc->isBlocked() || amount <= 0) return false;
    acc->deposit(amount);
    recordTransaction(accountNumber, "Deposit", amount, acc->getBalance());
    saveData();
    return true;
}

bool Bank::withdraw(const std::string& accountNumber, double amount) {
    Account* acc = findAccount(accountNumber);
    if (!acc || acc->isBlocked() || amount <= 0) return false;
    if (!acc->withdraw(amount)) return false;
    recordTransaction(accountNumber, "Withdraw", amount, acc->getBalance());
    saveData();
    return true;
}

bool Bank::transfer(const std::string& fromAccount, const std::string& toAccount, double amount) {
    if (fromAccount == toAccount || amount <= 0) return false;

    int senderIdx = findAccountIndex(fromAccount);
    int recipientIdx = findAccountIndex(toAccount);

    if (senderIdx == -1 || recipientIdx == -1) return false;
    if (accounts[senderIdx].isBlocked() || accounts[recipientIdx].isBlocked()) return false;

    if (!accounts[senderIdx].transfer(accounts[recipientIdx], amount)) return false;

    recordTransaction(fromAccount, "Transfer Out", amount, accounts[senderIdx].getBalance());
    recordTransaction(toAccount, "Transfer In", amount, accounts[recipientIdx].getBalance());
    saveData();
    return true;
}

std::vector<Transaction> Bank::getTransactionHistory(const std::string& accountNumber) const {
    std::vector<Transaction> history;
    for (const Transaction& t : transactions) {
        if (t.getAccountNumber() == accountNumber) {
            history.push_back(t);
        }
    }
    return history;
}

bool Bank::changePIN(const std::string& accountNumber, const std::string& oldPIN, const std::string& newPIN) {
    Account* acc = findAccount(accountNumber);
    if (!acc || acc->getPIN() != oldPIN) return false;
    acc->setPIN(newPIN);
    saveData();
    return true;
}

std::vector<Account> Bank::getAllAccounts() const {
    return accounts;
}

int Bank::getTotalAccounts() const {
    return static_cast<int>(accounts.size());
}

double Bank::getTotalBankBalance() const {
    double total = 0.0;
    for (const Account& acc : accounts) {
        total += acc.getBalance();
    }
    return total;
}

bool Bank::deleteAccount(const std::string& accountNumber) {
    int idx = findAccountIndex(accountNumber);
    if (idx == -1) return false;
    accounts.erase(accounts.begin() + idx);
    saveData();
    return true;
}

bool Bank::blockAccount(const std::string& accountNumber) {
    Account* acc = findAccount(accountNumber);
    if (!acc) return false;
    acc->setBlocked(true);
    saveData();
    return true;
}

bool Bank::unblockAccount(const std::string& accountNumber) {
    Account* acc = findAccount(accountNumber);
    if (!acc) return false;
    acc->setBlocked(false);
    saveData();
    return true;
}

std::vector<Account> Bank::searchByName(const std::string& name) const {
    std::vector<Account> results;
    std::string searchName = name;
    std::transform(searchName.begin(), searchName.end(), searchName.begin(), ::tolower);

    for (const Account& acc : accounts) {
        std::string custName = acc.getCustomer().getName();
        std::transform(custName.begin(), custName.end(), custName.begin(), ::tolower);
        if (custName.find(searchName) != std::string::npos) {
            results.push_back(acc);
        }
    }
    return results;
}
