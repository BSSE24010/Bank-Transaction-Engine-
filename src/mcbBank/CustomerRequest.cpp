//
// Created by AZKA on 12/15/2025.
//

#include "CustomerRequest.h"

#include "TransactionProcessor.h"

#include "Transaction.h"
#include "BankingUtilities.h"
#include "BankAccount.h"
#include <iostream>
using namespace std;
#include <string>
#include "../all_structures.h"
#include "DateTime.h"


void CustomerRequest::displayRequest()
{
    cout << "-----------------------------\n";
    cout << "Token Number: " << tokenNumber << endl;
    cout << "Customer Name: " << customerName << endl;
    cout << "Request Type: " << requestType << endl;
    cout << "Priority: " << priority << endl;
    cout << "Estimated Service Time: " << estimatedServiceTime << " minutes\n";
    cout << "Arrival Time: ";
    arrivalTime.display();
    cout << "-----------------------------\n";
}

bool CustomerRequest::operator<(const CustomerRequest& other) const
{
    return priority < other.priority;
}

bool CustomerRequest::operator>(const CustomerRequest& other) const
{
    return priority > other.priority;
}

CustomerRequest::CustomerRequest(int token, string name, string type, int pri, int serviceTime)
{
    tokenNumber = token;
    customerName = name;
    requestType = type;
    priority = pri;
    estimatedServiceTime = serviceTime;

    cout << "Enter arrival time for customer:\n";
    arrivalTime.input();
}
