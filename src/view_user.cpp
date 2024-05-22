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

void ui::ViewUser::displayUserList(
    storage::Database<storage::User> userDatabase)
{
  for (auto element : userDatabase.getData())
  {
    auto id = element.first;
    auto data = element.second;

    displayTable(
      std::to_string(id), data.getName(), 
      data.getPassword(), data.getType());
  }
}

void ui::ViewUser::display()
{
  auto *userDatabase = new storage::Database<storage::User>("storage/user.txt");
  
  ui::createHeader("User List");
  this->displayTable("ID", "Name", "Password", "Type");
  ui::createLine();
  this->displayUserList(*userDatabase);
  ui::createLine();

  this->getOption(
      {'1', '2'},
      {"Create User", "Delete User"},
      {[]()
       { std::cout << "Creating User" << std::endl; },
       []()
       { std::cout << "Deleting User" << std::endl; }},
      true);
}