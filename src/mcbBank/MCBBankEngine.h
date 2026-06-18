//
// Created by AZKA on 12/15/2025.
//

#ifndef MCBBANKENGINE_H
#define MCBBANKENGINE_H

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


class MCBBankEngine {
private:
    BinarySearchTree<BankAccount*> accountDatabase;  //  POINTER-BASED
    CustomerServiceQueue serviceQueue;
    ATMNetwork atmNetwork;
    TransactionProcessor* transactionProcessor;
    DateTime currentSystemTime;

public:
    MCBBankEngine();
    ~MCBBankEngine();

    void setSystemTime(DateTime dt);
    DateTime getSystemTime() const;
    //void updateSystemTime(int hours, int minutes);

    void openAccount(string name, string cnic, double initialBalance, string type);
    void closeAccount(string accountNumber);
    BankAccount* searchAccount(string accountNumber);
    void displayAccountDetails(string accountNumber);

    void depositMoney(string accountNumber, double amount);
    void withdrawMoney(string accountNumber, double amount);
    void transferMoney(string fromAccount, string toAccount, double amount);
    void payBill(string accountNumber, double amount, string billType);

    void addCustomerToQueue(string name, string requestType, int priority, int serviceTime);
    void serveCustomer();
    void displayServiceQueue();

    void addATMToNetwork(ATM atm);
    void connectATMsInNetwork(string atmID1, string atmID2, int distance);
    void findOptimalCashVanRoute(string startATM, string endATM);
    void displayATMNetwork();


    void generateDailyReport();
    void generateMonthlyReport();
    void generateYearlyReport();
    void displayBankStatistics();

    void displayMainMenu();
    void run();
};


#endif //MCBBANKENGINE_H
