#include "Transaction.h"

Transaction::Transaction() : amount(0.0), balanceAfter(0.0) {}

Transaction::Transaction(const std::string& transactionId, const std::string& accountNumber,
                           const std::string& dateTime, const std::string& type,
                           double amount, double balanceAfter)
    : transactionId(transactionId), accountNumber(accountNumber), dateTime(dateTime),
      type(type), amount(amount), balanceAfter(balanceAfter) {}

void Transaction::setTransactionId(const std::string& id) { this->transactionId = id; }
std::string Transaction::getTransactionId() const { return transactionId; }

void Transaction::setAccountNumber(const std::string& accNo) { this->accountNumber = accNo; }
std::string Transaction::getAccountNumber() const { return accountNumber; }

void Transaction::setDateTime(const std::string& dt) { this->dateTime = dt; }
std::string Transaction::getDateTime() const { return dateTime; }

void Transaction::setType(const std::string& type) { this->type = type; }
std::string Transaction::getType() const { return type; }

void Transaction::setAmount(double amount) { this->amount = amount; }
double Transaction::getAmount() const { return amount; }

void Transaction::setBalanceAfter(double bal) { this->balanceAfter = bal; }
double Transaction::getBalanceAfter() const { return balanceAfter; }
