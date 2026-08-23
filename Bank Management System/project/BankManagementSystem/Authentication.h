#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <string>

class Account;
class Bank;

class Authentication {
private:
    static const int MAX_ATTEMPTS = 3;

public:
    static Account* login(Bank& bank, const std::string& accountNumber, const std::string& pin);
    static int getMaxAttempts();
};

#endif
