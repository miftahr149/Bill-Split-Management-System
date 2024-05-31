#include "ui.h"
#include "utility.h"

void ui::ViewUser::displayUserRow(
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

    displayUserRow(
        std::to_string(id), data.getName(),
        data.getPassword(), data.getType());
  }
}

void ui::ViewUser::displayUserTable()
{
  this->displayUserRow("ID", "Name", "Password", "Type");
  ui::createLine();
  this->displayUserList();
  ui::createLine();
}

void ui::ViewUser::createUser()
{
  storage::User user;
  std::string userInput;

  user.setType("USER");

  ui::createHeader("Create User");

  std::cout << std::setw(20) << "username" << std::setw(3) << ":";
  std::cin >> userInput;
  user.setName(userInput);

  std::cout << std::setw(20) << "password" << std::setw(3) << ":";
  std::cin >> userInput;
  user.setPassword(userInput);

  std::cout << std::setw(20) << "confirm password" << std::setw(3) << ":";
  std::cin >> userInput;
  std::cout << std::endl;

  if (userInput == user.getPassword())
  {
    this->userDatabase->add(user);
    return this->display();
  }

  std::cout << "Password and Confirm Password are not the same!" << std::endl;
  return this->createUser();
}

void ui::ViewUser::deleteUser()
{
  ui::createHeader("Delete User");
  this->displayUserTable();
  std::cout << std::endl;

  std::cout << "Press <1> to confirm to delete" << std::endl;
  std::cout << "Press <2> to go back" << std::endl;
  std::cout << std::endl;

  std::cout << "Input the name you want to delete: " << std::endl;

  std::vector<std::string> accumulator;
  std::string userInput;

  while (true)
  {
    std::cout << "List Delete Name: ";

    for (int i = 0; i < accumulator.size(); i++)
    {
      std::string name = accumulator[i];
      std::cout << name;
      if (i != accumulator.size() - 1)
        std::cout << ",";
    }
    std::cout << std::endl;
    
    std::cin >> userInput;

    if (util::find(accumulator, userInput) != -1)
    {
      std::cout << "this name is already in the delete list!" << std::endl;
      continue;
    }

    if (userInput == "1")
    {
      std::cout << "Deleting Listed Name" << std::endl;
      std::cout << std::endl;
      for (auto name : accumulator)
      {
        std::cout << "Deleting User '" << name << "'" << std::endl;
        int id = this->userDatabase->find(name);
        this->userDatabase->deleteElement(id);
      }
      this->display();
      break;
    }

    if (userInput == "0")
    {
      std::cout << std::endl;
      this->display();
      break;
    }

    if (userInput == this->userInfo.getName())
    {
      std::cout << "You Can't Delete yourself!" << std::endl;
      continue;
    }

    accumulator.push_back(userInput);
  }
}

void ui::ViewUser::display()
{
  this->userDatabase = new storage::Database<storage::User>("storage/user.txt");

  ui::createHeader("User List");
  this->displayUserTable();
  this->getOption(
      {'1', '2'},
      {"Create User", "Delete User"},
      {[this]()
       { this->createUser(); },
       [this]()
       { this->deleteUser(); }},
      true);
}

ui::ViewUser::~ViewUser()
{
  std::cout << "Deleting View User" << std::endl;
}