#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class Customer {
private:
    std::string name;
    int age;
    std::string phone;
    std::string address;

public:
    Customer();
    Customer(const std::string& name, int age, const std::string& phone, const std::string& address);

    void setName(const std::string& name);
    std::string getName() const;

    void setAge(int age);
    int getAge() const;

    void setPhone(const std::string& phone);
    std::string getPhone() const;

    void setAddress(const std::string& address);
    std::string getAddress() const;
};

#endif
