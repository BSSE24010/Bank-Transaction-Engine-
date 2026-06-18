cmake_minimum_required(VERSION 3.29)
project(src)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(src
    all_structures.h
    ATM.cpp
    ATM.h
    ATMNetwork.cpp
    ATMNetwork.h
    BankAccount.cpp
    BankAccount.h
    BankingUtilities.cpp
    BankingUtilities.h
    CustomerRequest.cpp
    CustomerRequest.h
    CustomerServiceQueue.cpp
    CustomerServiceQueue.h
    main.cpp
    MCBBankEngine.cpp
    MCBBankEngine.h
    Transaction.cpp
    Transaction.h
    TransactionProcessor.cpp
    TransactionProcessor.h
        DateTime.cpp
        DateTime.h)
