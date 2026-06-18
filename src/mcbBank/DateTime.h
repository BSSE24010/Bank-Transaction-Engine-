//
// Created by AZKA on 12/15/2025.
//

#ifndef DATETIME_H
#define DATETIME_H

#include <iostream>
using namespace std;

class DateTime {
    int day;
    int month;
    int year;
    int hour;
    int minute;
    int second;


public:
    DateTime() : day(1), month(1), year(2024), hour(0), minute(0), second(0) {}

    DateTime(int d, int m, int y, int h, int min, int s)
        : day(d), month(m), year(y), hour(h), minute(min), second(s) {}

    void setDay(int d) { day = d; }
    void setMonth(int m) { month = m; }
    void setYear(int y) { year = y; }
    void setHour(int h) { hour = h; }
    void setMinute(int min) { minute = min; }
    void setSecond(int s) { second = s; }



    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
    int getHour() const { return hour; }
    int getMinute() const { return minute; }
    int getSecond() const { return second; }


    void input() {
        cout << "Enter day: ";
        cin >> day;
        cout << "Enter month: ";
        cin >> month;
        cout << "Enter year: ";
        cin >> year;
        cout << "Enter hour: ";
        cin >> hour;
        cout << "Enter minute: ";
        cin >> minute;
        cout << "Enter second: ";
        cin >> second;
    }

    void display() {
        cout <<day<< "/" <<month << "/" <<year << "  ";
        cout <<hour<< ":" <<minute << ":" <<second << endl;
    }

};

#endif //DATETIME_H
