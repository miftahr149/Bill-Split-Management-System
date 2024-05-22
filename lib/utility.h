#pragma once

#include <iostream>
#include <vector>

namespace util
{
  bool isFolderEmpty(std::string);
  void initFolder(std::string = "Storage");

  template <typename T>
  int find(std::vector<T> array, T findValue)
  {
    for (int i = 0; i < array.size(); i++)
      if (array[i] == findValue)
        return i;
    return -1;
  }
}