//
// Created by AZKA on 12/15/2025.
//

#ifndef ATM_H
#define ATM_H


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



class ATM {
private:
    string atmID;
    string location;
    double cashAvailable;
    double cashCapacity;
    bool isOperational;
    int dailyTransactions;

public:
    ATM()
    {
        atmID="";
        location="";
        cashAvailable=0.0;
        cashCapacity=0.0;
        isOperational=true;
        dailyTransactions=0;
    }
    ATM(string id, string loc, double capacity)
    {
        atmID=id;
        location=loc;
        cashCapacity=capacity;
        cashAvailable=capacity;
        isOperational=true;
        dailyTransactions=0;
    }

    string getATMID() const
    {
        return atmID;
    }
    string getLocation() const
    {
        return location;
    }
    double getCashAvailable() const
    {
        return cashAvailable;
    }
    bool getOperationalStatus() const
    {
        return isOperational;
    }
    int getDailyTransactions() const
    {
        return dailyTransactions;
    }

    bool dispenseCash(double amount);
    void refillCash(double amount);
    void setOperationalStatus(bool status);
    void incrementTransaction();
    void displayATMInfo();

    bool operator<(const ATM& other) const {
        return this->cashCapacity < other.cashCapacity;
    }

    bool operator>(const ATM& other) const {
        return this->cashCapacity > other.cashCapacity;
    }

    bool operator<=(const ATM& other) const {
        return this->cashCapacity <= other.cashCapacity;
    }

    bool operator>=(const ATM& other) const {
        return this->cashCapacity >= other.cashCapacity;
    }

    bool operator==(const ATM& other) const {
        return this->atmID == other.atmID;
    }
};

#endif //ATM_H
