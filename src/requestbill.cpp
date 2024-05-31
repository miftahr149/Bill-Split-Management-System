#include "ui.h"
#include <vector>
#include <string>
#include "utility.h"
#include <map>

using namespace std;

void ui::RequestBill::display()
{
  string name;
  int amount, select;
  ui::createHeader("Request New Bill Split");
  cout << endl;
  cout << "Type the name of the bill split : ";
  cin.ignore();
  getline(cin, name);
  cout << "Enter amount : ";
  cin >> amount;
  cout << "Add user : " << endl;

  auto userDatabase = storage::Database<storage::User>("storage/user.txt");
  for (auto element : userDatabase.getData())
  {
    auto userData = element.second;
    cout << userData.getName() << ", ";
  }
  
  vector<string> arrayName = {userInfo.getName()};
  
  cout << "\n1. Confirm\n" << "0. Back\n" << endl;
  while (true)
  {
    string userInput;
    
    cout << "Participant: ";
    for (int i = 0; i < arrayName.size(); i++)
    {
      cout << arrayName[i];
      if (i != arrayName.size() - 1)
      {
        cout << ", ";
      }
    }
    cout << endl;

    cin >> userInput;

    if (userInput == "1")
    {
      storage::BillSplit requestBillSplit;
      requestBillSplit.setName(name);

      float value = amount/arrayName.size();
      std::map<std::string, float> x;
      for(int i = 0; i < arrayName.size(); i++)
      {
        string name = arrayName[i];
        x[name] = value;
      }
      requestBillSplit.setDebtData(x);

      requestedBillSplit->add(requestBillSplit);
      break;
    }
    if (userInput == "0")
      break;
    
    string sign(userInput, 0, 1);
    userInput.erase(0, 1);

    if (!(sign == "+" ||  sign == "-"))
    {
      cout << "Invalid Sign!!" << endl;
      continue;
    }

    if (!userDatabase.find(userInput))
    {
      cout << "Invalid Name!!" << endl;
      continue;
    }

    int index = util::find(arrayName, userInput);
    if (sign == "+")
    {
      if (index != -1)
      {
        cout << "Name is Already in the list" << endl;
        continue;
      }

      arrayName.push_back(userInput);
    } else 
    {
      if (index == -1)
      {
        cout << "Name is not in the list" << endl;
        continue;
      }
      arrayName.erase(arrayName.begin() + index);
    }
  }

    return master->display();
}