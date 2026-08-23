#include "Authentication.h"
#include "Bank.h"
#include "Account.h"

int Authentication::getMaxAttempts() {
    return MAX_ATTEMPTS;
}

Account* Authentication::login(Bank& bank, const std::string& accountNumber, const std::string& pin) {
    Account* acc = bank.findAccount(accountNumber);
    if (!acc) return nullptr;
    if (acc->isBlocked()) return nullptr;
    if (acc->getPIN() == pin) return acc;
    return nullptr;
}
