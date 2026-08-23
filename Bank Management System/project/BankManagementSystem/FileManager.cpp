#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <sys/stat.h>

void FileManager::ensureDataDirectory(const std::string& dirPath) {
    struct stat info;

    if (stat(dirPath.c_str(), &info) != 0) {
        mkdir(dirPath.c_str());
    }
}

std::vector<Account> FileManager::loadAccounts(const std::string& filename) {
    std::vector<Account> accounts;
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        return accounts;
    }

    while (file.peek() != EOF) {
        Account acc;
        std::string accountNumber, name, phone, address, accountType, pin;
        int age;
        double balance;
        bool blocked;

        size_t len;

        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        if (file.peek() == EOF) break;
        accountNumber.resize(len);
        file.read(&accountNumber[0], len);
        acc.setAccountNumber(accountNumber);

        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        name.resize(len);
        file.read(&name[0], len);

        file.read(reinterpret_cast<char*>(&age), sizeof(age));

        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        phone.resize(len);
        file.read(&phone[0], len);

        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        address.resize(len);
        file.read(&address[0], len);

        Customer cust(name, age, phone, address);
        acc.setCustomer(cust);

        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        accountType.resize(len);
        file.read(&accountType[0], len);
        acc.setAccountType(accountType);

        file.read(reinterpret_cast<char*>(&balance), sizeof(balance));
        acc.setBalance(balance);

        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        pin.resize(len);
        file.read(&pin[0], len);
        acc.setPIN(pin);

        file.read(reinterpret_cast<char*>(&blocked), sizeof(blocked));
        acc.setBlocked(blocked);

        if (file) {
            accounts.push_back(acc);
        }
    }

    file.close();
    return accounts;
}

void FileManager::saveAccounts(const std::string& filename, const std::vector<Account>& accounts) {
    std::ofstream file(filename, std::ios::binary | std::ios::trunc);
    if (!file) {
        std::cerr << "Error: Unable to save accounts to " << filename << std::endl;
        return;
    }

    for (const Account& acc : accounts) {
        std::string accountNumber = acc.getAccountNumber();
        Customer cust = acc.getCustomer();
        std::string name = cust.getName();
        int age = cust.getAge();
        std::string phone = cust.getPhone();
        std::string address = cust.getAddress();
        std::string accountType = acc.getAccountType();
        double balance = acc.getBalance();
        std::string pin = acc.getPIN();
        bool blocked = acc.isBlocked();

        size_t len;

        len = accountNumber.size();
        file.write(reinterpret_cast<const char*>(&len), sizeof(len));
        file.write(accountNumber.c_str(), len);

        len = name.size();
        file.write(reinterpret_cast<const char*>(&len), sizeof(len));
        file.write(name.c_str(), len);

        file.write(reinterpret_cast<const char*>(&age), sizeof(age));

        len = phone.size();
        file.write(reinterpret_cast<const char*>(&len), sizeof(len));
        file.write(phone.c_str(), len);

        len = address.size();
        file.write(reinterpret_cast<const char*>(&len), sizeof(len));
        file.write(address.c_str(), len);

        len = accountType.size();
        file.write(reinterpret_cast<const char*>(&len), sizeof(len));
        file.write(accountType.c_str(), len);

        file.write(reinterpret_cast<const char*>(&balance), sizeof(balance));

        len = pin.size();
        file.write(reinterpret_cast<const char*>(&len), sizeof(len));
        file.write(pin.c_str(), len);

        file.write(reinterpret_cast<const char*>(&blocked), sizeof(blocked));
    }

    file.close();
}

std::vector<Transaction> FileManager::loadTransactions(const std::string& filename) {
    std::vector<Transaction> transactions;
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        return transactions;
    }

    while (file.peek() != EOF) {
        std::string transactionId, accountNumber, dateTime, type;
        double amount, balanceAfter;
        size_t len;

        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        if (file.peek() == EOF) break;
        transactionId.resize(len);
        file.read(&transactionId[0], len);

        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        accountNumber.resize(len);
        file.read(&accountNumber[0], len);

        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        dateTime.resize(len);
        file.read(&dateTime[0], len);

        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        type.resize(len);
        file.read(&type[0], len);

        file.read(reinterpret_cast<char*>(&amount), sizeof(amount));
        file.read(reinterpret_cast<char*>(&balanceAfter), sizeof(balanceAfter));

        if (file) {
            Transaction t(transactionId, accountNumber, dateTime, type, amount, balanceAfter);
            transactions.push_back(t);
        }
    }

    file.close();
    return transactions;
}

void FileManager::saveTransactions(const std::string& filename, const std::vector<Transaction>& transactions) {
    std::ofstream file(filename, std::ios::binary | std::ios::trunc);
    if (!file) {
        std::cerr << "Error: Unable to save transactions to " << filename << std::endl;
        return;
    }

    for (const Transaction& t : transactions) {
        std::string transactionId = t.getTransactionId();
        std::string accountNumber = t.getAccountNumber();
        std::string dateTime = t.getDateTime();
        std::string type = t.getType();
        double amount = t.getAmount();
        double balanceAfter = t.getBalanceAfter();

        size_t len;

        len = transactionId.size();
        file.write(reinterpret_cast<const char*>(&len), sizeof(len));
        file.write(transactionId.c_str(), len);

        len = accountNumber.size();
        file.write(reinterpret_cast<const char*>(&len), sizeof(len));
        file.write(accountNumber.c_str(), len);

        len = dateTime.size();
        file.write(reinterpret_cast<const char*>(&len), sizeof(len));
        file.write(dateTime.c_str(), len);

        len = type.size();
        file.write(reinterpret_cast<const char*>(&len), sizeof(len));
        file.write(type.c_str(), len);

        file.write(reinterpret_cast<const char*>(&amount), sizeof(amount));
        file.write(reinterpret_cast<const char*>(&balanceAfter), sizeof(balanceAfter));
    }

    file.close();
}

void FileManager::appendTransaction(const std::string& filename, const Transaction& transaction) {
    std::vector<Transaction> all = loadTransactions(filename);
    all.push_back(transaction);
    saveTransactions(filename, all);
}
