#include "keywords.h"
#include <iostream>
#include <regex>
#include <string>

class Person {
private:
  std::string name;
  std::string password;
  double bal{};

public:
  Person(std::string name, std::string password) {
    this->name = name;
    this->password = password;
  }
  Person() {};
  void deposit(double amount) {
    bal += amount;
    return;
  }
  void withdraw(double amount) {
    bal -= amount;
    return;
  }
  void send(std::string username, double amount) {}
  std::string getName() { return this->name; }
  std::string getPassword() { return this->password; }
  double getBalance() { return this->bal; }
  bool equals(Person person) {
    return (this->name == person.getName() &&
            this->password == person.getPassword());
  }
};

static Person parse(std::string rawUserData) {
  std::string name{};
  std::string password{};
  double bal{};
  std::smatch regexMatches;
  std::regex_search(rawUserData, regexMatches, regexPattern);
  name = regexMatches[1];
  password = regexMatches[2];
  bal = std::stod(regexMatches[3]);
  Person person = Person(name, password);
  person.deposit(bal);
  return person;
}
static std::string parseUsername(std::string rawUsername) {
  std::string name{};
  std::smatch regexMatches;
  std::regex_search(rawUsername, regexMatches, regexPattern);
  name = regexMatches[1];
  return name;
}
static Person createPersonFromRawData(std::string rawUserData) {
  Person newPerson = parse(rawUserData);
  return newPerson;
}
