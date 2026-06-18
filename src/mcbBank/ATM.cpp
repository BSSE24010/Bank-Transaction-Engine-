//
// Created by AZKA on 12/15/2025.
//

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


//=============ATM====================
void ATM::displayATMInfo()
{
    cout << "ATM ID: " << atmID << endl;
    cout << "Location: " << location << endl;
    cout << "Cash Available: " << cashAvailable << "/" << cashCapacity << endl;
    cout << "Operational: " ;
    if(isOperational )
    {
        cout<<"YES....IT IS"<<endl;
    }
    else
    {
        cout<<"NO...IT ISN'T"<<endl;
    }
    cout << "Daily Transactions: " << dailyTransactions << endl;
}

bool ATM:: dispenseCash(double amount)
{
    if(!isOperational)
    {
        return false;
    }

    if(cashAvailable<amount)
    {
        return false;
    }


    cashAvailable=cashAvailable-amount;
    cout << "Dispensed: " << amount << endl;
    dailyTransactions++;
    return true;

}
void ATM:: refillCash(double amount)
{
    if(cashAvailable==cashCapacity)
    {
        cout<<"No cash needed....atm is full according to its capacity"<<endl;
        return;
    }
    double total=0;
    total=cashAvailable+amount;
    if(total>cashCapacity)
    {
        cout<<"adding amount is exceeding the capacity ....the ammount you can add to refill is: "
        <<cashCapacity-cashAvailable<<endl;

    }else
    {
        cashAvailable=cashAvailable+amount;

    }
}
void ATM:: setOperationalStatus(bool status)
{
    isOperational=status;
}
void ATM:: incrementTransaction()
{
    dailyTransactions++;
}
