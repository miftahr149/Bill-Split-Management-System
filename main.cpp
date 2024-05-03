#include <iostream>
#include "utility.h"
#include "storage.h"
int main()
{
  if (util::isFolderEmpty("storage"))
    util::initFolder();

  storage::Database<storage::User> userData(
      "storage/user.txt",
      [](storage::User &user, int i, std::string str)
      {
        if (i == 1)
          user.name = str;
        if (i == 2)
          user.password = str;
        if (i = 3)
          user.type = str;
      },
      [](std::ofstream &outputStream, int id, storage::User user)
      {
        outputStream << id << ",";
        outputStream << user.name << ",";
        outputStream << user.password << ",";
        outputStream << user.type;
        outputStream << std::endl;
      });

  storage::Database<storage::BillSplit> billSplitData(
      "storage/billSplit.txt",
      [](storage::BillSplit &billSplit, int id, std::string str) {
        
      },
      [](std::ofstream &outputStream, int id, storage::BillSplit billSplit) {

      });

  return 0;
}