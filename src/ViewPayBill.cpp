#include "ui.h"
#include <vector>

using namespace std;

//Payment Status page
void ui::ViewPayBill::display()
{
  int select;
  ui::createHeader("Payment Status");
  cout << endl;
  cout << "Current unpaid bill: " << endl;
  
  for (auto billSplitElement : this->billSplit->getData())
  {
    int id = billSplitElement.first;
    storage::BillSplit billSplitData = billSplitElement.second;

    auto participants = billSplitData.getDebtData();
    for (auto participant : participants)
    {
      std::string participant_name = participant.first;
      if (participant_name == userInfo.getName())
      {
        cout << id << ". " << billSplitData.getName() << " (" << participant.second << ")" << endl;
      }
    }
  }
  cout << "0. Back" << endl << "Select a number: ";
  cin >> select;
  
    if(select == 0)
    {
      return master->display();
    }
    else 
    {
      paybill(select);
    }

}

//Pay Bill Split page
void ui::ViewPayBill::paybill(int id)
{
  int select;
  auto billSplitData = billSplit->getData(id);

  auto participants = billSplitData.getDebtData();
  int amount = participants[userInfo.getName()];
  ui::createHeader("Pay Bill Split");
  cout << "Unpaid amount for " << billSplitData.getName() << " : " << amount << endl << endl;
  cout << "1. Pay\n" << "0. Back\n" << "Select a number: ";
  cin >> select;

    if(select == 0)
    {
    }
    else 
    {
      billSplitData.deleteParticipant(userInfo.getName());
      billSplit->update(id, billSplitData);
    }

    return display();
}