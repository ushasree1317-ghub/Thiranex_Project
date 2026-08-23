#ifndef ADMIN_H
#define ADMIN_H

#include <string>

class Admin {
private:
    std::string username;
    std::string password;

public:
    Admin();
    Admin(const std::string& username, const std::string& password);

    bool authenticate(const std::string& username, const std::string& password) const;
    std::string getUsername() const;
};

#endif
