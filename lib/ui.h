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
    int right = maxLength - (length + left + 2 * space);

    std::cout << std::setfill('=') << std::setw(left) << "";
    std::cout << std::setfill(' ') << std::setw(space) << "";
    std::cout << header << std::setw(space) << "";
    std::cout << std::setfill('=') << std::setw(right) << "";
    std::cout << std::endl;
  }

  void createLine(char style = '=', int maxLength = 60)
  {
    std::cout << std::setfill(style) << std::setw(maxLength);
    std::cout << "" << std::endl;
  }

  class UIMaster
  {
  protected:
    storage::User userInfo;
    storage::Database<storage::BillSplit> billSplit;
    storage::Database<storage::BillSplit> requestedBillSplit;
    ui::UIMaster *master;

    void getOption(
        std::vector<char> options,
        std::vector<std::string> labels,
        std::vector<std::function<void()>> functions,
        bool back = false)

    {

      if (back)
      {
        options.push_back('0');
        labels.push_back("Back");
        functions.push_back(
            [this]()
            { this->master->display(); });
      }

      for (int i = 0; i < options.size(); i++)
        std::cout << options[i] << "."
                  << " " << labels[i] << std::endl;

      std::cout << std::endl;
      createLine();

      char userOption;
      std::cout << "Please insert your Option: ";
      std::cin >> userOption;

      for (int i = 0; i < options.size(); i++)
        if (userOption == options[i])
        {
          functions[i]();
          return;
        }

      std::cout << "your option is invalid! please enter correct option";
      std::cout << std::endl
                << std::endl;
      getOption(options, labels, functions);
    }

  public:
    explicit UIMaster(
        storage::User userInfo,
        storage::Database<storage::BillSplit> &billSplit,
        storage::Database<storage::BillSplit> &requestedBillSplit)
    {
      this->billSplit = billSplit;
      this->userInfo = userInfo;
      this->requestedBillSplit = requestedBillSplit;
    }

    explicit UIMaster(ui::UIMaster *master)
    {
      this->master = master;

      this->requestedBillSplit = master->requestedBillSplit;
      this->billSplit = master->billSplit;
      this->userInfo = master->userInfo;
    }

    virtual void display() { std::cout << "Using UIMaster Display" << std::endl; }
  };

  class ViewUser : UIMaster
  {
  public:
    using UIMaster::UIMaster;

    void display() override
    {
      std::cout << "X" << std::endl;
      this->master->display();
    }
  };

  class MainMenu : UIMaster
  {

  public:
    using UIMaster::UIMaster;

    void display() override
    {
      std::cout << "Welcome Back " << this->userInfo.getName();
      std::cout << std::endl;
      createHeader("Main Menu");
      std::cout << std::endl;

      if (userInfo.getType() == "USER")
        getOption(
            {'1', '2', '0'},
            {"View Current Bill", "Request New Bill", "Exit"},
            {
                []()
                { std::cout << " Hello World"; },
                []()
                { std::cout << " Hello World"; },
                []()
                { std::cout << " Hello World"; },
            });
      else
        getOption(
            {'1', '2', '3', '4', '0'},
            {"View Current Payment", "View Requested Payment",
             "Add Payment", "View User", "Exit"},
            {
                []()
                { std::cout << "Hello World"; },
                []()
                { std::cout << "Hello World"; },
                []()
                { std::cout << "Hello World"; },
                [this]()
                {
                  ui::ViewUser *x = new ViewUser(this);
                  x->display();
                },
                []()
                { std::cout << "Hello World"; },
            });
    }
  };
}

#endif