#include "UserController.h"
#include "keywords.h"
#include <iostream>
#include <string>

int loginAccount = 1;
int registerAccount = 2;
int deposit = 1;
int withdraw = 2;
int send = 3;
int logout = 4;
int closeAccount = 5;
std::string success = "Success";
std::string failure = "Failure";
std::string delimiter = ":%:";
std::regex regexPattern("(.*):%:(.*):%:(.*):%:(.*)");
int main() {
  UserController Controller;
  Controller.start();
}
