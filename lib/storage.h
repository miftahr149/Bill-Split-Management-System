#ifndef STORAGE_H
#define STORAGE

#include <iostream>
#include <map>
#include <functional>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <type_traits>

namespace storage
{
  class MasterClass
  {
  public:
    virtual void extract(std::vector<std::string>) {}
    virtual void save(std::ofstream &) {}
  };

  class BillSplit : MasterClass
  {
    std::string name;
    int bill;
    std::vector<std::string> debt;
    std::vector<std::string> paymentSuccessful;

  public:
    BillSplit() {}
    BillSplit(std::vector<std::string> array) { this->extract(array); }

    void extract(std::vector<std::string> array)
    {
      int counter = 0;
      int nextDestination = 2;
      int counterCycle = 0;

      for (int i = 0; i < array.size(); i++)
      {
        if (i == 0)
        {
          this->name = array[i];
          continue;
        }

        if (i == 1)
        {
          this->bill = std::stoi(array[i]);
          continue;
        }

        if (i == nextDestination)
        {
          counter = std::stoi(array[i]);
          nextDestination += counter + 1;
          counterCycle++;
          continue;
        }

        if (counterCycle == 1)
          this->debt.push_back(array[i]);
        else
          this->paymentSuccessful.push_back(array[i]);
        counter--;
      }
    }

    void save(std::ofstream &output)
    {
      output << this->name << ",";
      output << this->bill << ",";

      output << debt.size() << ",";
      for (auto peopleName : this->debt)
        output << peopleName << ",";

      output << this->paymentSuccessful.size() << ",";
      for (auto peopleName : this->paymentSuccessful)
      {
        output << peopleName;
        if (peopleName == this->paymentSuccessful.back())
          output << std::endl;
        else
          output << ",";
      }
    }

    BillSplit(const BillSplit &obj1)
    {
      this->name = obj1.name;
      this->bill = obj1.bill;
      this->debt = obj1.debt;
      this->paymentSuccessful = obj1.paymentSuccessful;
    }

    std::string getName() const { return this->name; }
    int getBill() const { return this->bill; }
    std::vector<std::string> getDebt() const { return this->debt; }
    std::vector<std::string> getSuccessfulPayment() const
    {
      return this->paymentSuccessful;
    }
  };

  class User : MasterClass
  {
    std::string name;
    std::string password;
    std::string type;

  public:
    User() {}
    User(std::vector<std::string> array) { this->extract(array); }

    User(const User &obj)
    {
      this->name = obj.name;
      this->password = obj.password;
      this->type = obj.type;
    }

    void extract(std::vector<std::string> array) override
    {
      this->name = array[0];
      this->password = array[1];
      this->type = array[2];
    }

    void save(std::ofstream &output) override
    {
      output << name << ',';
      output << password << ',';
      output << type << std::endl;
    }

    bool operator==(std::string username) { return (this->name == username); }

    void setName(std::string name) { this->name = name; }
    void setPassword(std::string password) { this->password = password; }
    void setType(std::string type) { this->type = type; }

    std::string getName() const { return this->name; }
    std::string getPassword() const { return this->password; }
    std::string getType() const { return this->type; }
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
    std::function<void(std::ofstream &, int, T)> saveFunc;

  public:
    Database(std::string dirname) : dirname(dirname), highestId(0)
    {
      std::ifstream inputStream(this->dirname);

      while (!inputStream.eof())
      {
        std::string inputResult;
        std::getline(inputStream, inputResult);

        if (inputResult == "")
          break;

        auto extract = split(inputResult);
        int id = std::stoi(extract[0]);
        extract.erase(extract.begin());

        if (std::max(id, this->highestId) == id)
          this->highestId = id;

        this->add(T(extract), id);
      }

      inputStream.close();
    }

    void add(T newData, int id = -1)
    {
      if (id == -1)
        id = ++this->highestId;
      this->data[id] = newData;
    }

    void update(int id, T newData) { this->data[id] = newData; }

    void save()
    {
      std::ofstream outputStream(this->dirname);
      for (auto element : data)
      {
        outputStream << element.first << ",";
        element.second.save(outputStream);
      }
      outputStream.close();
    }

    void deleteElement(int id) { this->data.erase(id); }
    T getData(int id) { return this->data[id]; }

    int find(std::string name)
    {
      for (auto element : data)
        if (element.second == name)
          return element.first;
      return -1;
    }
  };
}

#endif