//
// Created by AZKA on 12/15/2025.
//

#include "MCBBankEngine.h"

#include "TransactionProcessor.h"
//
//#include "Transaction.h"
//#include "BankingUtilities.h"
//#include "BankAccount.h"
//#include <iostream>
//using namespace std;
//#include <string>
//#include "all_structures.h"
//#include "DateTime.h"

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
#include "helper.h"


MCBBankEngine::MCBBankEngine()
    : atmNetwork(10)
{
    transactionProcessor = new TransactionProcessor(&accountDatabase);
}

MCBBankEngine::~MCBBankEngine()
{
    delete transactionProcessor;
}
void MCBBankEngine::setSystemTime(DateTime dt)
{
    currentSystemTime = dt;
    cout << "System time updated to: ";
    currentSystemTime.display();
}

DateTime MCBBankEngine::getSystemTime() const
{
    return currentSystemTime;
}


// ==================== ACCOUNT MANAGEMENT ====================

void MCBBankEngine::openAccount(string name, string cnic, double initialBalance, string type)
{
    cout << "\nOpening New Account: "<< endl;
    if (!BankingUtilities::validateCNIC(cnic)) {
        cout << " Invalid CNIC .... Must be 13 digits." << endl;
        return;
    }

    if (initialBalance < 0) {
        cout << " Initial balance cannot be less than zero!" << endl;
        return;
    }

    string accNum = BankingUtilities::generateAccountNumber();
    BankAccount* newAccount = new BankAccount(accNum, name, cnic, initialBalance, type);
    newAccount->setDateOpened(currentSystemTime);
    newAccount->recordInitialDeposit();
    accountDatabase.insertNodeInBST(newAccount);

    cout << "\naccount created successfully" << endl;
    cout << "Account Number: " << accNum << endl;
    cout << "Account Holder: " << name << endl;
    cout << "Account Type: " << type << endl;
    cout << "Initial Balance: Rupees. " << initialBalance << endl;
}

void MCBBankEngine::closeAccount(string accountNumber)
{
    cout << "\n Closing Account: " << endl;
    if (!BankingUtilities::validateAccountNumber(accountNumber))
    {
        cout << " Invalid account number " << endl;
        return;
    }

    TreeNodeB<BankAccount*>* node = findAccountByNumber(&accountDatabase, accountNumber);

    if (node==nullptr)
    {
        cout << "Account not found." << endl;
        return;
    }
    BankAccount* acc = node->getData1();
    if (acc->getBalance() > 0)
    {
        cout << "Account balance  " << acc->getBalance() << endl;
        cout << "Please withdraw money before closing the account." << endl;
        return;
    }
    acc->setActiveStatus(false);
    cout << "Account " << accountNumber << "has been closed successfully." << endl;
}

BankAccount* MCBBankEngine::searchAccount(string accountNumber)
{
    if (!BankingUtilities::validateAccountNumber(accountNumber))
    {
        cout <<" Invalid account no..... "<< endl;
        return nullptr;
    }
    TreeNodeB<BankAccount*>* node= findAccountByNumber(&accountDatabase, accountNumber);

    if (node == nullptr)
    {
        return nullptr;
    }
    return node->getData1();
}

void MCBBankEngine::displayAccountDetails(string accountNumber)
{
    cout << "\n--- Searching for Account ---" << endl;
    BankAccount* acc = searchAccount(accountNumber);
    if (acc == nullptr) {
        cout << " Account not found!!!!" << endl;
        return;
    }
    acc->displayAccountInfo();

    cout << "\nTransaction History:" << endl;
    acc->displayTransactionHistory();
}

// ==================== TRANSACTION OPERATIONS ====================

void MCBBankEngine::depositMoney(string accountNumber, double amount)
{
    cout << "\nProcessing Deposit: " << endl;
    if (transactionProcessor->processDeposit(accountNumber, amount))
    {
        cout << "Deposit transaction is successful!!!" << endl;
    }
}

void MCBBankEngine::withdrawMoney(string accountNumber, double amount)
{
    cout << "\nProcessing Withdrawal: " << endl;
    if (transactionProcessor->processWithdrawal(accountNumber, amount))
    {
        cout << "  Withdrawal transaction is successful!!!!" << endl;
    }
}

void MCBBankEngine::transferMoney(string fromAccount, string toAccount, double amount)
{
    cout << "\nProcessing Transfer: " << endl;
    if (transactionProcessor->processTransfer(fromAccount, toAccount, amount))
    {
        cout << "Transfer transaction is successful........" << endl;
    }
}

void MCBBankEngine::payBill(string accountNumber, double amount, string billType)
{
    cout << "\n Processing Bill Payment: " << endl;
    if (transactionProcessor->processBillPayment(accountNumber, amount, billType))
    {
        cout << " Bill payment transaction is successful!!!!!!" << endl;
    }
}

// ==================== CUSTOMER SERVICE QUEUE ====================

void MCBBankEngine::addCustomerToQueue(string name, string requestType, int priority, int serviceTime)
{
    cout << "\n Add Customer to Service Queue: " << endl;
    serviceQueue.addCustomer(name, requestType, priority, serviceTime);
}

void MCBBankEngine::serveCustomer()
{
    cout << "\nServe Next Customer: " << endl;
    CustomerRequest served = serviceQueue.serveNextCustomer();

    if (served.getTokenNumber()!=0)
    {
        cout << "\nCustomer Served:" << endl;
        served.displayRequest();
    }
}

void MCBBankEngine::displayServiceQueue()
{
    serviceQueue.displayQueue();
}

// ==================== ATM NETWORK MANAGEMENT ====================

void MCBBankEngine::addATMToNetwork(ATM atm)
{
    cout << "\n Adding ATM to Network: " << endl;
    atmNetwork.addATM(atm);
}

void MCBBankEngine::connectATMsInNetwork(string atmID1, string atmID2, int distance)
{
    cout << "\n Connecting ATMs: " << endl;
    atmNetwork.connectATMs(atmID1, atmID2, distance);
}
//
// void MCBBankEngine::findOptimalCashVanRoute(string startATM, string endATM)
// {
//     cout << "\n--- Finding Optimal Cash Van Route ---" << endl;
//    // atmNetwork.findShortestRoute(startATM, endATM);
// }

void MCBBankEngine::displayATMNetwork()
{
    atmNetwork.displayNetwork();
}

// ==================== REPORTS & STATISTICS ====================

void MCBBankEngine::generateDailyReport()
{
    cout << "\n=================================================" << endl;
    cout << "║          DAILY BANK REPORT                     ║" << endl;
    cout << "===================================================" << endl;

    cout << "\n Date & Time: ";
    currentSystemTime.display();
    cout << endl;

    cout << "\n--- TRANSACTION DETSILS ---" << endl;
    transactionProcessor->generateDailyReport();

    cout << "\n--- CUSTOMER SERVICE DETAILS ---" << endl;
    serviceQueue.generateQueueReport();

    cout << "\n--- ATM NETWORK DETAILS ---" << endl;
    cout << "Total ATMs in Network: " << atmNetwork.getTotalATMs() << endl;
    cout << "Total Connections: " << atmNetwork.getTotalConnections() << endl;

    cout << "\n==================================================\n" << endl;
}

void MCBBankEngine::generateMonthlyReport()
{
    cout <<"\n==================================================" <<endl;
    cout <<"║         MONTHLY BANK REPORT                    ║" <<endl;
    cout <<"===================================================" <<endl;

    cout<< "\nMonth: " << currentSystemTime.getMonth()
         << "/" << currentSystemTime.getYear() << endl;

    cout<< "\n--- MONTHLY STATISTICS ---" <<endl;
    transactionProcessor->generateDailyReport();

    cout<< "\n--- CUSTOMER SERVICE PERFORMANCE ---" <<endl;
    serviceQueue.generateQueueReport();
    cout <<"Average Wait Time: "<<serviceQueue.getAverageWaitTime()<<" minutes" << endl;

    cout <<"\n--- ATM NETWORK DETAILS ---" <<endl;
    cout <<"Total ATMs: " <<atmNetwork.getTotalATMs() << endl;

    cout << "\n====================================================\n" << endl;
}

void MCBBankEngine::generateYearlyReport()
{
    cout << "\n╔════════════════════════════════════════════════╗" << endl;
    cout << "║          YEARLY BANK REPORT                    ║" << endl;
    cout << "╚════════════════════════════════════════════════╝" << endl;

    cout << "\nReport Year: " << currentSystemTime.getYear() << endl;

    cout << "\n--- YEARLY OVERVIEW ---" << endl;
    cout << "This feature will aggregate monthly data for complete year analysis." << endl;

    transactionProcessor->generateDailyReport();

    cout << "\n╚════════════════════════════════════════════════╝\n" << endl;
}

void MCBBankEngine::displayBankStatistics()
{
    cout << "\n=================================================" << endl;
    cout << "║        BANK STATISTICS DASHBOARD                ║" << endl;
    cout << "===================================================" << endl;

    cout << "\nCurrent System Time: ";
    currentSystemTime.display();

    cout << "\n--- ACCOUNT STATISTICS ---" << endl;
    cout << "Total Active Accounts: [Count from BST]" << endl;

    cout << "\n--- TRANSACTION STATISTICS ---" << endl;
    transactionProcessor->displayTransactions();

    cout << "\n--- CUSTOMER SERVICE STATISTICS ---" << endl;
    cout << "Customers in Queue: " << serviceQueue.getQueueSize() << endl;
    cout << "Average Wait Time: " << serviceQueue.getAverageWaitTime() << " minutes" << endl;

    cout << "\n--- ATM NETWORK STATISTICS ---" << endl;
    cout << "Total ATMs: " << atmNetwork.getTotalATMs() << endl;
    cout << "Network Connections: " << atmNetwork.getTotalConnections() << endl;

    cout << "\n============================================\n" << endl;
}

// ==================== MENU SYSTEM ====================

void MCBBankEngine::displayMainMenu()
{
    cout << "\n╔════════════════════════════════════════════════╗" << endl;
    cout << "║   MCB BANK FINTECH ENGINE - MAIN MENU         ║" << endl;
    cout << "╚════════════════════════════════════════════════╝" << endl;
    cout << "\n1.  Account Management" << endl;
    cout << "2.  Transaction Processing" << endl;
    cout << "3.  Customer Service Queue" << endl;
    cout << "4.  ATM Network Management" << endl;
    cout << "5.  Reports & Analytics" << endl;
    cout << "6.  Bank Statistics" << endl;
    cout << "7.  System Time Settings" << endl;
    cout << "8.  Exit System" << endl;
    cout << "\nEnter your choice: ";
}

// ==================== RUN METHOD ====================

void MCBBankEngine::run()
{
    int mainChoice;

    do {
        displayMainMenu();
        cin >> mainChoice;

        switch (mainChoice) {
            case 1: {
                // Account Management Menu
                int accChoice;
                do {
                    cout << "\n--- ACCOUNT MANAGEMENT ---" << endl;
                    cout << "1. Open New Account" << endl;
                    cout << "2. Close Account" << endl;
                    cout << "3. Search Account" << endl;
                    cout << "4. Display Account Details" << endl;
                    cout << "5. Back to Main Menu" << endl;
                    cout << "Enter choice: ";
                    cin >> accChoice;

                    if (accChoice == 1) {
                        string name, cnic, type;
                        double balance;

                        cout << "Enter Account Holder Name: ";
                        cin.ignore();
                        getline(cin, name);
                        cout << "Enter CNIC (13 digits): ";
                        cin >> cnic;
                        cout << "Enter Initial Balance: ";
                        cin >> balance;
                        cout << "Enter Account Type (Savings/Current/Business): ";
                        cin >> type;

                        openAccount(name, cnic, balance, type);
                    }
                    else if (accChoice == 2) {
                        string accNum;
                        cout << "Enter Account Number: ";
                        cin >> accNum;
                        closeAccount(accNum);
                    }
                    else if (accChoice == 3 || accChoice == 4) {
                        string accNum;
                        cout << "Enter Account Number: ";
                        cin >> accNum;
                        displayAccountDetails(accNum);
                    }
                } while (accChoice != 5);
                break;
            }

            case 2: {
                // Transaction Processing Menu
                int transChoice;
                do {
                    cout << "\n--- TRANSACTION PROCESSING ---" << endl;
                    cout << "1. Deposit Money" << endl;
                    cout << "2. Withdraw Money" << endl;
                    cout << "3. Transfer Money" << endl;
                    cout << "4. Pay Bill" << endl;
                    cout << "5. Display All Transactions" << endl;
                    cout << "6. Sort Transactions by Amount" << endl;
                    cout << "7. Back to Main Menu" << endl;
                    cout << "Enter choice: ";
                    cin >> transChoice;

                    if (transChoice == 1) {
                        string accNum;
                        double amount;
                        cout << "Enter Account Number: ";
                        cin >> accNum;
                        cout << "Enter Amount to Deposit: ";
                        cin >> amount;
                        depositMoney(accNum, amount);
                    }
                    else if (transChoice == 2) {
                        string accNum;
                        double amount;
                        cout << "Enter Account Number: ";
                        cin >> accNum;
                        cout << "Enter Amount to Withdraw: ";
                        cin >> amount;
                        withdrawMoney(accNum, amount);
                    }
                    else if (transChoice == 3) {
                        string fromAcc, toAcc;
                        double amount;
                        cout << "Enter From Account: ";
                        cin >> fromAcc;
                        cout << "Enter To Account: ";
                        cin >> toAcc;
                        cout << "Enter Amount: ";
                        cin >> amount;
                        transferMoney(fromAcc, toAcc, amount);
                    }
                    else if (transChoice == 4) {
                        string accNum, billType;
                        double amount;
                        cout << "Enter Account Number: ";
                        cin >> accNum;
                        cout << "Enter Bill Amount: ";
                        cin >> amount;
                        cout << "Enter Bill Type (Electricity/Gas/Water/Internet): ";
                        cin >> billType;
                        payBill(accNum, amount, billType);
                    }
                    else if (transChoice == 5) {
                        transactionProcessor->displayTransactions();
                    }
                    else if (transChoice == 6) {
                        transactionProcessor->sortTransactionsByAmount();
                    }
                } while (transChoice != 7);
                break;
            }

            case 3: {
                // Customer Service Queue Menu
                int queueChoice;
                do {
                    cout << "\n--- CUSTOMER SERVICE QUEUE ---" << endl;
                    cout << "1. Add Customer to Queue" << endl;
                    cout << "2. Serve Next Customer" << endl;
                    cout << "3. Display Queue" << endl;
                    cout << "4. Generate Queue Report" << endl;
                    cout << "5. Back to Main Menu" << endl;
                    cout << "Enter choice: ";
                    cin >> queueChoice;

                    if (queueChoice == 1) {
                        string name, requestType;
                        int priority, serviceTime;

                        cout << "Enter Customer Name: ";
                        cin.ignore();
                        getline(cin, name);
                        cout << "Enter Request Type (Account Opening/Loan/Card/General): ";
                        cin >> requestType;
                        cout << "Enter Priority (1=Highest, 5=Lowest): ";
                        cin >> priority;
                        cout << "Enter Estimated Service Time (minutes): ";
                        cin >> serviceTime;

                        addCustomerToQueue(name, requestType, priority, serviceTime);
                    }
                    else if (queueChoice == 2) {
                        serveCustomer();
                    }
                    else if (queueChoice == 3) {
                        displayServiceQueue();
                    }
                    else if (queueChoice == 4) {
                        serviceQueue.generateQueueReport();
                    }
                } while (queueChoice != 5);
                break;
            }

            case 4: {
                // ATM Network Management Menu
                int atmChoice;
                do {
                    cout << "\n--- ATM NETWORK MANAGEMENT ---" << endl;
                    cout << "1. Add ATM to Network" << endl;
                    cout << "2. Connect Two ATMs" << endl;
                    cout << "3. Find Shortest Cash Van Route" << endl;
                    cout << "4. Display ATM Network" << endl;
                    cout << "5. Display Network Connections" << endl;
                    cout << "6. Find Nearest ATM" << endl;
                    cout << "7. Back to Main Menu" << endl;
                    cout << "Enter choice: ";
                    cin >> atmChoice;

                    if (atmChoice == 1) {
                        string atmID, location;
                        double capacity;
                        bool operational;

                        cout << "Enter ATM ID: ";
                        cin >> atmID;
                        cout << "Enter Location: ";
                        cin.ignore();
                        getline(cin, location);
                        cout << "Enter Cash Capacity: ";
                        cin >> capacity;

                        ATM newATM(atmID, location, capacity);
                        addATMToNetwork(newATM);
                    }
                    else if (atmChoice == 2) {
                        string atmID1, atmID2;
                        int distance;

                        cout << "Enter First ATM ID: ";
                        cin >> atmID1;
                        cout << "Enter Second ATM ID: ";
                        cin >> atmID2;
                        cout << "Enter Distance (km): ";
                        cin >> distance;

                        connectATMsInNetwork(atmID1, atmID2, distance);
                    }
                    else if (atmChoice == 3) {
                        atmNetwork.sortATMsByCash();
                        cout << "\nATMs sorted by cash capacity!\n";
                        atmNetwork.displayNetwork();
                    }
                    else if (atmChoice == 4) {
                        displayATMNetwork();
                    }
                    else if (atmChoice == 5) {
                        atmNetwork.displayConnections();
                    }
                    else if (atmChoice == 6) {
                        string currentATM;
                        cout << "Enter Current ATM ID: ";
                        cin >> currentATM;

                        ATM nearest = atmNetwork.findNearestATM(currentATM);
                        if (nearest.getATMID() != "") {
                            cout << "\nNearest ATM Found:" << endl;
                            nearest.displayATMInfo();
                        } else {
                            cout << "No nearby ATM found!" << endl;
                        }
                    }
                } while (atmChoice != 7);
                break;
            }

            case 5: {
                // Reports Menu
                int reportChoice;
                do {
                    cout << "\n--- REPORTS & ANALYTICS ---" << endl;
                    cout << "1. Generate Daily Report" << endl;
                    cout << "2. Generate Monthly Report" << endl;
                    cout << "3. Generate Yearly Report" << endl;
                    cout << "4. Back to Main Menu" << endl;
                    cout << "Enter choice: ";
                    cin >> reportChoice;

                    if (reportChoice == 1) {
                        generateDailyReport();
                    }
                    else if (reportChoice == 2) {
                        generateMonthlyReport();
                    }
                    else if (reportChoice == 3) {
                        generateYearlyReport();
                    }
                } while (reportChoice != 4);
                break;
            }

            case 6: {
                // Bank Statistics
                displayBankStatistics();
                break;
            }

            case 7: {
                // System Time Settings
                int timeChoice;
                do {
                    cout << "\n--- SYSTEM TIME SETTINGS ---" << endl;
                    cout << "1. View Current System Time" << endl;
                    cout << "2. Set System Time" << endl;
                    cout << "3. Update System Time" << endl;
                    cout << "4. Back to Main Menu" << endl;
                    cout << "Enter choice: ";
                    cin >> timeChoice;

                    if (timeChoice == 1) {
                        cout << "\nCurrent System Time: ";
                        currentSystemTime.display();
                    }
                    else if (timeChoice == 2) {
                        DateTime newTime;
                        cout << "Enter new system time:" << endl;
                        newTime.input();
                        setSystemTime(newTime);
                    }
                    else if (timeChoice == 3) {
                        int hours, minutes;
                        cout << "Enter hours to add: ";
                        cin >> hours;
                        cout << "Enter minutes to add: ";
                        cin >> minutes;
                       // updateSystemTime(hours, minutes);
                    }
                } while (timeChoice != 4);
                break;
            }

            case 8: {
                cout << "\n╔════════════════════════════════════════════════╗" << endl;
                cout << "║   Thank you for using MCB Bank System!        ║" << endl;
                cout << "║   Have a great day!                            ║" << endl;
                cout << "╚════════════════════════════════════════════════╝\n" << endl;
                break;
            }

            default:
                cout << "\n✗ Invalid choice! Please try again." << endl;
        }

    } while (mainChoice != 8);
}

