#ifndef VALIDATION_H
#define VALIDATION_H

#include <string>

class Validation {
public:
    static bool isValidAccountNumber(const std::string& accNo);
    static bool isValidName(const std::string& name);
    static bool isValidAge(int age);
    static bool isValidPhone(const std::string& phone);
    static bool isValidAddress(const std::string& address);
    static bool isValidAccountType(const std::string& type);
    static bool isValidAmount(double amount);
    static bool isValidPIN(const std::string& pin);
    static bool isAllDigits(const std::string& s);
};

#endif
