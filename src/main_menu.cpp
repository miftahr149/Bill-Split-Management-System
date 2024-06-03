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
            [this]()
            {ui::ViewPayBill(this).display();},
            [this]()
            {ui::RequestBill(this).display();},
            []()
            {},
        });
  else
    getOption(
        {'1', '2', '3', '4', '0'},
        {"View Current Payment", "View Requested Payment",
         "Add Payment", "View User", "Exit"},
        {
            [this]()
            { ui::ViewPayBill(this).display(); },
            [this]()
            { ui::ViewRequestedPayment(this).display(); },
            [this]()
            { ui::RequestBill(this).display(); },
            [this]()
            { ui::ViewUser(this).display(); },
            []()
            {},
        });

  std::cout << std::endl;
}