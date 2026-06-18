//
// Created by AZKA on 12/15/2025.
//

#include "helper.h"

#include "Transaction.h"
#include "BankingUtilities.h"
#include "BankAccount.h"
#include <iostream>
using namespace std;
#include <string>
#include "../all_structures.h"
#include "DateTime.h"



TreeNodeB<BankAccount*>* findAccountByNumber(BinarySearchTree<BankAccount*>* database, string accountNumber)
{
    if (database == nullptr) return nullptr;

    TreeNodeB<BankAccount*>* current = database->getRoot();
    while (current != nullptr)
    {
        BankAccount* acc = current->getData1();
        if (acc->getAccountNumber() == accountNumber)
            return current;
        else if (accountNumber < acc->getAccountNumber())
            current = current->getLeftChild();
        else
            current = current->getRightChild();
    }
    return nullptr;
}