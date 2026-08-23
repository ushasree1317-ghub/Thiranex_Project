#include "Admin.h"

Admin::Admin() : username("admin"), password("admin123") {}

Admin::Admin(const std::string& username, const std::string& password)
    : username(username), password(password) {}

bool Admin::authenticate(const std::string& username, const std::string& password) const {
    return (this->username == username && this->password == password);
}

std::string Admin::getUsername() const {
    return username;
}
