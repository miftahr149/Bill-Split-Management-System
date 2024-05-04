#include <iostream>
#include "utility.h"
#include "storage.h"

int main()
{
  if (util::isFolderEmpty("storage"))
    util::initFolder();

  storage::Database<storage::User> userData("storage/user.txt");
  storage::Database<storage::BillSplit> billSplitData("storage/billSplit.txt");
  
  std::string str = "storage/requestedBillSplit"; 
  storage::Database<storage::BillSplit> requestedBillSplit(str);

  return 0;
}