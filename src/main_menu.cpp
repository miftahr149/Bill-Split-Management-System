#include "ui.h"

void ui::MainMenu::display()
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