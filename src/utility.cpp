#include "utility.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>

bool util::isFolderEmpty(std::string folderDirname)
{
  auto folder = std::filesystem::directory_iterator(folderDirname);
  auto emptyFolder = std::filesystem::directory_iterator(folderDirname);
  return folder == emptyFolder;
}

void util::initFolder(std::string folderDirname)
{
  std::vector<std::string> fileNames = {
      "billSplit", "user", "requestedBillSplit"};

  for (const auto fileName : fileNames)
  {
    std::string fileDirname(folderDirname + "/" + fileName + ".txt");
    std::ofstream outputStream(fileDirname);
    if (fileName == "user")
      outputStream << "00001,admin,12345,ADMIN";
    else
      outputStream << 0 << std::endl;
    outputStream.close();
  }
}