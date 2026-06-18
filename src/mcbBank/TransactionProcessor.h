//
// Created by AZKA on 12/15/2025.
//

#ifndef TRANSACTIONPROCESSOR_H
#define TRANSACTIONPROCESSOR_H

#include "Transaction.h"
#include "BankingUtilities.h"
#include "BankAccount.h"
#include <iostream>
using namespace std;
#include <string>
#include "../all_structures.h"
#include "DateTime.h"


class TransactionProcessor {
private:
    Array<Transaction> dailyTransactions;
    BinarySearchTree<BankAccount*>* accountDatabase;  // POINTER-BASED

public:
    TransactionProcessor(BinarySearchTree<BankAccount*>* accDB): dailyTransactions(50)
    {
        if (accDB == nullptr)
        {
            cout << "ERROR: Account database is NULL!" << endl;
            accountDatabase = nullptr;
            return;
        }

        accountDatabase=accDB;
        cout << "TransactionProcessor created successfully\n";
    }

    bool processDeposit(string accountNumber, double amount);
    bool processWithdrawal(string accountNumber, double amount);
    bool processTransfer(string fromAccount, string toAccount, double amount);
    bool processBillPayment(string accountNumber, double amount, string billType);

    void addTransaction(Transaction trans);
    void sortTransactionsByAmount();
    void sortTransactionsByTime();
    void generateDailyReport();
    void displayTransactions();
};


#endif //TRANSACTIONPROCESSOR_H
