//
// Created by AZKA on 12/15/2025.
//

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "BankingUtilities.h"
#include "BankAccount.h"
#include <iostream>
using namespace std;
#include <string>
#include "../all_structures.h"
#include "DateTime.h"


// ==================== TRANSACTION PROCESSING ====================

class Transaction {
private:
    string transactionID;
    string accountNumber;
    string transactionType;
    double amount;
    DateTime timestamp;
    bool isSuccessful;
    string description;

public:
    Transaction()
    {
        transactionID = "";
        accountNumber = "";
        transactionType = "";
        amount = 0.0;
        isSuccessful = false;
        description = "";
        timestamp = DateTime();
    }
    Transaction(string id, string accNum, string type, double amt, string desc);

    string getTransactionID() const{ return transactionID; }
    string getAccountNumber() const { return accountNumber; }
    string getTransactionType() const{ return transactionType; }
    double getAmount() const{ return amount;  }
    DateTime getTimestamp() const{ return timestamp; }
    bool getStatus() const{ return isSuccessful; }

    void setStatus(bool status){ isSuccessful=status; }
    void setTimestamp(DateTime dt){ timestamp=dt; }

    void displayTransaction();

    bool operator>(const Transaction& other) const;
    bool operator<(const Transaction& other) const;
    bool operator<=(const Transaction& other) const;
    bool operator>=(const Transaction& other) const;
    bool operator==(const Transaction& other) const;
};


#endif //TRANSACTION_H
