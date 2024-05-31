#include "ui.h"
#include <functional>

using namespace std;

void ui::ViewRequestedPayment::requestDetail(storage::BillSplit request)
{
    cout << "Bill Split Name: " << request.getName() << endl;
    for (auto element : request.getDebtData())
    {
        cout << element.first << " RM" << element.second << endl;
    }

    cout << endl;
    cout << "1. Accept" << endl;
    cout << "2. Reject" << endl;
    cout << "0. Back" << endl;
    createLine();
    cout << "Please insert your option: ";

    string input;
    cin >> input;

    if (input == "0")
    {
    }
    else if (input == "1")
    {
        int id = requestedBillSplit->find(request.getName());

        billSplit->add(request, id);

        requestedBillSplit->deleteElement(id);
    }
    else if (input == "2")
    {
        int id = requestedBillSplit->find(request.getName());
        requestedBillSplit->deleteElement(id);
    }
    display();
}

void ui::ViewRequestedPayment::display()
{
    ui::createHeader("View Requested Payment");
    cout << endl;
    auto requestList = requestedBillSplit->getData();

    int counter = 1;
    string input;
    for (auto element : requestList)
    {
        cout << counter << ". ";
        cout << element.second.getName() << std::endl;
        counter++;
    }
    cout << "0. Back" << endl
         << endl;

    createLine();
    cout << "Please insert your option: ";
    cin >> input;

    if (input == "0")
    {
        master->display();
        return;
    }

    cout << endl;
    createHeader("Bill Details");
    cout << endl;

    counter = 1;
    for (auto element : requestList)
    {
        if (counter == stoi(input))
        {
            requestDetail(element.second);
        }
        counter++;
    }
}
