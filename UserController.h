#include "Bank.h"
#include "keywords.h"
#include <iostream>
#include <string>
class UserController {
  int input{};
  Bank bankController;

public:
  UserController() { bankController = Bank(); }
  void start() {
    int option{};
    std::cout << "Welcome to the bank! Please select an option" << std::endl;

    do {
      std::cout << "(1) Log into the bank" << std::endl;
      std::cout << "(2) Register with the bank" << std::endl;
      std::cin >> option;
    } while (!inputIsValid(option));

    if (option == registerAccount) {
      registerUser();
    } else if (option == loginAccount) {
      loginUser();
    }
  }

  void registerUser() {
    std::string username{};
    std::string password{};
    while (true) {
      do {
        std::cout
            << "Please enter a username you'd like for your new bank account: ";
        std::cin >> username;
      } while (!usernameIsValid(username));
      do {

        std::cout
            << "Please enter a password you'd like for your new bank account: ";
        std::cin >> password;
      } while (!passwordIsValid(password));

      if (bankController.createAccount(username, password) == success) {
        std::cout
            << "Congrats! You've created a bank account. Now proceed to log in."
            << std::endl;
        break;
      } else {

        std::cout << "Error creating account. Please try again" << std::endl;
      }
    }
    start();
  }

  void loginUser() {
    std::string username{};
    std::string password{};
    do {
      std::cout << "Please enter your login details:" << std::endl;
      std::cout << "Username: ";
      std::cin >> username;

      std::cout << "Password: ";
      std::cin >> password;
    } while (!bankController.attemptLogin(username, password));
    bankController.start();
    return;
  }
  bool inputIsValid(int input) {
    if (input != loginAccount && input != registerAccount) {
      return false;
    }
    return true;
  }
  bool usernameIsValid(std::string input) {
    if (input.length() < 5 || input.length() > 26) {
      std::cout << "Username must be longer than 5 characters and less that 26 "
                   "characters"
                << std::endl;
      return false;
    }
    return true;
  }

  bool passwordIsValid(std::string input) {
    if (input.length() < 5 || input.length() > 26) {
      std::cout << "Username must be longer than 5 characters and less that 26 "
                   "characters"
                << std::endl;
      return false;
    }
    return true;
  }
};
