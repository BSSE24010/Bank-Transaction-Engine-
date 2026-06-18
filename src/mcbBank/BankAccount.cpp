//
// Created by AZKA on 12/15/2025.
//

#include "BankAccount.h"
#include <iostream>
using namespace std;
#include <string>
#include "../all_structures.h"
#include "DateTime.h"
// ========== BANKACCOUNT IMPLEMENTATION ==========

BankAccount::BankAccount(string accNum, string name, string cnic, double initialBalance, string type)
{
    accountNumber = accNum;
    accountHolderName = name;
    CNIC = cnic;
    balance = initialBalance;
    accountType = type;
    isActive = true;
    dateOpened = DateTime();
}

void BankAccount::recordInitialDeposit()
{
    if (balance > 0) {
        string d = string("Initial Deposit: ") + intToString(balance);
        transactionHistory.push_back(d);
    }
}

bool BankAccount::deposit(double amount)
{
    if (!isActive) return false;
    if (amount <= 0) return false;

    balance = balance + amount;

    string t = string("Deposited Amount: ") + intToString(amount) +
               string(" | Updated balance: ") + intToString(balance);
    transactionHistory.push_back(t);

    return true;
}

bool BankAccount::withdraw(double amount)
{
    if (!isActive) return false;
    if (amount <= 0) return false;

    if (balance < amount) {
        return false;
    }

    balance = balance - amount;

    string t = string("Withdrawal: ") + intToString(amount) +
               string(" | Updated balance: ") + intToString(balance);
    transactionHistory.push_back(t);

    return true;
}

void BankAccount::addTransaction(string transaction)
{
    transactionHistory.push_back(transaction);
}

void BankAccount::displayAccountInfo()
{
    cout << "------INFO OF ACCOUNT-------" << endl;
    cout << "Account Number: " << accountNumber << endl;
    cout << "Holder Name: " << accountHolderName << endl;
    cout << "CNIC: " << CNIC << endl;
    cout << "Account Type: " << accountType << endl;
    cout << "Balance: Rs. " << balance << endl;
    cout << "Status: " << (isActive ? "Active" : "Inactive") << endl;
    cout << "Date Opened: ";
    dateOpened.display();
}

void BankAccount::displayTransactionHistory()
{
    if (transactionHistory.isEmpty())
    {
        cout << "No transactions recorded.\n";
        return;
    }

    Node<string>* temp = transactionHistory.getHead();
    int i = 1;
    while (temp != nullptr) {
        cout << i << ") " << temp->getData() << endl;
        temp = temp->getNext();
        i++;
    }
}

void BankAccount::showBalance()
{
    cout << "Current balance: Rs. " << balance << endl;
}

bool BankAccount::operator<(const BankAccount& other) const
{
    return accountNumber < other.accountNumber;
}

bool BankAccount::operator>(const BankAccount& other) const
{
    return accountNumber > other.accountNumber;
}

bool BankAccount::operator==(const BankAccount& other) const
{
    return accountNumber == other.accountNumber;
}

ostream& operator<<(ostream& out, const BankAccount& acc) {
    out << acc.getAccountNumber();
    return out;
}
