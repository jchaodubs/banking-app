#include "Person.h"
#include "keywords.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

enum Option { DEPOSIT = 1, WITHDRAW, SEND, LOG_OUT, CLOSE_ACCOUNT };

class Bank {
private:
public:
  std::string userDataFile = "userData.txt";
  Person user;
  std::time_t timestamp;
  Bank() {}
  void start() {
    std::time(&timestamp);
    std::cout << std::ctime(&timestamp);

    std::cout << "Salutations " << user.getName()
              << ". What would you like to do today?" << std::endl;

    int option{};

    enum Option selectedOption;
    do {
      std::cout << "1. Deposit money" << std::endl
                << "2. Withdraw money" << std::endl
                << "3. Send money" << std::endl
                << "4. Log out" << std::endl
                << "5. Close Account" << std::endl;
      std::cin >> option;
    } while (!inputIsValid(option, selectedOption));
    executeOption(selectedOption);
  }

  std::string createAccount(std::string username, std::string password) {
    Person person = Person(username, password);
    if (alreadyExists(person)) {
      return failure;
    } else {

      saveNewPerson(person);
      return success;
    }
  }
  bool alreadyExists(Person person) {
    std::ifstream usersFile(userDataFile);

    std::string rawUserData;
    while (std::getline(usersFile, rawUserData)) {
      Person existingUser = parse(rawUserData);
      if (person.equals(existingUser)) {
        usersFile.close();
        return true;
      }
    }
    usersFile.close();
    return false;
  }
  void saveNewPerson(Person person) {
    std::ofstream usersFile(userDataFile, std::ios::app);
    usersFile << person.getName() << delimiter << person.getPassword()
              << delimiter << person.getBalance() << delimiter
              << person.getIsChildAccount() << std::endl;
    usersFile.close();
  }
  bool attemptLogin(std::string username, std::string password) {
    Person personLoggingIn = Person(username, password);
    bool isCorrectLogin = alreadyExists(personLoggingIn);
    if (isCorrectLogin) {
      login(personLoggingIn);
      return true;
    } else {
      return false;
    }
  }
  void login(Person personLoggingIn) { user = personLoggingIn; }
  bool inputIsValid(int option, Option &selectedOption) {
    switch (option) {
    case 1:
      selectedOption = DEPOSIT;
      return true;
    case 2:
      selectedOption = WITHDRAW;
      return true;
    case 3:
      selectedOption = SEND;
      return true;
    case 4:
      selectedOption = LOG_OUT;

      return true;
    case 5:
      selectedOption = CLOSE_ACCOUNT;
      return true;
    default:
      return false;
    }
  }
  void executeOption(Option option) { return; }
};
