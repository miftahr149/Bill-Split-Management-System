#include <iostream>
#include "utility.h"
#include "storage.h"
#include "ui.h"

int main()
{
  if (util::isFolderEmpty("storage"))
    util::initFolder();

  storage::Database<storage::User> userData("storage/user.txt");
  storage::Database<storage::BillSplit> billSplitData("storage/billSplit.txt");
  
  std::string str = "storage/requestedBillSplit.txt"; 
  storage::Database<storage::BillSplit> requestedBillSplit(str);

  auto user = ui::loginUI(userData);
  ui::MainMenu mainMenu(user, billSplitData, requestedBillSplit);
  mainMenu.display();

  return 0;
}