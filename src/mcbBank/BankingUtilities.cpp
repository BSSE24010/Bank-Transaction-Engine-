//
// Created by AZKA on 12/15/2025.
//

#include "BankingUtilities.h"
#include "BankAccount.h"
#include <iostream>
using namespace std;
#include <string>
#include "../all_structures.h"
#include "DateTime.h"
// ========== BANKING UTILITIES ==========

int BankingUtilities::accountCounter = 100000;
int BankingUtilities::transactionCounter = 1;
int BankingUtilities::applicationCounter = 5000;
int BankingUtilities::employeeCounter = 200;

string BankingUtilities::generateAccountNumber()
{
    string acc = string("MCB") + intToString(accountCounter);
    accountCounter++;
    return acc;
}

string BankingUtilities::generateTransactionID()
{
    string id = string("TXN") + intToString(transactionCounter);
    transactionCounter++;
    return id;
}

string BankingUtilities::generateApplicationID()
{
    string id = string("APP") + intToString(applicationCounter);
    applicationCounter++;
    return id;
}

string BankingUtilities::generateEmployeeID()
{
    string id = string("EMP") + intToString(employeeCounter);
    employeeCounter++;
    return id;
}

string BankingUtilities::dateTimeToString(DateTime dt)
{
    return intToString(dt.getDay()) + string("/") +
           intToString(dt.getMonth()) + string("/") +
           intToString(dt.getYear()) + string("   ") +
           intToString(dt.getHour()) + string(":") +
           intToString(dt.getMinute()) + string(":") +
           intToString(dt.getSecond());
}

bool BankingUtilities::validateCNIC(string cnic)
{
    if (getLength(cnic) != 13)
    {
        return false;
    }

    for (int i = 0; i < 13; i++)
    {
        if (cnic[i] < '0' || cnic[i] > '9')
        {
            return false;
        }
    }

    return true;
}

bool BankingUtilities::validateAccountNumber(string accountNumber)
{
    if (getLength(accountNumber) < 4) return false;

    if (accountNumber[0] !='M' || accountNumber[1] !='C' || accountNumber[2] !='B')
    {
        return false;
    }

    for (int i = 3; i < getLength(accountNumber); i++) {
        if (accountNumber[i] <'0' || accountNumber[i] >'9')
        {
            return false;
        }
    }
    return true;
}

double BankingUtilities::calculateInterest(double principal, double rate, int months)
{
    double year = months/12.0;
    double interest = (principal * rate * year) / 100.0;
    return interest;
}

int BankingUtilities::generateOTP()
{
    int otp = (accountCounter + transactionCounter) % 9000 + 1000;
    return otp;
}

DateTime BankingUtilities::getCurrentDateTime()
{
    DateTime dt;
    cout << "Enter current date & time:\n";
    dt.input();
    return dt;
}
