#include "ui.h"

void ui::ViewUser::displayTable(
    std::string id, std::string name,
    std::string password, std::string type)
{
  std::cout << std::setw(5) << id;
  std::cout << std::setw(19) << name;
  std::cout << std::setw(18) << password;
  std::cout << std::setw(18) << type;
  std::cout << std::endl;
}

void ui::ViewUser::displayUserList()
{
  for (auto element : this->userDatabase->getData())
  {
    auto id = element.first;
    auto data = element.second;

    displayTable(
        std::to_string(id), data.getName(),
        data.getPassword(), data.getType());
  }
}

void ui::ViewUser::createUser()
{
  storage::User user;
  std::string userInput;

  user.setType("USER");

  std::cout << std::setw(20) << "username" << std::setw(3) << ":";
  std::cin >> userInput;
  user.setName(userInput);

  std::cout << std::setw(20) << "password" << std::setw(3) << ":";
  std::cin >> userInput;
  user.setPassword(userInput);

  std::cout << std::setw(20) << "confirm password" << std::setw(3) << ":";
  std::cin >> userInput;
  std::cout << std::endl;

  if (userInput == user.getPassword()) {
    this->userDatabase->add(user);
    return this->display();
  }

  std::cout << "Password and Confirm Password are not the same!" << std::endl;
  return this->createUser();
}

void ui::ViewUser::display()
{
  this->userDatabase = new storage::Database<storage::User>("storage/user.txt");

  ui::createHeader("User List");
  this->displayTable("ID", "Name", "Password", "Type");
  ui::createLine();
  this->displayUserList();
  ui::createLine();

  this->getOption(
      {'1', '2'},
      {"Create User", "Delete User"},
      {[this]()
       { this->createUser(); },
       []()
       { std::cout << "Deleting User" << std::endl; }},
      true);
}