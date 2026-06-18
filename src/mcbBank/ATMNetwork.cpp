//
// Created by AZKA on 12/15/2025.
//

#include "ATMNetwork.h"

#include "ATM.h"

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


void ATMNetwork::addATM(ATM atm)
{
    {
        if(atms->getSize()>=networkSize)
        {
            cout<<"no further links can be added"<<endl;
            return;
        }

        atms->append(atm);
       // atmCount++;
        cout<<"network added to the atm"<<endl;
    }
}

int ATMNetwork::findATMIndex(string atmID)
{
    for(int i=0; i<atms->getSize(); i++)
    {
        ATM* atm = atms->getDataAtIndex(i);
        if(atm != nullptr && atm->getATMID() == atmID)
        {
            return i;
        }
    }
    return -1;
}

ATM* ATMNetwork::getATM(string atmID)
{
    int idx = findATMIndex(atmID);
    if(idx != -1)
    {
        return atms->getDataAtIndex(idx);
    }

    return nullptr;
}

// ===== CONNECTION MANAGEMENT =====
void ATMNetwork::connectATMs(string atmID1, string atmID2, int distance)
{
    int idx1=findATMIndex(atmID1);
    int idx2= findATMIndex(atmID2);

    if(idx1 !=-1 && idx2 !=-1)
    {
        graph->addEdge(idx1, idx2, distance);
        cout << "Connect " << atmID1 << " and " << atmID2 << " with distance of " << distance <<"."<< endl;
    }
    else
    {
        cout << "atm not found!\n";
    }

}

void ATMNetwork::disconnectATMs(string atmID1, string atmID2)
{
    int idx1 =findATMIndex(atmID1);
    int idx2 =findATMIndex(atmID2);

    if(idx1 != -1 && idx2 != -1)
    {
        graph->deleteEdge(idx1, idx2);
        cout << "disconnected " << atmID1 << " and " << atmID2 << endl;
    }
    else
        cout << "atm not found!\n";
}

void ATMNetwork::updateConnection(string atmID1, string atmID2, int newDistance)
{
    int idx1 = findATMIndex(atmID1);
    int idx2 = findATMIndex(atmID2);
    if(idx1 !=-1 && idx2 !=-1)
    {
        graph->addEdge(idx1, idx2, newDistance);
        cout << "Updated connection " <<atmID1 << "-" <<atmID2 << "to distance of " <<newDistance << endl;
    }
    else
    {
        cout << "atm not found!\n";
    }

}

// ===== NETWORK INFO =====
void ATMNetwork::displayNetwork()
{
    cout << "\n=ATM NETWORK\n";
    for(int i=0;i<atms->getSize();i++)
    {
        ATM* atm = atms->getDataAtIndex(i);
        if(atm != nullptr)
        {
            cout << "--- ATM" << (i+1) << " ---\n";
            atm->displayATMInfo();
            cout << endl;
        }
    }
}

void ATMNetwork::displayConnections()
{
    cout << "\nFULL ATM NETWORK THROUGH GRAPH \n";
    graph->displayGraph();
}

int ATMNetwork::getTotalATMs() const
{
    return atms->getSize();
}
int ATMNetwork::getTotalConnections()
{
    return graph->getEdgesCount();
}

bool ATMNetwork::isConnected(string atmID1, string atmID2)
{
    int idx1 = findATMIndex(atmID1);
    int idx2 = findATMIndex(atmID2);
    if(idx1 != -1 && idx2 != -1)
    {
        return graph->checkEdgeStatus(idx1, idx2);
    }
    return false;
}

// ===== NEAREST ATM =====
ATM ATMNetwork::findNearestATM(string currentATMID)
{
    int idx =findATMIndex(currentATMID);
    if(idx == -1) return ATM();

    int nearest = -1;
    int minDistance = 1000; // large number

    for(int i=0;i<atms->getSize();i++)
    {
        if(i!=idx && graph->checkEdgeStatus(idx,i))
        {
            int d = graph->getEdgeWeight(idx,i);
            if(d<minDistance)
            {
                minDistance=d;
                nearest=i;
            }
        }
    }

    if(nearest != -1)
    {
        ATM* atmPtr = atms->getDataAtIndex(nearest);
        if(atmPtr != nullptr)
        {
            return *atmPtr;  // Dereference to return copy
        }
    }

    return ATM();
}

void ATMNetwork:: sortATMsByCash()
{
    cout << "\nSorting ATMs by cash capacity...\n";
    atms->insertionSort();  //Template sorting function
    cout << "ATMs sorted successfully!\n";
}

