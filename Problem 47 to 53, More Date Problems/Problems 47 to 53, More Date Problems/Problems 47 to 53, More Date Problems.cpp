#pragma warning(disable : 4996)

#include <iostream>
#include <ctime>

using namespace std;

struct sDate {
    short Day;
    short Month;
    short Year;
};

short ReadNumInRange(string Message, short From, short To)
{
    short Number;
    do {
        cout << Message;
        cin >> Number;
    } while (Number < From || Number > To);
    return Number;
}

short NumberOfDayInWeek(short Year, short Month, short Day)
{
    short a = (14 - Month) / 12;
    short y = Year - a;
    short m = Month + 12 * a - 2;

    short R = (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12));

    return R % 7;
}

short NumberOfDayInWeek(sDate Date)
{
    short a = (14 - Date.Month) / 12;
    short y = Date.Year - a;
    short m = Date.Month + 12 * a - 2;

    short R = (Date.Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12));

    return R % 7;
}

string DayName(int Day)
{
    string Days[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

    return Days[Day];
}

sDate ReadLocalTime()
{
    time_t t = time(0);
    tm* dt = localtime(&t);

    sDate Date;
    Date.Day = dt->tm_mday;
    Date.Month = dt->tm_mon+1;
    Date.Year = dt->tm_year+1900;
        
    Date.Day = 27;
    Date.Month = 9;
    Date.Year = 2022;

    return Date;
}

bool IsWeekend(short DayInWeek)
{
    return DayInWeek == 5 || DayInWeek == 6;
}

bool IsEndOfWeek(short DayInWeek)
{
    return DayInWeek == 6;
}

bool IsBusinessDay(short DayInWeek)
{
    return !IsWeekend(DayInWeek);
}

short DaysUntilEndOfWeek(short Day)
{
    return 6 - Day;
}

bool IsLeapYear(int Year)
{
    return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
}

short DaysInMonth(short Year, short Month)
{
    short Arr[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    return Month == 2 ? (IsLeapYear(Year) ? 29 : 28) : Arr[Month];
}

short DaysUntilEndOfMonth(sDate Date)
{
    return DaysInMonth(Date.Year, Date.Month) - Date.Day + 1;
}

short CountDaysFromDay1InYear(sDate Date)
{
    short NumOfDays = 0;
    for (int i = 1; i < Date.Month; i++)
        NumOfDays += DaysInMonth(Date.Year, i);

    NumOfDays += Date.Day;

    return NumOfDays;
}

int DaysInYear(int Year)
{
    return IsLeapYear(Year) ? 366 : 365;
}

short DaysUntilEndOfYear(sDate Date)
{
    
    return  DaysInYear(Date.Year) - CountDaysFromDay1InYear(Date) + 1;
}

int main()
{      
    sDate Date = ReadLocalTime();

    cout << "Today is : " << DayName(NumberOfDayInWeek(Date)) << " , " << Date.Day << "/" << Date.Month << "/" << Date.Year << "\n";

    cout << "\nIs it end of week?\n";
    IsEndOfWeek(NumberOfDayInWeek(Date)) ? 
        cout << "Yes, It is week end\n\n" 
        : 
        cout << "No, Not end of week?\n";

    cout << "\nIs it weekend?\n";
    IsWeekend(NumberOfDayInWeek(Date)) ? 
        cout << "Yes today is "<< DayName(NumberOfDayInWeek(Date)) <<", It is a weekend\n\n" 
        : 
        cout << "No today is " << DayName(NumberOfDayInWeek(Date)) << ", Not a weekend\n";

    cout << "\nIs it Business Day?\n";
    IsBusinessDay(NumberOfDayInWeek(Date)) ? 
        cout << "Yes, It is a business Day\n\n" 
        : 
        cout << "No, Not a business Day\n\n";

    cout << "Days until end of week : " << DaysUntilEndOfWeek(NumberOfDayInWeek(Date)) << " Day(s)\n";
    cout << "Days until end of Month : " << DaysUntilEndOfMonth(Date) << " Day(s)\n";
    cout << "Days until end of year : " << DaysUntilEndOfYear(Date) << " Day(s)\n";

    system("pause>0");
}