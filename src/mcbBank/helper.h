//
// Created by AZKA on 12/15/2025.
//

#ifndef HELPER_H
#define HELPER_H


#include "Transaction.h"
#include "BankingUtilities.h"
#include "BankAccount.h"
#include <iostream>
using namespace std;
#include <string>
#include "../all_structures.h"
#include "DateTime.h"


// BankingUtilities.h
TreeNodeB<BankAccount*>* findAccountByNumber(BinarySearchTree<BankAccount*>* database, string accountNumber);


#endif //HELPER_H
