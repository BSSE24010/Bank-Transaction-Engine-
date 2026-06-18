//
// Created by AZKA on 12/15/2025.
//

#ifndef CUSTOMERREQUEST_H
#define CUSTOMERREQUEST_H


//#include "CustomerRequest.h"

#include "TransactionProcessor.h"

#include "Transaction.h"
#include "BankingUtilities.h"
#include "BankAccount.h"
#include <iostream>
using namespace std;
#include <string>
#include "../all_structures.h"
#include "DateTime.h"


class CustomerRequest {
private:
    int tokenNumber;
    string customerName;
    string requestType;
    int priority; // set priority btw 1 to 5
    DateTime arrivalTime;
    int estimatedServiceTime;

public:
    CustomerRequest()
    {
        tokenNumber=0;
        customerName="";
        requestType="";
        priority = 5;
        estimatedServiceTime = 0;
    }
    CustomerRequest(int token, string name, string type, int pri, int serviceTime);

    int getTokenNumber() const{return tokenNumber;}
    string getCustomerName() const{return customerName;};
    string getRequestType() const{return requestType;};
    int getPriority() const{return priority;}
    DateTime getArrivalTime() const{return arrivalTime;};
    int getEstimatedServiceTime() const{return estimatedServiceTime;}

    void setArrivalTime(DateTime dt)
    {
        arrivalTime=dt;
    }
    void displayRequest();
    bool operator<(const CustomerRequest& other) const;
    bool operator>(const CustomerRequest& other) const;
};

#endif //CUSTOMERREQUEST_H
