#pragma warning(disable : 4996)

#include <iostream>
#include <ctime>

using namespace std;

struct sDate {
    short Year;
    short Month;
    short Day;
};

sDate SystemLocalTime()
{
    time_t t = time(0);

    tm* LocDate = localtime(&t);
    sDate Date;
    Date.Year = LocDate->tm_year + 1900;
    Date.Month = LocDate->tm_mon + 1;
    Date.Day = LocDate->tm_mday;

    Date.Year = 2022;
    Date.Month = 9;
    Date.Day = 23;

    return Date;
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
    return NumberOfDayInWeek(Date.Year, Date.Month, Date.Day);
}

string DayName(short Day)
{
    string Days[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

    return Days[Day];
}

bool IsEndOfWeek(short Day)
{
    return Day == 0;
}

bool IsWeekend(short Day)
{
    return Day == 0 || Day == 6;
}

bool IsBusinessDay(short Day)
{
    return !IsWeekend(Day);
}

bool IsDate1BeforeDate2(sDate Date1, sDate Date2)
{
    return Date1.Year < Date2.Year ? true : (Date1.Year > Date2.Year ? false :
        (Date1.Month < Date2.Month ? true : (Date1.Month > Date2.Month ? false :
            (Date1.Day < Date2.Day ? true : false))));
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

short DaysInMonth(sDate Date)
{
    return DaysInMonth(Date.Year, Date.Month);
}

bool IsLastDayInMonth(sDate Date)
{
    return Date.Day == DaysInMonth(Date.Year, Date.Month);
}

bool IsLastMonth(sDate Date)
{
    return Date.Month == 12;
}

sDate IncreseDateByOneDay(sDate Date)
{
    if (IsLastDayInMonth(Date))
    {
        if (IsLastMonth(Date))
        {
            Date.Year++;
            Date.Month = 1;
            Date.Day = 1;
        }
        else
        {
            Date.Month++;
            Date.Day = 1;
        }
    }
    else
        Date.Day++;

    return Date;
}

short DaysBetweenDate1Date2(sDate Date1, sDate Date2, bool IncludEndDay = false)
{
    short NumberOfDays = 0;

    while (IsDate1BeforeDate2(Date1, Date2))
    {
        NumberOfDays++;
        Date1 = IncreseDateByOneDay(Date1);
    }
    return IncludEndDay ? ++NumberOfDays : NumberOfDays;
}

short DaysUntilEndOfWeek(sDate Date)
{
    return 6 - NumberOfDayInWeek(Date);
}

short DaysUntilEndOfMonth(sDate Date)
{
    sDate DateEndOfMonth;
    DateEndOfMonth.Day = DaysInMonth(Date);
    DateEndOfMonth.Month = Date.Month;
    DateEndOfMonth.Year = Date.Year;
    return DaysBetweenDate1Date2(Date, DateEndOfMonth, true);
}

short DaysUntilEndOfYear(sDate Date)
{
    sDate DateEndOfYear;
    DateEndOfYear.Day = 31;
    DateEndOfYear.Month = 12;
    DateEndOfYear.Year = Date.Year;
    return DaysBetweenDate1Date2(Date, DateEndOfYear);
}

int main()
{
    sDate Date = SystemLocalTime();

    cout << "Today is : " << DayName(NumberOfDayInWeek(Date)) << " , " << Date.Day << "/" << Date.Month << "/" << Date.Year << "\n";

    cout << "\nIs it end of week?\n";
    IsEndOfWeek(NumberOfDayInWeek(Date)) ?
        cout << "Yes, It is week end\n\n"
        :
        cout << "No, Not end of week?\n";

    cout << "\nIs it weekend?\n";
    IsWeekend(NumberOfDayInWeek(Date)) ?
        cout << "Yes today is " << DayName(NumberOfDayInWeek(Date)) << ", It is a weekend\n\n"
        :
        cout << "No today is " << DayName(NumberOfDayInWeek(Date)) << ", Not a weekend\n";

    cout << "\nIs it business Day?\n";
    IsBusinessDay(NumberOfDayInWeek(Date)) ?
        cout << "Yes, It is a business Day\n\n"
        :
        cout << "No, Not a business Day\n\n";

    cout << "Days until end of week : " << DaysUntilEndOfWeek(Date) << " Day(s)\n";
    cout << "Days until end of Month : " << DaysUntilEndOfMonth(Date) << " Day(s)\n";
    cout << "Days until end of year : " << DaysUntilEndOfYear(Date) << " Day(s)\n";

    system("pause>0");
}