#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include <string>
#include "Account.h"
#include "Transaction.h"

class FileManager {
public:
    static std::vector<Account> loadAccounts(const std::string& filename);
    static void saveAccounts(const std::string& filename, const std::vector<Account>& accounts);

    static std::vector<Transaction> loadTransactions(const std::string& filename);
    static void saveTransactions(const std::string& filename, const std::vector<Transaction>& transactions);
    static void appendTransaction(const std::string& filename, const Transaction& transaction);

    static void ensureDataDirectory(const std::string& dirPath);
};

#endif
