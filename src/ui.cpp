#include "ui.h"

// handle the login process for a user. It takes a Database object of User type as an argument
storage::User ui::loginUI(storage::Database<storage::User> userData)
{
  // collect user input
  std::string username, password;

  std::cout << std::setw(20) << std::left << "Username"
            << ":";
  std::cin >> username;
  std::cout << std::setw(20) << std::left << "Password"
            << ":";
  std::cin >> password;
  std::cout << std::endl;

  // Find Users
  int id = userData.find(username);
  if (id == -1)
  {
    std::cout << "couldn't find such username, please try again" << std::endl;
    return ui::loginUI(userData);
  }

  // Check Passwords
  auto user = userData.getData(id);
  if (password != user.getPassword())
  {
    std::cout << "Password is incorrect, please try again";
    return ui::loginUI(userData);
  }

  return user;
}

void ui::createHeader(std::string header, int maxLength, int space)
{
  int length = header.length();
  int left = (maxLength - (length + 2 * space)) / 2;
  int right = maxLength - (length + left + 2 * space);

  std::cout << std::setfill('=') << std::setw(left) << "";
  std::cout << std::setfill(' ') << std::setw(space) << "";
  std::cout << header << std::setw(space) << "";
  std::cout << std::setfill('=') << std::setw(right) << "";
  std::cout << std::endl << std::setfill(' ');
}

void ui::createLine(char style, int maxLength)
{
  std::cout << std::setfill(style) << std::setw(maxLength);
  std::cout << "" << std::endl << std::setfill(' ');
}