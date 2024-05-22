#pragma once

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
  // This class is used to determine the body for the database's data type
  class MasterClass
  {
  public:
    // use to extract string into into respective class attributes
    virtual void extract(std::vector<std::string>) {}

    // use to write from attributes data to string format in the given file
    virtual void save(std::ofstream &) {}
  };

  // this class contain the name of the bill split, the amount of bill in RM,
  // who has paid, and who hasn't paid yet.
  class BillSplit : MasterClass
  {
    std::string name;
    std::map<std::string, float> debtData;

  public:
    BillSplit() {}

    BillSplit(std::vector<std::string> array) { this->extract(array); }

    void extract(std::vector<std::string> array)
    {
      for (int i = 0; i < array.size(); i++)
      {
        if (i == 0)
        {
          this->name = array[i];
          continue;
        }

        int startKeyIndex = 0;
        int endKeyIndex = array[i].find(':');

        std::string debtName = array[i].substr(0, endKeyIndex - startKeyIndex);

        int startValueIndex = endKeyIndex + 1;
        int endValueIndex = array[i].length() - 1;
        int valueLength = endValueIndex - startValueIndex;
        std::string strDebtValue = array[i].substr(
            startValueIndex, valueLength);
        
        this->debtData[debtName] = std::stof(strDebtValue);
      }
    }

    void save(std::ofstream &output)
    {
      output << this->name;
      for (auto element : this->debtData)
      {
        output << ",";
        output << "(" << element.first << ":"; 
        output << element.second  << ")";
      }
      output << std::endl;
    }

    BillSplit(const BillSplit &obj1)
    {
      this->name = obj1.name;
      this->debtData = obj1.debtData;
    }

    std::string getName() const { return this->name; }
    std::map<std::string, float> getDebtData() const {return this->debtData;}
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

  // this function is use to find all the index of char 'sep' in string 'str'
  inline std::vector<int> findSubStrIndex(std::string str, char sep)
  {
    std::vector<int> result = {-1};
    for (int i = str.find(sep); i < str.length(); i = str.find(sep, i + 1))
      result.push_back(i);
    result.push_back(str.length());
    return result;
  }

  // split the string into an array of string using char 'sep'
  inline std::vector<std::string> split(std::string str, char sep = ',')
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

  // The Database class is a template class that provides a simple way to
  // manage and persist data. It is designed to work with any data type T that
  // can be serialized and deserialized.
  //
  // ### Attributes:
  // highestId: An integer that keeps track of the highest ID assigned to an
  //            element in the database
  // dirname: the directory where the database file is stored
  // data: store the data elements, where each element is associated with a
  //       unique integer ID
  template <typename T>
  class Database
  {
    int highestId;
    std::string dirname;
    std::map<int, T> data;

  public:
    // initializes the dirname and highestId, and loads data from the file into the data map
    Database(std::string dirname) : dirname(dirname), highestId(0)
    {
      std::ifstream inputStream(this->dirname);

      std::string strHighestId;
      std::getline(inputStream, strHighestId);
      this->highestId = std::stoi(strHighestId);

      while (!inputStream.eof())
      {
        std::string inputResult;
        std::getline(inputStream, inputResult);

        if (inputResult == "")
          break;

        auto extract = split(inputResult);
        int id = std::stoi(extract[0]);
        extract.erase(extract.begin());

        this->add(T(extract), id);
      }

      inputStream.close();
    }

    Database(const Database &obj)
    {
      this->data = obj.data;
      this->highestId = obj.highestId;
      this->dirname = obj.dirname;
    }
    Database() {}

    // adds a new data element to the database. If no ID is provided, it assigns the next available ID
    void add(T newData, int id = -1)
    {
      if (id == -1)
        id = ++this->highestId;
      this->data[id] = newData;
      this->save();
    }

    // updates the data element associated with the given ID
    void update(int id, T newData)
    {
      this->data[id] = newData;
      this->save();
    }

    // saves all the data elements in the database to the file
    void save()
    {
      std::ofstream outputStream(this->dirname);
      outputStream << this->highestId << std::endl;
      for (auto element : data)
      {
        outputStream << element.first << ",";
        element.second.save(outputStream);
      }
      outputStream.close();
    }

    // removes the data element associated with the given ID from the database
    void deleteElement(int id)
    {
      this->data.erase(id);
      this->save();
    }

    // retrieves the data element associated with the given ID
    T getData(int id) { return this->data[id]; }
    std::map<int, T> getData() const { return this->data; }

    // finds the ID of the data element that matches the given name
    int find(std::string name)
    {
      for (auto element : data)
        if (element.second == name)
          return element.first;
      return -1;
    }
  };
}
