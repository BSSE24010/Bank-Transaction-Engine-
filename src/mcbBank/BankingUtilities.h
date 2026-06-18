//
// Created by AZKA on 12/15/2025.
//

#ifndef BANKINGUTILITIES_H
#define BANKINGUTILITIES_H

//#include "BankingUtilities.h"
#include "BankAccount.h"
#include <iostream>
using namespace std;
#include <string>
#include "../all_structures.h"
#include "DateTime.h"
class BankingUtilities {
private:
    static int accountCounter;
    static int transactionCounter;
    static int applicationCounter;
    static int employeeCounter;

public:
    static int getLength(string s)
    {
        int count=0;
        while (s[count] != '\0')
        {
            count++;
        }
        return count;
    }

    static string reverseString(string s)
    {
        int len=getLength(s);
        string rev="";
        for(int i=len-1; i>=0; i--)
        {
            rev=rev+s[i];
        }
        return rev;
    }

    static string intToString(int num)
    {
        string result="";

        if(num==0)
        {
            result= "0";
        }

        while(num>0)
        {
            int digit=num%10;
            char c='0' +digit;
            result=result+c;
            num=num/10;
        }
        string sResult=reverseString(result);
        return sResult;
    }

    static string doubleToString(double num)
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

    static string generateAccountNumber();
    static string generateTransactionID();
    static string generateApplicationID();
    static string generateEmployeeID();
    static bool validateCNIC(string cnic);
    static bool validateAccountNumber(string accountNumber);
    static string dateTimeToString(DateTime dt);
    static double calculateInterest(double principal, double rate, int months);
    static int generateOTP();
    static DateTime getCurrentDateTime();
};

#endif //BANKINGUTILITIES_H
