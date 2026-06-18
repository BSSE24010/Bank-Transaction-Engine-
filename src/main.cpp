#include <iostream>
#include <string>
#include "mcbBank/helper.h"
#include "mcbBank/MCBBankEngine.h"
#include "mcbBank/TransactionProcessor.h"
#include "mcbBank/ATMNetwork.h"
#include "mcbBank/ATM.h"
#include "mcbBank/CustomerServiceQueue.h"
#include "mcbBank/CustomerRequest.h"
#include "mcbBank/Transaction.h"
#include "mcbBank/BankingUtilities.h"
#include "mcbBank/BankAccount.h"
#include "mcbBank/DateTime.h"

using namespace std;

int main() {
    MCBBankEngine m;
    m.run();
    return 0;
}