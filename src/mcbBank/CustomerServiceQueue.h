//
// Created by AZKA on 12/15/2025.
//

#ifndef CUSTOMERSERVICEQUEUE_H
#define CUSTOMERSERVICEQUEUE_H


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
class CustomerServiceQueue {
private:
    LinkedQueue<CustomerRequest> regularQueue;
    LinkedQueue<CustomerRequest> priorityQueue;
    int nextTokenNumber;
    int servedCustomers;
    int totalTime;

public:
    CustomerServiceQueue();

    void addCustomer(string name, string requestType, int priority, int serviceTime);
    CustomerRequest serveNextCustomer();
    void displayQueue();

    int getQueueSize();
    int getAverageWaitTime();
    void generateQueueReport();
};

#endif //CUSTOMERSERVICEQUEUE_H
