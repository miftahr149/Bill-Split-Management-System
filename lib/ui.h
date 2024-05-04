#ifndef UI_H
#define UI_H

#include "storage.h"
#include <iomanip>
#include <functional>

namespace ui
{
  // handle the login process for a user. It takes a Database object of User type as an argument
  storage::User loginUI(storage::Database<storage::User> userData)
  {
    // collect user input
    std::string username, password;

    std::cout << std::setw(20) << std::left << "Username"
              << ":";
    std::cin >> username;
    std::cout << std::setw(20) << std::left << "Password"
              << ":";
    std::cin >> password;

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

  void createHeader(std::string header, int maxLength = 60, int space = 2)
  {
    int length = header.length();
    int left = (maxLength - (length + 2 * space)) / 2;
    int right = maxLength - (length + left);

    std::cout << std::setfill('=') << std::setw(left) << "";
    std::cout << std::setfill(' ') << std::setw(space) << "";
    std::cout << header << std::setw(space) << "";
    std::cout << std::setfill('=') << std::setw(right);
    std::cout << std::endl;
  }

  void createLine(char style = '=', int maxLength = 60)
  {
    std::cout << std::setfill(style) << std::setw(maxLength);
    std::cout << "" << std::endl;
  }

  class MainMenu
  {
    storage::User userInfo;
    storage::Database<storage::BillSplit> billSplit;
    storage::Database<storage::BillSplit> requestedBillSplit;

    void displayUser()
    {
      // display input;
      std::cout << "1. view current bill" << std::endl;
      std::cout << "2. request new bill" << std::endl;
      std::cout << std::endl;
      std::cout << "0. Exit" << std::endl;
      createLine();

      // get user input
      char userOption;
      std::cout << "Please insert your option: ";
      std::cin.get(userOption);

      if (userOption == '0')
        return;
      if (userOption == '1')
      {
        // ViewBills(this);
        return;
      }
      if (userOption == '2')
      {
        // requestBills(this);
        return;
      }

      std::cout << "you option is invalid! please enter correct option"; 
      std::cout << std::endl;
      this->displayUser();
    }
    void displayAdmin();

  public:
    MainMenu(
        storage::User userInfo,
        storage::Database<storage::BillSplit> billSplit,
        storage::Database<storage::BillSplit> requestedBillSplit)
    {
      this->userInfo = userInfo;
      this->billSplit = billSplit;
      this->requestedBillSplit = requestedBillSplit;
      this->display();
    }

    void display()
    {
      std::cout << "Welcome Back " << this->userInfo.getName();
      std::cout << std::endl
                << std::endl;
      createHeader("Main Menu");
      std::cout << std::endl;
      createLine();

      if (userInfo.getType() == "USER")
        this->displayUser();
      else
        this->displayAdmin();
    }
  };
}

#endif