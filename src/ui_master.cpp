#include "ui.h"

void ui::UIMaster::getOption(
    std::vector<char> options,
    std::vector<std::string> labels,
    std::vector<std::function<void()>> functions,
    bool back)

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
      std::cout << std::endl;
      functions[i]();
      return;
    }

  std::cout << "your option is invalid! please enter correct option";
  std::cout << std::endl
            << std::endl;
  getOption(options, labels, functions);
}

ui::UIMaster::UIMaster(
    storage::User userInfo,
    storage::Database<storage::BillSplit>& billSplit,
    storage::Database<storage::BillSplit>& requestedBillSplit)
{
  this->billSplit = &billSplit;
  this->userInfo = userInfo;
  this->requestedBillSplit = &requestedBillSplit;
}

ui::UIMaster::UIMaster(ui::UIMaster *master)
{
  this->master = master;

  this->requestedBillSplit = master->requestedBillSplit;
  this->billSplit = master->billSplit;
  this->userInfo = master->userInfo;
}