//
// Created by AZKA on 12/15/2025.
//

#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <iostream>
using namespace std;
#include <string>
#include "../all_structures.h"
#include "DateTime.h"
class BankAccount {
private:
    string accountNumber;
    string accountHolderName;
    string CNIC;
    double balance;
    string accountType; // Savings, Current, Business
    DateTime dateOpened;
    bool isActive;
    List<string> transactionHistory;

public:
    BankAccount()
    {
        accountNumber=" ";
        accountHolderName=" ";
        CNIC=" ";
        balance=0.0;
        accountType=" ";
        isActive=false;
    }

    int getLength(string s)
    {
        int count=0;
        while (s[count] != '\0')
        {
            count++;
        }
        return count;
    }

    string reverseString(string s)
    {
        int len=getLength(s);
        string rev="";
        for(int i=len-1; i>=0; i--)
        {
            rev=rev+s[i];
        }
        return rev;
    }

    string intToString(double num)
    {
        int intNum = num;
        double fracNum = num - intNum;

        string temp = "";
        if(intNum == 0)
        {
            temp = "0";
        }

        while(intNum > 0)
        {
            int t = (intNum) % 10;
            char c = '0' + t;
            temp = temp + c;
            intNum = intNum / 10;
        }

        string intString = reverseString(temp);

        string FracString = "";
        int fracDigitIntoNum = (int)(fracNum * 100);
        int d1 = fracDigitIntoNum / 10;
        int d2 = fracDigitIntoNum % 10;

        FracString = FracString + (char)('0' + d1);
        FracString = FracString + (char)('0' + d2);

        return intString + "." + FracString;
    }

    BankAccount(string accNum, string name, string cnic, double initialBalance, string type);

    // Getters
    string getAccountNumber() const{ return accountNumber; }
    string getAccountHolderName() const{ return accountHolderName; };
    string getCNIC() const {return CNIC; };
    double getBalance() const { return balance; }
    string getAccountType() const{ return accountType;};
    bool getActiveStatus() const { return isActive; }
    DateTime getDateOpened() const{ return dateOpened; };

    // Setters
    void setBalance(double amount){ balance=amount; }
    void setActiveStatus(bool status){ isActive=status; }
    void setDateOpened(DateTime dt){ dateOpened=dt; };

    // Operations
    bool deposit(double amount);
    bool withdraw(double amount);
    void addTransaction(string transaction);
    void displayAccountInfo();
    void displayTransactionHistory();
    void showBalance();
    void recordInitialDeposit();

    // Operator overloading for BST comparison
    bool operator<(const BankAccount& other) const;
    bool operator>(const BankAccount& other) const;
    bool operator==(const BankAccount& other) const;
};

#endif //BANKACCOUNT_H
