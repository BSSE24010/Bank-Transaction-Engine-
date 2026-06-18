//
// Created by AZKA on 12/15/2025.
//

#ifndef ATMNETWORK_H
#define ATMNETWORK_H


#include "CustomerRequest.h"

#include "ATM.h"
#include "TransactionProcessor.h"

#include "Transaction.h"
#include "BankingUtilities.h"
#include "BankAccount.h"
#include <iostream>
using namespace std;
#include <string>
#include "../all_structures.h"
#include "DateTime.h"

class ATMNetwork {
private:
    Array<ATM>* atms;             // Array to store ATMs
    Graph<int>* graph;      // Graph for storing distances between ATMs
    int networkSize;        // Maximum capacity


public:
    ATMNetwork(int maxSize)
    {
        networkSize=maxSize;
        //atmCount=0;
        atms=  new Array<ATM>(networkSize);
        graph= new Graph<int>(networkSize);
    }

    ~ATMNetwork()
    {
        delete atms;
        delete graph;
    }

    // ATM Management
    void addATM(ATM atm);
    int findATMIndex(string atmID);
    ATM* getATM(string atmID);

    // Network Connections
    void connectATMs(string atmID1, string atmID2, int distance);
    void disconnectATMs(string atmID1, string atmID2);
    void updateConnection(string atmID1, string atmID2, int newDistance);

    // Path Finding
    // void findShortestRoute(string startATMID, string endATMID);
    void findAllPaths(string startATMID);
    ATM findNearestATM(string currentATMID);
    void sortATMsByCash();

    // Network Analysis
    void displayNetwork();
    void displayConnections();
    void generateNetworkReport();
    //void optimizeCashDistribution();

    // Utility
    int getTotalATMs() const;
    int getTotalConnections();
    bool isConnected(string atmID1, string atmID2);
};

#endif //ATMNETWORK_H
