#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
private:
    std::string transactionId;
    std::string accountNumber;
    std::string dateTime;
    std::string type;
    double amount;
    double balanceAfter;

public:
    Transaction();
    Transaction(const std::string& transactionId, const std::string& accountNumber,
                 const std::string& dateTime, const std::string& type,
                 double amount, double balanceAfter);

    void setTransactionId(const std::string& id);
    std::string getTransactionId() const;

    void setAccountNumber(const std::string& accNo);
    std::string getAccountNumber() const;

    void setDateTime(const std::string& dt);
    std::string getDateTime() const;

    void setType(const std::string& type);
    std::string getType() const;

    void setAmount(double amount);
    double getAmount() const;

    void setBalanceAfter(double bal);
    double getBalanceAfter() const;
};

#endif
