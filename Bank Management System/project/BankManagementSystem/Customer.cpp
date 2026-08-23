#include "Customer.h"

Customer::Customer() : age(0) {}

Customer::Customer(const std::string& name, int age, const std::string& phone, const std::string& address)
    : name(name), age(age), phone(phone), address(address) {}

void Customer::setName(const std::string& name) { this->name = name; }
std::string Customer::getName() const { return name; }

void Customer::setAge(int age) { this->age = age; }
int Customer::getAge() const { return age; }

void Customer::setPhone(const std::string& phone) { this->phone = phone; }
std::string Customer::getPhone() const { return phone; }

void Customer::setAddress(const std::string& address) { this->address = address; }
std::string Customer::getAddress() const { return address; }
