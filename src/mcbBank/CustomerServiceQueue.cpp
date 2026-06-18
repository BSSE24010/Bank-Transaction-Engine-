//
// Created by AZKA on 12/15/2025.
//

#include "CustomerServiceQueue.h"
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

//======= CUSTOMER SERVICE QUEUE==========
CustomerServiceQueue:: CustomerServiceQueue()
{
    nextTokenNumber=0;
    servedCustomers=0;
    totalTime=0;
}


   void CustomerServiceQueue:: addCustomer(string name, string requestType, int priority, int serviceTime)
    {
        nextTokenNumber++;
        CustomerRequest c( nextTokenNumber ,name, requestType, priority, serviceTime);

        if(priority<=2)
        {
            priorityQueue.enqueue(c);
        }
        else
        {
            regularQueue.enqueue(c);
        }

        cout<<"customer added to the queue"<<endl;
    }
    CustomerRequest CustomerServiceQueue:: serveNextCustomer()
    {

        if(!priorityQueue.isEmpty())
        {
            CustomerRequest c= priorityQueue.dequeue();
            servedCustomers++;
            totalTime=totalTime+c.getEstimatedServiceTime();
            return c;

        }else
        {
            if(!regularQueue.isEmpty())
            {
              CustomerRequest c= regularQueue.dequeue();
                servedCustomers++;
                totalTime=totalTime+c.getEstimatedServiceTime();
                return c;
            }else
            {
                cout<<"there is no customer in bank"<<endl;
                return CustomerRequest();
            }
        }
    }



    void CustomerServiceQueue:: displayQueue()
    {
    cout << "\n===== PRIORITY QUEUE =====\n";
       NodeQ<CustomerRequest> *temp=priorityQueue.getFrontNode();
        while (temp != nullptr)
        {
            CustomerRequest c = temp->getData();
            cout << "Token: " << c.getTokenNumber()
                 << ", Name: " << c.getCustomerName()
                 << ", Request: " << c.getRequestType()
                 << ", Priority: " << c.getPriority()
                 << ", Service Time: " << c.getEstimatedServiceTime() << " mins\n";
            temp = temp->getNext();
        }

        cout << "\n===== REGULAR QUEUE =====\n";
        temp = regularQueue.getFrontNode();
        while (temp != nullptr)
        {
            CustomerRequest c = temp->getData();
            cout << "Token: " << c.getTokenNumber()
                 << ", Name: " << c.getCustomerName()
                 << ", Request: " << c.getRequestType()
                 << ", Priority: " << c.getPriority()
                 << ", Service Time: " << c.getEstimatedServiceTime() << " mins\n";
            temp = temp->getNext();
        }

        cout << "\nTotal Customers Waiting: " << getQueueSize() << endl;
    }

    int CustomerServiceQueue:: getQueueSize()
    {
        return regularQueue.getSize()+ priorityQueue.getSize();
    }


    int CustomerServiceQueue:: getAverageWaitTime()
    {
        if(servedCustomers ==0)
        {
            return 5;
        }
       return totalTime/servedCustomers;
    }


    void CustomerServiceQueue:: generateQueueReport()
    {
        cout << "\n===== CUSTOMER SERVICE REPORT =====\n";
        cout << "Total Customers Served: " << servedCustomers << endl;
        cout << "Customers Waiting: " << getQueueSize() << endl;
        cout << "Average Wait Time: " << getAverageWaitTime() << " minutes\n";
    }
