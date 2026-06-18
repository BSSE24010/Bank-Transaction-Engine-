//
// Created by AZKA on 12/15/2025.
//

#include "Transaction.h"
#include "BankingUtilities.h"
#include "BankAccount.h"
#include <iostream>
using namespace std;
#include <string>
#include "../all_structures.h"
#include "DateTime.h"

// ========== TRANSACTION IMPLEMENTATION ==========

Transaction::Transaction(string id, string accNum, string type, double amt, string desc)
{
    transactionID = id;
    accountNumber = accNum;
    transactionType = type;
    amount = amt;
    description = desc;
    isSuccessful = false;
    timestamp = DateTime();
}

void Transaction::displayTransaction()
{
    cout << "-----------------------------\n";
    cout << "Transaction ID: " << transactionID << endl;
    cout << "Account Number: " << accountNumber << endl;
    cout << "Type: " << transactionType << endl;
    cout << "Amount: Rs. " << amount << endl;
    cout << "Status: " << (isSuccessful ? "Success" : "Failed") << endl;
    cout << "Description: " << description << endl;
    cout << "Timestamp: ";
    timestamp.display();
    cout << "-----------------------------\n";
}
//
// bool Transaction::operator<(const Transaction& other) const
// {
//     if (timestamp.getYear() != other.timestamp.getYear())
//         return timestamp.getYear() < other.timestamp.getYear();
//
//     if (timestamp.getMonth() != other.timestamp.getMonth())
//         return timestamp.getMonth() < other.timestamp.getMonth();
//
//     if (timestamp.getDay() != other.timestamp.getDay())
//         return timestamp.getDay() < other.timestamp.getDay();
//
//     if (timestamp.getHour() != other.timestamp.getHour())
//         return timestamp.getHour() < other.timestamp.getHour();
//
//     if (timestamp.getMinute() != other.timestamp.getMinute())
//         return timestamp.getMinute() < other.timestamp.getMinute();
//
//     return timestamp.getSecond() < other.timestamp.getSecond();
// }
bool Transaction::operator<(const Transaction& other) const
{
    return amount < other.amount;
}

bool Transaction::operator>(const Transaction& other) const
{
    return amount > other.amount;
}

bool Transaction::operator<=(const Transaction& other) const
{
    return amount <= other.amount;
}

bool Transaction::operator>=(const Transaction& other) const
{
    return amount >= other.amount;
}

bool Transaction::operator==(const Transaction& other) const {
    return transactionID == other.transactionID;
}
