#include <iostream>

using namespace std;

short ReadNumInRange(string msg, short From, short To)
{
    short Num;
    do {
        cout << msg;
        cin >> Num;
    } while (Num < From || Num > To);
    return Num;
}

struct sDate
{
    short Day;
    short Month;
    short Year;
};

sDate ReadFullDate()
{
    sDate Date;
    Date.Day = ReadNumInRange("Please enter a day : ", 1, 31);
    Date.Month = ReadNumInRange("Please enter a Month : ", 1, 12);
    Date.Year = ReadNumInRange("Please enter a Year : ", 1, 5000);
    return Date;
}

bool isLeapYear(short Year)
{
    return (Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0;
}

short DaysInMonth(short Year, short Month)
{
    short Arr[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    return Month == 2 ? (isLeapYear(Year) ? 29 : 28) : Arr[Month];
}

bool IsLastDay(sDate Date)
{
    return Date.Day == DaysInMonth(Date.Year, Date.Month);
}

bool IsLastMonth(sDate Date)
{
    return Date.Month == 12;
}

int main()
{
    sDate Date = ReadFullDate();
    cout << "\n";

    string LastDay = IsLastDay(Date) ? "\nYes, it is the last day in month\n" : "\nNo, it is not the last day in month\n";
    cout << LastDay;
    
    string LastMonth = IsLastMonth(Date) ? "\nYes, it is the last month in year\n" : "\nNo, it is not the last month in year\n";
    cout << LastMonth;

    system("pause>0");
}