#include "Person.h"
#include "keywords.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

enum Option { DEPOSIT = 1, WITHDRAW, SEND, LOG_OUT, CLOSE_ACCOUNT };

class Bank {
private:
public:
  std::string userDataFile = "userData.txt";
  Person user;
  std::time_t timestamp;
  Bank() {}
  void start() {
    std::cout << "Your current balance is $" << user.getBalance() << std::endl;
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

  bool alreadyExists(std::string username) {
    std::ifstream usersFile(userDataFile);

    std::string rawUserData;
    while (std::getline(usersFile, rawUserData)) {
      std::string existingUser = parseUsername(rawUserData);
      if (username == existingUser) {
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
              << delimiter << person.getBalance() << delimiter << std::endl;
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
  void login(Person personLoggingIn) {
    user = personLoggingIn;
    fetchBal(user);
    introduce();
  }
  void introduce() {

    std::time(&timestamp);
    std::cout << std::ctime(&timestamp);

    std::cout << "Salutations " << user.getName()
              << ". What would you like to do today?" << std::endl;
  }
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
  void executeOption(Option option) {
    switch (option) {
    case DEPOSIT:
      depositMoney();
      start();
    case WITHDRAW:
      withdrawMoney();
      start();
    case SEND:
      sendMoney();
      start();
    case LOG_OUT:
      start();
    case CLOSE_ACCOUNT:
    default:
      start();
    }
  }
  void depositMoney() {
    double amount{};
    std::cout << "How much would you like to deposit?" << std::endl;
    while (true) {
      std::cin >> amount;
      if (amount < 0) {
        std::cout << "Uh oh. Error. Try again." << std::endl;
      } else {
        break;
      }
    }
    user.deposit(amount);
    writeBal(user, user.getBalance());
    std::cout << "Successful. Your new balance is now $" << user.getBalance()
              << std::endl;
  };
  void withdrawMoney() {
    double amount{};

    std::cout << "How much would you like to withdraw?" << std::endl;

    while (true) {
      std::cin >> amount;
      if (amount < 0) {
        std::cout << "Uh oh. Error. Try again." << std::endl;
      } else if (amount > user.getBalance()) {
        std::cout << "Balance too low. Try again." << std::endl;

      } else {
        break;
      }
    }
    user.withdraw(amount);
    writeBal(user, user.getBalance());
    std::cout << "Successful. Your new balance is now $" << user.getBalance()
              << std::endl;
  }
  void sendMoney() {
    std::string username{};
    double amount{};
    std::cout << "Please enter the username of the person you'd like to send "
                 "money to: ";
    while (true) {
      std::cin >> username;

      if (!alreadyExists(username)) {
        std::cout << "User not found try again." << std::endl;
      } else {
        break;
      }
    }
    std::cout << "Please enter the amount you'd like to send: ";
    while (true) {
      std::cin >> amount;
      if (amount < 0) {

        std::cout << "Uh oh. Error. Try again." << std::endl;
      } else if (amount > user.getBalance()) {

        std::cout << "Balance too low. Try again." << std::endl;
      } else {

        break;
      }
    }
    user.send(username, amount);
    std::cout << "Successful. Your new balance is now $" << user.getBalance()
              << std::endl;
  }

  void writeBal(Person person, double amount) {
    std::vector<std::string> fileContents;

    std::fstream usersFile(userDataFile);
    std::string rawUserData{};
    while (std::getline(usersFile, rawUserData)) {

      Person existingUser = parse(rawUserData);
      if (existingUser.equals(user)) {
        continue;
      }
      fileContents.push_back(rawUserData);
    }
    usersFile.close();
    usersFile.open(userDataFile, std::ios::out | std::ios::trunc);
    usersFile.close();
    saveNewPerson(person);
    for (std::string rawUser : fileContents) {
      Person person = createPersonFromRawData(rawUser);
      saveNewPerson(person);
    }
  }
  void fetchBal(Person &person) {

    std::ifstream usersFile(userDataFile);
    std::string rawUserData{};
    while (std::getline(usersFile, rawUserData)) {
      std::cout << rawUserData;
      Person existingUser = parse(rawUserData);
      if (existingUser.equals(person)) {
        person.deposit(existingUser.getBalance());
        break;
      }
    }
    usersFile.close();
  }
};
