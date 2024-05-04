#include "ui.h"
#include "storage.h"
#include <iomanip>
#include <iostream>

storage::User ui::loginUI(storage::Database<storage::User> userData)
{
  std::string username, password;

  std::cout << std::setw(20) << "Username"
            << ":";
  std::cin >> username;
  std::cout << std::setw(20) << "Password"
            << ":";
  std::cin >> password;

  int id = userData.find(username);
  if (id == -1)
  {
    std::cout << "couldn't find such username, please try again" << std::endl;
    return ui::loginUI(userData);
  }

  auto user = userData.getData(id);
  if (password != user.getPassword())
  {
    std::cout << "Password is incorrect, please try again";
    return ui::loginUI(userData);
  }

  return user;
}