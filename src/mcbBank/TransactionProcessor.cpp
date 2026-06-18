//
// Created by AZKA on 12/15/2025.
//

#include "TransactionProcessor.h"

#include "Transaction.h"
#include "BankingUtilities.h"
#include "BankAccount.h"
#include <iostream>
using namespace std;
#include <string>
#include "../all_structures.h"
#include "DateTime.h"
#include "helper.h"


// ========== TRANSACTION PROCESSOR ==========

bool TransactionProcessor::processDeposit(string accountNumber, double amount)
{
    if (accountDatabase == nullptr) {
        cout << "database not initialized" << endl;
        return false;
    }

    if (amount <= 0) {
        cout << "invalid deposit amount" << endl;
        return false;
    }

    // Use helper function
    TreeNodeB<BankAccount*>* accNode = findAccountByNumber(accountDatabase, accountNumber);

    if (accNode == nullptr)
    {
        cout << "account not found" << endl;
        return false;
    }

    BankAccount* account = accNode->getData1();

    if (!account->getActiveStatus())
    {
        cout << "account is inactive" << endl;
        return false;
    }

    bool depositSuccess = account->deposit(amount);

    if (!depositSuccess) {
        cout << "deposit failed" << endl;
        return false;
    }

    string transID = BankingUtilities::generateTransactionID();
    Transaction t(transID, accountNumber, "Deposit", amount, "Cash Deposit");
    t.setStatus(depositSuccess);

    addTransaction(t);

    cout << "Deposit successful.... New balance: Rs. " << account->getBalance() << endl;

    return true;
}

bool TransactionProcessor::processWithdrawal(string accountNumber, double amount)
{
    if (accountDatabase == nullptr)
    {
        cout << "database not initialized" << endl;
        return false;
    }

    if (amount <= 0) {
        cout << "invalid withdrawal amount!" << endl;
        return false;
    }

    // Use helper function
    TreeNodeB<BankAccount*>* accNode = findAccountByNumber(accountDatabase, accountNumber);

    if (accNode == nullptr)
    {
        cout << "account not found" << endl;
        return false;
    }

    BankAccount* account = accNode->getData1();

    if (!account->getActiveStatus())
    {
        cout << "account is inactive" << endl;
        return false;
    }

    if (account->getBalance() < amount)
    {
        cout << " insufficient balance" << endl;
        cout << "available balance: Rupees " << account->getBalance() << endl;
        return false;
    }

    bool withdrawalSuccess = account->withdraw(amount);

    if (!withdrawalSuccess)
    {
        cout << "withdrawal failed" << endl;
        return false;
    }

    string transID = BankingUtilities::generateTransactionID();
    Transaction t(transID, accountNumber, "Withdrawal", amount, "Cash Withdrawal");
    t.setStatus(withdrawalSuccess);

    addTransaction(t);

    cout << "Withdrawal successful.... New balance: Rs. " << account->getBalance() << endl;

    return true;
}

bool TransactionProcessor::processTransfer(string fromAccount, string toAccount, double amount)
{
    if (accountDatabase == nullptr)
    {
        cout << "Database not initialized" << endl;
        return false;
    }

    if (amount <= 0)
    {
        cout << "invalid transfer amount" << endl;
        return false;
    }

    if (!BankingUtilities::validateAccountNumber(fromAccount))
    {
        cout << "invalid source account number" << endl;
        return false;
    }

    if (!BankingUtilities::validateAccountNumber(toAccount))
    {
        cout << "invalid destination account number!" << endl;
        return false;
    }

    // Use helper function
    TreeNodeB<BankAccount*>* fromNode = findAccountByNumber(accountDatabase, fromAccount);

    if (fromNode == nullptr)
    {
        cout << "source account not found" << endl;
        return false;
    }

    TreeNodeB<BankAccount*>* toNode = findAccountByNumber(accountDatabase, toAccount);

    if (toNode == nullptr)
    {
        cout << "destination account not found" << endl;
        return false;
    }

    BankAccount* fromAcc = fromNode->getData1();
    BankAccount* toAcc = toNode->getData1();

    if (!fromAcc->getActiveStatus())
    {
        cout << "source account is inactive" << endl;
        return false;
    }

    if (!toAcc->getActiveStatus())
    {
        cout << "destination account is inactive" << endl;
        return false;
    }

    if (fromAcc->getBalance() < amount)
    {
        cout << "insufficient balance" << endl;
        cout << "available Rs. " << fromAcc->getBalance() << endl;
        return false;
    }

    bool withdrawSuccess = fromAcc->withdraw(amount);
    if (!withdrawSuccess)
    {
        return false;
    }

    bool depositSuccess = toAcc->deposit(amount);
    if (!depositSuccess)
    {
        fromAcc->deposit(amount);
        cout << " transfer failed" << endl;
        return false;
    }

    string transID1 = BankingUtilities::generateTransactionID();
    string desc1 = string("transfer to ") + toAccount;
    Transaction t1(transID1, fromAccount, "transfer out", amount, desc1);
    t1.setStatus(true);
    addTransaction(t1);

    string transID2 = BankingUtilities::generateTransactionID();
    string desc2 = string("transfer from ") + fromAccount;
    Transaction t2(transID2, toAccount, "transfer in", amount, desc2);
    t2.setStatus(true);
    addTransaction(t2);

    cout << "transfer successful!!!" << endl;
    cout << "From balance: " << fromAcc->getBalance() << endl;
    cout << "To balance:  " << toAcc->getBalance() << endl;

    return true;
}

bool TransactionProcessor::processBillPayment(string accountNumber, double amount, string billType)
{
    if (accountDatabase == nullptr)
    {
        cout << "Database not initialized" << endl;
        return false;
    }

    if (amount <= 0) {
        cout << " Invalid bill amount!" << endl;
        return false;
    }

    // Use helper function
    TreeNodeB<BankAccount*>* accNode = findAccountByNumber(accountDatabase, accountNumber);

    if (accNode == nullptr)
    {
        cout << "Account not found!" << endl;
        return false;
    }

    BankAccount* account = accNode->getData1();

    if (!account->getActiveStatus())
    {
        cout << "Account is inactive!" << endl;
        return false;
    }

    if (account->getBalance() < amount)
    {
        cout << " Insufficient balance..." << endl;
        cout << "Available: Rupees " << account->getBalance() << endl;
        return false;
    }

    bool paymentSuccess = account->withdraw(amount);

    if (!paymentSuccess)
    {
        cout << " Bill payment failed!" << endl;
        return false;
    }

    string transID = BankingUtilities::generateTransactionID();
    string description = billType + string(" Bill Payment");
    Transaction t(transID, accountNumber, "Bill Payment", amount, description);
    t.setStatus(paymentSuccess);

    addTransaction(t);
    cout << "Bill payment successful!" << endl;
    cout << "New balance: Rs. " << account->getBalance() << endl;

    return true;
}

void TransactionProcessor::addTransaction(Transaction trans)
{
    dailyTransactions.append(trans);

    TreeNodeB<BankAccount*>* node = findAccountByNumber(accountDatabase, trans.getAccountNumber());

    if (node != nullptr)
    {
        BankAccount* acc = node->getData1();

        string rec = trans.getTransactionID() + string(" - ") +
                     trans.getTransactionType() + string(" - Rs.") +
                     BankingUtilities::doubleToString(trans.getAmount());

        acc->addTransaction(rec);
    }
}

void TransactionProcessor::sortTransactionsByAmount()
{
    cout << "\n=== Sorting Transactions by Amount (Merge Sort) ===" << endl;
    dailyTransactions.mergeSort();
    cout << "Transactions sorted successfully!" << endl;
}

void TransactionProcessor::sortTransactionsByTime()
{
    cout << "\n=== Sorting Transactions by Time (Quick Sort) ===" << endl;
    dailyTransactions.quickSort();
    cout << "Transactions sorted successfully!" << endl;
}

void TransactionProcessor::generateDailyReport()
{

    cout << " -----------DAILY TRANSACTION REPORT------------" << endl;

    int totalTransactions = dailyTransactions.getSize();
    if (totalTransactions == 0)
    {
        cout << "No transactions today" << endl;
        return;
    }
    double totalDeposits =0.0;
    double totalWithdrawals =0.0;
    double totalTransfers =0.0;
    double totalBillPayments =0.0;

    int depCount = 0;
    int withCount = 0;
    int transCount = 0;
    int billCount = 0;

    for (int i = 0; i < totalTransactions; i++)
    {
        Transaction* t = dailyTransactions.getDataAtIndex(i);

        if (t != nullptr)
        {
            string type = t->getTransactionType();
            double amount = t->getAmount();

            if (type == "Deposit")
            {
                totalDeposits =totalDeposits+ amount;
                depCount++;
            }
            else if (type == "Withdrawal")
            {
                totalWithdrawals = totalWithdrawals+ amount;
                withCount++;
            }
            else if (type == "Transfer Out" || type == "Transfer In")
            {
                totalTransfers =totalTransfers+ amount;
                transCount++;
            }
            else if (type == "Bill Payment") {
                totalBillPayments = totalBillPayments+ amount;
                billCount++;
            }
        }
    }

    cout << "\nTotal Transactions: " << totalTransactions << endl;
    cout << "----------------------------------------" << endl;

    cout << "\nDeposits:" << endl;
    cout << "  Count: " << depCount << endl;
    cout << "  Amount: Rs. " << totalDeposits << endl;

    cout << "\nWithdrawals:" << endl;
    cout << "  Count: " << withCount << endl;
    cout << "  Amount: Rs. " << totalWithdrawals << endl;

    cout << "\nTransfers:" << endl;
    cout << "  Count: " << transCount << endl;
    cout << "  Amount: Rs. " << totalTransfers << endl;

    cout << "\nBill Payments:" << endl;
    cout << "  Count: " << billCount << endl;
    cout << "  Amount: Rs. " << totalBillPayments << endl;

}

void TransactionProcessor::displayTransactions()
{

    cout << "ALL TRANSACTIONS" << endl;
    int totalTransactions = dailyTransactions.getSize();

    if (totalTransactions == 0)
    {
        cout << "No transactions to display!" << endl;
        return;
    }

    cout << "\nSr. | Transaction ID | Account No. | Type          | Amount    | Status" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < totalTransactions; i++)
    {
        Transaction* t = dailyTransactions.getDataAtIndex(i);

        if (t != nullptr)
        {
            cout << (i + 1) << ".  | ";
            cout << t->getTransactionID() << " | ";
            cout << t->getAccountNumber() << " | ";
            cout << t->getTransactionType() << " | ";
            cout << "Rs. " << t->getAmount() << " | ";
            if(t->getStatus() )
            {
               cout<<   "SUCCESS"<<endl;
            }
            else
            {
                cout<<"FAILED"<< endl;
            }
        }
    }

    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "Total: " << totalTransactions << endl;
    cout << "========================================\n" << endl;
}
