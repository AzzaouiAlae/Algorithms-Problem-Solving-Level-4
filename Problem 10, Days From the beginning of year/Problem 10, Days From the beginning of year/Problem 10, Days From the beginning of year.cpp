#include <iostream>

using namespace std;

short ReadNumInRange(short from, short To, string msg)
{
    short Num;
    do {
        cout << msg;
        cin >> Num;
    } while (from > Num || To < Num);
    return Num;
}

bool isLeapYear(short Year)
{
    return (Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0;
}

short DaysInMonth(short Year, short Month)
{
    short Arr[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    return isLeapYear(Year) ? (Month == 2 ? 29 : 28) : Arr[Month];
}

short CountDaysFromDay1InYear(short Day, short Month, short Year)
{
    short NumOfDays = 0;
    for (int i = 1; i < Month; i++)
        NumOfDays += DaysInMonth(Year, i);

    NumOfDays += Day;

    return NumOfDays;
}

int main()
{
    short Day = ReadNumInRange(1, 31, "Plase enter a day : ");

    short Month = ReadNumInRange(1, 12, "Plase enter a Month : ");

    short Year = ReadNumInRange(1, 5000, "Plase enter a Year : ");

    cout << "Number of days from the beginning of the year are : " << CountDaysFromDay1InYear(Day, Month, Year) << endl;
}
