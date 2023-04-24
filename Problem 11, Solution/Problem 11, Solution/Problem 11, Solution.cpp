#include <iostream>
#include <string>

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

struct sDate 
{
    short Day;
    short Month;
    short Year;
};

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

sDate GetDaysFromDaysOrderInYear(short DaysOrderInYear, short Year)
{
    sDate Date;
    Date.Year = Year;
    Date.Month = 1;

    while(true)
    {
        short MonthDays = DaysInMonth(Year, Date.Month);
        if (DaysOrderInYear - MonthDays > 0)
            DaysOrderInYear -= MonthDays;

        else
            break;
        Date.Month++;
    }
    Date.Day = DaysOrderInYear;

    return Date;
}

int main()
{
    short Day = ReadNumInRange(1, 31, "Plase enter a day : ");

    short Month = ReadNumInRange(1, 12, "\nPlase enter a Month : ");

    short Year = ReadNumInRange(1, 5000, "\nPlase enter a Year : ");

    short DaysOrderInYear = CountDaysFromDay1InYear(Day, Month, Year);

    cout << "\nNumber of days from the beginning of the year are : " << DaysOrderInYear << endl;

    sDate Date = GetDaysFromDaysOrderInYear(DaysOrderInYear, Year);

    cout << "\nDate for [" << DaysOrderInYear << "] is: " << Date.Day << "/" << Date.Month << "/" << Date.Year << "\n";

    system("pause>0");
}