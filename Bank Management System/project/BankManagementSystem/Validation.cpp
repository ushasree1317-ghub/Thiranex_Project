#include "Validation.h"
#include <cctype>

bool Validation::isAllDigits(const std::string& s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (!std::isdigit(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

bool Validation::isValidAccountNumber(const std::string& accNo) {
    return accNo.length() >= 4 && isAllDigits(accNo);
}

bool Validation::isValidName(const std::string& name) {
    if (name.empty()) return false;
    for (char c : name) {
        if (!std::isalpha(static_cast<unsigned char>(c)) && c != ' ' && c != '-' && c != '\'') return false;
    }
    return true;
}

bool Validation::isValidAge(int age) {
    return age >= 18 && age <= 120;
}

bool Validation::isValidPhone(const std::string& phone) {
    if (phone.length() < 7 || phone.length() > 15) return false;
    for (char c : phone) {
        if (!std::isdigit(static_cast<unsigned char>(c)) && c != '+' && c != '-') return false;
    }
    return true;
}

bool Validation::isValidAddress(const std::string& address) {
    return !address.empty() && address.length() <= 200;
}

bool Validation::isValidAccountType(const std::string& type) {
    return (type == "Savings" || type == "Current");
}

bool Validation::isValidAmount(double amount) {
    return amount > 0.0;
}

bool Validation::isValidPIN(const std::string& pin) {
    return pin.length() == 4 && isAllDigits(pin);
}
