#ifndef STORAGE_H
#define STORAGE

#include <iostream>
#include <map>
#include <functional>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>

namespace storage
{
  struct User
  {
    std::string name;
    std::string password;
    std::string type;
  };

  struct BillSplit
  {
  };

  class RequestedBillSplit
  {
  };

  std::vector<int> findSubStrIndex(std::string str, char sep)
  {
    std::vector<int> result = {-1};
    for (int i = str.find(sep); i < str.length(); i = str.find(sep, i + 1))
      result.push_back(i);
    result.push_back(str.length());
    return result;
  }

  std::vector<std::string> split(std::string str, char sep = ',')
  {
    std::vector<std::string> result;
    auto sepIndex = findSubStrIndex(str, sep);
    for (int i = 1; i < sepIndex.size(); i++)
    {
      int start = sepIndex[i - 1] + 1;
      int length = sepIndex[i] - start;
      result.push_back(str.substr(start, length));
    }
    return result;
  }

  template <typename T>
  class Database
  {
    int highestId;
    std::string dirname;
    std::map<int, T> data;
    std::function<void(std::ofstream&, int, T)> saveFunc;

  public:
    Database(
        std::string dirname,
        std::function<void(T &, int, std::string)> extractFunc,
        std::function<void(std::ofstream&, int, T)> saveFunc)
        : dirname(dirname), highestId(0)
    {
      std::ifstream inputStream(this->dirname);

      while (!inputStream.eof())
      {
        std::string inputResult;
        std::getline(inputStream, inputResult); 
        
        if (inputResult == "") break;

        auto extract = split(inputResult);
        int id = std::stoi(extract[0]);

        if (std::max(id, this->highestId) == id)
          this->highestId = id;

        T newData;
        for (int i = 1; i < extract.size(); i++)
          extractFunc(newData, i, extract[i]);

        this->add(newData, id);
      }

      inputStream.close();
    }

    void add(T newData, int id = -1)
    {
      if (id == -1)
        id = ++this->highestId;
      this->data[id] = newData;
    }

    void update(int id, T newData){this->data[id] = newData;}

    void save()
    {
      std::ofstream outputStream(this->dirname);
      for (const auto element : data)
        this->saveFunc(outputStream, element.first, element.second);
      outputStream.close();
    }

    void deleteElement(int id) { this->data.erase(id); }
    T getData(int id) { return this->data[id]; }
  };
}

#endif